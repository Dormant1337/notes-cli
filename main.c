#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#define NOTES_FILE "notes.txt"


char *get_notes_path();

int show_list(int argc, char *argv[]) {
        FILE *f = fopen(get_notes_path(), "r");
        if (!f) {
                perror("fopen");
                return 1;
        }
        char line[512];
        int i = 1;
        while (fgets(line, sizeof(line), f)) {
                printf("[%d]: %s", i++, line);
        }
        fclose(f);
        return 0;
}

int clear_notes(int argc, char *argv[]) {
        FILE *f = fopen(get_notes_path(), "w");
        if (!f) {
                perror("fopen");
                return 1;
        }
        fclose(f);
        puts("All notes cleared!");
        return 0;
}

int delete_note(int argc, char *argv[]) {
        if (argc < 3) {
                puts("Please provide a note number to delete");
                return 1;
        }
        FILE *f = fopen(get_notes_path(), "r");
        if (!f) {
                perror("fopen");
                return 1;
        }
        FILE *temp = fopen("temp.txt", "w");
        if (!temp) {
                perror("fopen");
                fclose(f);
                return 1;
        }
        char line[512];
        int note_to_delete = atoi(argv[2]);
        int i = 1;
        while (fgets(line, sizeof(line), f)) {
                if (i != note_to_delete) {
                        fputs(line, temp);
                }
                i++;
        }
        fclose(f);
        fclose(temp);
        remove(get_notes_path());
        rename("temp.txt", get_notes_path());
        printf("Note [%s] with content: %s deleted!", argv[2], line);
        return 0;
}


int add_note(int argc, char *argv[]) {
        if (argc < 3) {
                puts("Please provide a note to add");
                return 1;
        }
        FILE *f = fopen(get_notes_path(), "a");
        if (!f) {
                perror("fopen");
                return 1;
        }
        for (int i = 2; i < argc; i++) {
                fprintf(f, "%s ", argv[i]);
        }
        fprintf(f, "\n");
        fclose(f);
        puts("Note added!");
        return 0;
}

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
        char *path = get_notes_path();
        check_notes_path(get_notes_path());
        if (argc < 2 || argv[1][0] == '\0') {
                puts("Please use arguments");
                return 1;
        }

        if (strcmp(argv[1], "--add") == 0) {             add_note(argc, argv);
        } else if (strcmp(argv[1], "--list") == 0) {     show_list(argc, argv);
        } else if (strcmp(argv[1], "--delete") == 0) {   delete_note(argc, argv);
        } else if (strcmp(argv[1], "--clear") == 0) {    clear_notes(argc, argv);
        } else { puts("Invalid command. Use --add, --list, --delete, or --clear."); return 1; }
}