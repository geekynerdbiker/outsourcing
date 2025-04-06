#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

typedef struct {
    unsigned char *data;
    size_t size;
} fragment_t;

static fragment_t *fragments = NULL;
static size_t fragments_count = 0;
static size_t largest_index = 0;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    char *subdir_path;
} thread_arg_t;

static void *thread_func(void *arg);
static void traverse_directory(const char *path);
static int parse_bin_filename(const char *filename);
static void store_fragment_data(int index, const unsigned char *data, size_t size);

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <directory> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *start_dir = argv[1];
    const char *output_file = argv[2];

    DIR *dirp = opendir(start_dir);
    if (!dirp) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    pthread_t thread_ids[256];
    int thread_count = 0;

    while ((entry = readdir(dirp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_type == DT_DIR) {
            size_t needed = strlen(start_dir) + 1 + strlen(entry->d_name) + 1;
            char *full_path = malloc(needed);
            snprintf(full_path, needed, "%s/%s", start_dir, entry->d_name);

            thread_arg_t *targ = malloc(sizeof(thread_arg_t));
            targ->subdir_path = full_path;

            if (pthread_create(&thread_ids[thread_count], NULL, thread_func, targ) != 0) {
                perror("pthread_create");
                free(targ->subdir_path);
                free(targ);
                continue;
            }
            thread_count++;
        }
    }

    closedir(dirp);

    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    FILE *outfp = fopen(output_file, "wb");
    if (!outfp) {
        perror("fopen (output_file)");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i <= largest_index; i++) {
        if (fragments[i].data && fragments[i].size > 0) {
            fwrite(fragments[i].data, 1, fragments[i].size, outfp);
        }
    }
    fclose(outfp);

    for (size_t i = 0; i < fragments_count; i++) {
        free(fragments[i].data);
    }
    free(fragments);

    return EXIT_SUCCESS;
}

static void *thread_func(void *arg)
{
    thread_arg_t *targ = (thread_arg_t *)arg;
    traverse_directory(targ->subdir_path);

    free(targ->subdir_path);
    free(targ);

    return NULL;
}

static void traverse_directory(const char *path)
{
    DIR *dp = opendir(path);
    if (!dp) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        size_t needed = strlen(path) + 1 + strlen(entry->d_name) + 1;
        char *child_path = malloc(needed);
        snprintf(child_path, needed, "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            traverse_directory(child_path);
            free(child_path);
        }
        else if (entry->d_type == DT_REG) {
            int idx = parse_bin_filename(entry->d_name);
            if (idx >= 0) {
                FILE *fp = fopen(child_path, "rb");
                if (fp) {
                    fseek(fp, 0, SEEK_END);
                    long fsize = ftell(fp);
                    fseek(fp, 0, SEEK_SET);

                    if (fsize > 0) {
                        unsigned char *buffer = malloc(fsize);
                        fread(buffer, 1, fsize, fp);
                        fclose(fp);

                        store_fragment_data(idx, buffer, fsize);

                    } else {
                        fclose(fp);
                    }
                }
            }
            free(child_path);
        }
        else {
            free(child_path);
        }
    }

    closedir(dp);
}

static int parse_bin_filename(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || strcmp(dot, ".bin") != 0) {
        return -1;
    }

    size_t len = dot - filename;
    if (len == 0) {
        return -1;
    }

    char *number_str = malloc(len + 1);
    strncpy(number_str, filename, len);
    number_str[len] = '\0';

    int idx = -1;
    for (size_t i = 0; i < len; i++) {
        if (number_str[i] < '0' || number_str[i] > '9') {
            free(number_str);
            return -1;
        }
    }

    idx = atoi(number_str);
    free(number_str);
    return idx;
}

static void store_fragment_data(int index, const unsigned char *data, size_t size)
{
    pthread_mutex_lock(&lock);

    if ((size_t)index >= fragments_count) {
        size_t new_count = (size_t)index + 1;
        fragment_t *tmp = realloc(fragments, new_count * sizeof(fragment_t));
        if (!tmp) {
            fprintf(stderr, "realloc failed\n");
            pthread_mutex_unlock(&lock);
            abort();
        }
        fragments = tmp;

        for (size_t i = fragments_count; i < new_count; i++) {
            fragments[i].data = NULL;
            fragments[i].size = 0;
        }
        fragments_count = new_count;
    }

    if ((size_t)index > largest_index) {
        largest_index = (size_t)index;
    }

    fragments[index].data = (unsigned char *)data;
    fragments[index].size = size;

    pthread_mutex_unlock(&lock);
}
