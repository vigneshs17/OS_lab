#include<stdio.h>

int main() {
	int n, sum=0, totalWaiting=0, totalTurnAround=0, cpuIdleTime=0;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	int arr[n], burst[n];
	printf("Enter the arrival time of each process:\n");
	for(int i=0;i<n;i++) 
		scanf("%d", &arr[i]);
	printf("Enter the burst time of each process:\n");
	for(int i=0;i<n;i++)
		scanf("%d", &burst[i]);

	int service_time[n], turnAround[n], waiting[n], completion[n];
	service_time[0]=0;
	waiting[0]=0;
	//waiting time
	for(int i=1;i<n;i++) {
		service_time[i]=service_time[i-1]+burst[i-1];
		waiting[i]=service_time[i] - arr[i];
		totalWaiting+=waiting[i];
		if(waiting[i]<0)
			waiting[i]=0;
	}

	//turnAround time
	for(int i=0;i<n;i++) {
		turnAround[i]=waiting[i]+burst[i];
		completion[i]=turnAround[i]+arr[i];
		totalTurnAround+=turnAround[i];
		
	}

	//cpu idle time
	for(int i=0;i<n-1;i++) {
		if(completion[i]<arr[i+1])
			cpuIdleTime+=(arr[i+1]-completion[i]);
	}

	printf("Process\tArrival time\tBurst time\tWaiting time\tTurnaround time\tCompletion time\n");
	for(int i=0;i<n;i++) {
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, arr[i], burst[i], waiting[i], turnAround[i], completion[i]);
	}

	printf("Number of context switches: %d\n", n-1);
	printf("CPU idle time: %d\n", cpuIdleTime);
	printf("Average waiting time: %f\n", (float)totalWaiting/(float)n);
	printf("Average turn around time: %f\n", (float)totalTurnAround/(float)n);
	return 0;
}
	
	
