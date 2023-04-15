#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <fnmatch.h>

static int aflag = 0; // use as static int option -a
static int lflag = 0; // use as static int option -l
static int Sflag = 0; // use as static int option -S
static int rflag = 0; // use as static int option -r
static int hflag = 0; // use as static int option -h

static int nfflag = 0;
static int fflag = 0;
static int oflag = 0;
static int dflag = 0;

static int excution = 1;

typedef struct Node {
    char file[256];
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;

char fileType(mode_t m);
void fileSort(char (*path)[256], int argc);
char *permission(mode_t m);

int matching(char (*path)[256], int argc);
int checkSymbol(char* str);
int checkSlash(char* str);
void removeChar(char *str, char ch);

void insertNode(char* fname);
void eliminate(void);

void print(int total, int argc,char *dirpath);
void filePrint(char *name);
void unitPrint(long int size);

// Control all working
int main(int argc, char** argv) {
    char pathname[256];
    
    int c = 0;
    DIR *dirp;
    
    struct dirent *dir;
    struct stat buf;
    
    char path[256][256];
    char sort[256][256];
    char subargv[256][256];
    
    int args = 0;
    int total = 0;
    int count = 1;
    
    while ((c = getopt(argc, argv, "alhSrc:")) != -1) {
        switch (c) {
            case 'a':
                aflag++;
                break;
            case 'l':
                lflag++;
                break;
            case 'S':
                Sflag++;
                break;
            case 'r':
                rflag++;
                break;
            case 'h':
                hflag++;
                break;
            default:
                break;
        }
    }
    
    for (int i = 0; i< argc; i++)
        strcpy(path[i], argv[i]);
    
    argc = matching(path, argc);
    
    for (int i = 0; i < argc; i++)
        strcpy(sort[i], path[i]);
    
    for (int i = 0; i < argc; i++)
        if(sort[i][0] == '/')
            removeChar(sort[i], '/');
    
    char tmp[256];
    for (int i = 1; i < argc; i++) {
        for (int j = 1; j < argc - i; j++) {
            if ((rflag && strcasecmp(sort[j], sort[j + 1]) < 0) || (!rflag && strcasecmp(sort[j], sort[j + 1]) > 0)) {
                strcpy(tmp, path[j]);
                strcpy(path[j], path[j+1]);
                strcpy(path[j+1], tmp);
                
                strcpy(tmp, sort[j]);
                strcpy(sort[j], sort[j+1]);
                strcpy(sort[j+1], tmp);
            }
        }
    }
    
    for (int i = 1; i < argc; i++) {
        if (path[i][0] == '-') {
            strcpy(subargv[count], path[i]);
            count++;
            oflag++;
        }
    }
    
    for (int i = 1; i < argc; i++) {
        char linker[256];
        
        if (!lflag)
            realpath(path[i], linker);
        else
            strcpy(linker, path[i]);
        
        if (lstat(linker, &buf) < 0 && path[i][0] != '-') {
            strcpy(subargv[count], path[i]);
            count++;
            nfflag++;
        }
        
        if (!lstat(linker, &buf) && !S_ISDIR(buf.st_mode) && path[i][0] != '-') {
            strcpy(subargv[count], path[i]);
            count++;
            fflag++;
        }
        
        if (!lstat(linker, &buf) && S_ISDIR(buf.st_mode)) {
            strcpy(subargv[count], path[i]);
            count++;
            dflag++;
        }
    }
    
    if (Sflag)
        fileSort(subargv, argc);
    
    for (int i = 0; argv[i]; i++)
        if (argv[i][0] != '-')
            args++;
    
    if (args == 1) {
        dirp = opendir(".");
        chdir(".");
        
        while ((dir = readdir(dirp))) {
            lstat(dir->d_name, &buf);
            
            if (aflag || dir->d_name[0] != '.')
                total += buf.st_blocks / 2;
            insertNode(dir->d_name);
        }
        
        print(total, argc, pathname);
        eliminate();
        
        chdir((char *)getenv("PWD"));
        total = 0;
        
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        char dirpath[256];
        strcpy(dirpath, subargv[i]);
        
        if (checkSlash(subargv[i])) {
            int check = 0, num = 0;
            
            while (subargv[i][num] != '\0')
                num++;
            while (subargv[i][num] != '/')
                num--;
            while (check < num) {
                dirpath[check] = subargv[i][check];
                check++;
            }
        }
        
        excution++;
        if (subargv[i][0] == '-')
            continue;
        
        if (lstat(subargv[i], &buf) < 0) {
            if (subargv[i][0] == '/' && (subargv[i][strlen(subargv[i])-1] == '*' || subargv[i][strlen(subargv[i])-1] == '?' || subargv[i][strlen(subargv[i])-1] == ']'))
                printf("ls: cannot access %s: No such file or directory\n", subargv[i]);
            else
                printf("cannot access %s: No such file or directory\n", subargv[i]);
            continue;
        }
        
        else {
            if (!lflag) {
                char linker[256];
                struct stat new_buf;
                
                realpath(subargv[i], linker);
                lstat(linker, &new_buf);
                if (S_ISDIR(new_buf.st_mode))
                    buf.st_mode = new_buf.st_mode;
            }
            
            if (S_ISDIR(buf.st_mode)) {
                dirp = opendir(subargv[i]);
                chdir(subargv[i]);
                
                while ((dir = readdir(dirp))) {
                    lstat(dir->d_name, &buf);
                    
                    if (aflag || dir->d_name[0] != '.')
                        total += buf.st_blocks / 2;
                    insertNode(dir->d_name);
                }
                
                print(total, argc, dirpath);
                eliminate();
                closedir(dirp);
                chdir((char *)getenv("PWD"));
                total = 0;
            } else {
                filePrint(subargv[i]);
                if (i == nfflag + fflag + oflag && excution != argc)
                    printf("\n");
            }
        }
    }
    
    return 0;
}


// Open directory, Read files
char fileType(mode_t m) {
    switch (m) {
        case S_IFREG:
            return('-');
        case S_IFDIR:
            return('d');
        case S_IFCHR:
            return('c');
        case S_IFBLK:
            return('b');
        case S_IFLNK:
            return('l');
        case S_IFIFO:
            return('p');
        case S_IFSOCK:
            return('s');
    }
    return('-');
}

// Sort Files
void fileSort(char (*path)[256], int argc) {
    struct stat buf1;
    struct stat buf2;
    
    char tmp[256];
    char sub[256][256];
    
    int count = 0;
    
    int i = nfflag + oflag + 1, j = 0;
    while (i < nfflag + fflag + oflag + 1) {
        strcpy(sub[j], path[i]);
        i++; j++; count++;
    }
    
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            lstat(sub[j], &buf1);
            lstat(sub[j+1], &buf2);
            
            if ((rflag && buf1.st_size < buf2.st_size) || (!rflag && buf1.st_size > buf2.st_size)) {
                strcpy(tmp, sub[j]);
                strcpy(sub[j], sub[j+1]);
                strcpy(sub[j+1] , tmp);
            }
        }
    }
    
    i = nfflag + oflag + 1; j = 0;
    while (i < nfflag + fflag + oflag + 1) {
        strcpy(path[i],sub[j]);
        i++; j++;
    }
}

// Check Permissions
char* permission(mode_t m) {
    int i;
    static char ret[10] = "---------";
    
    for (i = 0; i < 3; i++) {
        if (m & (S_IRUSR >> i*3))
            ret[i*3] = 'r';
        else
            ret[i*3] = '-';
        if (m & (S_IWUSR >> i*3))
            ret[i*3+1] = 'w';
        else
            ret[i*3+1] = '-';
        if (m & (S_IXUSR >> i*3))
            ret[i*3+2] = 'x';
        else
            ret[i*3+2] = '-';
    }
    
    if (m & S_ISUID) {
        if (m & S_IXUSR)
            ret[2] = 's';
        else
            ret[2] = 'S';
    }
    
    if (m & S_ISGID) {
        if (m & S_IXGRP)
            ret[5] = 's';
        else
            ret[5] = 'S';
    }
    
    if (m & S_ISVTX) {
        if (m & S_IXOTH)
            ret[8] = 't';
        else
            ret[8] = 'T';
    }
    
    return (ret);
}

// Match command from parameter
int matching(char (*path)[256], int argc) {
    DIR *dirp;
    
    struct dirent *dir;
    
    char cmd[256][256];
    char match[256][256];
    char pathname[256][256];
    
    int count = 0, args = 0, flag = 0;
    
    for (int i = 1; i < argc; i++) {
        for (int j = 0; j < strlen(path[i]); j++) {
            if (path[i][j] == '*' || path[i][j] == '?') {
                strcpy(match[count], path[i]);
                count++;
                break;
            } else if(path[i][j] == '[' && ((path[i][j+1] >= '0' && path[i][j+1] <= '9') || (path[i][j+1] >= 'A' && path[i][j+1] <= 'Z') || (path[i][j+1] >= 'A' && path[i][j+1] <= 'z'))
                      && path[i][j+2]==']') {
                strcpy(match[count],path[i]);
                count++;
                break;
            } else if (path[i][j] == '[' && ((path[i][j+1] >= '0' && path[i][j+1] <= '9') || (path[i][j+1] >= 'A' && path[i][j+1] <= 'Z') || (path[i][j+1]>= 'a' && path[i][j+1] <= 'z'))
                       && path[i][j+2] == '-' && ((path[i][j+3] >= '0' && path[i][j+3] <= '9') || (path[i][j+3] >= 'A' && path[i][j+3] <= 'Z') || (path[i][j+3] >= 'a' && path[i][j+3] <= 'z')) && path[i][j+4] == ']') {
                strcpy(match[count],path[i]);
                count++;
                break;
            }
        }
    }
    
    for (int i = 0; i < count; i++) {
        for (int j = 1; j < argc; j++) {
            if(!strcmp(path[j], match[i])) {
                for (int k = j; k < argc; k++)
                    strcpy(path[k], path[k+1]);
                argc--;
                break;
            }
        }
    }
    
    
    args = argc;
    for (int i = 0; i < count; i++) {
        int idx = 0;
        
        while (match[i][idx] != '\0')
            idx++;
        
        while (idx && match[i][idx] != '/')
            idx--;
        
        for (int j = 0; j < idx; j++) {
            pathname[i][j] = match[i][j];
            pathname[i][j+1] = '\0';
        }
        
        for (int j = 0, k = idx; match[i][j] != '\0'; j++, k++) {
            cmd[i][j] = match[i][k];
            cmd[i][j+1] = '\0';
        }
    }
    
    for (int i = 0; i < count; i++) {
        int isDir = 0;
        
        if (cmd[i][0] == '/')
            for(int j = 0; cmd[i][j] != '\0'; j++)
                cmd[i][j] = cmd[i][j+1];
        
        if (strlen(pathname[i])) {
            isDir = 1;
            dirp = opendir(pathname[i]);
        } else
            dirp = opendir(".");
        
        chdir((char *)getenv("PWD"));
        
        if (!dirp) {
            strcpy(path[args], match[i]);
            args++;
            continue;
        }
        
        while ((dir = readdir(dirp))) {
            if (dir->d_name[0] != '.' && !fnmatch(cmd[i], dir->d_name, 0)) {
                char tmp[256] = {0};
                strcat(tmp, pathname[i]);
                
                if (isDir)
                    strcat(tmp, "/");
                strcat(tmp, dir->d_name);
                strcpy(path[args], tmp);
                args++;
                flag = 1;
            }
        }
        
        if (!flag) {
            strcpy(path[args], match[i]);
            args++;
        }
        
        flag = 0;
        rewinddir(dirp);
    }
    
    return args;
}

// Check symbols in string
int checkSymbol(char* str) {
    if (str[0] != '.')
        return 0;
    
    for (int i = 0; str[i] != '\0'; i++)
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
            return 1;
    return 0;
}

// Check '/' in string
int checkSlash(char* str) {
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] == '/')
            return 1;
        i++;
    }
    return 0;
}

// Remove symbol in string
void removeChar(char *str, char ch) {
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] == ch) {
            for (int j = 0; j < strlen(str) - 1; j++)
                str[j] = str[j+1];
            str[strlen(str) - 1] = '\0';
            return;
        }
        str++;
    }
}

// Create List and Insert Node
void insertNode(char* name) {
    struct stat buf1;
    struct stat buf2;
    
    char symbolChecker[256];
    char tmp[256];
    
    Node* p = head;
    Node* prev;
    
    
    if (!head) {
        Node* n = (Node*)malloc(sizeof(Node));
        
        strcpy(n->file, name);
        n->next = NULL;
        n->prev = NULL;
        head = n;
        
        return;
    } else {
        while (p) {
            if (Sflag) {
                lstat(name, &buf1);
                lstat(p->file,&buf2);
            }
            
            strcpy(symbolChecker, name);
            strcpy(tmp, p->file);
            
            if (checkSymbol(symbolChecker))
                removeChar(symbolChecker, '.');
            if (checkSymbol(tmp))
                removeChar(tmp, '.');
            
            if (strcasecmp(tmp, symbolChecker) > 0) {
                if ((Sflag && (buf1.st_size - buf2.st_size) > 0) || !(buf1.st_size - buf2.st_size)) {
                    if (p == head) {
                        Node* n = (Node*)malloc(sizeof(Node));
                        
                        strcpy(n->file, name);
                        n->prev = NULL;
                        n->next = head;
                        head->prev = n;
                        head = n;
                        
                        return;
                    } else {
                        Node* n = (Node*)malloc(sizeof(Node));
                        
                        strcpy(n->file, name);
                        n->next = p;
                        n->prev = p->prev;
                        p->prev->next = n;
                        p->prev = n;
                        
                        return;
                    }
                }
            }
            p = p->next;
        }

        for (prev = head; prev->next; prev = prev->next);
        Node* n = (Node*)malloc(sizeof(Node));
        
        strcpy(n->file, name);
        n->next = NULL;
        prev->next = n;
        n->prev = prev;
        tail = n;
        
        return;
    }
}

// Delete List
void eliminate(void) {
    Node* tmp = head;
    
    for (;tmp->next;) {
        head = tmp->next;
        free(tmp);
        tmp = head;
    }
    
    free(tmp);
    head = NULL;
}

// Print File List in Directory
void print(int total, int argc, char *dirpath) {
    struct passwd *uid;
    struct group *gid;
    struct stat buf;
    struct tm *time;
    
    char path[256];
    char buffer[256];
    char linker[256];
    char subdir[256];
    char currdir[256];
    char subpath[256];
    char checkpath[256];
    
    int i = 0, j = 0, k = 0, m = 0;
    
    
    if (lflag || argc > 2) {
        getcwd(currdir, sizeof(currdir));
        
        while (currdir[k] != '\0')
            k++;
        
        while (k && currdir[k] != '/')
            k--;
        
        while (m < k) {
            subpath[m] = currdir[m];
            m++;
        }
        
        k = 0;
        while (dirpath[k] != '\0')
            k++;
        
        while (k && dirpath[k] != '/')
            k--;
        
        if (dirpath[k] == '/')
            k++;
        
        m = 0;
        while (dirpath[k] != '\0') {
            subdir[m] = dirpath[k];
            m++;
            k++;
        }
        
        strcat(checkpath, subpath);
        strcat(checkpath, "/");
        strcat(checkpath, subdir);
        
        lstat(checkpath, &buf);
        if (S_ISLNK(buf.st_mode))
            strcpy(currdir, checkpath);
        
        if (lflag || dflag > 1 || nfflag > 1 || fflag > 1) {
            printf("Directory path: %s\n", currdir);
            printf("total: %d\n", total);
        } else if (dflag > 1|| nfflag > 1|| fflag > 1)
            printf("Directory path: %s\n", currdir);
    }
    
    Node *p = head;
    
    if (rflag)
        while (p->next)
            p = p->next;

    while (p) {
        if ((lflag && aflag) || (lflag && !aflag && p->file[0] != '.')) {
            lstat(p->file, &buf);
            
            uid = getpwuid(buf.st_uid);
            gid = getgrgid(buf.st_gid);
            
            time = localtime(&buf.st_mtime);
            printf("%c%s ", fileType(buf.st_mode), permission(buf.st_mode));
            
            if (fileType(buf.st_mode) == 'l') {
                realpath(p->file, linker);
                
                while (linker[i] != '\0')
                    i++;
                
                while (linker[i] != '/')
                    i--;
                
                while (linker[i] != '\0') {
                    path[j] = linker[i+1];
                    i++;
                    j++;
                } path[j+1] = '\0';
                
                strcat(p->file, "->");
                strcat(p->file, path);
            }
            
            printf("%ld\t", buf.st_nlink);
            printf("%s\t", uid->pw_name);
            printf("%s\t", gid->gr_name);
            
            if (hflag)
                unitPrint(buf.st_size);
            else
                printf("%ld\t", buf.st_size);
            
            strftime(buffer, 255, "%b %d %H:%M", time);
            printf("%s\t", buffer);
        }
        
        if (aflag || (!aflag && p->file[0] != '.'))
            printf("%s\n", p->file);
        
        if (rflag)
            p = p->prev;
        else
            p = p->next;
    }
    
    if (excution != argc)
        printf("\n");
    
    return;
}

// Print Information of Files
void filePrint(char *filename) {
    struct passwd *uid;
    struct group *gid;
    struct stat buf;
    struct tm *time;
    
    char path[256];
    char buffer[256];
    char linker[256];
    
    int i = 0, j = 0;
    
    if ((lflag && aflag) || (lflag && !aflag && filename[0] != '.')) {
        lstat(filename, &buf);
        
        uid = getpwuid(buf.st_uid);
        gid = getgrgid(buf.st_gid);
        
        time = localtime(&buf.st_mtime);
        printf("%c%s ", fileType(buf.st_mode), permission(buf.st_mode));
        
        if (fileType(buf.st_mode) == 'l') {
            realpath(filename, linker);
            
            while (linker[i] != '\0')
                i++;
            
            while (linker[i] != '/')
                i--;
            
            while (linker[i] != '\0') {
                path[j] = linker[i+1];
                i++;
                j++;
            } path[j+1] = '\0';
            
            strcat(filename, "->");
            strcat(filename, path);
        }
        
        printf("%ld\t", buf.st_nlink);
        printf("%s\t", uid->pw_name);
        printf("%s\t", gid->gr_name);
        
        if (hflag)
            unitPrint(buf.st_size);
        else
            printf("%ld\t", buf.st_size);
        
        strftime(buffer, 255, "%b %d %H:%M", time);
        printf("%s\t", buffer);
    }
    
    if (aflag || (!aflag && filename[0] != '.'))
        printf("%s\n", filename);
}

// Print with Data Size Unit
void unitPrint(long int size) {
    int k = 0, flag = 0;
    char unit[4] = { 'K', 'M', 'G', 'T' };
    
    double unitCounter = (double)size;
    
    while (unitCounter > 1024) {
        unitCounter /= 1024;
        k++;
    }
    
    size = (int)unitCounter;
    unitCounter = (int)(unitCounter * 10);
    unitCounter = unitCounter/10;
    
    if (size * 10 == (int)(unitCounter * 10))
        flag = 1;
    
    int size_int = 0;
    
    if (!k) {
        size_int = (int)unitCounter;
        printf("%d\t", size_int);
    }
    
    if (flag) {
        size_int = (int)unitCounter;
        printf("%d%c\t", size_int, unit[k-1]);
    } else
        printf("%.1lf%c\t", unitCounter, unit[k-1]);
    
    return;
}

