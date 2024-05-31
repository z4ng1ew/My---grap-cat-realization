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
    printf("  -E                      display $ at end of each line\n");
    printf("  -n, --number            number all lines\n");
    printf("  -s, --squeeze-blank     suppress repeated empty lines\n");
    printf("  -t                      display TAB characters as ^I\n");
    printf("  -T                      display TAB characters as ^I\n");
    printf("  -v                      use ^ and M- notation, except for LFD and TAB\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int flag_b = 0, flag_e = 0, flag_E = 0, flag_n = 0, flag_s = 0, flag_t = 0, flag_T = 0, flag_v = 0;
    
    while ((opt = getopt(argc, argv, "benstTEv")) != -1) {
        switch (opt) {
            case 'b':
                flag_b = 1;
                break;
            case 'e':
                flag_e = 1;
                flag_v = 1;
                break;
            case 'E':
                flag_E = 1;
                break;
            case 'n':
                flag_n = 1;
                break;
            case 's':
                flag_s = 1;
                break;
            case 't':
                flag_t = 1;
                flag_v = 1;
                break;
            case 'T':
                flag_T = 1;
                break;
            case 'v':
                flag_v = 1;
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
        process_file(file, flag_b, flag_e, flag_E, flag_n, flag_s, flag_t, flag_T, flag_v);
        fclose(file);
    }

    return EXIT_SUCCESS;
}

void process_file(FILE *file, int flag_b, int flag_e, int flag_E, int flag_n, int flag_s, int flag_t, int flag_T, int flag_v) {
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
        for (unsigned char *p = (unsigned char *)line; *p; p++) {
            if (flag_T && *p == '\t') {
                printf("^I");
            } else if (flag_t && *p == '\t') {
                printf("^I");
            } else if (flag_e && *p == '\n') {
                printf("$");
            } else if (flag_E && *p == '\n') {
                printf("$");
            } else if (flag_v && (*p < 32 || (*p >= 127 && *p < 160))) {
                if (*p < 32 && *p != '\n' && *p != '\t') {
                    printf("^%c", *p + 64);
                } else if (*p >= 127 && *p < 160) {
                    printf("M-^%c", *p - 64);
                } else {
                    putchar(*p);
                }
            } else {
                putchar(*p);
            }
        }

        // Обработка случая, когда строка не заканчивается новой строкой
        if ((flag_e || flag_E) && line[strlen(line) - 1] != '\n') {
            printf("$");
        }

        putchar('\n'); // Добавляем символ новой строки после каждой строки
    }
}