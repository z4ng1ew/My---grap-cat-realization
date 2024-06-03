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
  int defaultflag; //используется для обработки нераспознанных опций командной строки (ошибок ввода)
};

int main(int argc, char **argv) {  //основная функция
  //создаем переменную которая является структурой типа данных flags и обнуляем значения
  //argc является сокращением от "argument count", что в переводе с английского означает "количество аргументов".

  /*
  В функции main() параметр char **argv используется для передачи массива строк, который содержит аргументы командной строки. В C параметр argv является массивом указателей на строки (char *). Обычно аргументы командной строки представляют собой строки, и каждый элемент массива argv указывает на одну из этих строк.

  Почему используется двойной указатель (char **argv)? Потому что argv — это массив указателей, а в C массивы передаются по указателю на первый элемент. Таким образом, char **argv означает, что это указатель на указатель на char, то есть указатель на первый элемент массива указателей на строки.

  Это делает возможным доступ к каждому аргументу командной строки по отдельности. Например, argv[0] содержит имя исполняемого файла, а argv[1], argv[2], и так далее, содержат остальные аргументы, переданные при запуске программы.
  */



  struct flags option = {0}; //создаёт переменную option типа struct flags и инициализирует её - 0-ми. Синтаксис {0} используется для инициализации всех членов структуры нулями. все флаги (bflag, ...) в структуре option будут установлены в 0, что обычно означает, что никакие опции не активированы.

  //Когда вы создаете переменную option типа struct flags, вы резервируете память для этой переменной в соответствии с размером структуры struct flags.

  int number_file;  // индекс обрабатываемого элемента. Он нужен для:
  // 1 Инициализация структуры и парсинг опций
  // 2 Проверка на неправильные опции:
  // 3 Обработка файлов:
  // присваиваем значение индексу файла через return optind


  number_file = get_opt(argc, argv, &option); //  number_file - хранит 2-ой индек из массива аргументов команной строки (то есть 3-ий елемент, то есть путь к файлу )


  //   argc (argument count) — это количество аргументов командной строки, включая имя самой программы.
  // argv (argument vector) — это массив строк (char **), где каждая строка является отдельным аргументом командной строки.
  // Пример вызова программы:


  // ./s21_cat -b tests/empty_lines_b_s.txt  - пример команды
  
  // Здесь:

  // argv[0] — это строка "./s21_cat", которая представляет имя самой программы.
  // argv[1] — это строка "-b", которая представляет первый аргумент (флаг -b).
  // argv[2] — это строка "tests/empty_lines_b_s.txt", которая представляет второй аргумент (путь к файлу).





  /* Когда вы запускаете программу с командой:
  ```sh
  ./s21_cat -b tests/empty_lines_b_s.txt
  ```

### Аргументы командной строки

- **argc** (argument count) содержит количество аргументов командной строки. В данном случае:


  - `argc = 3` (потому что у нас три аргумента: `./s21_cat`, `-b`, `tests/empty_lines_b_s.txt`) !!!!

- **argv** (argument vector) — массив строк, содержащий сами аргументы командной строки. В данном случае:
  - `argv[0] = "./s21_cat"`
  - `argv[1] = "-b"`
  - `argv[2] = "tests/empty_lines_b_s.txt"`

### Обработка аргументов командной строки

Когда выполняется следующая строка:
```c
number_file = get_opt(argc, argv, &option);
```

происходит следующее:

1. **Вызов функции `get_opt`**:
   - Функция `get_opt` принимает `argc`, `argv` и указатель на структуру `flags` (`&option`).

2. **Анализ аргументов командной строки**:
   - Внутри функции `get_opt` используется `getopt_long` для анализа аргументов командной строки.
   - Аргументы, которые начинаются с `-` (например, `-b`), рассматриваются как флаги.
   - Флаг `-b` распознается и устанавливает соответствующий флаг в структуре `flags`:
     ```c
     case 'b':
       flag->bflag = 1;
       break;
     ```

3. **Возвращение индекса первого необработанного аргумента**:
   - `get_opt` возвращает индекс первого аргумента, не являющегося флагом. В данном случае, это индекс `2`, потому что аргумент с индексом `2` — это `"tests/empty_lines_b_s.txt"`.

### Итог

- **number_file**: после вызова `get_opt`, переменная `number_file` содержит значение `2`, что указывает на первый аргумент, не являющийся флагом (`tests/empty_lines_b_s.txt`).
- **option**: структура `option` теперь содержит установленные флаги. В данном случае, `option.bflag = 1`.

### Пример использования

После вызова `get_opt`, ваш основной цикл в `main` начинает обрабатывать файлы, начиная с индекса `number_file`:
```c
while (number_file < argc) {
  char *path = argv[number_file]; // Получаем путь к файлу
  cat(path, option); // Обрабатываем файл с учетом установленных флагов
  number_file++; // Переходим к следующему файлу
}
```
В данном случае `path` будет равен `"tests/empty_lines_b_s.txt"`.

### Резюме

- **argc**: количество аргументов командной строки (включая имя программы).
- **argv**: массив строк, содержащий аргументы командной строки.
- **number_file**: индекс первого аргумента, не являющегося флагом, который будет использоваться для обработки файлов.
- **option**: структура, содержащая информацию о установленных флагах командной строки.
  */



  if (option.defaultflag == 1) {
    //Эта строка проверяет, установлен ли флаг defaultflag в структуре option. Флаг defaultflag устанавливается в 1, если в командной строке обнаружена неверная опция. Это происходит в функции get_opt, в блоке default:



    printf(
        "s21_cat: illegal option -- %c \nНеверное значение опций, используйте "
        "флаги beEvnstT\n",
        optopt);
    exit(1);
    //Если defaultflag равен 1, то вызывается printf для вывода сообщения об ошибке.
    // Сообщение содержит текст: "s21_cat: illegal option -- %c \nНеверное значение опций, используйте флаги beEvnstT\n".
    //%c заменяется на значение переменной optopt, которая содержит неправильную опцию, вызвавшую ошибку.




/*
optopt — это глобальная переменная, предоставляемая функцией getopt_long (или getopt), которая содержит значение символа, вызвавшего ошибку при разборе командной строки. Использование optopt позволяет программе сообщить пользователю, какая именно опция была некорректной.


exit(1) завершает выполнение программы с кодом ошибки 1. Код ошибки 1 обычно означает, что программа завершилась с ошибкой. Завершение программы с кодом ошибки полезно для других программ или скриптов, которые могут запускать эту программу и проверять ее завершение на наличие ошибок.


Это не дублирование, потому что:

optopt просто предоставляет информацию о том, что именно пошло не так.
exit(1) прекращает выполнение программы, сигнализируя об ошибке.
*/

  } else {
    while (number_file < (argc)) {  // если индекс файла меньше, чем количество аргументов командной строки argc



    // while (number_file < (argc)): Это цикл while, который будет выполняться, пока переменная number_file (которая предположительно инициализирована нулем до этого кода) меньше, чем количество аргументов командной строки (argc).

      char *path;  // создаем переменную пути к файлу

      //char *path;: Здесь создается указатель на строку path, который будет использоваться для хранения пути к файлу.


      path = argv[number_file];  // записываем путь к файлу по индексу аргумента

      //path = argv[number_file];: Здесь переменной path присваивается значение аргумента командной строки по индексу number_file. Это позволяет получить путь к файлу, который нужно обработать на текущей итерации цикла.


      cat(path, option);  // обрабатываем через функцию наш файл и флаги

      //cat(path, option);: Эта строка вызывает функцию cat (предположительно представляющую собой функцию для вывода содержимого файла), передавая ей путь к файлу path и опции option.


      number_file++;  //переходим к следующему файлу для обработки

      // number_file++;: После того как файл был обработан, переменная number_file увеличивается на единицу, чтобы перейти к следующему файлу в списке аргументов командной строки.
    }
  }








  return 0;
}









int get_opt(int argc, char **argv, struct flags *flag) {  //функция парсинга (ПАРСЕР)

// get_opt() выполняет парсинг опций командной строки и устанавливает соответствующие флаги в структуре flags




  /*
  argc: количество аргументов командной строки.
  argv: массив строк, содержащий аргументы командной строки.
  flag: указатель на структуру flags, которая, вероятно, содержит информацию о флагах, установленных пользователем.
  */

  int c = 0;

  //c используется для хранения символа опции

  /*
  В main создается структура flag и инициализируется нулями.
  
  Вызывается функция get_opt, которая заполняет структуру flag в соответствии с переданными аргументами командной строки.
  
  После вызова get_opt выводятся значения флагов.
  
  Таким образом, переменная c помогает определить, какая опция была передана, и установить соответствующие флаги в структуре flag.
  */



  int option_index = 0; 
  
// хранит номер позиции текущей длинной опции в массиве long_options
//Таким образом, код позволяет программе распознавать длинные параметры и соответствующим образом устанавливать флаги для дальнейшей обработки.
//Условие с четырьмя нулями в массиве long_options ({0, 0, 0, 0}) используется для обозначения конца массива. Это необходимо для функций, работающих с массивами структур, таких как getopt_long, чтобы знать, где массив заканчивается.
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}}; // массив структур option

  //Поля has_arg, flag, и val установлены в 0, потому что в данном случае опции не принимают аргументов и не используют флаги.
  //Последний элемент {0, 0, 0, 0} служит как маркер конца массива long_options. Это общепринятый способ показать, что больше опций в массиве нет.
  

  //!!!!!!
  //Каждая структура в этом массиве представляет одну опцию командной строки. Вот какие поля есть в каждой структуре:

  // name - это имя длинной опции командной строки.
  // has_arg - указывает, принимает ли эта опция аргумент. В этом случае 0 указывает на то, что опция не принимает аргумент.
  // flag - это указатель на целочисленную переменную, которая устанавливается равной val, если опция обнаружена.
  // val - это значение, которое возвращается в случае, если эта опция обнаружена.

  //!!!!!!!!!


  /*
  Пояснение структуры long_options
  Структура long_options определяет параметры, которые могут быть переданы в командной строке. Каждый элемент массива является структурой struct option, которая имеет следующие поля:

  name: Имя длинного параметра.
  has_arg: Указывает, принимает ли параметр аргумент:
  no_argument (или 0): Параметр не принимает аргумент.
  required_argument (или 1): Параметр требует аргумент.
  optional_argument (или 2): Параметр может принимать аргумент, но это не обязательно.
  flag: Указатель на переменную, в которую будет записано значение параметра. Если это значение NULL, то результат функции getopt_long будет равен val.
  val: Значение, которое будет возвращено, если параметр найден.
  */


 /*
 Давайте разберем структуру long_options 

{"number-nonblank", 0, 0, 'b'}:

name: "number-nonblank" - это имя длинного параметра.
has_arg: 0 - это no_argument, что означает, что параметр не принимает аргумент.
flag: 0 - в данном случае это NULL, поэтому результатом будет значение val.
val: 'b' - это значение, которое будет возвращено, если параметр найден.
{"number", 0, 0, 'n'}:

name: "number".
has_arg: 0.
flag: 0.
val: 'n'.
{"squeeze-blank", 0, 0, 's'}:

name: "squeeze-blank".
has_arg: 0.
flag: 0.
val: 's'.
{0, 0, 0, 0}:
 
 */




/*
Флаги b, n и s в структуре long_options соответствуют параметрам, которые могут быть переданы в командной строке, а также флагам, которые они представляют:

b соответствует параметру --number-nonblank, который, вероятно, отвечает за нумерацию только непустых строк.
n соответствует параметру --number, который, вероятно, отвечает за нумерацию всех строк.
s соответствует параметру --squeeze-blank, который, вероятно, отвечает за устранение сжатия пустых строк.
Эти флаги используются в структуре long_options для их идентификации при разборе аргументов командной строки.

*/



  /*
  ПРИМЕРЕ КОМАНДЫ   ./s21_cat --squeeze-blank  --number -ev  empty_lines_b_s.txt

  Давай разберем этот ответ на примере команды ./s21_cat --squeeze-blank --number -ev empty_lines_b_s.txt:

  name: Имя длинного параметра - это строка, которая определяет параметр. Например, для опций --squeeze-blank и --number имя длинного параметра будет "squeeze-blank" и "number" соответственно.

  has_arg: Это поле указывает, принимает ли параметр аргумент. Посмотрим на примере:

  --squeeze-blank: Эта опция не требует аргумента, поэтому has_arg будет равно no_argument.
  --number: Эта опция также не требует аргумента, так что has_arg также будет равно no_argument.
  -e и -v: Эти опции не являются длинными параметрами, но для иллюстрации has_arg в их случае равно no_argument, так как они просто указывают на присутствие опции, а не  наличие дополнительного аргумента.
  flag: Это указатель на переменную, в которую будет записано значение параметра. Если flag установлен в NULL, то результатом функции getopt_long будет значение поля   val. Например:

  --squeeze-blank: Можно установить флаг, указывающий на то, что опция обнаружена.
  --number: Аналогично, можно установить флаг для обозначения обнаружения опции.
  -e и -v: В случае коротких опций флаг обычно используется для установки переменной, которая будет использоваться для указания на то, что опция обнаружена.
  val: Это значение, которое будет возвращено, если параметр найден. Для каждой опции, кроме длинных параметров, будет использоваться короткий символ. Например:

  --squeeze-blank может иметь значение 's'.
  --number может иметь значение 'n'.
  -e и -v также могут иметь соответствующие значения.
  Надеюсь, это объяснение помогло лучше понять структуру long_options и как ее использовать для обработки параметров командной строки.
  */




 /*
 Давай разберем этот ответ на примере команды `./s21_cat --squeeze-blank --number -ev empty_lines_b_s.txt`:

1. `name`: Имя длинного параметра - это строка, которая определяет параметр. Например, для опций `--squeeze-blank` и `--number` имя длинного параметра будет `"squeeze-blank"` и `"number"` соответственно.

2. `has_arg`: Это поле указывает, принимает ли параметр аргумент. Посмотрим на примере:
   - `--squeeze-blank`: Эта опция не требует аргумента, поэтому `has_arg` будет равно `no_argument`.
   - `--number`: Эта опция также не требует аргумента, так что `has_arg` также будет равно `no_argument`.
   - `-e` и `-v`: Эти опции не являются длинными параметрами, но для иллюстрации `has_arg` в их случае равно `no_argument`, так как они просто указывают на присутствие опции, а не наличие дополнительного аргумента.

3. `flag`: Это указатель на переменную, в которую будет записано значение параметра. Если `flag` установлен в NULL, то результатом функции `getopt_long` будет значение поля `val`. Например:
   - `--squeeze-blank`: Можно установить флаг, указывающий на то, что опция обнаружена.
   - `--number`: Аналогично, можно установить флаг для обозначения обнаружения опции.
   - `-e` и `-v`: В случае коротких опций флаг обычно используется для установки переменной, которая будет использоваться для указания на то, что опция обнаружена.

4. `val`: Это значение, которое будет возвращено, если параметр найден. Для каждой опции, кроме длинных параметров, будет использоваться короткий символ. Например:
   - `--squeeze-blank` может иметь значение `'s'`.
   - `--number` может иметь значение `'n'`.
   - `-e` и `-v` также могут иметь соответствующие значения.

Надеюсь, это объяснение помогло лучше понять структуру `long_options` и как ее использовать для обработки параметров командной строки.
 */









  //бесконечный цикл, который будет выполняться до тех пор, пока гет опп..
  while (flag->defaultflag == 0 &&
         (c = getopt_long(argc, argv, "beEvnstT", long_options,  &option_index)) != -1) {
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



// первоначальная версия функции -v
// void v(struct flags flag, int *ch) {
//   if (flag.vflag == 1) {
//     if (*ch > 127 && *ch < 160) printf("M-^");
//     if ((*ch < 32 && *ch != '\n' && *ch != '\t') || *ch == 127) printf("^");
//     if ((*ch < 32 || (*ch > 126 && *ch < 160)) && *ch != '\n' && *ch != '\t')
//       *ch = *ch > 126 ? *ch - 128 + 64 : *ch + 64;
//   }
// }



void v(struct flags flag, int *ch) {
  if (flag.vflag == 1) {
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









/*
В контексте всего кода:

1. **`argc`**: Этот параметр представляет собой количество аргументов командной строки, переданных программе при ее запуске. Это целое число, которое указывает на количество строк в массиве `argv`. Обычно `argc` содержит как минимум значение `1`, так как первым аргументом является имя самой программы.

2. **`argv`**: Это массив строк, представляющий собой аргументы командной строки, переданные программе при ее запуске. Каждый элемент массива `argv` является строкой (массивом символов), представляющей отдельный аргумент командной строки. Первый элемент `argv[0]` обычно содержит имя самой программы, а остальные элементы содержат дополнительные аргументы, переданные пользователем при запуске программы.

Таким образом, `argc` и `argv` позволяют программе получить доступ к аргументам командной строки, переданным ей при запуске. Весь массив `argv` доступен программе для использования, а `argc` указывает на количество доступных аргументов.

*/



/*  struct - это и тип данных и тип переменных 

В C переменные могут быть созданы с типом структуры данных. В данном случае, struct flags - это пользовательский тип данных, который определен с использованием ключевого слова struct. Когда вы создаете переменную option типа struct flags, вы резервируете память для этой переменной в соответствии с размером структуры struct flags.

Что касается того, что такая конструкция возвращает, то при инициализации переменной с помощью = {0}, все поля (или члены) структуры struct flags будут установлены в ноль. В этом случае, переменная option будет содержать экземпляр структуры struct flags, где все флаги будут установлены в ноль.
*/




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




/*
Символ возврата каретки (CR) и символ доллара ($) - это два разных символа, которые выполняют разные функции в тексте.

1. Символ возврата каретки (CR) (\r) обозначает конец текущей строки и перемещает курсор (или печатающее устройство) в начало этой же строки. Он используется для перевода курсора в начало строки без перехода на новую строку.

2. Символ доллара ($) - это символ, который может использоваться в тексте для различных целей в зависимости от контекста. Обычно он интерпретируется как обычный символ и отображается как знак доллара ($), если не используется в каком-то специфическом контексте или формате.

Таким образом, главное различие между символом возврата каретки и символом доллара заключается в их функциональности: первый управляет переводом курсора в тексте, а второй является символом с определенным значением.

*/






/*

Переменная `number_file` используется для хранения индекса текущего обрабатываемого аргумента командной строки, который представляет путь к файлу. Рассмотрим, как она применяется в контексте функции `main`:

1. **Инициализация структуры и парсинг опций**:
   ```c
   struct flags option = {0}; // Инициализация структуры флагов
   number_file = get_opt(argc, argv, &option); // Парсинг опций командной строки
   ```
   Функция `get_opt` обрабатывает аргументы командной строки, устанавливая соответствующие флаги в структуре `flags` и возвращая индекс следующего необработанного аргумента (т.е. первого аргумента, который не является опцией).

2. **Проверка на неправильные опции**:
   ```c
   if (option.defaultflag == 1) {
       printf("s21_cat: illegal option -- %c \nНеверное значение опций, используйте флаги beEvnstT\n", optopt);
       exit(1);
   }
   ```
   Если обнаружена неправильная опция, программа выводит сообщение об ошибке и завершает работу.

3. **Обработка файлов**:
   ```c
   else {
       while (number_file < (argc)) { // Пока индекс файла меньше количества аргументов
           char *path; // Создание переменной для пути к файлу
           path = argv[number_file]; // Присвоение пути к файлу по текущему индексу аргумента
           cat(path, option); // Обработка файла с использованием функции cat и текущих опций
           number_file++; // Увеличение индекса для перехода к следующему файлу
       }
   }
   ```
   Цикл `while` продолжает выполнение, пока `number_file` меньше `argc` (количества аргументов командной строки). Внутри цикла:
   - Получается путь к файлу из аргументов командной строки.
   - Вызывается функция `cat` для обработки файла с учетом установленных опций.
   - Увеличивается значение `number_file`, чтобы перейти к следующему аргументу.

Таким образом, переменная `number_file` позволяет программе обрабатывать все аргументы командной строки, которые являются путями к файлам, после того как все опции были распознаны и установлены.
*/
















/* 1



 в контексте данного кода number_file не содержит непосредственно путь к файлу tests/empty_lines_b_s.txt, но он является индексом в массиве аргументов командной строки argv, который содержит этот путь. То есть argv[number_file] будет указывать на строку "tests/empty_lines_b_s.txt". Это позволяет программе получить доступ к аргументам командной строки, включая пути к файлам, которые она должна обработать.



*/








/*

Давайте разберём этот момент подробнее.

Когда программа запускается с аргументами командной строки, они передаются в функцию `main` через параметры `argc` и `argv`. 

- `argc` (argument count) — это количество аргументов командной строки, включая имя самой программы.
- `argv` (argument vector) — это массив строк (char **), где каждая строка является отдельным аргументом командной строки.

Пример вызова программы:
```
./s21_cat -b tests/empty_lines_b_s.txt
```

Здесь:
- `argv[0]` — это строка `"./s21_cat"`, которая представляет имя самой программы.
- `argv[1]` — это строка `"-b"`, которая представляет первый аргумент (флаг `-b`).
- `argv[2]` — это строка `"tests/empty_lines_b_s.txt"`, которая представляет второй аргумент (путь к файлу).

Теперь вернёмся к коду:

```c
int number_file;
number_file = get_opt(argc, argv, &option);
```

Функция `get_opt` анализирует аргументы командной строки и возвращает индекс первого аргумента, который не является опцией (в данном случае, это индекс аргумента `"tests/empty_lines_b_s.txt"`).

Таким образом:
- `number_file` содержит индекс `2`, потому что `"tests/empty_lines_b_s.txt"` находится на третьей позиции в массиве `argv` (начиная с нуля).

Далее, в коде используется `argv[number_file]` для получения пути к файлу:

```c
char *path;
path = argv[number_file];  // записываем путь к файлу по индексу аргумента
cat(path, option);  // обрабатываем через функцию наш файл и флаги
```

В этом случае, `path` будет указывать на строку `"tests/empty_lines_b_s.txt"`, и функция `cat` будет обрабатывать этот файл, используя установленные флаги.


*/





/*
`optind`, `opterr`, и `optopt` — это переменные, используемые в функциях `getopt` и `getopt_long` для обработки аргументов командной строки в C. Они имеют разные роли и назначения.

### `optind`

- **Описание**: Переменная `optind` (option index) указывает на текущий индекс в массиве `argv`, который анализируется функцией `getopt` или `getopt_long`.
- **Инициализация**: По умолчанию инициализируется значением 1.
- **Использование**:
  - Указывает на первый аргумент, не являющийся опцией, после завершения анализа.
  - Может быть изменен программой, чтобы повторно запустить анализ или пропустить некоторые аргументы.

**Пример**:
```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "ab:")) != -1) {
        switch (opt) {
            case 'a':
                printf("Option a\n");
                break;
            case 'b':
                printf("Option b with value %s\n", optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-b value]\n", argv[0]);
                return 1;
        }
    }
    // optind указывает на первый аргумент, не являющийся опцией
    for (int i = optind; i < argc; i++) {
        printf("Non-option argument: %s\n", argv[i]);
    }
    return 0;
}
```

### `opterr`

- **Описание**: Переменная `opterr` (option error) указывает, должна ли функция `getopt` автоматически выводить сообщения об ошибках.
- **Инициализация**: По умолчанию установлена в 1 (true), что означает, что сообщения об ошибках будут автоматически выводиться.
- **Использование**:
  - Если `opterr` установить в 0, функция `getopt` не будет выводить сообщения об ошибках.

**Пример**:
```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    opterr = 0;  // Отключаем автоматические сообщения об ошибках
    while ((opt = getopt(argc, argv, "ab:")) != -1) {
        switch (opt) {
            case 'a':
                printf("Option a\n");
                break;
            case 'b':
                printf("Option b with value %s\n", optarg);
                break;
            case '?':
                // Обрабатываем ошибку вручную
                printf("Unknown option: %c\n", optopt);
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-b value]\n", argv[0]);
                return 1;
        }
    }
    return 0;
}
```

### `optopt`

- **Описание**: Переменная `optopt` (option character) содержит символ опции, который вызвал ошибку.
- **Использование**:
  - Используется для определения, какая опция вызвала ошибку, когда `getopt` возвращает `?`.

**Пример**:
```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "ab:")) != -1) {
        switch (opt) {
            case 'a':
                printf("Option a\n");
                break;
            case 'b':
                printf("Option b with value %s\n", optarg);
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-b value]\n", argv[0]);
                return 1;
        }
    }
    return 0;
}
```

### Итог

- **`optind`**: Указывает на текущий индекс в `argv` для анализа. Используется для отслеживания позиции и пропуска обработанных опций.
- **`opterr`**: Управляет выводом сообщений об ошибках. Можно отключить автоматический вывод ошибок.
- **`optopt`**: Содержит символ опции, вызвавшей ошибку. Используется для обработки ошибок, связанных с неверными опциями.

Эти переменные помогают более гибко и эффективно обрабатывать аргументы командной строки в C.
*/












/*
Программа не понимает автоматически, что в переменной `number_file` содержится путь к файлу. Вместо этого программа опирается на то, что в командной строке аргументы передаются в определенном порядке, и ожидает, что в `argv[number_file]` будет содержаться путь к файлу.

Когда программа запускается из командной строки, ей передаются аргументы. Первый аргумент (`argv[0]`) обычно содержит имя исполняемого файла, а последующие аргументы (`argv[1]`, `argv[2]`, и т.д.) содержат дополнительные параметры, такие как пути к файлам или флаги.

В данном случае, предполагается, что пользователь запускает программу с аргументами, содержащими пути к файлам, которые нужно обработать. Когда программа доходит до строки `path = argv[number_file];`, она просто присваивает переменной `path` значение аргумента командной строки по индексу `number_file`, предполагая, что этот аргумент содержит путь к файлу.

Таким образом, программа не "понимает" автоматически, что `number_file` содержит путь к файлу; она просто использует его для доступа к аргументам командной строки в порядке, в котором они были переданы при запуске программы.

*/


















/*

В языке C ключевое слово `static` изменяет область видимости и время жизни переменных и функций. Рассмотрим, как это применяется к структурам.

### Статическая структура

Когда структура объявляется как `static`, это означает следующее:

1. **Область видимости**: Статическая структура видима только в том файле, в котором она объявлена.
2. **Время жизни**: Статическая структура существует на протяжении всего времени работы программы.

Пример:
```c
static struct option long_options[] = {
    {"number-nonblank", no_argument, 0, 'b'},
    {"number", no_argument, 0, 'n'},
    {"squeeze-blank", no_argument, 0, 's'},
    {0, 0, 0, 0}
};
```
В этом случае `long_options` доступна только в том файле, где она объявлена, и будет существовать на протяжении всей работы программы.

### Не статическая структура

Когда структура объявляется без ключевого слова `static`, она имеет следующие характеристики:

1. **Область видимости**: Глобальная структура доступна во всех файлах, где она объявлена (если она объявлена во внешнем заголовочном файле, подключенном к другим файлам с помощью `#include`).
2. **Время жизни**: Глобальная структура существует на протяжении всего времени работы программы.

Пример:
```c
struct option long_options[] = {
    {"number-nonblank", no_argument, 0, 'b'},
    {"number", no_argument, 0, 'n'},
    {"squeeze-blank", no_argument, 0, 's'},
    {0, 0, 0, 0}
};
```
В этом случае `long_options` доступна во всех файлах, которые включают ее объявление, и будет существовать на протяжении всей работы программы.

### В чем разница?

1. **Область видимости**:
   - **Статическая структура**: Доступна только в пределах одного файла.
   - **Не статическая структура**: Доступна в пределах всех файлов, где она объявлена или включена через заголовочный файл.

2. **Время жизни**:
   - Оба типа (и статическая, и не статическая глобальная структура) существуют на протяжении всего времени работы программы.

3. **Использование**:
   - **Статические структуры** используются для данных, которые не должны быть видимы за пределами текущего файла, что помогает избежать конфликтов имен и улучшает инкапсуляцию.
   - **Не статические структуры** используются для данных, которые должны быть доступны во всей программе.

### Пример использования

```c
// file1.c
#include <stdio.h>

static struct option long_options[] = {
    {"number-nonblank", no_argument, 0, 'b'},
    {"number", no_argument, 0, 'n'},
    {"squeeze-blank", no_argument, 0, 's'},
    {0, 0, 0, 0}
};

void print_options() {
    for (int i = 0; long_options[i].name != 0; i++) {
        printf("Option: %s\n", long_options[i].name);
    }
}

int main() {
    print_options();
    return 0;
}

// file2.c
#include <stdio.h>

extern struct option long_options[];

void print_options() {
    for (int i = 0; long_options[i].name != 0; i++) {
        printf("Option: %s\n", long_options[i].name);
    }
}

int main() {
    print_options();
    return 0;
}
```

- В `file1.c` структура `long_options` объявлена как `static`, поэтому она доступна только внутри `file1.c`.
- В `file2.c` структура `long_options` не объявлена как `static`, поэтому она может быть объявлена как `extern` в других файлах и использована там же.

*/