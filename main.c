#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#define NOTES_FILE "notes.txt"





char *get_notes_path() {
        static char first_part_of_path[512];
        static char second_path_of_path[512];
        static char result_path[1024];
        char path[512];

        char *home = getenv("HOME");
        if (!home) home = "";

        if (home[strlen(home) - 1] == '/') {
                snprintf(path, sizeof(path), "%s%s", home, NOTES_FILE);
        } else {
                snprintf(path, sizeof(path), "%s/%s", home, NOTES_FILE);
        }

        int number_of_slash = 0;
        int first_index = 0;
        int second_index = 0;

        first_part_of_path[0] = '\0';
        second_path_of_path[0] = '\0';

        for (int i = 0; path[i] != '\0'; i++) {
                first_part_of_path[first_index++] = path[i];
                first_part_of_path[first_index] = '\0';
                if (path[i] == '/') {
                        number_of_slash++;
                        if (number_of_slash == 3) break;
                }
        }

        if (first_part_of_path[first_index - 1] != '/') {
                strcat(first_part_of_path, "/notes-cli/");
        } else {
                strcat(first_part_of_path, "notes-cli/");
        }

        for (int i = first_index; path[i] != '\0'; i++) {
                second_path_of_path[second_index++] = path[i];
                second_path_of_path[second_index] = '\0';
        }

        strcpy(result_path, first_part_of_path);
        strcat(result_path, second_path_of_path);

        return result_path;
}

void check_notes_path(char *path) {
        struct stat st;
        char dir[512];
        strcpy(dir, path);
        char *last_slash = strrchr(dir, '/');
        if (last_slash) *last_slash = '\0';

        if (stat(dir, &st) != 0) mkdir(dir, 0755);

        if (stat(path, &st) == 0 && (st.st_mode & S_IFREG)) {
                return;
        } else {
                FILE *f = fopen(path, "w");
                if (f) fclose(f);
        }
}



int main(int argc, char *argv[]) {
        check_notes_path(get_notes_path());
        if (argc < 2 || argv[1][0] == '\0') {
                puts("Please use arguments");
                return 1;
        }

        if (strcmp(argv[1], "add") == 0) {
                puts("Under maintence!");
        }

        if (strcmp(argv[1], "show-path") == 0) {
                const char *path = get_notes_path();
                printf("%s", path);
        }
}