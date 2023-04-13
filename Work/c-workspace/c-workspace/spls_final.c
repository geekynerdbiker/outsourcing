//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <string.h>
//#include <strings.h>
//#include <dirent.h>
//#include <pwd.h>
//#include <time.h>
//#include <grp.h>
//#include <fnmatch.h>
//
//static int aflag = 0; // use as static int option -a
//static int lflag = 0; // use as static int option -l
//static int Sflag = 0; // use as static int option -S
//static int rflag = 0; // use as static int option -r
//static int hflag = 0; // use as static int option -h
//
//static int nfflag = 0;
//static int fflag = 0;
//static int oflag = 0;
//static int dflag = 0;
//
//// 이중 연결리스트 구현을 위한 노드
//typedef struct Node {
//    char filename[256]; // 파일 이름 데이터
//    struct Node *next; // 다음 노드
//    struct Node *prev; // 이전 노드
//} Node;
//
//Node *head = NULL; // 리스트의 헤드 노드
//Node *tail = NULL; // 리스트의 꼬리 노드
//
//int excount = 1; //excution count
//
//// ------------------------------------------------------------------------------------------
//
//char fileType(mode_t m);
//char *perm(mode_t m);
//int matching(char *path[256], int argc);
//void removeChar(char *str, char ch);
//void fileSort(char(*path)[256], int argc);
//
//// ------------------------------------------------------------------------------------------
//
//void insertNode(char* fname);
//void printlist(int aflag, int lflag, int total, int argc,char *dirpath);
//void deletelist(void);
//int checkstring(char* str);
//
//void printfile(int aflag, int lflag,char *name);
//void printOph(long int size);
//void printlistr(int aflag, int lflag,int total, int argc,char *dirpath);
//
//
//int checkexist(char* str);
//
////////////////////////////////////////////////////////////////////
//// distinguish filetype and permission informations                //
//// =============================================================//
//// read, write, execute                                         //
//// Purpose: open directory and read file names                    //
////////////////////////////////////////////////////////////////////
//char fileType(mode_t m) {
//    switch (m) {
//        case S_IFREG:
//            return('-');
//        case S_IFDIR:
//            return('d');
//        case S_IFCHR:
//            return('c');
//        case S_IFBLK:
//            return('b');
//        case S_IFLNK:
//            return('l');
//        case S_IFIFO:
//            return('p');
//        case S_IFSOCK:
//            return('s');
//    }
//    return('?');
//}
//
//char* perm(mode_t m) {
//    int i;
//    static char ret[10] = "---------";
//    char *p;
//    
//    for (i = 0; i < 3; i++) {
//        if (m & (S_IRUSR >> i*3))
//            ret[i*3] = 'r'; // read permission
//        else
//            ret[i*3] = '-';
//        if (m & (S_IWUSR >> i*3))
//            ret[i*3+1] = 'w'; // write permission
//        else
//            ret[i*3+1] = '-';
//        if (m & (S_IXUSR >> i*3))
//            ret[i*3+2] = 'x'; // execute permission
//        else
//            ret[i*3+2] = '-';
//    }
//    
//    if (m & S_ISUID) {
//        if (m & S_IXUSR)
//            ret[2] = 's';
//        else
//            ret[2] = 'S';
//    }
//    
//    if (m & S_ISGID) {
//        if (m & S_IXGRP)
//            ret[5] = 's';
//        else
//            ret[5] = 'S';
//    }
//    
//    if (m & S_ISVTX) {
//        if (m & S_IXOTH)
//            ret[8] = 't';
//        else
//            ret[8] = 'T';
//    }
//    
//    return (ret); //return permission
//}
//
//
////////////////////////////////////////////////////////////////////////
//// For matching command function                                    //
//// ================================================================ //
//// Input: char** -> Information of parameter                        //
////      int -> argment count                                      //
////                                                                  //
//// Output: int  -> New count of argc                                //
////                                                                  //
//// Purpose: For checking match command from parameter               //
////////////////////////////////////////////////////////////////////////
//int matching(char *path[256], int argc) {
//    int count = 0;
//    int flag = 0;
//    int args = argc;
//    
//    DIR *dirp;
//    struct stat buf;
//    struct dirent *dir;
//    
//    char cmd[256][256]={ '\0' };
//    char match[256][256] = { '\0' };
//    char pathname[256][256]={ '\0' };
//    
//    
//    for (int i = 1; i < argc; i++) {
//        for (int j = 0; j < strlen(path[i]); j++) {
//            if (path[i][j] == '*' || path[i][j] == '?') {
//                strcpy(match[count], path[i]);
//                count++;
//                break;
//            } else if (path[i][j] == '[' && ((path[i][j+1] >= '0' && path[i][j+1] <= '9') || (path[i][j+1] >= 'A' && path[i][j+1] <= 'Z') || (path[i][j+1]>= 'a' && path[i][j+1] <= 'z'))
//                       && path[i][j+2] == '-' && ((path[i][j+3] >= '0' && path[i][j+3] <= '9') || (path[i][j+3] >= 'A' && path[i][j+3] <= 'Z') || (path[i][j+3] >= 'a' && path[i][j+3] <= 'z')) && path[i][j+4] == ']') {
//                strcpy(match[count],path[i]);
//                count++;
//                break;
//            } else if(path[i][j] == '[' && ((path[i][j+1] >= '0' && path[i][j+1] <= '9') || (path[i][j+1] >= 'A' && path[i][j+1] <= 'Z') || (path[i][j+1] >= 'A' && path[i][j+1] <= 'z'))
//                      && path[i][j+2]==']') {
//                strcpy(match[count],path[i]);
//                count++;
//                break;
//            }
//        }
//    }
//    
//    for (int i = 0; i < count; i++) {
//        for (int j = 1; j < argc; j++) {
//            if(!strcmp(path[j],match[i])) {
//                for (int k = j; k < argc; k++)
//                    strcpy(path[k],path[k+1]);
//                argc--;
//                break;
//            }
//        }
//    }
//    
//    
//    for (int i = 0; i < count; i++) {
//        int idx = 0;
//        while (match[i][idx] != '\0')
//            idx++;
//        
//        while (idx != 0 && match[i][idx]!='/')
//            idx--;
//        
//        for (int j = 0; j < idx ;j++) {
//            pathname[i][j] = match[i][j];
//            pathname[i][j+1] = '\0';
//        }
//        
//        for (int j = 0, k = j; match[i][j] != '\0'; j++, k++) {
//            cmd[i][j] = match[i][k];
//            cmd[i][k+1] = '\0';
//        }
//        
//    }
//    
//    for (int i = 0; i < count; i++) {
//        int flag=0;
//        
//        if (cmd[i][0] == '/')
//            for(int j = 0; cmd[i][j] != '\0'; j++)
//                cmd[i][j] = cmd[i][j+1];
//        
//        if (strlen(pathname[i]) == 0)
//            dirp = opendir(".");
//        else {
//            flag = 1;
//            dirp = opendir(pathname[i]);
//        }
//        chdir((char *)getenv("PWD"));
//        
//        if (!dirp) {
//            strcpy(path[args], match[i]);
//            args++;
//            continue;
//        }
//        
//        while ((dir = readdir(dirp))) {
//            if (dir->d_name[0] != '.' && !fnmatch(cmd[i], dir->d_name, 0)) {
//                char tmp[256] = { '\0' };
//                strcat(tmp, pathname[i]);
//                
//                if (flag)
//                    strcat(tmp, "/");
//                strcat(tmp, dir->d_name);
//                strcpy(path[args], tmp);
//                args++;
//                flag++;
//            }
//        }
//        
//        if (!flag) {
//            strcpy(path[args], match[i]);
//            args++;
//        }
//        
//        flag = 0;
//        rewinddir(dirp);
//    }
//    
//    return args;
//}
//
//void bubbleSort(char *path[256], char* sort[256], int argc) {
//    char tmp[256] = {'\0'};
//    
//    for (int i = 1; i < argc; i++) {
//        for (int j = 1; j < argc -i; j++) {
//            if ((rflag && strcasecmp(sort[j], sort[j + 1]) < 0) || !rflag && strcasecmp(sort[j], sort[j + 1]) > 0) {
//                strcpy(tmp, path[j]);
//                strcpy(path[j], path[j+1]);
//                strcpy(path[j+1], tmp);
//                
//                strcpy(tmp, sort[j]);
//                strcpy(sort[j], sort[j+1]);
//                strcpy(sort[j+1], tmp);
//            }
//        }
//    }
//}
////////////////////////////////////////////////////////////////////////
//// Main function                                                    //
//// ================================================================ //
//// Input: int -> argument count                                     //
////        char** -> argument vector                                 //
////                                                                  //
//// Output: int 0 End program success                                //
////                                                                  //
//// Purpose: Control all working                                     //
////////////////////////////////////////////////////////////////////////
//int main(int argc, char** argv) {
//    char pathname[128]; // to save name of the file
//    
//    int c = 0;
//    int height = 2;
//    DIR *dirp;
//    
//    struct dirent *dir;
//    struct stat buf;
//    struct group *gid;
//    struct passwd *uid;
//    
//    struct tm *time;
//    
//    char swap[256] = {'\0'};
//    char match[256] = {'\0'};
//    char buffer[256] = {'\0'};
//    
//    char path[256][256] = {'\0'};
//    char sort[256][256] = {'\0'};
//    char subargv[256][256] = {'\0'};
//    
//    int args = 0;
//    int total = 0;
//    int count = 1;
//    
//    
//    while ((c = getopt(argc, argv, "alhSrc:")) != -1) {
//        switch (c) {
//            case 'a':
//                aflag++; // a flag on
//                break;
//            case 'l':
//                lflag++; // a flag on
//                break;
//            case'S':
//                Sflag++; // a flag on
//                break;
//            case'r':
//                rflag++; // a flag on
//                break;
//            case'h':
//                hflag++; // a flag on
//                break;
//        }
//    }
//    
//    // move parameter for other working
//    
//    // move content of parameter
//    for (int i = 0; i< argc; i++)
//        strcpy(path[i], argv[i]);
//    
//    // find matching
//    argc = matching(path, argc);
//    
//    // sorting argument vector
//    for (int i = 0; i < argc; i++) //move content of parameter
//        strcpy(sort[i], path[i]);
//    
//    for (int i = 0; i < argc; i++) //check all parameter
//        if(sort[i][0] == '/') //check exist of '/'
//            removeChar(sort[i], '/'); //remove '/'
//    
//    bubbleSort(path, sort, argc);
//    
//    
//    for (int i = 1; i < argc; i++) {
//        if (path[i][0] == '-') {
//            strcpy(subargv[count], path[i]);
//            count++;
//            oflag++;
//        }
//    }
//    
//    for (int i = 1; i < argc; i++) {
//        char linker[256] = {'\0'};
//        
//        if (!lflag)
//            realpath(path[i], linker);
//        else
//            strcpy(linker, path[i]);
//        
//        if (lstat(linker, &buf) && path[i][0]!='-') {
//            strcpy(subargv[count], path[i]);
//            count++;
//            nfflag++;
//        }
//    }
//    
//    
//    for (int i = 1; i < argc; i++) {
//        char linker[256] = {'\0'};
//        if (!lflag) //check option of L
//            realpath(path[i], linker); //load real path
//        else
//            strcpy(linker, path[i]);
//        
//        if (lstat(linker, &buf) && !S_ISDIR(buf.st_mode) && path[i][0]!='-') {
//            strcpy(subargv[count], path[i]);
//            count++;
//            fflag++;
//        }
//    }
//    
//    for (int i = 1; i < argc; i++) {
//        char linker[256] = {'\0'};
//        if (!lflag)
//            realpath(path[i], linker); //load real path
//        else
//            strcpy(linker, path[i]);
//        
//        if (!lstat(linker, &buf) && S_ISDIR(buf.st_mode)) {
//            strcpy(subargv[count], path[i]);
//            count++;
//            dflag++;
//        }
//    }
//    
//    if (Sflag)
//        fileSort(subargv, argc);
//    
//    for (int i = 0; argv[i]; i++)
//        if (argv[i][0] != '-')
//            args++;
//    
//    if (args) {
//        dirp = opendir(".");
//        chdir(".");
//        
//        while ((dir = readdir(dirp))) {
//            lstat(dir->d_name, &buf);
//            
//            if (aflag || dir->d_name[0] != '.') //check hidden file
//                total += buf.st_blocks / 2;
//            insertNode(dir->d_name); //insert node
//        }
//        
//        if (rflag)
//            printlistr(aflag, lflag,total, argc,pathname); //print reverse
//        else
//            printlist(aflag, lflag,total, argc,pathname); //print linkered list
//        
//        deletelist(); //delete list
//        
//        chdir((char *)getenv("PWD"));
//        total = 0;
//        
//        return 0;
//    }
//    
//    
//    
//    /////////////////////////If argument count is not 1////////////////////////////////
//    for (int i = 1; i<argc; i++) //For checking all parameter
//    {
//        /*for(int i=0;i<argc;i++)
//         printf("%s\n",subargv[i]);
//         exit(0);*/
//        char dirpath[256] = {'\0'};
//        strcpy(dirpath,subargv[i]);
//        
//        if(checkexist(subargv[i])) //check exist character of '/'
//        {
//            int num=0;
//            for(;subargv[i][num]!='\0';num++); //move pointer to end of string
//            for(;subargv[i][num]!='/';num--); //search '/'
//            for(int check=0;check<num;check++)
//                dirpath[check]=subargv[i][check];
//        }
//        
//        
//        excount++;
//        if (subargv[i][0] == '-') //If the parameter is option
//            continue;
//        
//        if (lstat(subargv[i], &buf)<0) //If the parameter is not file
//        {
//            if(subargv[i][0]=='/'&& (subargv[i][strlen(subargv[i])-1]=='*' || subargv[i][strlen(subargv[i])-1]=='?' || subargv[i][strlen(subargv[i])-1]==']'))
//                printf("ls: cannot access %s: No such file or directory\n",subargv[i]); //print error
//            
//            else
//                printf("cannot access %s: No such file or directory\n",subargv[i]); //print error
//            continue;
//        }
//        
//        else
//        {
//            if(lflag!=1) //check flag L
//            {
//                char linker[256] = {'\0'};
//                struct stat buf2;
//                realpath(subargv[i], linker); //real path of linker file
//                lstat(linker, &buf2); //read file
//                if(S_ISDIR(buf2.st_mode)) //check directory
//                    buf.st_mode=buf2.st_mode;
//            }
//            
//            if (S_ISDIR(buf.st_mode)) //If the parameter is directory
//            {
//                dirp = opendir(subargv[i]); //open directory
//                chdir(subargv[i]); //change directory
//                
//                do
//                {
//                    dir = readdir(dirp); //read
//                    
//                    if (!dir) //check NULL
//                        break; //stop repeat functsion
//                    
//                    else
//                    {
//                        lstat(dir->d_name,&buf); //read file
//                        if(aflag!=0||dir->d_name[0]!='.') //check hidden file
//                            total+=buf.st_blocks/2;
//                        
//                        insertNode(dir->d_name); //insert node
//                    }
//                    
//                } while (1);
//                
//                if(rflag==1)
//                    printlistr(aflag, lflag,total,argc,dirpath); //print linkered list (reverse)
//                else
//                    printlist(aflag, lflag,total,argc,dirpath); //print linkered list
//                deletelist(); //delete linkered list
//                closedir(dirp); //close dirp
//                chdir((char *)getenv("PWD")); //change directory
//                total=0;
//            }
//            
//            else //If the parameter just file
//            {
//                printfile(aflag,lflag,subargv[i]); //print information of file
//                
//                if(excount!=argc && i==(nfflag+fflag+oflag)) //check count
//                    printf("\n");
//            }
//        }
//    }
//    
//    return 0;
//}
//
////////////////////////////////////////////////////////////////////////
//// Print function                                                   //
//// ================================================================ //
//// Input: int -> Information of option flag                         //
////      int -> Information of option flag                         //
////        int -> For calculating tootal                             //
////        char* -> For print current working directory              //
////                                                                  //
//// Output: void                                                     //
////                                                                  //
//// Purpose: Print list of directory's files                         //
////////////////////////////////////////////////////////////////////////
//void printlist(int aflag, int lflag, int total, int argc,char *dirpath)
//{
//    struct group *gid;
//    struct passwd *uid;
//    struct tm *time;
//    char buffer[256];
//    char cwd[256];
//    struct stat buf;
//    struct dirent *dir;
//    
//    int k=0, m=0;
//    char subpath[256] = {'\0'};
//    char subdirpath[256] = {'\0'};
//    char checkpath[256] = {'\0'};
//    
//    //printf("%s\n",dirpath);
//    
//    
//    if (lflag==1||argc>2) //check option if '-l'
//    {
//        getcwd(cwd, sizeof(cwd)); //load current working directory
//        
//        for(;cwd[k]!='\0';k++);
//        for(;cwd[k]!='/';k--);
//        for(;m<k;m++)
//            subpath[m]=cwd[m];
//        
//        for(k=0;dirpath[k]!='\0';k++); //move pointer to end
//        for(;dirpath[k]!='/'&&k!=0;k--); //search '/'
//        if(dirpath[k]=='/') k++; //check character
//        for(m=0;dirpath[k]!='\0';m++,k++)
//            subdirpath[m]=dirpath[k];
//        
//        strcat(checkpath,subpath); //letter aggregation
//        strcat(checkpath,"/"); //letter aggregation
//        strcat(checkpath,subdirpath); //letter aggregation
//        //printf("%s\n",checkpath);
//        
//        lstat(checkpath,&buf);
//        if(S_ISLNK(buf.st_mode))
//            strcpy(cwd,checkpath);
//        
//        if(lflag==1||dflag>1||nfflag>1||fflag>1) //check option
//            printf("Directory path: %s\n", cwd);
//        else if(dflag>1||nfflag>1||fflag>1)
//        {
//            printf("Directory path: %s\n", cwd);
//            printf("total: %d\n",total);
//        }
//        
//    }
//    
//    
//    for (Node *tmp = head; tmp; tmp = tmp->next) //Repeat function for printing all list
//    {
//        
//        if ((lflag == 1 && aflag == 0 && tmp->filename[0] != '.') || (lflag == 1 && aflag == 1))
//        { //check option of '-l'
//            
//            lstat(tmp->filename, &buf); //read file
//            
//            uid = getpwuid(buf.st_uid); //get user id
//            gid = getgrgid(buf.st_gid); //get group id
//            
//            time = localtime(&buf.st_mtime);//save time of fixed file
//            printf("%c%s ", fileType(buf.st_mode), perm(buf.st_mode));
//            
//            if(fileType(buf.st_mode)=='l') //for printing linker file
//            {
//                char linker[256] = {'\0'};
//                char realp[256] = {'\0'};
//                int i=0;
//                int j=0;
//                
//                realpath(tmp->filename, linker); //real path of linker file
//                for(;linker[i]!='\0';i++); //move pointer to end
//                for(;linker[i]!='/';i--); //search '/'
//                for(;linker[i]!='\0';i++,j++)
//                    realp[j]=linker[i+1];
//                realp[j+1]='\0';
//                strcat(tmp->filename,"->"); //letter aggregation
//                strcat(tmp->filename,realp); //letter aggregation
//            }
//            
//            
//            printf("%hu\t", buf.st_nlink); //number of linker
//            printf("%s\t", uid->pw_name);  //usser ID
//            printf("%s\t", gid->gr_name);  //group ID
//            ////////////////option h///////////////////
//            if(hflag==1)
//                printOph(buf.st_size);
//            
//            else
//                printf("%lld\t", buf.st_size); //size of file
//            ///////////////////////////////////////////
//            
//            
//            strftime(buffer, 255, "%b %d %H:%M", time);
//            printf("%s\t", buffer);
//        }
//        
//        if ((aflag == 0 && tmp->filename[0] != '.') || aflag == 1)
//            printf("%s\n", tmp->filename); //file name
//    }
//    if(excount!=argc)
//        printf("\n");
//    return;
//}
//
////////////////////////////////////////////////////////////////////////
//// Print function                                                   //
//// ================================================================ //
//// Input: int -> Information of option flag                         //
////      int -> Information of option flag                         //
////        int -> For calculating tootal                             //
////        char* -> For print current working directory              //
////                                                                  //
//// Output: void                                                     //
////                                                                  //
//// Purpose: Print list of directory's files to reverse              //
////////////////////////////////////////////////////////////////////////
//void printlistr(int aflag, int lflag,int total, int argc,char *dirpath)
//{
//    struct group *gid;
//    struct passwd *uid;
//    struct tm *time;
//    char buffer[256] = {'\0'};
//    char cwd[256] = {'\0'};
//    struct stat buf;
//    struct dirent *dir;
//    
//    int k=0, m=0;
//    char subpath[256] = {'\0'};
//    char subdirpath[256] = {'\0'};
//    char checkpath[256] = {'\0'};
//    
//    //printf("%s\n",dirpath);
//    
//    
//    if (lflag==1||argc>2) //check option if '-l'
//    {
//        getcwd(cwd, sizeof(cwd)); //load current working directory
//        
//        for(;cwd[k]!='\0';k++); //move pointer to end
//        for(;cwd[k]!='/';k--); //search '/'
//        for(;m<k;m++)
//            subpath[m]=cwd[m];
//        
//        for(k=0;dirpath[k]!='\0';k++); //move pointer to end
//        for(;dirpath[k]!='/'&&k!=0;k--); //search '/'
//        if(dirpath[k]=='/') k++; //check character
//        for(m=0;dirpath[k]!='\0';m++,k++)
//            subdirpath[m]=dirpath[k];
//        
//        strcat(checkpath,subpath); //letter aggregation
//        strcat(checkpath,"/"); //letter aggregation
//        strcat(checkpath,subdirpath); //letter aggregation
//        //printf("%s\n",checkpath);
//        
//        lstat(checkpath,&buf); //read file
//        if(S_ISLNK(buf.st_mode)) //check linker file
//            strcpy(cwd,checkpath);
//        
//        if(lflag==1||dflag>1||nfflag>1||fflag>1) //check option
//            printf("Directory path: %s\n", cwd);
//        else if(dflag>1||nfflag>1||fflag>1)
//        {
//            printf("Directory path: %s\n", cwd);
//            printf("total: %d\n",total);
//        }
//        
//    }
//    
//    Node *tmp=head;
//    for (; tmp->next; tmp = tmp->next);
//    for (; tmp; tmp = tmp->prev) //Repeat function for printing all list
//    {
//        
//        if ((lflag == 1 && aflag == 0 && tmp->filename[0] != '.') || (lflag == 1 && aflag == 1))
//        { //check option of '-l'
//            
//            lstat(tmp->filename, &buf); //read file
//            
//            uid = getpwuid(buf.st_uid); //get user id
//            gid = getgrgid(buf.st_gid); //get group id
//            
//            time = localtime(&buf.st_mtime);//save time of fixed file
//            printf("%c%s ", fileType(buf.st_mode), perm(buf.st_mode));
//            
//            if(fileType(buf.st_mode)=='l') //for printing linker file
//            {
//                char linker[256] = {'\0'};
//                char realp[256] = {'\0'};
//                int i=0;
//                int j=0;
//                
//                realpath(tmp->filename, linker); //real path of linker file
//                for(;linker[i]!='\0';i++); //move pointer
//                for(;linker[i]!='/';i--); //search '/'
//                for(;linker[i]!='\0';i++,j++)
//                    realp[j]=linker[i+1];
//                realp[j+1]='\0';
//                strcat(tmp->filename,"->");
//                strcat(tmp->filename,realp);
//            }
//            
//            
//            printf("%hu\t", buf.st_nlink); //number of linker
//            printf("%s\t", uid->pw_name);  //usser ID
//            printf("%s\t", gid->gr_name);  //group ID
//            ////////////////option h///////////////////
//            if(hflag==1)
//                printOph(buf.st_size); //print h option
//            
//            else
//                printf("%lld\t", buf.st_size); //size of file
//            ///////////////////////////////////////////
//            
//            
//            strftime(buffer, 255, "%b %d %H:%M", time); //time function
//            printf("%s\t", buffer);
//        }
//        
//        if ((aflag == 0 && tmp->filename[0] != '.') || aflag == 1)
//            printf("%s\n", tmp->filename); //file name
//    }
//    if(excount!=argc)
//        printf("\n");
//    return;
//}
////////////////////////////////////////////////////////////////////////
//// Print function                                                   //
//// ================================================================ //
//// Input: int -> Information of option flag                         //
////      int -> Information of option flag                         //
////        int -> For calculating tootal                             //
////                                                                  //
//// Output: void                                                     //
////                                                                  //
//// Purpose: Print just file information                             //
////////////////////////////////////////////////////////////////////////
//void printfile(int aflag, int lflag, char *name) //The function is equal function of printlist
//{ //It just print each file from parameter
//    struct group *gid;
//    struct passwd *uid;
//    struct tm *time;
//    char buffer[256] = {'\0'};
//    char cwd[256] = {'\0'};
//    struct stat buf;
//    struct dirent *dir;
//    
//    if ((lflag == 1 && aflag == 0 && name[0] != '.') || (lflag == 1 && aflag == 1))
//    { //check option if '-l'
//        
//        lstat(name, &buf); //read file
//        
//        uid = getpwuid(buf.st_uid); //get user id
//        gid = getgrgid(buf.st_gid); //get group id
//        
//        time = localtime(&buf.st_mtime);//save time of fixed file
//        printf("%c%s ", fileType(buf.st_mode), perm(buf.st_mode));
//        
//        if(fileType(buf.st_mode)=='l') //for printing linker file
//        {
//            char linker[256] = {'\0'};
//            char realp[256] = {'\0'};
//            int i=0;
//            int j=0;
//            
//            realpath(name, linker); //real path of linker file
//            for(;linker[i]!='\0';i++); //move pointer to end of string
//            for(;linker[i]!='/';i--); //search character of '/'
//            for(;linker[i]!='\0';i++,j++)
//                realp[j]=linker[i+1];
//            realp[j+1]='\0';
//            strcat(name,"->"); //sign of linker
//            strcat(name,realp);
//        }
//        
//        
//        printf("%hu\t", buf.st_nlink); //linker
//        printf("%s\t", uid->pw_name);  //usser ID
//        printf("%s\t", gid->gr_name);  //group ID
//        ////////////////option h///////////////////
//        if(hflag==1)
//            printOph(buf.st_size);
//        else
//            printf("%lld\t", buf.st_size); //size of file
//        ///////////////////////////////////////////
//        
//        strftime(buffer, 255, "%b %d %H:%M", time); //time function
//        printf("%s\t", buffer);
//    }
//    
//    if ((aflag == 0 && name[0] != '.') || aflag == 1)
//        printf("%s\n", name); //file name
//}
//
////////////////////////////////////////////////////////////////////////
//// Print function                                                   //
//// ================================================================ //
//// Input: long int -> Information of option size                    //
////                                                                  //
//// Output: void                                                     //
////                                                                  //
//// Purpose: For printing option of h                                //
////////////////////////////////////////////////////////////////////////
//void printOph(long int size)
//{
//    int k=0,flag=0;
//    double sub_size;
//    
//    sub_size=(double)size;
//    
//    for(k=0;1;k++) //for check size of k(unit)
//    {
//        if(sub_size>(double)1024)
//            sub_size/=1024;
//        
//        else
//            break;
//    }
//    size=(int)sub_size; //change of type
//    sub_size=(int)(sub_size*10); //Remove from decimal second
//    sub_size=sub_size/10;
//    if(size*10==(int)(sub_size*10)) //check first decimal point
//        flag=1;
//    
//    int size_int=0;
//    
//    if(k==0) //below kilobytes
//    {
//        
//        size_int=(int)sub_size;
//        printf("%d\t",size_int);
//        
//    }
//    
//    else if(k==1) //kilobytes
//    {
//        if(flag==1) //flag of intger
//        {
//            size_int=(int)sub_size;
//            printf("%d%s\t",size_int,"K");
//        }
//        else //exist decimal point
//            printf("%.1lf%s\t",sub_size,"K");
//    }
//    
//    else if(k==2) //megabytes unit
//    {
//        if(flag==1) //flag of intger
//        {
//            size_int=(int)sub_size;
//            printf("%d%s\t",size_int,"M");
//        }
//        else //exist decimal point
//            printf("%.1lf%s\t",sub_size,"M");
//    }
//    
//    else if(k==3) //gigabytes unit
//    {
//        if(flag==1) //flag of intger
//        {
//            size_int=(int)sub_size;
//            printf("%d%s\t",size_int,"G");
//        }
//        else //exist decimal point
//            printf("%.1lf%s\t",sub_size,"G");
//    }
//    
//    else if(k==4) //terabytes unit
//    {
//        if(flag==1) //flag of intger
//        {
//            size_int=(int)sub_size;
//            printf("%d%s\t",size_int,"T");
//        }
//        else //exist decimal point
//            printf("%.1lf%s\t",sub_size,"T");
//    }
//    return;
//}
//
//void fileSort(char (*path)[256], int argc) {
//    int count = 0;
//    
//    struct stat buf1;
//    struct stat buf2;
//    
//    char tmp[256] = {'\0'};
//    char sub[256][256] = {'\0'};
//    
//    int i = nfflag + oflag + 1, j = 0;
//    while (i < nfflag + fflag + oflag + 1) {
//        strcpy(sub[j], path[i]);
//        i++; j++; count++;
//    }
//    
//    for (i = 0; i < count - 1; i++) {
//        for (j = 0; j < count - 1 - i; j++) {
//            lstat(sub[j], &buf1);
//            lstat(sub[j+1], &buf2);
//            
//            if ((rflag && buf1.st_size < buf2.st_size) || (!rflag && buf1.st_size > buf2.st_size)) {
//                strcpy(tmp, sub[j]);
//                strcpy(sub[j], sub[j+1]);
//                strcpy(sub[j+1] , tmp);
//            }
//        }
//    }
//    
//    i = nfflag + oflag + 1; j = 0;
//    while (i < nfflag + fflag + oflag + 1) {
//        strcpy(path[i],sub[j]);
//        i++; j++;
//    }
//}
//
////////////////////////////////////////////////////////////////////////
//// Insert function                                                  //
//// ================================================================ //
//// Input: char* -> Name of file                                     //
////                                                                  //
//// Output: void                                                     //
////                                                                  //
//// Purpose: For creating linkered list                                //
////////////////////////////////////////////////////////////////////////
//void insertNode(char* name) //The function of inserting node to linkered list
//{
//    struct stat buf1;
//    struct stat buf2;
//    
//    char Ename[256] = {'\0'};
//    char Etmpname[256] = {'\0'};
//    
//    Node* tmp = head;
//    Node* prevnode;
//    
//    
//    if (!head) //If not exist linkered list
//    {
//        Node* newnode = (Node*)malloc(sizeof(Node));
//        strcpy(newnode->filename, name);
//        newnode->next = NULL;
//        newnode->prev = NULL;
//        
//        head = newnode; //Creating head of list
//        return;
//    }
//    
//    else //when exist linkered list
//    {
//        for (; tmp; tmp = tmp->next) //For checking all node
//        {
//            if (Sflag) {
//                lstat(name,&buf); //read file
//                lstat(tmp->filename,&buf2); //read file
//            }
//            //////////For checking symbol in string//////////
//            strcpy(Ename, name);
//            strcpy(Etmpname, tmp->filename);
//            
//            if (checkstring(Ename)) //check string
//                removeChar(Ename, '.'); //delete '.'
//            if (checkstring(Etmpname))
//                removeChar(Etmpname, '.');
//            /////////////////////////////////////////////////
//            
//            if (strcasecmp(Etmpname, Ename) > 0) {
//                if (Sflag && buf1.st_size - buf2.st_size)
//                    continue;
//                if (tmp == head) //when the new node insert before head node
//                {
//                    Node* newnode = (Node*)malloc(sizeof(Node));
//                    strcpy(newnode->filename, name);
//                    newnode->prev = NULL;
//                    
//                    newnode->next = head; //linker node
//                    head->prev = newnode; //linker node
//                    head = newnode; //Declare head
//                    return;
//                }
//                
//                else //when the new node insert before tmp node
//                {
//                    Node* newnode = (Node*)malloc(sizeof(Node));
//                    strcpy(newnode->filename, name);
//                    newnode->next = tmp; //linker node
//                    newnode->prev = tmp->prev; //linker node
//                    tmp->prev->next = newnode; //linker node
//                    tmp->prev = newnode; //linker node
//                    return;
//                }
//            } else if (Sflag && buf1.st_size - buf2.st_size) {
//                if (tmp == head) //when the new node insert before head node
//                {
//                    Node* newnode = (Node*)malloc(sizeof(Node));
//                    strcpy(newnode->filename, name);
//                    newnode->prev = NULL;
//                    
//                    newnode->next = head; //link node
//                    head->prev = newnode; //link node
//                    head = newnode; //declare head
//                    return;
//                }
//                
//                else //when the new node insert before tmp node
//                {
//                    Node* newnode = (Node*)malloc(sizeof(Node));
//                    strcpy(newnode->filename, name);
//                    newnode->next = tmp; //link node
//                    newnode->prev = tmp->prev; //link node
//                    tmp->prev->next = newnode; //link node
//                    tmp->prev = newnode; //link node
//                    return;
//                }
//            }
//            else continue;
//        }
//        //when the new node insert next tail node
//        for (prevnode = head; prevnode->next; prevnode = prevnode->next);
//        Node* newnode = (Node*)malloc(sizeof(Node));
//        
//        strcpy(newnode->filename, name);
//        newnode->next = NULL;
//        prevnode->next = newnode; //link node
//        newnode->prev = prevnode; //link node
//        tail = newnode; //declare Tail
//        return;
//        
//    }
//}
//
////////////////////////////////////////////////////////////////////////
//// Check function                                                   //
//// ================================================================ //
//// Input: int -> Information of option flag                         //
////      int -> Information of option flag                         //
////        int -> For calculating tootal                             //
////                                                                  //
//// Output: int 1 -> Not exist symbol                                //
////             0 -> Exist symbol                                    //
////                                                                  //
//// Purpose: For checking symbol in string                           //
////////////////////////////////////////////////////////////////////////
//int checkstring(char* str)
//{
//    if(str[0]!='.')
//        return 0;
//    for (int i = 0; str[i] != '\0'; i++) //checking all character in string
//    {
//        if (str[i] >= 65 && str[i] <= 132) //check letters
//            return 1;
//        else if (str[i] >= 97 && str[i] <= 122) //check letters
//            return 1;
//    }
//    return 0;
//}
//
//
////////////////////////////////////////////////////////////////////////
//// Checking function                                                //
//// ================================================================ //
//// Input: char* -> The string is checked                            //
////                                                                  //
//// Output: void                                                     //
////                                                                  //
//// Purpose: For eliminating '/' symbol                              //
////////////////////////////////////////////////////////////////////////
//int checkexist(char* str)
//{
//    for(int i=0;str[i]!='\0';i++) //cehck string
//    {
//        if(str[i]=='/') //if match '/'
//            return 1;
//    }
//    return 0;
//}
//
////////////////////////////////////////////////////////////////////////
//// Delete function                                                  //
//// ================================================================ //
//// Input: char* -> The string is checked                            //
////      char -> The character is wanted to eliminating            //
////                                                                  //
//// Output: void                                                     //
////                                                                  //
//// Purpose: For eliminating '.' symbol                              //
////////////////////////////////////////////////////////////////////////
//void removeChar(char *str, char ch) {
//    while (*str != '\0') {
//        if (*str == ch) {
//            strcpy(str, str + 1);
//            str--;
//            return;
//        }
//        str++;
//    }
//}
//
////////////////////////////////////////////////////////////////////////
//// Delete function                                                  //
//// ================================================================ //
//// Input:  void                                                     //
////                                                                  //
//// Output: void                                                     //
////                                                                  //
//// Purpose: Delete linkered list                                      //
////////////////////////////////////////////////////////////////////////
//void deletelist() //for deleteing all linkered list
//{
//    Node* tmp = head;
//    for (;tmp->next;) //Hit all node
//    {
//        head = tmp->next;
//        free(tmp); //free
//        tmp = head;
//    }
//    free(tmp);
//    head = NULL;
//}
//
//
//
