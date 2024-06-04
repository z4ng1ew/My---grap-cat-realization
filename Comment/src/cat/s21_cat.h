#ifndef s21_cat
#define s21_cat

#include <getopt.h>  // Для функции getopt_long и структуры option
#include <stdio.h>   // Для функций ввода-вывода, таких как printf, fopen, getc, putchar и fprintf
#include <stdlib.h>  // Для функций управления памятью и завершения программы, таких как exit
#include <string.h>  // Для работы со строками, например, для функции strcmp

struct flags;

//функция парсинга
int get_opt(int argc, char **argv, struct flags *flag);

//функция обработки файла и текстового потока
void cat(char *path, struct flags);

//флаги
int s(struct flags flag, int *prev, int *ch, int *str);
void b(struct flags flag, int *prev, int *ch, int *current_line);
void n(struct flags flag, int *prev, int *current_line);
void E(struct flags flag, int *prev, int *ch);
void T(struct flags flag, int *ch);
void v(struct flags flag, int *ch);

#endif



