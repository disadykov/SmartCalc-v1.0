#include "s21_core.h"

/// @brief удаляет все пробелы в строке
/// @param str строка, в которой удаляем пробелы
void s21_remove_space(char *str) {
  if (str != NULL) {
    int i, j;
    for (i = j = 0; str[i] != '\0'; i++)
      if (str[i] != ' ' && str[i] != '\t') str[j++] = str[i];
    str[j] = '\0';
  }
}

/// @brief переводит всю строку в нижний регистр.
/// @param str строка, которую нужно преобразовать.
void s21_to_lower(char *str) {
  if (str != NULL) {
    for (size_t i = 0; i < strlen(str); i++) {
      str[i] = tolower(str[i]);
    }
  }
}

/// @brief проверяет символ на вхождение в набор допустимых
/// @param symbol проверяемый символ
/// @return 0 - входит в диапозон, 1 - не входит
int s21_is_characters(char symbol) {
  int status = ERROR_NO;
  char character_set[] = ".()+-*/^modcsintaqrlgx";
  for (size_t i = 0; i < strlen(character_set); i++) {
    if (symbol == character_set[i]) {
      status = ERROR_NO;
      break;
    } else {
      status = ERROR_BAD_SYMBOL;
    }
  }
  return status;
}

/// @brief проверяет, что строка состоит только из допустимого набора символов
/// @param str строка, которую проверяем
/// @return 0 - ошибок нет и все символы допустимые, 1 - ошибка, в строке есть
/// недопустимый символ, 2 - на вход подана не строка
int s21_valid_characters(char *str) {
  int err_flag = ERROR_NO;
  if (str != NULL) {
    for (size_t i = 0; i < strlen(str); i++) {
      if (isdigit(str[i]) || !(s21_is_characters(str[i]))) {
        err_flag = ERROR_NO;
      } else {
        err_flag = ERROR_BAD_SYMBOL;
        break;
      }
    }
  } else {
    err_flag = ERROR_BAD_STR;
  }
  return err_flag;
}

/// @brief проверка, что строка выражения не пустая
/// @param str строка, которую проверяем
/// @return 0 - ошибок нет, строка не пустая, 3 - ошибка, строка пустая
int s21_is_str_empty(char *str) {
  int err_flag = ERROR_NO;
  if (strlen(str) == 0) {
    err_flag = ERROR_EMPTY_STR;
  }
  return err_flag;
}

/// @brief расшифровывает код ошибки
/// @param errnum код ошибки
/// @return возвращаем тектовое описание кода ошибки
char *s21_strerror(int errnum) {
  char *const error[] = ERROR_BASE;
  static char *result;
  result = error[errnum];
  return result;
}

/// @brief проверка длинны выражения
/// @param str строка, которую проверяем
/// @return 0 - в допутимых значениях, 4 - меньше 2 символов, 5 - более 255
/// символов
int s21_expression_size(char *str) {
  int err_flag = ERROR_NO;
  if (strlen(str) < 2) {
    err_flag = ERROR_SHORT_STR;
  } else {
    if (strlen(str) > 255) {
      err_flag = ERROR_LONG_STR;
    }
  }
  return err_flag;
}

/// @brief проверка кол-ва открывающихся и закрывающихся скобок
/// @param str строка, которую проверяем
/// @return 0 - ошибок нет, кол-во скобок равно, 6 - кол-во скобок не равно
int s21_brackets_count(char *str) {
  int err_flag = ERROR_NO;
  int left_brackets = 0;
  int right_brackets = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == '(') {
      left_brackets++;
    } else {
      if (str[i] == ')') {
        right_brackets++;
      }
    }
  }
  if (left_brackets != right_brackets) {
    err_flag = ERROR_BAD_BRACKETS;
  }
  return err_flag;
}

/// @brief Проверка точек в выражении
/// @param str строка, которую проверяем
/// @return 0 - ошибок нет, 7 - ошибка, не корректное выражение
int s21_check_point(char *str) {
  int err_flag = ERROR_NO;
  if ((str[0] == '.') || (str[strlen(str) - 1] == '.')) {
    err_flag = ERROR_BAD_EXPRESSION;
  } else {
    for (size_t i = 0; i < strlen(str) - 1; i++) {
      if ((str[i] == '.') && (str[i + 1] == '.')) {
        err_flag = ERROR_BAD_EXPRESSION;
        break;
      } else {
        if (strlen(str) > 3) {
          for (size_t j = 1; j < strlen(str) - 1; j++) {
            if ((str[j] == '.') &&
                (!(isdigit(str[j - 1])) || !(isdigit(str[j + 1])))) {
              err_flag = ERROR_BAD_EXPRESSION;
              break;
            }
          }
        }
      }
    }
  }
  return err_flag;
}

/// @brief Проверка на наличие операторов или функций
/// @param str строка, которую проверяем
/// @return 0 - ошибок нет, 8 - ошибка, операторы или функции не найдены
int s21_check_operators(char *str) {
  int err_flag = ERROR_NO;
  char *check_operator;
  int count_operators = 0;

  check_operator = strchr(str, '+');
  if (check_operator != NULL) count_operators++;
  check_operator = strchr(str, '-');
  if (check_operator != NULL) count_operators++;
  check_operator = strchr(str, '*');
  if (check_operator != NULL) count_operators++;
  check_operator = strchr(str, '/');
  if (check_operator != NULL) count_operators++;
  check_operator = strchr(str, '^');
  if (check_operator != NULL) count_operators++;
  check_operator = strstr(str, "mod");
  if (check_operator != NULL) count_operators++;
  check_operator = strstr(str, "cos");
  if (check_operator != NULL) count_operators++;
  check_operator = strstr(str, "sin");
  if (check_operator != NULL) count_operators++;
  check_operator = strstr(str, "tan");
  if (check_operator != NULL) count_operators++;
  check_operator = strstr(str, "sqrt");
  if (check_operator != NULL) count_operators++;
  check_operator = strstr(str, "ln");
  if (check_operator != NULL) count_operators++;
  check_operator = strstr(str, "log");
  if (check_operator != NULL) count_operators++;

  if (count_operators == 0) {
    err_flag = ERROR_NO_OPERATORS;
  }
  return err_flag;
}

/// @brief Находит и меняет в строке выражения переменную <x> на ее значение
/// @param str строка выражения
/// @param x - значение переменной для подстановки
void s21_replaceX(char *str, const char *x) {
  if (str != NULL) {
    size_t countX = 0;
    size_t lenSTR = strlen(str);
    size_t lenX = strlen(x);
    size_t i = 0;
    size_t j = 0;
    for (i = 0; i < lenSTR; i++) {
      if (str[i] == 'x') {
        countX++;
      }
    }
    size_t new_lenSTR = lenSTR + countX * (lenX + 2);
    char *newSTR = malloc(new_lenSTR + 1);
    // Проходим по исходной строке и заменяем переменную "x" на ее значение
    for (i = 0, j = 0; i < lenSTR; i++) {
      if (str[i] == 'x') {
        if (x[0] == '-') {
          newSTR[j++] = '(';
          newSTR[j++] = '0';
        }
        strcpy(newSTR + j, x);
        j += lenX;
        if (x[0] == '-') {
          newSTR[j++] = ')';
        }
      } else {
        newSTR[j++] = str[i];
      }
    }
    newSTR[j++] = '\0';
    strcpy(str, newSTR);
    free(newSTR);
  }
}

/// @brief проверяет, что символ является оператором
/// @param oper проверяемый символ
/// @return 0 - не оператор, 1 - оператор
int s21_is_operator(const char oper) {
  int check = 0;
  if ((oper == '-') || (oper == '+') || (oper == '*') || (oper == '/') ||
      (oper == '^')) {
    check = 1;
  }
  return check;
}

/// @brief проверяет, что выражение не заканчивается оператором и что не
/// используются два подряд идущих оператора
/// @param str строка-выражение
/// @return 0 - ошибок нет, 7 - ошибка, не корректное выражение
int s21_correct_operators(char *str) {
  int err_flag = ERROR_NO;
  char last_ch = str[strlen(str) - 1];
  if ((last_ch == '-') || (last_ch == '+') || (last_ch == '*') ||
      (last_ch == '/') || (last_ch == '^') || (last_ch == 's') ||
      (last_ch == 'n') || (last_ch == 't') || (last_ch == 'g')) {
    err_flag = ERROR_BAD_EXPRESSION;
  } else {
    for (size_t i = 0; i < strlen(str) - 1; i++) {
      if (s21_is_operator(str[i]) && s21_is_operator(str[i + 1])) {
        err_flag = ERROR_BAD_EXPRESSION;
        break;
      }
    }
  }
  return err_flag;
}

/// @brief проверяет что после функции следует открывающаяся скобока
/// @param token строка в которой есть функция
/// @param ch символ после которого должна быть скобка
/// @return 0 - скобка есть, 1 - скобки нет
int s21_check_func(const char *token, char ch) {
  int flag = 0;
  for (size_t i = 0; i < strlen(token) - 1; i++) {
    if ((token[i] == ch) && (token[i + 1] != '(')) {
      flag = 1;
      break;
    }
  }
  return flag;
}

/// @brief проверяет, что после функции есть открывающаяся скобка
/// @param str строка-выражение
/// @return 0 - ошибок нет, 7 - ошибка, не корректное выражение
int s21_correct_func(const char *str) {
  char *tmpStr = strdup(str);
  char *savePtr;
  int err_flag = ERROR_NO;
  int err_count = 0;
  char *find_func;
  char *token = __strtok_r(tmpStr, "()-+/*^", &savePtr);
  while (token != NULL) {  // пока есть лексемы
    if (strlen(token) > 2) {
      find_func = strstr(token, "sin");
      if (find_func != NULL) {
        if (s21_check_func(token, 'n')) err_count++;
      }
      find_func = strstr(token, "cos");
      if (find_func != NULL) {
        if (s21_check_func(token, 's')) err_count++;
      }
      find_func = strstr(token, "tan");
      if (find_func != NULL) {
        if (s21_check_func(token, 'n')) err_count++;
      }
      find_func = strstr(token, "sqrt");
      if (find_func != NULL) {
        if (s21_check_func(token, 't')) err_count++;
      }
      find_func = strstr(token, "log");
      if (find_func != NULL) {
        if (s21_check_func(token, 'g')) err_count++;
      }
      find_func = strstr(token, "ln");
      if (find_func != NULL) {
        if (s21_check_func(token, 'n')) err_count++;
      }
    }
    token = __strtok_r(NULL, "()-+/*^", &savePtr);
  }
  free(tmpStr);
  if (err_count > 0) err_flag = ERROR_BAD_EXPRESSION;
  return err_flag;
}

/// @brief проверяет что выражение заканчивается скобкой или цифрой
/// @param str строка-выражение
/// @return 0 - ошибок нет, 7 - ошибка, не корректное выражение
int s21_last_symbol(const char *str) {
  int err_flag = ERROR_NO;
  int flag = isdigit(str[strlen(str) - 1]);
  if (str[strlen(str) - 1] != ')') {
    if (flag == 0) {
      err_flag = ERROR_BAD_EXPRESSION;
    }
  }
  return err_flag;
}

/// @brief ищет подстроки и меняет их во всей строке на заданное значение
/// @param dst указать на строку срезультатом
/// @param num максимальная длинна выходной строки
/// @param str строка в которой будем искать
/// @param orig подстрока которую ищем
/// @param rep подстрока на которую производим замену
/// @return адрес на строку в которой будет храниться результат.
char *s21_str_replace(char *dst, int num, const char *str, const char *orig,
                      const char *rep) {
  const char *ptr;
  size_t len1 = strlen(orig);
  size_t len2 = strlen(rep);
  char *tmp = dst;

  num -= 1;
  while ((ptr = strstr(str, orig)) != NULL) {
    num -= (ptr - str) + len2;
    if (num < 1) break;

    strncpy(dst, str, (size_t)(ptr - str));
    dst += ptr - str;
    strncpy(dst, rep, len2);
    dst += len2;
    str = ptr + len1;
  }

  for (; (*dst = *str) && (num > 0); --num) {
    ++dst;
    ++str;
  }
  return tmp;
}

/// @brief обнуляет строку выражения и копируют в нее другую строку
/// @param str строка в которую копируем
/// @param buf строка из которой копируем
void s21_clear_str(char *str, char *buf) {
  memset(str, 0, strlen(str));
  strcpy(str, buf);
}

/// @brief меняем в строке выражения функции на символьные заменители
/// @param str строка-выражение
void s21_replace_functions(char *str) {
  char buf[1024];
  // mod = %
  s21_str_replace(buf, sizeof(buf) - 1, str, "mod", "%");
  s21_clear_str(str, buf);
  // acos = c
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "acos", "C");
  s21_clear_str(str, buf);
  // cos = c
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "cos", "c");
  s21_clear_str(str, buf);
  // asin = S
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "asin", "S");
  s21_clear_str(str, buf);
  // sin = s
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "sin", "s");
  s21_clear_str(str, buf);
  // atan = T
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "atan", "T");
  s21_clear_str(str, buf);
  // tan = t
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "tan", "t");
  s21_clear_str(str, buf);
  // sqrt = q
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "sqrt", "q");
  s21_clear_str(str, buf);
  // log = l
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "log", "l");
  s21_clear_str(str, buf);
  // ln = L
  memset(buf, 0, strlen(buf));
  s21_str_replace(buf, sizeof(buf) - 1, str, "ln", "L");
  s21_clear_str(str, buf);
}

/// @brief проверяет что выражение не начинается с мод, степени или операторов
/// не равных плюс и минус, подставляет 0 перед унарным плюсом или минусом
/// @param str строка выражение
/// @return 0 - ошибок нет, 7 - ошибка не корректного выражения, а так же
/// измененная строка выражение
int s21_first_operator_and_sign(char *str) {
  int err_flag = ERROR_NO;
  if ((str[0] == 'm') || (str[0] == '^') || (str[0] == '/') ||
      (str[0] == '*')) {
    err_flag = ERROR_BAD_EXPRESSION;
  } else {
    char buf[1024];
    int buf_step = 0;
    if ((str[0] == '+') || (str[0] == '-')) {
      buf[buf_step] = '0';
      buf_step++;
    }
    for (size_t i = 0; i < strlen(str) - 1; i++) {
      if ((str[i] == '(') && ((str[i + 1] == '-') || (str[i + 1] == '+'))) {
        buf[buf_step] = str[i];
        buf_step++;
        buf[buf_step] = '0';
        buf_step++;
      } else {
        buf[buf_step] = str[i];
        buf_step++;
      }
    }
    buf[buf_step] = str[strlen(str) - 1];
    buf_step++;
    buf[buf_step] = '\0';
    memset(str, 0, strlen(str));
    strcpy(str, buf);
    memset(buf, 0, strlen(buf));
  }

  return err_flag;
}

/// @brief Проверяет, что внутри скобок не пусто
/// @param str строка-выражение
/// @return 0 - ошибок нет, 10 - ошибка внутри скобок пусто
int s21_empty_brackets(const char *str) {
  int err_flag = ERROR_NO;
  for (size_t i = 0; i < strlen(str) - 1; i++) {
    if ((str[i] == '(') && ((str[i + 1] == ')'))) {
      err_flag = ERROR_EMPTY_BRACKETS;
    }
  }
  return err_flag;
}

/// @brief Проверяет что за фунцией не идет оператор
/// @param str  строка-выражение
/// @return 0 - ошибок нет, 7 - ошибка выражение не корректно
int s21_sing_before_func(const char *str) {
  int err_flag = ERROR_NO;
  for (size_t i = 0; i < strlen(str) - 1; i++) {
    if ((str[i] == 's' || str[i] == 'n' || str[i] == 't' || str[i] == 'g' ||
         str[i] == 'd') &&
        s21_is_operator(str[i + 1])) {
      err_flag = ERROR_BAD_EXPRESSION;
      break;
    }
  }
  return err_flag;
}

/// @brief Общая проверка корректности выражения
/// @param expression строка-выражения
/// @return 0 - ошибок нет. Коды ошибок от 1 до 9
int s21_expression_check(char *expression) {
  int err_code = 0;
  // проверка строки на пустоту
  if (s21_is_str_empty(expression) != ERROR_NO) {
    err_code = s21_is_str_empty(expression);
  } else {
    // Проверка длины выражаения (>2<255)
    if (s21_expression_size(expression) != ERROR_NO) {
      err_code = s21_expression_size(expression);
    } else {
      // Проверка на допустимые символы
      if (s21_valid_characters(expression) != ERROR_NO) {
        err_code = s21_valid_characters(expression);
      } else {
        // Проверка открывающихся и закрывающихся скобок
        if (s21_brackets_count(expression) != ERROR_NO) {
          err_code = s21_brackets_count(expression);
        } else {
          // Проверка точек на корректность
          if (s21_check_point(expression) != ERROR_NO) {
            err_code = s21_check_point(expression);
          } else {
            // Проверка корректности операторов
            if (s21_check_operators(expression) != ERROR_NO) {
              err_code = s21_check_operators(expression);
            } else {
              // Проверка операторов в функциях
              if (s21_correct_operators(expression) != ERROR_NO) {
                err_code = s21_correct_operators(expression);
              } else {
                // Проверка скобок
                if (s21_check_brackets(expression) != ERROR_NO) {
                  err_code = s21_check_brackets(expression);
                } else {
                  // Проверка корректности функций
                  if (s21_correct_func(expression) != ERROR_NO) {
                    err_code = s21_correct_func(expression);
                  } else {
                    // Проверка последнего символа
                    if (s21_last_symbol(expression) != ERROR_NO) {
                      err_code = s21_last_symbol(expression);
                    } else {
                      if (s21_first_operator_and_sign(expression) != ERROR_NO) {
                        err_code = ERROR_BAD_EXPRESSION;
                      } else {
                        if (s21_empty_brackets(expression) != ERROR_NO) {
                          err_code = s21_empty_brackets(expression);
                        } else {
                          if (s21_sing_before_func(expression) != ERROR_NO) {
                            err_code = s21_sing_before_func(expression);
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  return err_code;
}

/// @brief добавляет в строку-выражение пробелы сепараторы
/// @param str строка-выражение
void s21_add_separator(char *str) {
  char buf[1024];
  int buf_step = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    if ((str[i] == ')') || (str[i] == '%') || (str[i] == '+') ||
        (str[i] == '-') || (str[i] == '*') || (str[i] == '/') ||
        (str[i] == '^')) {
      buf[buf_step] = ' ';
      buf_step++;
      buf[buf_step] = str[i];
      buf_step++;
      buf[buf_step] = ' ';
    } else {
      if ((str[i] == 'c') || (str[i] == 'C') || (str[i] == 's') ||
          (str[i] == 'S') || (str[i] == 't') || (str[i] == 'T') ||
          (str[i] == 'l') || (str[i] == 'L') || (str[i] == 'q') ||
          (str[i] == '(')) {
        buf[buf_step] = str[i];
        buf_step++;
        buf[buf_step] = ' ';
      } else {
        buf[buf_step] = str[i];
      }
    }
    buf_step++;
  }
  buf[buf_step] = '\0';
  memset(str, 0, strlen(str));
  strcpy(str, buf);
  memset(buf, 0, strlen(buf));
}

/// @brief разбивает выражение на лексемы и формирует массив лексем
/// @param str - преобразоованная функцией s21_add_separator строка выражения
/// @param lexems массив, в которым помещаем лексемы
/// @return кол-во лексем
int s21_lexems(const char *str, char lexems[][256]) {
  char *tmpStr = strdup(str);
  char *savePtr;
  int lexems_count = 0;
  int i = 0;
  char **strarray = NULL;
  char **tmp = NULL;
  char *token = __strtok_r(tmpStr, " ", &savePtr);
  while (token != NULL) {
    tmp = (char **)realloc(strarray, (lexems_count + 1) * sizeof(char *));
    if (tmp) {
      strarray = tmp;
      strarray[lexems_count] = strdup(token);
      lexems_count++;
      token = __strtok_r(NULL, " ", &savePtr);
    }
  }
  // Копируем значения в массив
  for (i = 0; i < lexems_count; i++) {
    strcpy(lexems[i], strarray[i]);
  }
  // Очистка памяти
  for (i = 0; i < lexems_count; i++) free(strarray[i]);
  free(strarray);
  free(tmpStr);
  return lexems_count;
}
