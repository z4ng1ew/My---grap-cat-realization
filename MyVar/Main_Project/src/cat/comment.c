#include "s21_cat.h"

struct flags {
 int b, e, E, v, n, s, t, T, d, err_f;
};


int main(int countArg, char **arrPoint) { 
  struct flags option = {0};
  int exit_status = 0;
  int number_file = get_opt(countArg, arrPoint, &option);

  if (option.err_f == 1) {
    printf("Пожалуйста, используйте следующие опции: beEvnstT\n");
    exit_status = 1;
  } else {
    while (number_file < countArg) {  
      char *path = arrPoint[number_file]; 
      cat(path, option);  
      number_file++;  
    }
  }

  return exit_status;
}

int get_opt(int countArg, char **arrPoint, struct flags *flag) {
  int c = 0;
  int option_index = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};

  while ((c = getopt_long(countArg, arrPoint, "beEvnstT", long_options, &option_index)) != -1) {
    handle_option(c, flag);
  }
  if (flag->b) flag->n = 0;
  return optind;
}



void handle_option(int c, struct flags *flag) {
    if (c == 'b') {
        flag->b = 1;
    } else if (c == 'e') {
        flag->E = 1;
        flag->v = 1;
    } else if (c == 'E') {
        flag->E = 1;
    } else if (c == 'v') {
        flag->v = 1;
    } else if (c == 'n') {
        flag->n = 1;
    } else if (c == 's') {
        flag->s = 1;
    } else if (c == 't') {
        flag->T = 1;
        flag->v = 1;
    } else if (c == 'T') {
        flag->T = 1;
    } else {
        flag->err_f = 1;
    }
}


void process_file(FILE *filename, struct flags flag) {
  int ch, prev = '\n', current_line = 1, str = 0;
  while ((ch = getc(filename)) != EOF) {
    if (s(flag, &prev, &ch, &str)) continue;
    b(flag, &prev, &ch, &current_line);
    n(flag, &prev, &current_line);
    E(flag, &prev, &ch);
    T(flag, &ch);
    v(flag, &ch);
    putchar(ch);
    prev = ch;
  }
}

void cat(char *path, struct flags flag) {
  FILE *filename = fopen(path, "r");
  if (!filename) {
    fprintf(stderr, "No such file or directory\n");
    return;
  }
  process_file(filename, flag);
  fclose(filename);
}


int s(struct flags flag, int *prev, int *ch, int *str) {
  int f = 0;
  if (flag.s == 1 && (*prev == '\n' && *ch == '\n')) {
    *str = *str + 1;
    if (*str > 1) {
      f = 1;
    }
  } else {
    *str = 0;
  }
  return f;
}


void b(struct flags flag, int *prev, int *ch, int *current_line) {
  if (flag.b == 1) {
    if (*prev == '\n' && *ch != '\n') {
      printf("%*d\t", 6, *current_line);
      *current_line = *current_line + 1;
    }
  }
}

void n(struct flags flag, int *prev, int *current_line) {
  if (flag.n == 1) {
    if (*prev == '\n') {
      printf("%*d\t", 6, *current_line);
      *current_line = *current_line + 1;
    }
  }
}

void E(struct flags flag, int *prev, int *ch) {
  if (flag.E == 1) {
    if (*prev != '\0' && *ch == '\n') {
      if (*prev == '\n' && flag.b) {
        printf("      \t$");
      } else {
        int dollar = '$';
        putc(dollar, stdout);
      }
    }
  }
}

void T(struct flags flag, int *ch) {
  if (flag.T == 1) {
    if (*ch == '\t') {
      printf("^");
      *ch = 'I';
    }
  }
}

void v(struct flags flag, int *ch) {
  if (flag.v == 1) {
    if ((*ch < 32 && *ch != '\n' && *ch != '\t') || *ch == 127)
      printf("^%c", *ch ^ 64);
    else if (*ch >= 128 && *ch < 160)
      printf("M-^%c", *ch ^ 128 ^ 64);
    else if (*ch >= 160) {
      if (*ch == 255) {
        printf("M-^?"); // Обработка символа 255
      } else {
        printf("M-%c", *ch - 128);
      }
    }
  }
}