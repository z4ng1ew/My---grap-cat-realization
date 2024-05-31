#ifndef s21_grep
#define s21_grep

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags;

void get_opt(int argc, char *argv[]);
void grep(int counter_files, char *argv[]);
void fflag();
void sym_eof();
void oflag(int match, regex_t reg, regmatch_t first, int counter_files,
           char *argv[]);
int main(int argc, char *argv[]);

#endif