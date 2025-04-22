#include "dir_tree.h"

void watchUrDesktop()
{
    const char *user = getenv("USERPROFILE"); // C:\Users\YourName
    char desktop[512];
    if (user)
    {
        snprintf(desktop, sizeof(desktop), "%s\\Desktop", user);
    }
    else
    {
        exit(0);
    }

    // test dir_tree
    list_dir_recursive(desktop);
    // print_filenames_array();
    write_list_txt();
}

int main(void)
{
    watchUrDesktop();
    for (int i = 0; i < file_index; i++)
    {
        printf("%s: %s\n", filenames[i][0], filenames[i][1]);
    }
    // step1. build a new directory
    // step2. entry all the file into new directory
    // step3. leave a txt with filename
    // step4. delete the all the file on Desktop
    return 0;
}
