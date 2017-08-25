
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
void prn (int x)
{
	if (x)
		write(STDOUT_FILENO,"YES\n",sizeof("YES\n")-1);
	else
		write(STDOUT_FILENO,"NO\n",sizeof("NO\n")-1);
}

char buf1,buf2;

int main(int argc, char *argv[])
{
	int fd2,fd1,siz;
	struct stat check_file, check_dir, check_sym ;
	char dir[]="Assignment", oldpath[]="Assignment/Answer.txt", newpath[]="Answer.txt";
	symlink(oldpath,newpath);

	write(STDOUT_FILENO,"Checking whether the directory has been created:",sizeof("Checking whether the directory has been created:")-1);
	if(!(stat(dir,&check_dir)) && S_ISDIR(check_dir.st_mode))
		prn(1);
	else
		prn(0);

	write(STDOUT_FILENO,"Checking whether the file has been created:",sizeof("Checking whether the file has been created:")-1);
	if(!(stat(oldpath,&check_file)) && S_ISREG(check_file.st_mode))
		prn(1);
	else
		prn(0);

	write(STDOUT_FILENO,"Checking whether the symlink has been created:",sizeof("Checking whether the symlink has been created:")-1);
	if(!(lstat(newpath,&check_sym)) & S_ISLNK(check_sym.st_mode))
		prn(1);
	else
		prn(0);

	fd1 = open("Assignment/Answer.txt", O_RDONLY | O_LARGEFILE);
	fd2 = open(argv[1], O_RDONLY | O_LARGEFILE);

	int flag = 1;

	siz = lseek(fd1, (off_t) 0, SEEK_END);
	for(int i = siz - 1; i >= 1; i--)
	{
		lseek(fd1, (off_t) i, SEEK_SET);
		lseek(fd2, (off_t) siz-i, SEEK_SET);
		int n = read(fd1, &buf1, 1);
		n = read(fd2, &buf2, 1);


		if(buf1 >= 'a' && buf1 <='z')
			buf1 += ('A'-'a');
		else if(buf1 >='A' && buf1 <= 'Z')
			buf1 += ('a'-'A');
		printf("%c%c\n ", buf1,buf2);
		if(buf1!=buf2)
			flag = 0;
	}

	write(STDOUT_FILENO,"Checking whether file contents have been reversed and case-inverted:",sizeof("Checking whether file contents have been reversed and case-inverted:")-1);
	if(flag)
		prn(1);
	else
		prn(0);

	write(STDOUT_FILENO,"User has read permission on file:",sizeof("User has read permission on file:")-1);
	if(check_file.st_mode & S_IRUSR)
		prn(1);
	else
		prn(0);
	write(STDOUT_FILENO,"User has write permission on file:",sizeof("User has write permission on file:")-1);
	if(check_file.st_mode & S_IWUSR)
		prn(1);
	else
		prn(0);
	write(STDOUT_FILENO,"User has execute permission on file:",sizeof("User has execute permission on file:")-1);
	if(check_file.st_mode & S_IXUSR)
		prn(1);
	else
		prn(0);

	write(STDOUT_FILENO,"Group has read permission on file:",sizeof("Group has read permission on file:")-1);
	if(check_file.st_mode & S_IRGRP)
		prn(1);
	else
		prn(0);
	write(STDOUT_FILENO,"Group has write permission on file:",sizeof("Group has write permission on file:")-1);
	if(check_file.st_mode & S_IWGRP)
		prn(1);
	else
		prn(0);
	write(STDOUT_FILENO,"Group has execute permission on file:",sizeof("Group has execute permission on file:")-1);
	if(check_file.st_mode & S_IXGRP)
		prn(1);
	else
		prn(0);

	write(STDOUT_FILENO,"Others has read permission on file:",sizeof("Others has read permission on file:")-1);
	if(check_file.st_mode & S_IROTH)
		prn(1);
	else
		prn(0);
	write(STDOUT_FILENO,"Others has write permission on file:",sizeof("Others has write permission on file:")-1);
	if(check_file.st_mode & S_IWOTH)
		prn(1);
	else
		prn(0);
	write(STDOUT_FILENO,"Others has execute permission on file:",sizeof("Others has execute permission on file:")-1);
	if(check_file.st_mode & S_IXOTH)
		prn(1);
	else
		prn(0);

	exit(0);
}
