#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>

int cmd_pk_ls(char *path)
{
    DIR *dir;
    dir = opendir(path);
    if(dir==NULL)
        perror("ITskfjslkdf:");
    struct dirent *directoryPtr;
    directoryPtr = readdir(dir);
    while(directoryPtr!=NULL)
    {
        if(directoryPtr->d_name[0]!='.')
            printf("%s\n",directoryPtr->d_name);
        directoryPtr = readdir(dir);
    }
    closedir(dir);
    return 0;
}
int cmd_pk_ls_a(char *path)
{
    DIR *dir;
    dir = opendir(path);
    if(dir==NULL)
        perror("ITskfjslkdf:");
    struct dirent *directoryPtr;
    directoryPtr = readdir(dir);
    while(directoryPtr!=NULL)
    {
        printf("%s\n",directoryPtr->d_name);
        directoryPtr = readdir(dir);
    }
    closedir(dir);
    return 0;
}
int print_pk_ls_l(char *path,char *fileName)
{
    struct stat file_buff;
    int check = stat(path,&file_buff);
    char permission[11];
    //Accessing whether file or directory
    if(S_ISDIR(file_buff.st_mode))
        permission[0]='d';
    else
        permission[0]='-';
    //Accessing data members of stat struct of file
    if(file_buff.st_mode & S_IRUSR)
        permission[1]='r';
    else
        permission[1]='-';
    if(file_buff.st_mode & S_IWUSR)
        permission[2]='w';
    else
        permission[2]='-';
    if(file_buff.st_mode & S_IXUSR)
       permission[3]='x';
    else
        permission[3]='-';

    if(file_buff.st_mode & S_IRGRP)
      permission[4]='r';
    else
        permission[4]='-';
    if(file_buff.st_mode & S_IWGRP)
      permission[5]='w';
    else
        permission[5]='-';
    if(file_buff.st_mode & S_IXGRP)
      permission[6]='x';
    else
        permission[6]='-';

    if(file_buff.st_mode & S_IROTH)
        permission[7]='r';
    else
        permission[7]='-';
    if(file_buff.st_mode & S_IWOTH)
        permission[8]='w';
    else
        permission[8]='-';
    if(file_buff.st_mode & S_IXOTH)
        permission[9]='x';
    else
        permission[9]='-';

    printf("%s\t %d\t ",permission,file_buff.st_nlink);
    printf("%s\t %s\t ",getpwuid(file_buff.st_uid)->pw_name,getgrgid(file_buff.st_gid)->gr_name);
    printf("%lld\t ",file_buff.st_size);

    /*   struct timespec ts=file_buff.st_mtime;
       timespec_get(&ts, 0);
       char buff[100];
       strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
       printf("Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
*/

    printf("%s\n",fileName);
    return 0;
}
int cmd_pk_ls_l(char *path)
{
    DIR *dir;
    dir = opendir(path);
    if(dir==NULL)
        perror("ITskfjslkdf:");
    struct dirent *directoryPtr;
    directoryPtr = readdir(dir);
    while(directoryPtr!=NULL)
    {
        print_pk_ls_l(directoryPtr->d_name,directoryPtr->d_name);
        directoryPtr = readdir(dir);
    }
    closedir(dir);
    return 0;
}
