#include "My_s21_cat.h"

struct Opt {
    int b, e, E, v, n, s, t, T, d, def_f;
};

int main (int ac, int **av){
    struct Opt str_fl = {0};
    
    int ind_f;

    ind_f = get_opt(ac, av, &str_fl);

    if (str_fl.def_f == 1) {
        printf("s21_cat: illegal optiont -- %c \nНеверное значение опций, используйте " "флаги beEvnstT\n", optopt);
        exit(1);
    }



    return 0;
}