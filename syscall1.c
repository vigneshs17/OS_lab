#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>

void sighandler(int);
int main() {
	int fd = open("a.txt", O_RDWR);
	
	//execl()
//	int ret=execl("/bin/ls", "ls", "-1", (char *)0);
//	printf("%d",ret);


	//fork()
//	fork();
	printf("This is the fork command which creates a new child process that runs concurrently.\n");
	
	//wait()
	int status;
	int cpid=wait(&status);
	printf("The ID of the terminated child process is %d",cpid);
	
	//getuid()
	printf("The real user ID of the calling process is %d\n", getuid());

	//geteuid()
	printf("The effective user ID of the calling process is %d\n", geteuid());

	//getgid()
	printf("The real group ID of the calling process is %d\n", getgid());

	//getegid()
	printf("The effective group ID of the calling process is %d\n", getegid());

	//getpid()
	printf("The process ID of the calling process is %d\n", getpid());

	//getppid()
	printf("The process ID of the parent of the calling process is %d\n", getppid());

	//alarm()
        for(int i=0;i<5;i++) {
                int al=alarm(i);
                printf("%d\n", al);
        }

	//chdir()
	chdir("/home/student/181co258");



	//signal()
	signal(SIGINT, sighandler);

	while(1) {
		printf("infinite loop\n");
	
	}

	//kill
	kill(pid(), 2);
	
	//exit()
	exit(0);

	printf("fdsjk");

	return 0;
}

void sighandler(int signum) {
	printf("Caught signal %d, exiting...\n", signum);
	exit(1);
}
