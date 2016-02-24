#include "./myDir.h"

/*
void printMode(struct stat fileInfo);
void usrOwner(struct stat fileInfo);
void grpOwner(struct stat fileInfo);
void printTime(struct stat fileInfo);

int changeDir(int argc, char **argv)
{
	DIR *dp;
	struct dirent *dirp;
    struct stat fileDesc;


	if(argc != 2)
	{
	    perror("Not enough arguments\n");
	    exit(-1);
	    
	}// end if
	
	if( (dp = opendir(argv[1])) == NULL)
	    perror("Could not open directory\n");
	
	while( (dirp = readdir(dp)) != NULL){
		    
		    stat(dirp->d_name, &fileDesc);
		    
		    printMode(fileDesc);    // print permissions
		    usrOwner(fileDesc);
		    grpOwner(fileDesc);
		    printf(" %-7ld  %-7s ", fileDesc.st_size, "bytes");       // print size
		    printTime(fileDesc);
		    printf(" %s ", dirp->d_name);
		    
		    
		    printf("\n");
		    
		    
    }
	return 0;
}

void printMode(struct stat fileInfo)
{
   	printf( (S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
    printf( (fileInfo.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileInfo.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileInfo.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileInfo.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileInfo.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileInfo.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileInfo.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileInfo.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileInfo.st_mode & S_IXOTH) ? "x" : "-");
	printf("  ");
	
}

void usrOwner(struct stat fileInfo)
{
	struct passwd *usr;
	usr = getpwuid(fileInfo.st_uid);
	printf("%s", usr->pw_name);
}

void grpOwner(struct stat fileInfo)
{
	struct group *grp;
	grp = getgrgid(fileInfo.st_gid);
	printf("  %s  ", grp->gr_name);
}

void printTime(struct stat fileInfo)
{
	time_t t = fileInfo.st_mtime;
    char tmp[100];
    struct tm lt;
    localtime_r(&t, &lt);   // allows thread reentrance 
	strftime(tmp, sizeof(tmp), "%b %d %H:%M ", &lt);
	printf("%-s", tmp);
	
}*/

void myDir(char** argv)
{
	char originalPWD[100];
	
	if(chdir(argv[1]) == 0){
	getcwd(originalPWD, sizeof(originalPWD));
	printf("changed into Directory: %s", originalPWD);
}
	else
	printf("change not unsuccessful");

  memset(&originalPWD[0], 0, sizeof(originalPWD));
}

