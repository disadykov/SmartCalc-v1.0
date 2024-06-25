#ifndef SRC_S21_CORE_H_
#define SRC_S21_CORE_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_err_base.h"

#define ERROR_NO 0          // Ошибок нет
#define ERROR_BAD_SYMBOL 1  // Ошибка, не корректный символ
#define ERROR_BAD_STR 2  // Ошибка, строка не корректная
#define ERROR_EMPTY_STR 3  // Ошибка, строка пустая
#define ERROR_SHORT_STR 4  // Ошибка, строка слишком короткая
#define ERROR_LONG_STR 5  // Ошибка, строка слишком длинная
#define ERROR_BAD_BRACKETS 6  // Ошибка, скобки не парные или пары не корректные
#define ERROR_BAD_EXPRESSION 7  // Ошибка, некорректное выражание
#define ERROR_NO_OPERATORS 8  // Ошибка, в выражении нет операторов
#define ERROR_MEMORY_ALLOCATION 9  // Ошибка выделения памяти
#define ERROR_EMPTY_BRACKETS 10    // Ошибка, в скобках пусто
#define ERROR_BAD_CONVERT 11  // Ошибка конвенртирования в стек
#define ERORR_UNKNOWN_FUNCTION 12   // Неизветная функция
#define ERORR_UNKNOWN_OPERATION 13  // Неизветная операция

// Сруктура для проверки корректности парности скобок
typedef struct stackBracket {
  char barcket;
  struct stackBracket *nextPtr;
} StackBracket;
typedef StackBracket *StackBracketPtr;

// Типизируем лексему
typedef enum {
  NUMBER = 0,         // число
  OPERATION = 1,      // +-*/^%
  FUNCTION = 2,       // sin, cos....
  LEFT_BRACKET = 3,   // (
  RIGHT_BRACKET = 4,  // )
  ERROR = 5
} type_t;

// Структура элемента стэка
typedef struct stack_data {
  double value;  // значение числа
  int priority;  // приоритет
  char symbols;  // значение символа
  type_t type;   // инфо о лексеме
  struct stack_data *nextPtr;
} stack_t;
typedef stack_t *StackDataPtr;

// Функции для валидации и нормализации строки выражения
void s21_remove_space(char *str);
void s21_to_lower(char *str);
int s21_valid_characters(char *str);
int s21_is_characters(char symbol);
int s21_is_str_empty(char *str);
char *s21_strerror(int errnum);
int s21_expression_size(char *str);
int s21_brackets_count(char *str);
int s21_check_point(char *str);
int s21_check_operators(char *str);
void s21_replaceX(char *str, const char *x);
int s21_is_operator(const char oper);
int s21_correct_operators(char *str);
int s21_check_brackets(char *str);
int s21_check_func(const char *token, char ch);
int s21_correct_func(const char *str);
int s21_last_symbol(const char *str);
int s21_empty_brackets(const char *str);
int s21_sing_before_func(const char *str);
int s21_first_operator_and_sign(char *str);
char *s21_str_replace(char *dst, int num, const char *str, const char *orig,
                      const char *rep);
void s21_clear_str(char *str, char *buf);
void s21_replace_functions(char *str);
int s21_expression_check(char *expression);
void s21_add_separator(char *str);
int s21_lexems(const char *str, char lexems[][256]);

// Проверка баланска скобок через стек
int bracket_push(StackBracketPtr *topPtr, char bracket);
void bracket_pop(StackBracketPtr *topPtr);
int bracket_isEmpty(const StackBracketPtr topPtr);

// Функции для управления основной структурой стека
int s21_stack_push(StackDataPtr *topPtr, stack_t stack_data);
int s21_isEmpty(const StackDataPtr topPtr);
stack_t s21_stack_pop(StackDataPtr *topPtr);
void s21_stack_clear(StackDataPtr *topPtr);
void s21_stack_revers(StackDataPtr *topPtr);
stack_t s21_stack_peek(const StackDataPtr *topPtr);
int s21_convert_to_stack(const char lexems[][256], const int lexems_count,
                         StackDataPtr *topPtr);
stack_t s21_create_item(const char *value, const int priority,
                        const char symbols, const type_t type);
int s21_isOperation(const char oper);
int s21_get_priority(const char oper);
int s21_valid_function(const char func);

// Польская нотация и вычисления
int s21_polish_postfix(StackDataPtr *topPtr);
double s21_smart_calc(StackDataPtr *topPtr, int *error_code);
double s21_calculation(char *expression, char *x, int *err_code);

#endif  // SRC_S21_CORE_H_
