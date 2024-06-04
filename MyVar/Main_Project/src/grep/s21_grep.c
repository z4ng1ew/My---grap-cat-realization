#include "s21_grep.h"

#define BUFFER 10000

struct flags {
  int eflag;
  int iflag;
  int vflag;
  int cflag;
  int lflag;
  int nflag;
  int hflag;
  int sflag;
  int oflag;
  int fflag;
  int lflag_file_match;
  int nflag_count_str;
  char arg_namefile[BUFFER];
  char o_namefile[BUFFER];
  char arg_fflag[BUFFER];
  char str_file[BUFFER];
  char str_arguments[BUFFER];
  char str_arguments_2[BUFFER];
} options = {0};


int main(int argc, char *argv[]) {
  if (argc == 1) {
    // Выводим сообщение о правильном использовании, если не переданы аргументы
    printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
    printf("Try 'grep --help' for more information.\n");
    return 1; // Возвращаем код ошибки
  }

  get_opt(argc, argv);
  int counter_files = argc - optind;
  while (optind < argc) {
    grep(counter_files, argv);
    optind++;
  }
  return 0;
}

void get_opt(int argc, char *argv[]) {
  int opt = 0;

  while ((opt = getopt_long(argc, argv, "e:ivclnhsof:", NULL, 0)) != -1) {
    switch (opt) {
      case 'e':
        options.eflag = 1;
        strcat(options.str_arguments, optarg);
        strcat(options.str_arguments, "|");
        break;
      case 'i':
        options.iflag = 1;
        break;
      case 'v':
        options.vflag = 1;
        break;
      case 'c':
        options.cflag = 1;
        break;
      case 'l':
        options.lflag = 1;
        break;
      case 'n':
        options.nflag = 1;
        break;
      case 'h':
        options.hflag = 1;
        break;
      case 's':
        options.sflag = 1;
        break;
      case 'o':
        options.oflag = 1;
        break;
      case 'f':
        options.fflag = 1;
        strcpy(options.arg_namefile, optarg);
        fflag();
        break;
      default:
        printf("неверное значение опции\n");
        break;
    }
  }
  if (!options.eflag && !options.fflag) {
    if (argc > optind) {
      strcat(options.str_arguments, argv[optind]);
    }
    optind++;
  }
  if (options.eflag || options.fflag) {
    options.str_arguments[strlen(options.str_arguments) - 1] = '\0';
  }
}

void grep(int counter_files, char *argv[]) {
  FILE *file;
  regex_t reg;
  regmatch_t first;
  int counter_str = 0;
  int flags_regular = REG_EXTENDED;
  if (options.iflag) {
    flags_regular = REG_EXTENDED | REG_ICASE;
  }
  if (!options.fflag) {
    regcomp(&reg, options.str_arguments, flags_regular);
  } else {
    regcomp(&reg, options.str_arguments_2, flags_regular);  // fflag
  }
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    while ((fgets(options.str_file, BUFFER, file)) != NULL) {
      int match = regexec(&reg, options.str_file, 1, &first, 0);
      options.nflag_count_str++;
      if (options.vflag) match = !match;
      if (!match && options.str_file[0] != '\n') counter_str++;
      if (!match && options.lflag) options.lflag_file_match = 1;
      if (!match && options.nflag) {
        if (counter_files == 1)
          printf("%d:%s", options.nflag_count_str, options.str_file);
        if (counter_files > 1)
          printf("%s:%d:%s", argv[optind], options.nflag_count_str,
                 options.str_file);
        if (counter_files > 0) sym_eof();
      }
      if (options.oflag == 1) oflag(match, reg, first, counter_files, argv);
      if (!match && !options.cflag && !options.lflag && !options.nflag &&
          !options.oflag) {
        if (counter_files == 1 || options.hflag) printf("%s", options.str_file);
        if (counter_files > 1 && !options.hflag)
          printf("%s:%s", argv[optind], options.str_file);
        if (counter_str > 0) sym_eof();
      }
    }
    if (options.cflag == 1) {
      if (counter_files == 1) printf("%d\n", counter_str);
      if (counter_files > 1) printf("%s:%d\n", argv[optind], counter_str);
    }
    if (options.lflag == 1 && options.lflag_file_match == 1)
      printf("%s\n", argv[optind]);
    options.nflag_count_str = 0;
    fclose(file);
  } else if (!options.sflag)
    fprintf(stderr, "No such file or directory\n");
  regfree(&reg);
}

void fflag() {
  FILE *file2;
  file2 = fopen(options.arg_namefile, "rb");
  if (file2 != NULL) {
    while (!feof(file2)) {
      if (fgets(options.arg_fflag, BUFFER, file2) != NULL) {
        strcat(options.str_arguments_2, options.arg_fflag);
        if (options.str_arguments_2[strlen(options.str_arguments_2) - 1] != '|')
          strcat(options.str_arguments_2, "|");
      }
    }
    options.str_arguments_2[strlen(options.str_arguments_2) - 1] = '\0';
    fclose(file2);
  }
}

void oflag(int match, regex_t reg, regmatch_t first, int counter_files,
           char *argv[]) {
  if (!match) {
    if (counter_files == 1)
      printf("%.*s\n", (int)(first.rm_eo - first.rm_so),
             options.str_file + first.rm_so);
    if (counter_files > 1)
      printf("%s:%.*s\n", argv[optind], (int)(first.rm_eo - first.rm_so),
             options.str_file + first.rm_so);
    char *remaining = options.str_file + first.rm_eo;
    while (!(regexec(&reg, remaining, 1, &first, 0))) {
      if (counter_files == 1)
        printf("%.*s\n", (int)(first.rm_eo - first.rm_so),
               remaining + first.rm_so);
      if (counter_files > 1)
        printf("%s:%.*s\n", argv[optind], (int)(first.rm_eo - first.rm_so),
               remaining + first.rm_so);
      remaining = remaining + first.rm_eo;
    }
  }
}

void sym_eof() {
  if (options.str_file[strlen(options.str_file) - 1] != '\n' &&
      *options.str_file != '\n' && !options.fflag) {
    printf("%c", '\n');
    *options.str_file = '\n';
  }
}