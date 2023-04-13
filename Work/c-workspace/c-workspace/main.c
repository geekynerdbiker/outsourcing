//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <string.h>
//#include <dirent.h>
//#include <stdbool.h>
//#include <pwd.h>
//#include <grp.h>
//#include <time.h>
//#include <ctype.h>
//#include <fnmatch.h>
//#include <limits.h>
//#include <linux/limits.h>
//#include <libgen.h>
//
//
//static int aflag = 0; // use as static int option -a
//static int lflag = 0; // use as static int option -l
//static int Sflag = 0; // use as static int option -S
//static int rflag = 0; // use as static int option -r
//static int hflag = 0; // use as static int option -h
//
////////////////////////////////////////////////////////////////////
//// distinguish filetype and permission informations                //
//// =============================================================//
//// read, write, execute                                         //
//// Purpose: open directory and read file names                    //
////////////////////////////////////////////////////////////////////
//char fileType(mode_t m) { // identify filetypes
//    if(S_ISREG(m))
//        return('-');
//    else if(S_ISDIR(m))
//        return ('d');
//    else if(S_ISCHR(m))
//        return ('c');
//    else if(S_ISBLK(m))
//        return ('b');
//    else if(S_ISLNK(m))
//        return ('l');
//    else if(S_ISFIFO(m))
//        return ('p');
//    else if(S_ISSOCK(m))
//        return ('s');
//}
//
// char* perm(mode_t m) { // parsing permission
//    int i;
//    static char ret[10] = "---------";
//    for(i = 0; i < 3; i++) {
//        if(m & (S_IRUSR >> i*3))
//            ret[i*3] = 'r'; //read permission
//        else
//            ret[i*3] = '-';
//        if(m & (S_IWUSR >> i*3))
//            ret[i*3+1] = 'w'; //write permission
//        else
//            ret[i*3+1] = '-';
//        if(m & (S_IXUSR >> i*3))
//            ret[i*3+2] = 'x'; //execute permission
//        else
//            ret[i*3+2] = '-';
//    }
//    if(m & S_ISUID) {
//        if(m & S_IXUSR)
//            ret[2] = 's';
//        else
//            ret[2] = 'S';
//    }
//    if(m & S_ISGID) {
//        if(m & S_IXGRP)
//            ret[5] = 's';
//        else
//            ret[5] = 'S';
//    }
//
//    return (ret);
//}
////////////////////////////////////////////////////////////////////////////////////
////                                                                                //
////lsoption - Lists files and directories based on the given options.            //
////==============================================================================//
////This function takes a name (file or directory) as its parameter and lists the    //
////                                                                                //
////contents of the directory (if it is a directory) or the file itself (if it is    //
////                                                                                //
////a file), taking into account the specified flags (such as '-a' to include        //
////                                                                                //
////hidden files). If the given name does not correspond to a valid file or        //
////                                                                                //
////directory, the function returns -1.                                            //
////                                                                                //
////@param name The name of the file or directory to list the contents of.        //
////                                                                                //
////@return int Returns 0 on success or -1 on failure.                            //
////////////////////////////////////////////////////////////////////////////////////
//int lsoption (const char *name){ // the ls option function
//    struct dirent *d;
//    DIR *dp;
//    int count = 0;
//    struct dirent **namelist;
//    struct dirent *temp;
//    struct stat statbuf;
//    char* pathname;
//    pathname = malloc(1024);
//    DIR* dirp;
//    struct dirent* entry;
//    int ino;
//    bool sym = false;
//    long total = 0;
//    bool found = 0;
//
//    if((dp = opendir(name)) == NULL) //if it is NULL return -1
//    {
//        if (lstat(name, &statbuf)== 0) {
//            printf("%s\n", name);// print the name of the file
//            return (0);
//        }
//        else{
//            return (-1);
//        }
//
//    }
//
//        // count the number of files in the directory
//        while(d = readdir(dp)){
//            if (d->d_ino == 0) continue;
//            if (aflag > 0) {
//                count++;
//            }
//            else if((d->d_name[0] != '.') && (aflag == 0)){
//                count++;
//            }
//        }
//
//        // allocate memory for an array of dirent pointers
//        namelist = (struct dirent **) malloc(count * sizeof(struct dirent *));
//
//        // fill the array with dirent pointers
//        rewinddir(dp); //rewind
//        int i = 0;
//        while(d = readdir(dp)){
//            if (d->d_ino == 0) continue;
//            if (aflag > 0) {
//                namelist[i++] = d;
//            }
//            else if((d->d_name[0] != '.') && (aflag == 0)){
//                namelist[i++] = d;
//            }
//        }
//        if(strcmp(name,".")!=0){
//        printf("Directory path : %s\n",name);}
//
//        //////////////////////////////////////////////////////////////////
//        // read directory and bubble sort                                //
//        // =============================================================//
//        // sort by ASCII number with bubble sort algorithm               //
//        //////////////////////////////////////////////////////////////////
//        // perform bubble sorts
//        for (int i = 0; i < count-1; i++) {
//            for (int j = 0; j < count-i-1; j++) {
//
//                if (aflag > 0) { // if there is a option
//                    if(namelist[j]->d_name=="."){continue;}
//                    if(namelist[j]->d_name==".."){continue;}
//                    int k = 0;
//                    int l = 0;
//                    if(namelist[j]->d_name[k] == '.'){ // if it is hidden file make it compare with the next alphabet
//                        k++;
//                    }
//                    if(namelist[j+1]->d_name[l] == '.'){ // if it is hidden file make it compare with the next alphabet
//                        l++;
//                    }
//                    if(strcasecmp(namelist[j]->d_name, namelist[j+1]->d_name) == 0){ // if both have same alphabet and only different cases
//                        if(strcmp(namelist[j]->d_name, namelist[j+1]->d_name) > 0){
//                            temp = namelist[j]; // move to temp
//                            namelist[j] = namelist[j+1]; // sort
//                            namelist[j+1] = temp;// sort
//                        }
//                    }
//                    else{
//                        char upper_a[128] = {};  // get ready to convert in to upper case
//                        char upper_b[128] = {};  // get ready to convert in to upper case
//                        int count_a = 0;
//                        int count_b = 0;
//                        while(namelist[j]->d_name[k]){
//                            upper_a[count_a] = toupper(namelist[j]->d_name[k]); // convert in to upper case
//                            k++;
//                            count_a++;}
//                        while(namelist[j+1]->d_name[l]){
//                            upper_b[count_b] = toupper(namelist[j+1]->d_name[l]); //convert in to upper case
//                            l++;
//                            count_b++;}
//                        if(strcmp(upper_a, upper_b) > 0){ // now compare converted alphabet
//                            temp = namelist[j]; // move to temp
//                            namelist[j] = namelist[j+1]; // sort
//                            namelist[j+1] = temp;// sort
//                        }
//                    }
//                }
//                else { //if a flag is 0
//                    char upper_a[128] = {};  // get ready to convert in to upper case
//                    char upper_b[128] = {};  // get ready to convert in to upper case
//                    int count_a = 0;
//                    int count_b = 0;
//                    int k = 0;
//                    int l = 0;
//                    if(strcasecmp(namelist[j]->d_name, namelist[j+1]->d_name) == 0){ // if both have same alphabet and only different cases
//                        if(strcmp(namelist[j]->d_name, namelist[j+1]->d_name) > 0){
//                            temp = namelist[j]; // move to temp
//                            namelist[j] = namelist[j+1]; // sort
//                            namelist[j+1] = temp;// sort
//                        }
//                    }
//                    else{
//                    while(namelist[j]->d_name[k]){
//                        upper_a[count_a] = toupper(namelist[j]->d_name[k]); // convert in to upper case
//                        k++;
//                        count_a++;}
//                    while(namelist[j+1]->d_name[l]){
//                        upper_b[count_b] = toupper(namelist[j+1]->d_name[l]); //convert in to upper case
//                        l++;
//                        count_b++;}
//                    if (strcmp(upper_a, upper_b) > 0) { // if upper a is bigger, swap
//                        temp = namelist[j];
//                        namelist[j] = namelist[j+1];
//                        namelist[j+1] = temp;
//                    }
//                    }
//                }
//
//            }
//        }
//        if (Sflag > 0) {
//            for (int i = 0; i < count-1; i++) {
//                for (int j = 0; j < count-i-1; j++){
//                // Get file sizes for the two files being compared
//                char file_a[PATH_MAX], file_b[PATH_MAX];
//                strcpy(file_a, name);
//                strcat(file_a, "/");
//                strcat(file_a, namelist[j]->d_name);
//                strcpy(file_b, name);
//                strcat(file_b, "/");
//                strcat(file_b, namelist[j+1]->d_name);
//                struct stat st_a, st_b;
//                lstat(file_a, &st_a);
//                lstat(file_b, &st_b);
//
//                // Swap the file entries if the file size of file_a is less than file_b
//                if (st_a.st_size < st_b.st_size) { // sort by Size in descending order like the original -S option
//                    temp = namelist[j];
//                    namelist[j] = namelist[j+1];
//                    namelist[j+1] = temp;
//                }
//                }
//            }
//        }
//        if (rflag > 0) {
//            // Reverse the namelist array
//            for (int i = 0; i < count / 2; i++) {
//                temp = namelist[i];
//                namelist[i] = namelist[count - i - 1];
//                namelist[count - i - 1] = temp;
//            }
//        }
//
//        if (lflag == 0) { //if lflag is 0
//        // print the sorted file names
//            for (int i = 0; i < count; i++) {
//                printf("%s\n", namelist[i]->d_name);// print the name of the file sorted in ASCII order
//            }
//        }
//        else { // if l flag is not 0
//
//            for (int i = 0 ; i < count; i++){
//            lstat(namelist[i]->d_name, &statbuf);
//            total += statbuf.st_blocks;} // add number of blocks
//
//            printf("total : %ld\n", total/2); // print number of total(number of 512B blocks allocated)
//            printf("Directory path : %s\n", getcwd(pathname, 1024));   //print Directory path
//            for (int i =0 ; i < count; i++) {
//                lstat(namelist[i]->d_name, &statbuf);
//                printf("%c%s    ", fileType(statbuf.st_mode), perm(statbuf.st_mode)); // print file type , permission
//                printf("%ld    ", statbuf.st_nlink); // print number of links
//                printf("%s    %s    ", getpwuid(statbuf.st_uid)->pw_name, getgrgid(statbuf.st_gid)->gr_name); // print uid and gid
//                if(hflag>0){ // if hflag is on , change format file size to human-readable format
//                    if (statbuf.st_size < 1024) {
//                        printf("%ld    ", statbuf.st_size ); // file size
//                    }
//                    else if (statbuf.st_size < 1024 * 1024) {
//                        printf("%.1fK    ", (float)statbuf.st_size / 1024); // file size in K
//                    }
//                    else if (statbuf.st_size < 1024 * 1024 * 1024) {
//                        printf("%.1fM    ", (float)statbuf.st_size / (1024 * 1024)); // file size in M
//                    }
//                    else {
//                        printf("%.1fG    ", (float)statbuf.st_size / (1024 * 1024 * 1024)); // file size in G
//                    }
//                }
//                else{
//                    printf("%ld    ", statbuf.st_size); // file size
//                }
//                printf("%.12s    ", ctime(&statbuf.st_mtime) +4); // print modified time
//                printf("%s\n", namelist[i]->d_name);// print the name of the file
//            }
//            closedir(dp); // close directory
//            return (0);
//        }
//}
//////////////////////////////////////////////////////////////////////////////////////
//// Function: process_wildcard                                                      //
////================================================================================//
//// Purpose: Processes a wildcard pattern in a file or directory name and lists      //
//// the matching files and directories. If print_dir_content is true,              //
//// the contents of the matching directories are also listed.                      //
////                                                                                  //
//// Parameters:                                                                      //
//// - wildcard_pattern: A string containing the wildcard pattern to match.          //
//// - name: The name of the directory to search for matching files and directories.//
//// - print_dir_content: A boolean flag indicating whether to list the contents    //
//// of the matching directories or not.                                              //
////                                                                                  //
//// Returns: void                                                                  //
//// /////////////////////////////////////////////////////////////////////////////////
//void process_wildcard(const char *wildcard_pattern, const char *name, bool print_dir_content) {
//    struct dirent *d; // Declare a pointer to a dirent structure, which will hold directory entry information
//    DIR *dp; // Declare a pointer to a DIR structure, which represents a directory stream
//    struct dirent **namelist; // Declare a pointer to an array of dirent pointers, which will store the matching directory entries
//    int count = 0; // Initialize a counter for the number of files matching the wildcard pattern
//    // Open the specified directory (name) and assign the directory stream to the DIR pointer (dp)
//    if ((dp = opendir(name)) == NULL) {
//        return;
//    }
//    // Count the number of files in the directory
//    while ((d = readdir(dp))) {
//        if (fnmatch(wildcard_pattern, d->d_name, FNM_NOESCAPE | FNM_PATHNAME | FNM_PERIOD) == 0) {
//            count++;
//        }
//    }
//    // Allocate memory for an array of dirent pointers
//    namelist = (struct dirent **)malloc(count * sizeof(struct dirent *));
//
//    // Fill the array with dirent pointers matching the wildcard pattern
//    rewinddir(dp);
//    int i = 0;
//    while ((d = readdir(dp))) {
//        if (fnmatch(wildcard_pattern, d->d_name, FNM_NOESCAPE | FNM_PATHNAME | FNM_PERIOD) == 0) {
//            namelist[i++] = d;
//        }
//    }
//    // Sort the array of dirent pointers in ASCII order using the bubble sort algorithm
//    struct dirent *temp;
//    for (int i = 0; i < count - 1; i++) {
//        for (int j = 0; j < count - i - 1; j++) {
//            if (strcmp(namelist[j]->d_name, namelist[j + 1]->d_name) > 0) {
//                temp = namelist[j];
//                namelist[j] = namelist[j + 1];
//                namelist[j + 1] = temp;
//            }
//        }
//    }
//    struct stat statbuf;
//    // Iterate through the sorted array of dirent pointers (namelist)
//    for (int i = 0; i < count; i++) {
//        // Print the name of the matching directory entry
//        if(S_ISDIR(statbuf.st_mode))
//        printf("%s\n", namelist[i]->d_name);
//
//        // If the matched entry is a directory, and print_dir_content is true, print the files inside
//        if (print_dir_content) {
//            char sub_path[1024];
//            strcpy(sub_path, name);
//            strcat(sub_path, "/");
//            strcat(sub_path, namelist[i]->d_name);
//            // Declare a stat structure to hold file information and retrieve the information using lstat
//            struct stat statbuf;
//            if (lstat(sub_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
//                // If lstat is successful and the matched entry is a directory, print the directory's contents
//
//                lsoption(sub_path); // Call the lsoption function (not provided in the code snippet) to list the contents of the directory
//            }
//        }
//    }
//     // Free the allocated memory for the namelist array and close the directory stream
//    free(namelist);
//    closedir(dp);
//}
////////////////////////////////////////////////////////////////////////////////////////////////////
//// Function: main                                                                                //
////==============================================================================================//
//// Purpose: The main function for a custom 'ls' command implementation. It accepts command-line    //
//// arguments and options, such as '-a', '-l', '-S', '-r', and '-h', to customize the            //
//// output format and contents. The program also supports wildcard patterns in file and            //
//// directory names.                                                                                //
////                                                                                                //
//// Parameters:                                                                                    //
//// - argc: The number of command-line arguments passed to the program.                            //
//// - argv: An array of strings containing the command-line arguments.                            //
////                                                                                                //
//// Returns: int (exit status)                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////
//int main(int argc, char **argv)
//{
//    char pathname[128]; // to save name of the file
//
//    int c = 0;
//    int getopt(int argc, char * const argv[], const char *optstring);
//    extern char *optarg;
//    extern int optind, opterr, optopt;
//    struct stat statbuf;
//    while((c = getopt(argc, argv, "alSrh")) != -1) // get options a, l, S, r ,h
//    {
//            switch(c)
//            {
//                    case 'a':           //a flag on
//                            aflag++;
//                            break;
//                    case 'l':           //l flag on
//                            lflag++;
//                            break;
//                    case 'S':           //S flag on
//                            Sflag++;
//                            break;
//                    case 'r':           //r flag on
//                            rflag++;
//                            break;
//                    case 'h' :            //h flag on
//                            hflag++;
//                            break;
//            }
//    }
//    // Initialize a flag to check if a wildcard pattern is used in the command-line arguments
//    bool wildcard_used = false;
//    // Iterate through the command-line arguments (starting from the second one as the first is the program name)
//    for (int i = 1; i < argc; i++) {
//        // Check if the argument is not an option (doesn't start with '-') and contains a wildcard character (*, ?, or [)
//        if (argv[i][0] != '-' && strchr(argv[i], '*') != NULL || strchr(argv[i], '?') != NULL || strchr(argv[i], '[') != NULL) {
//            wildcard_used = true;
//            // Call the process_wildcard function with the wildcard pattern, the current directory (.), and the print_dir_content flag set to true
//            if(strchr(argv[i], '/') != NULL){
//                for(int k=1;k<100;k++){
//                    argv[i][strlen(argv[i])-k]=0;
//                    if(argv[i][strlen(argv[i])-k]=='/')break;
//                }
//                process_wildcard(argv[i], argv[i], true);
//            }
//            else process_wildcard(argv[i], ".", true);
//
//        }
//
//    }
//
//        char *swap = "";
//        if (optind == argc) { // if there is no path name
//            strcpy(pathname, "."); //copy pwd to pathname
//            lsoption(pathname); //print result
//        }
//        else {
//            if(argc > 2){
//                for (int i = 1; i < argc-1 ; i++){
//                    if(strcmp(argv[i],argv[i+1])>0){
//                        swap = argv[i];
//                        argv[i] = argv[i+1];
//                        argv[i+1] = swap;
//                    }
//                }
//            }
//
//
//            for (int i = 1; i < argc ; i++) {
//                if (argv[i][0] != '-'){      // if it is a pathname
//                strcpy(pathname, argv[i]);} // copy pathname
//                lsoption(pathname); // print result with the pathname
//            }
//        }
//
//
//
//}

