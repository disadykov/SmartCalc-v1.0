#include "s21_core.h"

/// @brief Переводит стек строки-выражения в обратную польскую запись
/// @param topPtr указать на вершину стэка
/// @return 0 - ошибок нет, 7 - в выражении допущена ошибка
int s21_polish_postfix(StackDataPtr *topPtr) {
  int err_flag = ERROR_NO;
  StackDataPtr postfix = NULL;
  StackDataPtr support = NULL;
  while (*topPtr != NULL) {
    stack_t stack_item = s21_stack_pop(topPtr);
    if (stack_item.type == NUMBER) {
      s21_stack_push(&postfix, stack_item);
    } else {
      if (stack_item.type == LEFT_BRACKET) {
        s21_stack_push(&support, stack_item);
      } else {
        if (stack_item.type == OPERATION || stack_item.type == FUNCTION) {
          if (support == NULL) {
            s21_stack_push(&support, stack_item);
          } else {
            if (support->priority >= stack_item.priority) {
              while ((support != NULL) &&
                     (support->priority >= stack_item.priority) &&
                     (support->priority != 5)) {
                s21_stack_push(&postfix, s21_stack_pop(&support));
              }
              s21_stack_push(&support, stack_item);
            } else {
              s21_stack_push(&support, stack_item);
            }
          }
        } else {
          if (stack_item.type == RIGHT_BRACKET) {
            if (support == NULL) {
              err_flag = ERROR_BAD_EXPRESSION;
              break;
            } else {
              stack_t support_item = s21_stack_pop(&support);
              while (support != NULL && support_item.symbols != '(') {
                s21_stack_push(&postfix, support_item);
                support_item = s21_stack_pop(&support);
              }
            }
          }
        }
      }
    }
  }

  while (support != NULL) {
    stack_t support_item = s21_stack_peek(&support);
    if (support_item.type == LEFT_BRACKET) {
      err_flag = ERROR_BAD_EXPRESSION;
      break;
    } else {
      s21_stack_push(&postfix, s21_stack_pop(&support));
    }
  }
  *topPtr = postfix;
  s21_stack_clear(&support);
  return err_flag;
}