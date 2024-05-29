#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cat.h"

#include <ctype.h>

void print_usage() {
    printf("Usage: s21_cat [OPTION] [FILE]...\n");
    printf("Options:\n");
    printf("  -b, --number-nonblank   number non-blank lines\n");
    printf("  -e                      display $ at end of each line\n");
    printf("  -n, --number            number all lines\n");
    printf("  -s, --squeeze-blank     suppress repeated empty lines\n");
    printf("  -t                      display TAB characters as ^I\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int flag_b = 0, flag_e = 0, flag_n = 0, flag_s = 0, flag_t = 0;
    
    while ((opt = getopt(argc, argv, "benst")) != -1) {
        switch (opt) {
            case 'b':
                flag_b = 1;
                break;
            case 'e':
                flag_e = 1;
                break;
            case 'n':
                flag_n = 1;
                break;
            case 's':
                flag_s = 1;
                break;
            case 't':
                flag_t = 1;
                break;
            default:
                print_usage();
                return EXIT_FAILURE;
        }
    }

    if (optind == argc) {
        fprintf(stderr, "No files provided\n");
        return EXIT_FAILURE;
    }

    for (int i = optind; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "Cannot open file: %s\n", argv[i]);
            continue;
        }
        process_file(file, flag_b, flag_e, flag_n, flag_s, flag_t);
        fclose(file);
    }

    return EXIT_SUCCESS;
}

void process_file(FILE *file, int flag_b, int flag_e, int flag_n, int flag_s, int flag_t) {
    int line_number = 1;
    int last_line_empty = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        if (flag_s) {
            if (isspace(line[0])) {
                if (last_line_empty) continue; // Пропускаем дублирующие пустые строки
                last_line_empty = 1;
            } else {
                last_line_empty = 0;
            }
        }

        // Вывод номера строки
        if ((flag_b && strlen(line) > 1) || flag_n) {
            printf("%6d\t", line_number++);
        }

        // Вывод содержимого строки с учетом опций
        for (char *p = line; *p; p++) {
            if (flag_t && *p == '\t') {
                printf("^I");
            } else if (flag_e && *p == '\n') {
                printf("$\n");
            } else {
                putchar(*p);
            }
        }

        // Обработка случая, когда строка не заканчивается новой строкой
        if (flag_e && line[strlen(line) - 1] != '\n') {
            printf("$");
        }
    }
}