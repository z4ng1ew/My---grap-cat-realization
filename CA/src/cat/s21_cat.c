#include "s21_cat.h"

struct flags {
  int bflag;
  int eflag;
  int Eflag;
  int vflag;
  int nflag;
  int sflag;
  int tflag;
  int Tflag;
  int defaultflag;
};

int main(int argc, char **argv) {  //основная функция
  //создаем переменную которая является структурой типа данных flags и обнуляем значения
  //argc является сокращением от "argument count", что в переводе с английского означает "количество аргументов".







  struct flags option = {0}; //создаёт переменную option типа struct flags и инициализирует её - 0-ми. Синтаксис {0} используется для инициализации всех членов структуры нулями. все флаги (bflag, ...) в структуре option будут установлены в 0, что обычно означает, что никакие опции не активированы.

  //Когда вы создаете переменную option типа struct flags, вы резервируете память для этой переменной в соответствии с размером структуры struct flags.

  int number_file;  // индекс обрабатываемого элемента
  // присваиваем значение индексу файла через return optind
  number_file = get_opt(argc, argv, &option);
  if (option.defaultflag == 1) {
    printf(
        "s21_cat: illegal option -- %c \nНеверное значение опций, используйте "
        "флаги beEvnstT\n",
        optopt);
    exit(1);
  } else {
    while (number_file < (argc)) {  // если индекс файла меньше, чем количество
      char *path;  // создаем переменную пути к файлу
      path = argv[number_file];  // записываем путь к файлу по индексу аргумента
      cat(path, option);  // обрабатываем через функцию наш файл и флаги
      number_file++;  //переходим к следующему файлу для обработки
    }
  }
  return 0;
}

int get_opt(int argc, char **argv, struct flags *flag) {  //функция парсинга
  int c = 0;
  int option_index = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};
  //бесконечный цикл, который будет выполняться до тех пор, пок гетопn
  while (flag->defaultflag == 0 &&
         (c = getopt_long(argc, argv, "beEvnstT", long_options,
                          &option_index)) != -1) {
    opterr = 0;
    //указатель на переменную, в которую будет сохранен индекс найденной

    //сам парсинг четез гетопт

    //выход из цикла после того как гетопт дойдет до конца строки ввода

    switch (c) {  // меняем значение флагов в структуре flags
      case 'b':
        flag->bflag = 1;
        break;
      case 'e':
        flag->Eflag = 1;
        flag->vflag = 1;
        break;
      case 'E':
        flag->Eflag = 1;
        break;
      case 'v':
        flag->vflag = 1;
        break;
      case 'n':
        flag->nflag = 1;
        break;
      case 's':
        flag->sflag = 1;
        break;
      case 't':
        flag->Tflag = 1;
        flag->vflag = 1;
        break;
      case 'T':
        flag->Tflag = 1;
        break;
      default:
        flag->defaultflag = 1;
        break;
    }
  }
  if (flag->bflag) flag->nflag = 0;
  return optind;  // это индекс следующего обрабатываемого элемента argv
}

void cat(char *path, struct flags flag) {
  FILE *filename;
  filename = fopen(path, "r");

  if (filename) {
    int ch;
    int prev;  // текущий символ и предыдущий символ
    int current_line = 1;  // счетчик для нумерации строки
    int str = 0;

    for (prev = '\n'; (ch = getc(filename)) != EOF; prev = ch) {
      if (s(flag, &prev, &ch, &str)) continue;
      b(flag, &prev, &ch, &current_line);
      n(flag, &prev, &current_line);
      E(flag, &prev, &ch);
      T(flag, &ch);
      v(flag, &ch);

      putchar(ch);
    }
  } else
    fprintf(stderr, "No such file or directory\n");
  fclose(filename);
}

int s(struct flags flag, int *prev, int *ch, int *str) {
  int f = 0;
  if (flag.sflag == 1 && (*prev == '\n' && *ch == '\n')) {
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
  if (flag.bflag == 1) {
    if (*prev == '\n' && *ch != '\n') {
      printf("%*d\t", 6, *current_line);
      *current_line = *current_line + 1;
    }
  }
}

void n(struct flags flag, int *prev, int *current_line) {
  if (flag.nflag == 1) {
    if (*prev == '\n') {
      printf("%*d\t", 6, *current_line);
      *current_line = *current_line + 1;
    }
  }
}

void E(struct flags flag, int *prev, int *ch) {
  if (flag.Eflag == 1) {
    if (*prev != '\0' && *ch == '\n') {
      if (*prev == '\n' && flag.bflag) {
        printf("      \t$");
      } else {
        int dollar = '$';
        putc(dollar, stdout);
      }
    }
  }
}

void T(struct flags flag, int *ch) {
  if (flag.Tflag == 1) {
    if (*ch == '\t') {
      printf("^");
      *ch = 'I';
    }
  }
}

void v(struct flags flag, int *ch) {
  if (flag.vflag == 1) {
    if (*ch > 127 && *ch < 160) printf("M-^");
    if ((*ch < 32 && *ch != '\n' && *ch != '\t') || *ch == 127) printf("^");
    if ((*ch < 32 || (*ch > 126 && *ch < 160)) && *ch != '\n' && *ch != '\t')
      *ch = *ch > 126 ? *ch - 128 + 64 : *ch + 64;
  }
}






/*
Да, верно. В языке C ключевое слово `struct` используется как для определения новых типов данных, так и для создания переменных этих типов.

1. **Определение типа данных**: Вы можете использовать `struct` для создания новых пользовательских типов данных, которые могут содержать несколько различных членов (полей). Например:
   ```c
   struct person {
       char name[50];
       int age;
   };
   ```
   Здесь `struct person` - это определенный пользователем тип данных, который содержит два члена: `name` и `age`.

2. **Создание переменных**: Вы также можете создавать переменные этого типа, используя определенный пользователем тип данных `struct`. Например:
   ```c
   struct person employee;
   ```
   Здесь `employee` - это переменная типа `struct person`, которая содержит члены `name` и `age`.

Таким образом, `struct` в C действует как ключевое слово для определения пользовательских типов данных и для создания переменных этих типов.













После того как вы создали переменную типа `struct person`, содержащую члены `name` и `age`, вы можете работать с этими членами следующим образом:

1. **Присвоить значения членам**: Вы можете присвоить значения каждому из членов `name` и `age`:
   ```c
   strcpy(employee.name, "John Doe");
   employee.age = 30;
   ```

2. **Использовать значения членов**: Вы можете использовать значения членов, например, для печати или других операций:
   ```c
   printf("Имя: %s\n", employee.name);
   printf("Возраст: %d\n", employee.age);
   ```

3. **Манипулировать значениями членов**: Вы можете изменять значения членов по вашему усмотрению:
   ```c
   employee.age++;
   ```

4. **Передавать структуры в функции**: Вы можете передавать переменные типа `struct person` в функции, чтобы использовать их значения или изменить их:
   ```c
   void printPerson(struct person p) {
       printf("Имя: %s\n", p.name);
       printf("Возраст: %d\n", p.age);
   }
   ```

5. **Использовать структуры в массивах или динамической памяти**: Вы можете создавать массивы структур или выделять память для структур динамически, чтобы хранить несколько экземпляров вашего типа данных `struct person`.

*/