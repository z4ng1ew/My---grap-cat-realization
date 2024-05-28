#ifndef CAT_H
#define CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 4096 // Определение максимальной длины строки


void process_file(FILE *file, int flag_b, int flag_e, int flag_n, int flag_s, int flag_t);

#endif 