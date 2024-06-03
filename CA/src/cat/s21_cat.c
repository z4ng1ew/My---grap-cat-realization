#include "s21_cat.h"

struct flags {
  int bflag;
  int bflag;
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

  //В переменной option будет храниться структура flags


  // !!! Флаги, такие как bflag, eflag, Eflag и так далее, хранятся в структуре flags, которая инициализируется и используется в функции main для определения установленных опций. 
  
  //Эти флаги устанавливаются в соответствии с опциями, переданными через аргументы командной строки, и затем передаются в функцию cat для обработки файлов в соответствии с установленными опциями. !!!

  //Когда вы создаете переменную option типа struct flags, вы резервируете память для этой переменной в соответствии с размером структуры struct flags.



  int number_file;  // индекс обрабатываемого элемента - используется для хранения индекса текущего обрабатываемого аргумента командной строки, который представляет путь к файлу

  //Она хранит индекс - 2 - ПУТЬ К ФАЙЛУ !!!

  //то есть можно сказать, что переменная number_file всего лишь получает индекс массива, конкретно в нашем примере, здесь будет индекс - 2 (то есть путь к файлу - tests/empty_lines_b_s.txt)

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




  // присваиваем значение индексу файла через return optind
  number_file = get_opt(argc, argv, &option);

  //getopt и getopt_long — это функции, используемые для анализа опций командной строки. Основное различие между ними заключается в поддерживаемом формате опций: getopt работает с короткими опциями (одиночные символы, например, -a), а getopt_long — с длинными опциями (словами, например, --option). Происходит от слов - "get option"



  //Переменная number_file получает значение, которое является индексом первого аргумента, не являющегося флагом (например, путь к файлу). то есть индекс под номером 2

  //argc (argument count) содержит количество аргументов командной строки. В данном случае: argc = 3 (потому что у нас три аргумента: ./s21_cat, -b, tests/empty_lines_b_s.txt)

  //argv (argument vector) — массив строк, содержащий сами аргументы командной строки. В данном случае:

  //на примере этой команды: ./s21_cat -b tests/empty_lines_b_s.txt
  
  //argv[0] = "./s21_cat"
  //argv[1] = "-b"
  //argv[2] = "tests/empty_lines_b_s.txt"

  if (option.defaultflag == 1) {
    printf(
        "s21_cat: illegal option -- %c \nНеверное значение опций, используйте " //%c - специф-ор для char (который мы не правильно ввели)
        "флаги beEvnstT\n",
        optopt); //если пользователь ввел неизвестный флаг -z, optopt будет содержать z, и программа выведет: s21_cat: illegal option -- z Неверное значение опций, используйте флаги beEvnstT  // Резюме optopt — это глобальная переменная, которая используется функциями getopt и getopt_long для хранения символа опции, вызвавшей ошибку. Это полезно для информирования пользователя о том, какая именно опция была некорректной.


    exit(1); //














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










/*
В переменной `option` будет храниться структура `flags`, все члены которой инициализируются нулями. Это означает, что все флаги (например, `bflag`, `eflag`, и т.д.) будут установлены в значение `0`. В языке C такой синтаксис инициализации `{0}` используется для установки всех членов структуры в нулевое значение.

Рассмотрим конкретный пример с вашим кодом:

```c
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

int main(int argc, char **argv) {
  struct flags option = {0};  // Создание переменной типа struct flags и инициализация её нулями
  // Остальной код
}
```

### Что происходит в `struct flags option = {0};`:
1. **Создание переменной**: Создается переменная `option` типа `struct flags`.
2. **Инициализация нулями**: Все члены структуры `option` инициализируются нулями. Это значит:
   - `option.bflag = 0;`
   - `option.eflag = 0;`
   - `option.Eflag = 0;`
   - `option.vflag = 0;`
   - `option.nflag = 0;`
   - `option.sflag = 0;`
   - `option.tflag = 0;`
   - `option.Tflag = 0;`
   - `option.defaultflag = 0;`

Таким образом, в переменной `option` будет храниться структура, в которой все флаги изначально равны нулю. Это удобно, так как можно легко проверить, были ли какие-либо флаги установлены в ходе выполнения программы.

### Пример использования:
Когда вы анализируете аргументы командной строки и устанавливаете соответствующие флаги, эти флаги будут изменены с `0` на `1` (или другие значения, если нужно). Например:

```c
// Установка флагов в зависимости от аргументов командной строки
while (flag->defaultflag == 0 &&
       (c = getopt_long(argc, argv, "beEvnstT", long_options,
                        &option_index)) != -1) {
  switch (c) {
    case 'b':
      flag->bflag = 1;
      break;
    case 'e':
      flag->Eflag = 1;
      flag->vflag = 1;
      break;
    // И так далее для других флагов
  }
}
```

Итак, `struct flags option = {0};` создает структуру `option` с нулевыми значениями всех её членов, что означает, что никакие опции не активированы.
*/












/*
Понял вас. Давайте разберемся.

Когда запускается программа через командную строку, она получает доступ к аргументам командной строки через параметры `argc` и `argv` в функции `main()`. 

- `argc` (от "argument count") представляет количество аргументов командной строки, переданных при запуске программы.
- `argv` (от "argument vector") - это массив строк (`char *argv[]`), который содержит сами аргументы командной строки.

Теперь вернемся к вашему примеру с `./s21_cat -b tests/empty_lines_b_s.txt`. В этой команде:
- `./s21_cat` - имя исполняемого файла (программы).
- `-b` - это опция командной строки, указывающая программе, что нужно добавить номера строк в вывод.
- `tests/empty_lines_b_s.txt` - это аргумент командной строки, представляющий собой путь к файлу, который нужно обработать.

Теперь когда программа запускается, она начинает свое выполнение с функции `main()`. Параметры `argc` и `argv` предоставляют информацию о переданных аргументах. Индекс `argc` указывает на количество аргументов, а массив `argv` содержит сами аргументы!!!. Индекс элемента в массиве `argv` соответствует его позиции в командной строке, начиная с 0.

Теперь, когда вы используете переменную `number_file` в вашем коде, она используется для отслеживания текущего индекса обрабатываемого элемента в массиве `argv`. В вашем случае, когда программа запускается с опциями командной строки, индекс `number_file` указывает на путь к файлу, который нужно обработать (`tests/empty_lines_b_s.txt`).
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



























/*


В строке кода `number_file = get_opt(argc, argv, &option);` происходит следующее:

1. **Вызов функции `get_opt`**: Функция `get_opt` вызывается с тремя аргументами: 
   - `argc` — количество аргументов командной строки.
   - `argv` — массив строк, содержащий аргументы командной строки.
   - `&option` — указатель на структуру `flags`, в которую будут записаны установленные флаги.

2. **Парсинг аргументов командной строки**: Внутри функции `get_opt` происходит анализ аргументов командной строки. Она обрабатывает флаги (такие как `-b`, `-e`, и т.д.) и устанавливает соответствующие поля структуры `flags` (например, `bflag`, `eflag` и т.д.) в 1, если соответствующий флаг был передан.

3. **Возвращение индекса**: После завершения анализа аргументов командной строки, функция `get_opt` возвращает индекс первого аргумента, который не является флагом. Этот индекс указывает на путь к файлу или другому аргументу, который нужно обработать.

В результате:
- Переменная `number_file` получает значение, которое является индексом первого аргумента, не являющегося флагом (например, путь к файлу).

Пример кода функции `get_opt`:

```c
int get_opt(int argc, char **argv, struct flags *flag) {  //функция парсинга
  int c = 0;
  int option_index = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};
  //бесконечный цикл, который будет выполняться до тех пор, пока getopt_long не вернет -1
  while (flag->defaultflag == 0 &&
         (c = getopt_long(argc, argv, "beEvnstT", long_options,
                          &option_index)) != -1) {
    opterr = 0;
    //указатель на переменную, в которую будет сохранен индекс найденной опции

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
```

В этой функции происходит следующее:
- Цикл `while` использует `getopt_long` для обработки аргументов командной строки.
- Для каждого найденного флага устанавливается соответствующее поле структуры `flags`.
- В конце функция возвращает `optind`, который является индексом первого аргумента, не являющегося флагом. 

Таким образом, `number_file` получает этот индекс и указывает на аргумент командной строки, который следует обрабатывать (например, путь к файлу).


*/










/*
Да, ваш анализ в целом верный, но давайте разберем это немного подробнее для ясности.

### Параметры командной строки

Когда вы запускаете программу с командой:
```sh
./s21_cat -b tests/empty_lines_b_s.txt
```

### Аргументы командной строки

- **argc** (argument count) содержит количество аргументов командной строки. В данном случае:
  - `argc = 3` (потому что у нас три аргумента: `./s21_cat`, `-b`, `tests/empty_lines_b_s.txt`)

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