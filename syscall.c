#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

extern int errno;
int main() {
	//creat()
	int fd;
       	fd = creat("a.txt", S_IRWXU | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd!=-1) {
		printf("fd = %d\nFile created successfully!\n", fd);
	}
	else {
		printf("File was not created.\n");
	}

	//open()
	fd = open("a.txt", O_RDONLY | O_CREAT);
	if(fd==-1) {
		printf("Error number = %d", errno);
	}
	else {
		printf("fd = %d\nFile opened successfully!\n", fd);
	}

	//close()
	if(close(fd)==0) {
		printf("File closed successfully!\n");
	}
	else {
		printf("Error in closing the file.\n");
	}

	//write()
	int sz;
	fd = open("a.txt", O_RDWR);
	sz = write(fd, "Hello world.\n", strlen("Hello world.\n"));

	if(sz>0) {
		printf("called write(%d, \"Hello world.\n\", %ld). It returned %d\n", fd, strlen("Hello world.\n"), sz); 
	}
	else {
		printf("Error in writing to the file.\n");
	}

	//read()
	char *c = (char *)calloc(100, sizeof(char));
	fd = open("a.txt", O_RDONLY);
	sz = read(fd, c, 13);
	printf("called read(% d, c, 10). It returned that %d bytes  were read.\n", fd, sz); 
	c[sz] = '\0';
	printf("The bytes that were read are \n%s\n", c);

	//lseek()
	lseek(fd, 7, SEEK_SET);
	printf("The pointer is offset by 7 bytes.\n");
	
	close(fd);
	fd = open("a.txt", O_RDONLY);
	//dup()
	int fd_dup = dup(fd);
	printf("fd_dup = %d and fd = %d. These file descriptors can be used interchangeably.\n", fd_dup, fd);

	//link()
	link("a.txt", "b.txt");
	printf("old path is a.txt and the new path is b.txt\nBoth names refer to the same file; they have the same permission and ownership.\n");

	//unlink()
	unlink("b.txt");
	printf("b.txt is now unlinked from a.txt.\n");
	
	//access
	fd = access("a.txt", F_OK);
	if(fd==0) {
		printf("The file exists.\n");
	}
	else {
		printf("Error encountered during file access.\n");
	}

	//chmod()
	chmod("a.txt", S_IROTH);
	printf("The access mode of the file has been set to 00004 read by others.\n");

	//chown()
	chown("a.txt", )
	return 0;
}
