/*201564134
	kilimanjaro2
*/
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#ifndef O_LARGEFILE
#define O_LARGEFILE 0
#endif

char buf;

int main(int argc, char *argv[])
{
	int siz,fd1;

	if(argc != 2)
	{
		write(STDOUT_FILENO,"Usage: ./a.out [input filename] \n",sizeof("Usage: ./a.out [input filename] \n" )-1);
		exit(0);
	}

	fd1 = open(argv[1], O_RDONLY | O_LARGEFILE);
	if(fd1 < 0)
	{
		write(STDOUT_FILENO,"Failed to open file. Enter valid file.\n",sizeof("Failed to open file. Enter valid file.\n" )-1);
		exit(1);
	}

	int flag_createdir = mkdir("Assignment",(mode_t)0700);

	int fd2 = open("Assignment/Answer.txt", O_WRONLY | O_CREAT,  S_IRWXU);
	if (fd2 < 0)
	{
		write(STDOUT_FILENO,"Failed to open output file.\n",sizeof("Failed to open output file.\n")-1 );
		exit(0);
	}

	siz = lseek(fd1, (off_t) 0, SEEK_END);
	printf("%d\n",siz);
	for(int i = siz - 1; i >= 1; i--)
	{
		lseek(fd1, (off_t) i, SEEK_SET);

		int n = read(fd1, &buf, 1);
		//printf("%c",buf );
		if (n < 0)
		{
			write(STDOUT_FILENO,"Read interrupted.\n",sizeof("Read interrupted.\n")-1);
			exit(0);
		}

		if(buf >= 'a' && buf <='z')
			buf += ('A'-'a');
		else if(buf >='A' && buf <= 'Z')
			buf += ('a'-'A');
		n = write(fd2, &buf, 1);
		// printf("%d\n",n );
		if (n < 0)
		{
			write(STDOUT_FILENO,"Write interrupted.\n",sizeof("Write interrupted.\n")-1 );
			// printf("%d",siz);
			exit(0);
		}

	}
	exit(0);
}
