#include "My_s21_cat.h"
//заменить название структуры на тайп деф
struct Opt {
    int b, e, E, v, n, s, t, T, d, err_f;
};

int main (int ac, char **av){
    struct Opt fl = {0};
//заменить название структуры на тайп деф

    int ind_f;
    ind_f = get_opt(ac, av, &fl);

    if(fl.err_f == 1) {
        printf("s21_cat: illegal option -- %c", optopt);
    } else {
        while (ind_f < (ac)){
            char *file_p; //path
            file_p = av[ind_f];

            dispFile(file_p, fl); //cat

            ind_f++;
        }
    }
    return 0;
}




int get_opt(int ac, char **av, struct Opt *flags) { //flag
  int f = 0;
  int opt_ind = 0;
  //заменить название структуры на тайп деф
  static struct Opt l_opt[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {0, 0, 0, 0}};

    while(flags->err_f == 0 &)

}
