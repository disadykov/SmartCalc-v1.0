#ifndef SRC_S21_ERR_BASE_H_
#define SRC_S21_ERR_BASE_H_

// Текстовое описание кодов ошибок
#define ERROR_BASE                                                             \
  {                                                                            \
    "Errors not found", "Invalid symbol in expression", "Non-existent string", \
        "String is empty", "The expression is too short",                      \
        "The expression is too long",                                          \
        "The number of left parentheses is not equal to the number of right "  \
        "ones or there is no balance",                                         \
        "Incorrect expression", "The expression does not contain operators",   \
        "Memory allocation error", "There is nothing inside the brackets",     \
        "Conversion error", "Unknown function", "Unknown operation"            \
  }

#endif  // SRC_S21_ERR_BASE_H_
