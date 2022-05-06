/** 
 * This file contains the file system functions that you need to implement.
 * You can define helper functions in this file.
 *
 * Remember to remove the initial statements in the functions.
 * They are only used so that your semi-finished codes can compile.
 */

#include <iostream>
#include <cstring>
#include "file_sys.h"
#include "utils.h"
using namespace std;

int createFile(Dir *dir, const char *name, unsigned int size, Tag tag)
{
    File *f = (File *)malloc(sizeof(File));
    
    if (name == NULL) return 1;
    if (strcmp(name, ".") == 0 && strlen(name) == 1) return 2;
    else if (strcmp(name, "..") == 0 && strlen(name) == 2) return 2;
    else {
        for (int i = 0; i < strlen(name); i++) {
            if (!(name[i] >= '0' && name[i] <= '9'))
                continue;
            if (!(name[i] >= 'a' && name[i] <= 'z'))
                continue;
            if (!(name[i] >= 'A' && name[i] <= 'Z'))
                continue;
            if (name[i] == '.' || name[i] == '-' || name[i] == '_')
                continue;
            return 2;
        }
    }
    
    strcpy(f->name, name);
    f->size = size;
    f->tag = tag;
    f->parent = NULL;
    f->next = NULL;
    
    File * subfile = dir->subfile;
    
    if (subfile == NULL) {
        subfile = f;
    } else {
        while (subfile->next != NULL) {
            if (strcmp(subfile->name, name) == 0)
                return 3;
            subfile = subfile->next;
        }
        subfile->next = f;
    }
    
    return 0;
}

int createDir(Dir *dir, const char *name)
{
    Dir *d = (Dir *)malloc(sizeof(Dir));
    
    if (name == NULL) return 1;
    if (strcmp(name, ".") == 0 && strlen(name) == 1) return 2;
    else if (strcmp(name, "..") == 0 && strlen(name) == 2) return 2;
    else {
        for (int i = 0; i < strlen(name); i++) {
            if (!(name[i] >= '0' && name[i] <= '9'))
                continue;
            if (!(name[i] >= 'a' && name[i] <= 'z'))
                continue;
            if (!(name[i] >= 'A' && name[i] <= 'Z'))
                continue;
            if (name[i] == '.' || name[i] == '-' || name[i] == '_')
                continue;
            return 2;
        }
    }
    
    strcpy(d->name, name);
    
    d->parent = dir;
    d->next = NULL;
    d->subdir = NULL;
    d->subfile = NULL;
    dir->next = d;
    
    Dir* subdir = dir->subdir;
    
    if (subdir == NULL) {
        subdir = d;
    } else {
        while (subdir->next != NULL) {
            if (strcmp(subdir->name, name) == 0)
                return 3;
            subdir = subdir->next;
        }
        subdir->next = d;
    }
    
    return 0;
}

int deleteFile(Dir *dir, const char *name)
{
    File * subfile = dir->subfile;
    
    if (name == NULL) return 1;
    while (subfile != NULL) {
        if (strcmp(subfile->name, name) == 0) {
            free(subfile);
        
            return 0;
        }
    }
    return 2;
}

int deleteDir(Dir *dir, const char *name, bool recursive)
{
    Dir* subdir = dir->subdir;
    if (name == NULL) return 1;
    while (subdir != NULL) {
        if (strcmp(subdir->name, name) == 0) {
            if (subdir->subdir == NULL && subdir->subfile == NULL)
                free(subdir);
            else if (recursive)
                free(subdir);
            
            return 0;
        }
    }
    return 2;
}

unsigned int getSize(const Dir *dir)
{
    unsigned int size = 0;
    
    Dir *subdir = dir->subdir;
    File *subfile = dir->subfile;
    
    while (subfile != NULL) {
        size += subfile->size;
        subfile = subfile->next;
    }
    
    while (subdir != NULL) {
        File *subfile = subdir->subfile;
        
        while (subfile != NULL) {
            size += subfile->size;
            subfile = subfile->next;
        }
        subdir = subdir->next;
    }
    
    return size;
}

const File **filesOfTag(const Dir *dir, Tag tag, unsigned int &length)
{
    length = 0;     // Remove these two lines after you finish.
    return NULL;    // ....
}

int moveFile(File *tgt, Dir *dest)
{
    return -1;     // Remove this line after you finish.
}

int moveDir(Dir *tgt, Dir *dest)
{
    return -1;      // Remove this line after you finish.
}
