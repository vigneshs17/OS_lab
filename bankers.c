#include<stdio.h>

int main() {
	int n, m, count=0, index=0;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("Enter the number of resource types: ");
	scanf("%d", &m);

	int available[m], max[n][m], allocation[n][m], need[n][m], result[n], work[m];

	//available resource types and work vector
	printf("Enter the number of instances of each resource type\n");
	for(int i=0;i<m;i++) {
		scanf("%d", &available[i]);
		work[i]=available[i];
	}

	//allocation matrix
	printf("Enter the values of the allocation matrix\n");
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			scanf("%d", &allocation[i][j]);
		}
	}

	//max matrix
	printf("Enter the values of the max matrix\n");
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			scanf("%d", &max[i][j]);
		}
	}

	int finish[n];
	for(int i=0;i<n;i++) {
		finish[i]=0;
	}

	//need matrix
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			need[i][j]=max[i][j]-allocation[i][j];
		}
	}
	
	
	while(count<n) {
		for(int i=0;i<n;i++) {
			if(finish[i]==0) {
				int flag=0;
				for(int j=0;j<m;j++) {
					if(need[i][j]>work[j]) {
						flag=1;
						break;
					}
				}
	
				if(flag==0) {
					result[index++]=i;
					for(int k=0;k<m;k++) {
						work[k]+=allocation[i][k];
					}
					finish[i]=1;
				}
			}
		}
		count++;
	}

	
	//printing the safe sequence
	if(sizeof(result)/sizeof(int)==n) {
		for(int i=0;i<n-1;i++) {
			printf("P%d-> ", result[i]);
		}
		printf("P%d\n", result[n-1]);
	}	
	return 0;
}


