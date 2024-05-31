#include "s21_grep.h"

#define BUFFER 10000

struct flags {
  int eflag;
  int iflag;
  int vflag;
  int cflag;
  int lflag;
  int nflag;
  int hflag;
  int sflag;
  int oflag;
  int fflag;
  int lflag_file_match;  // мен]ем значение флага если найдено совпадение
  int nflag_count_str;   // счетчик всех строк
  char arg_namefile[BUFFER];  // fflag записываем имя файла из терминала
  char o_namefile[BUFFER];  // сохраняем имя файла для о флага
  char arg_fflag[BUFFER];  // аписываем аргумент из файла
  char str_file[BUFFER];   //строка считанная из файла
  char str_arguments[BUFFER];  //аргументы считанные из файла
  char str_arguments_2[BUFFER];
} options = {0};

int main(int argc, char *argv[]) {
  get_opt(argc, argv);
  int counter_files = argc - optind;
  while (optind < argc) {
    grep(counter_files, argv);
    optind++;
  }
  return 0;
}

// EFLAG - в optarg возвращается аргумент указанный после флага e
// и мы его записываем в структуру char str_file[BUFFER] с помощью strcat
// strcat (куда вставляем , что вставляем) добавляет копию строки
// после аргумента отдельным strcat записываем | как разделительную черту
// между аргументами, если аргументов после опции е будет больше одного
// то они запишутся подряд через | (пайплайн).
// (regcomp убирает | внутри структуры и понимает что это последовательность)

void get_opt(int argc, char *argv[]) {
  int opt = 0;

  while ((opt = getopt_long(argc, argv, "e:ivclnhsof:", NULL, 0)) != -1) {
    switch (opt) {
      case 'e':
        options.eflag = 1;
        strcat(options.str_arguments, optarg);
        strcat(options.str_arguments, "|");
        break;
      case 'i':
        options.iflag = 1;
        break;
      case 'v':
        options.vflag = 1;
        break;
      case 'c':
        options.cflag = 1;
        break;
      case 'l':
        options.lflag = 1;
        break;
      case 'n':
        options.nflag = 1;
        break;
      case 'h':
        options.hflag = 1;
        break;
      case 's':
        options.sflag = 1;
        break;
      case 'o':
        options.oflag = 1;
        break;
      case 'f':
        options.fflag = 1;
        strcpy(options.arg_namefile, optarg);
        fflag();
        break;
      default:
        printf("неверное значение опции\n");
        break;
    }
  }
  if (!options.eflag && !options.fflag) {
    if (argc > optind) {
      //встроенная в (strinf.h) функция strcat объединяет первую строку со
      //второй
      strcat(options.str_arguments, argv[optind]);
      // printf("Зашли в условие - флаг не е и не f\nЗначение аргумента: %s\n",
      // (argv[optind]));
    }
    optind++;
  }
  //из структуры аргументов в которую мы записали данные в таком виде (d|w|r|t|)
  //мы должны удалить последний пайп, иначе он думает, что у нас есть еще один
  //файл или аргумент, что приведет к утечкам памяти удаляем | с помощью strlen,
  //считаем количество аргументов вычитаем 1, потому что в массиве запись идет
  //от 0, а в счетсчике с 1 и приравниваем концу строку если этого не сделать,
  //помимо совпадений распечатает весь файл
  if (options.eflag || options.fflag) {
    options.str_arguments[strlen(options.str_arguments) - 1] = '\0';
  }
}

// IFLAG - создаешь переменную с флагом REG_EXTENDED (принимает регулярные
// выражения) если IFLAG добавляешь флаг игнорации регистра VFLAG - перед
// проверкой совпадения match для флага v инвертируем значение match что
// приводит к печати все несовпадающих строк CFLAG - создаем counter_str чтобы
// считать количество совпадений также создаем в мейне counter_files = argc -
// optind, чтобы считать файлы после while печатаем ответ в зависимости от
// кол-ва файлов LFLAG - создаем структуру и если находим совпадение меняем ее
// значение на 1 если совпадение есть, то после цикла печатаем название файла
// NFLAG - создаем счетчик всех строк и внутри цикла печатаем вывод в
// зависимости от количества файлов HFLAG - в обычный греп добавляем печать
// hflag только при counter_files == 1 а во второе условие на заходим SFLAG -
// else if (!options.sflag) printf ("-----ERROR: FILE NOT FIND-----");

void grep(int counter_files, char *argv[]) {
  FILE *file;
  regex_t reg;  //структура, котора хранит регулярные выражения
  regmatch_t first;
  int counter_str = 0;
  int flags_regular = REG_EXTENDED;
  if (options.iflag) {
    flags_regular = REG_EXTENDED | REG_ICASE;
  }
  if (!options.fflag) {
    regcomp(&reg, options.str_arguments, flags_regular);
  } else {
    regcomp(&reg, options.str_arguments_2, flags_regular);  // fflag
  }
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    while ((fgets(options.str_file, BUFFER, file)) != NULL) {
      int match = regexec(&reg, options.str_file, 1, &first, 0);
      options.nflag_count_str++;                                  // nflag
      if (options.vflag) match = !match;                          // vflag
      if (!match && options.str_file[0] != '\n') counter_str++;   // cflag
      if (!match && options.lflag) options.lflag_file_match = 1;  // lflag
      if (!match && options.nflag) {                              // nflag
        if (counter_files == 1)
          printf("%d:%s", options.nflag_count_str, options.str_file);
        if (counter_files > 1)
          printf("%s:%d:%s", argv[optind], options.nflag_count_str,
                 options.str_file);
        if (counter_files > 0)
          sym_eof();  //удаляем последний символ в конце файла
      }
      if (options.oflag == 1)
        oflag(match, reg, first, counter_files, argv);  // oflag
      if (!match && !options.cflag && !options.lflag && !options.nflag &&
          !options.oflag) {  // other flags
        if (counter_files == 1 || options.hflag)
          printf("%s", options.str_file);  // grep and hflag
        if (counter_files > 1 && !options.hflag)
          printf("%s:%s", argv[optind], options.str_file);  // grep and hflag
        if (counter_str > 0) sym_eof();
      }
    }
    if (options.cflag == 1) {  // cflag
      if (counter_files == 1) printf("%d\n", counter_str);
      if (counter_files > 1) printf("%s:%d\n", argv[optind], counter_str);
    }
    if (options.lflag == 1 && options.lflag_file_match == 1)
      printf("%s\n", argv[optind]);  // lflag
    options.nflag_count_str = 0;     // nflag
    fclose(file);
  } else if (!options.sflag)
    fprintf(stderr, "No such file or directory\n");
  regfree(&reg);
}

void fflag() {
  FILE *file2;
  file2 = fopen(options.arg_namefile, "rb");
  if (file2 != NULL) {
    while (!feof(file2)) {
      if (fgets(options.arg_fflag, BUFFER, file2) != NULL) {
        strcat(options.str_arguments_2, options.arg_fflag);
        if (options.str_arguments_2[strlen(options.str_arguments_2) - 1] != '|')
          strcat(options.str_arguments_2, "|");
      }
    }
    options.str_arguments_2[strlen(options.str_arguments_2) - 1] = '\0';
    fclose(file2);
  }
}

void oflag(int match, regex_t reg, regmatch_t first, int counter_files,
           char *argv[]) {
  if (!match) {
    if (counter_files == 1)
      printf("%.*s\n", (int)(first.rm_eo - first.rm_so),
             options.str_file + first.rm_so);
    if (counter_files > 1)
      printf("%s:%.*s\n", argv[optind], (int)(first.rm_eo - first.rm_so),
             options.str_file + first.rm_so);
    char *remaining = options.str_file + first.rm_eo;
    while (!(regexec(&reg, remaining, 1, &first, 0))) {
      if (counter_files == 1)
        printf("%.*s\n", (int)(first.rm_eo - first.rm_so),
               remaining + first.rm_so);
      if (counter_files > 1)
        printf("%s:%.*s\n", argv[optind], (int)(first.rm_eo - first.rm_so),
               remaining + first.rm_so);
      remaining = remaining + first.rm_eo;
    }
  }
}

void sym_eof() {
  if (options.str_file[strlen(options.str_file) - 1] != '\n' &&
      *options.str_file != '\n' && !options.fflag) {
    printf("%c", '\n');
    *options.str_file = '\n';
  }  //убираем символ конца файла
}