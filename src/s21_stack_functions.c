#include "s21_core.h"

/// @brief Добавляет скобку в стек
/// @param topPtr указатель на вершину стека
/// @param bracket символ скобка
/// @return 0 - ошибок нет, 9 - ошибка выделения памяти
int bracket_push(StackBracketPtr *topPtr, char bracket) {
  int err_flag = ERROR_MEMORY_ALLOCATION;
  StackBracketPtr newPtr;
  newPtr = malloc(sizeof(StackBracket));

  // Вставить узел на вершину стека
  if (newPtr != NULL) {
    newPtr->barcket = bracket;
    newPtr->nextPtr = *topPtr;
    *topPtr = newPtr;
    err_flag = ERROR_NO;
  }
  return err_flag;
}

/// @brief удаляет скобку из стека
/// @param topPtr указатель на вершину стека
void bracket_pop(StackBracketPtr *topPtr) {
  StackBracketPtr tempPtr;
  tempPtr = *topPtr;
  *topPtr = (*topPtr)->nextPtr;
  free(tempPtr);
}

/// @brief проверяет стек на пустоту
/// @param topPtr указатель на вершину стека
/// @return 1 - стек пустой, 0 - стек не пустой
int bracket_isEmpty(const StackBracketPtr topPtr) { return topPtr == NULL; }

/// @brief проверка что баланс скобок правильный
/// @param str строка выражения
/// @return 0 - ошибок нет, 6 - ошибка, баланс скобок некорректный
int s21_check_brackets(char *str) {
  int err_flag = ERROR_NO;
  StackBracketPtr stackPtr = NULL;
  int step = 0;
  char str_brackets[255];
  for (size_t j = 0; j < strlen(str); j++) {
    if (str[j] == '(' || str[j] == ')') {
      str_brackets[step] = str[j];
      step++;
    }
  }
  str_brackets[step] = '\0';
  for (size_t i = 0; i < strlen(str_brackets); i++) {
    if ((str_brackets[i] == '(')) {
      bracket_push(&stackPtr, str_brackets[i]);
    } else if (!bracket_isEmpty(stackPtr) &&
               ((str_brackets[i] == ')') && stackPtr->barcket == '(')) {
      bracket_pop(&stackPtr);
    } else
      err_flag = ERROR_BAD_BRACKETS;
  }
  if (!bracket_isEmpty(stackPtr)) err_flag = ERROR_BAD_BRACKETS;

  while (!bracket_isEmpty(stackPtr)) bracket_pop(&stackPtr);
  return err_flag;
}

/// @brief Добавляет новый элемент в стек
/// @param topPtr указатель на вершину стэка
/// @param stack_data структура данных для размещения в стеке
/// @return 0 - нет ошибок выделения памяти, 9 - память не выделена
int s21_stack_push(StackDataPtr *topPtr, stack_t stack_data) {
  int err_flag = ERROR_MEMORY_ALLOCATION;
  StackDataPtr newPtr;
  newPtr = malloc(sizeof(stack_t));

  // Вставить узел на вершину стека
  if (newPtr != NULL) {
    newPtr->value = stack_data.value;
    newPtr->priority = stack_data.priority;
    newPtr->symbols = stack_data.symbols;
    newPtr->type = stack_data.type;
    newPtr->nextPtr = *topPtr;
    *topPtr = newPtr;
    err_flag = ERROR_NO;
  }
  return err_flag;
}

/// @brief проверяет стек на пустоту
/// @param topPtr указатель на вершину стека
/// @return 1 - стек пустой, 0 - стек не пустой
int s21_isEmpty(const StackDataPtr topPtr) { return topPtr == NULL; }

/// @brief Удаляет узел с вершины стека
/// @param topPtr указатель на вершину стека
/// @return возвращает значение удаленного элемента
stack_t s21_stack_pop(StackDataPtr *topPtr) {
  StackDataPtr tmpPtr = *topPtr;
  stack_t data_item;

  data_item.value = (*topPtr)->value;
  data_item.priority = (*topPtr)->priority;
  data_item.symbols = (*topPtr)->symbols;
  data_item.type = (*topPtr)->type;
  *topPtr = (*topPtr)->nextPtr;
  data_item.nextPtr = NULL;
  free(tmpPtr);
  return data_item;
}

/// @brief Очищает стэк
/// @param topPtr указатель на вершину стэка
void s21_stack_clear(StackDataPtr *topPtr) {
  while (*topPtr != NULL) {
    StackDataPtr ptr = *topPtr;
    *topPtr = (*topPtr)->nextPtr;
    free(ptr);
  }
  *topPtr = NULL;
}

/// @brief Реверсирует стэк
/// @param topPtr указатель на вершину стека, который нужно реверсировать
void s21_stack_revers(StackDataPtr *topPtr) {
  StackDataPtr stack_tmp = NULL;
  stack_t data_item;
  while (*topPtr != NULL) {
    data_item = s21_stack_pop(topPtr);
    s21_stack_push(&stack_tmp, data_item);
  }
  *topPtr = stack_tmp;
}

/// @brief Получает значение элемента на вершиине стека
/// @param topPtr указатель на стек
/// @return значение элемента на вершине стека
stack_t s21_stack_peek(const StackDataPtr *topPtr) {
  stack_t data_item;
  data_item.value = (*topPtr)->value;
  data_item.priority = (*topPtr)->priority;
  data_item.symbols = (*topPtr)->symbols;
  data_item.type = (*topPtr)->type;
  data_item.nextPtr = (*topPtr)->nextPtr;
  return data_item;
}

/// @brief заполняет данными элемент стека
/// @param value лексема
/// @param priority приоритет
/// @param symbols символ
/// @param type тип
/// @return заполненный данными элемент стека
stack_t s21_create_item(const char *value, const int priority,
                        const char symbols, const type_t type) {
  stack_t data_item;
  data_item.nextPtr = NULL;
  data_item.type = type;
  data_item.priority = priority;
  data_item.symbols = symbols;
  if (type == NUMBER) {
    data_item.value = atof(value);
  } else {
    data_item.value = 0.0;
  }

  return data_item;
}

/// @brief Проверяет, что символ является одним из операторов
/// @param oper проверяемый символ
/// @return 0 - не оператор, 1 - оператор
int s21_isOperation(const char oper) {
  int check = 0;
  if ((oper == '-') || (oper == '+') || (oper == '*') || (oper == '/') ||
      (oper == '^') || (oper == '%')) {
    check = 1;
  }
  return check;
}

/// @brief Проверяет приоритет символа. По умолчанию = 0 (символ - цифра)
/// @param oper проверяемый символ
/// @return Приоритет от 0 до 5
int s21_get_priority(const char oper) {
  int priority = 0;
  if ((oper == '+') || (oper == '-'))
    priority = 1;
  else if ((oper == '*') || (oper == '/') || (oper == '%'))
    priority = 2;
  else if (oper == '^')
    priority = 3;
  else if (isalpha(oper))
    priority = 4;
  else if ((oper == '(') || (oper == ')'))
    priority = 5;
  return priority;
}

/// @brief Проверяет функции выражения на валидность
/// @param func кодовая буква названия функции
/// @return 0 - функции не существует, 1 - функции валидна
int s21_valid_function(const char func) {
  int valid = 0;
  char func_lower = tolower(func);
  if ((func_lower == 'c') || (func_lower == 's') || (func_lower == 't') ||
      (func_lower == 'q') || (func_lower == 'l')) {
    valid = 1;
  }
  return valid;
}

/// @brief Конвертирует строку выражение в формат стека
/// @param lexems строка выражения
/// @param lexems_count длина строки выражения
/// @param topPtr указатель на вершину стека
/// @return 0 - ошибок нет, 11 - ошибка конвертирования
int s21_convert_to_stack(const char lexems[][256], const int lexems_count,
                         StackDataPtr *topPtr) {
  int err_flag = ERROR_NO;
  stack_t data_item;

  for (int i = 0; i < lexems_count; i++) {
    char str[256] = {0};
    strcpy(str, lexems[i]);
    if (isdigit(str[0])) {
      data_item = s21_create_item(str, s21_get_priority(str[0]), ' ', NUMBER);
      s21_stack_push(topPtr, data_item);
    } else {
      if (s21_isOperation(str[0])) {
        data_item =
            s21_create_item(str, s21_get_priority(str[0]), str[0], OPERATION);
        s21_stack_push(topPtr, data_item);
      } else {
        if (str[0] == ')') {
          data_item = s21_create_item(str, s21_get_priority(str[0]), str[0],
                                      RIGHT_BRACKET);
          s21_stack_push(topPtr, data_item);
        } else {
          if (str[0] == '(') {
            data_item = s21_create_item(str, s21_get_priority(str[0]), str[0],
                                        LEFT_BRACKET);
            s21_stack_push(topPtr, data_item);
          } else {
            if (s21_valid_function(str[0])) {
              data_item = s21_create_item(str, s21_get_priority(str[0]), str[0],
                                          FUNCTION);
              s21_stack_push(topPtr, data_item);
            } else {
              err_flag = ERROR_BAD_CONVERT;
              break;
            }
          }
        }
      }
    }
  }
  return err_flag;
}