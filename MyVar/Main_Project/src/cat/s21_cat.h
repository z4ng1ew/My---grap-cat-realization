#ifndef s21_cat
#define s21_cat

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags;

int get_opt(int argc, char **argv, struct flags *flag);
void cat(char *path, struct flags);
void handle_option(int c, struct flags *flag);

int s(struct flags flag, int *prev, int *ch, int *str);
void b(struct flags flag, int *prev, int *ch, int *current_line);
void n(struct flags flag, int *prev, int *current_line);
void E(struct flags flag, int *prev, int *ch);
void T(struct flags flag, int *ch);
void v(struct flags flag, int *ch);

void process_file(FILE *filename, struct flags flag);

#endif