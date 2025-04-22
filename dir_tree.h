#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_FILES 1024
#define MAX_NAME_LEN 256
#define MAX_SIZE_LEN 32

char filenames[MAX_FILES][2][MAX_NAME_LEN]; // [index][0: name, 1: size]
int file_index = 0;

static inline void list_dir_recursive(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == 0)
        {
            if (S_ISDIR(st.st_mode))
            {
                list_dir_recursive(full_path); // Recursively go into subdirectory
            }
            else
            {
                // Store filename and size as strings
                snprintf(filenames[file_index][0], MAX_NAME_LEN, "%s", full_path);
                snprintf(filenames[file_index][1], MAX_SIZE_LEN, "%ld", st.st_size);
                file_index++;
            }
        }
    }

    closedir(dir);
}

static inline void print_filenames_array()
{
    printf("char *filenames[][2] = {\n");
    for (int i = 0; i < file_index; i++)
    {
        printf("    {\"%s\", \"%s\"},\n", filenames[i][0], filenames[i][1]);
    }
    printf("};\n");
}

static inline void write_list_txt()
{
    FILE *fp = fopen("list.txt", "w");
    if (!fp)
    {
        perror("fopen");
        return;
    }

    for (int i = 0; i < file_index; i++)
    {
        fprintf(fp, "%s: %s\n", filenames[i][0], filenames[i][1]);
    }

    fclose(fp);
    printf("> list.txt written successfully in current directory.\n");
}
