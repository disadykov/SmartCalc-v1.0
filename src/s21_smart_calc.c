#include "s21_core.h"

/// @brief Вычисляет выражение из записи в польской нотации
/// @param topPtr указатель на вершину стэка с польской нотацией
/// @param error_code код ошибки
/// @return 0 - ошибок нет, >0 - ошибка вычисления (деление на 0, корень из
/// отрицательного и т.п.)
double s21_smart_calc(StackDataPtr *topPtr, int *error_code) {
  double result = NAN;
  *error_code = 0;
  double left_value;
  double right_value;
  StackDataPtr digitStack = NULL;
  stack_t result_item;

  while (*topPtr != NULL && *error_code == ERROR_NO) {
    stack_t stack_item = s21_stack_pop(topPtr);
    if (stack_item.type == NUMBER) {
      result_item.type = NUMBER;
      s21_stack_push(&digitStack, stack_item);
    } else {
      if (stack_item.type == OPERATION) {
        right_value = s21_stack_pop(&digitStack).value;
        left_value = s21_stack_pop(&digitStack).value;
        *error_code = ERORR_UNKNOWN_OPERATION;
        switch (stack_item.symbols) {
          case '-':
            result_item.value = left_value - right_value;
            *error_code = ERROR_NO;
            break;
          case '+':
            result_item.value = left_value + right_value;
            *error_code = ERROR_NO;
            break;
          case '*':
            result_item.value = left_value * right_value;
            *error_code = ERROR_NO;
            break;
          case '/':
            result_item.value = (double)left_value / right_value;
            *error_code = ERROR_NO;
            break;
          case '^':
            result_item.value = powf(left_value, right_value);
            *error_code = ERROR_NO;
            break;
          case '%':
            result_item.value = fmod(left_value, right_value);
            *error_code = ERROR_NO;
            break;
        }
        s21_stack_push(&digitStack, result_item);
      } else {
        if (stack_item.type == FUNCTION) {
          right_value = s21_stack_pop(&digitStack).value;
          *error_code = ERORR_UNKNOWN_FUNCTION;
          switch (stack_item.symbols) {
            case 's':
              result_item.value = sin(right_value);
              *error_code = ERROR_NO;
              break;
            case 'S':
              result_item.value = asin(right_value);
              *error_code = ERROR_NO;
              break;
            case 'c':
              result_item.value = cos(right_value);
              *error_code = ERROR_NO;
              break;
            case 'C':
              result_item.value = acos(right_value);
              *error_code = ERROR_NO;
              break;
            case 't':
              result_item.value = tan(right_value);
              *error_code = ERROR_NO;
              break;
            case 'T':
              result_item.value = atan(right_value);
              *error_code = ERROR_NO;
              break;
            case 'q':
              result_item.value = sqrt(right_value);
              *error_code = ERROR_NO;
              break;
            case 'l':
              result_item.value = log10(right_value);
              *error_code = ERROR_NO;
              break;
            case 'L':
              result_item.value = log(right_value);
              *error_code = ERROR_NO;
              break;
          }
          s21_stack_push(&digitStack, result_item);
        }
      }
    }
  }
  result_item = s21_stack_pop(&digitStack);
  if (digitStack != NULL || result_item.type != NUMBER) {
    *error_code = ERROR_BAD_EXPRESSION;
    result = NAN;
  } else {
    result = result_item.value;
  }
  s21_stack_clear(&digitStack);
  return result;
}

/// @brief Проверяет строку выражение на корректность, проводит ее нормализацию
/// и производит вычисления
/// @param expression строка выражение
/// @param x значение переменной Х
/// @param error_code код ошибки
/// @return результат вычисления или NAN
double s21_calculation(char *expression, char *x, int *error_code) {
  *error_code = ERROR_NO;
  double result = NAN;

  // Перевод в нижний регистр
  s21_to_lower(expression);
  // удалим пробелы
  s21_remove_space(expression);
  // Подстановка значения x
  s21_replaceX(expression, x);

  if (s21_expression_check(expression) != ERROR_NO) {
    *error_code = s21_expression_check(expression);
  } else {
    s21_replace_functions(expression);
    s21_add_separator(expression);

    char strarray[500][256];
    int lexems_count = s21_lexems(expression, strarray);

    StackDataPtr stack_item = NULL;
    *error_code = s21_convert_to_stack(strarray, lexems_count, &stack_item);

    if (*error_code == ERROR_NO) {
      s21_stack_revers(&stack_item);
      *error_code = s21_polish_postfix(&stack_item);
      if (*error_code == ERROR_NO) {
        s21_stack_revers(&stack_item);
        result = s21_smart_calc(&stack_item, error_code);
        s21_stack_clear(&stack_item);
      }
    }
  }
  return result;
}
