#include<stdio.h>


void swap(int *a, int *b) {
	int temp=*a;
	*a=*b;
	*b=temp;
}

int main() {
	int n, cpuIdleTime=0, totalWaiting=0, totalTurnAround=0;
	printf("Enter the number of processes: ");
	scanf("%d", &n);

	int process[n], arr[n], burst[n], waiting[n], turnAround[n], completion[n];

	printf("Enter the process ID:\n");
	for(int i=0;i<n;i++)
		scanf("%d", &process[i]);

	printf("Enter the arrival time of each process:\n");
	for(int i=0;i<n;i++) 
		scanf("%d", &arr[i]);

	printf("Enter the burst time for each proccess:\n");
	for(int i=0;i<n;i++)
		scanf("%d", &burst[i]);

	//sorting the processes according to their arrival time
	for(int i=0;i<n-1;i++) {
		for(int j=0;j<n-i-1;j++) {
			if(arr[j]>arr[j+1]) {
				swap(&process[j], &process[j+1]);
				swap(&arr[j], &arr[j+1]);
				swap(&burst[j], &burst[j+1]);
			}
		}
	}

	//waiting time
	waiting[0]=0;
	for(int i=1;i<n;i++) {
		waiting[i]=0;
		for(int j=0;j<i;j++) 
			waiting[i]+=burst[j];
			
		totalWaiting+=waiting[i];
	}

	//turn around time
	for(int i=0;i<n;i++) {
		turnAround[i] = arr[i]+burst[i];
		completion[i]=turnAround[i]+waiting[i];
		totalTurnAround+=turnAround[i];
	}

	//cpu idle time
	for(int i=0;i<n-1;i++) {
		if(completion[i]<arr[i+1])
			cpuIdleTime+=(arr[i+1]-completion[i]);
	}

	printf("Process\tArrival time\tBurst time\tWaiting time\tTurn around time\n");
	for(int i=0;i<n;i++) {
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", process[i], arr[i], burst[i], waiting[i], turnAround[i]);
	}

	printf("Number of context switches: %d\n", n-1);
	printf("CPU idle time: %d\n", cpuIdleTime);
	printf("Average waiting time: %f\n", (float)totalWaiting/(float)n);
	printf("Average turn around time: %f\n", (float)totalTurnAround/(float)n);

	return 0;
}

