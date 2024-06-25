QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../s21_polish.c \
    ../s21_smart_calc.c \
    ../s21_stack_functions.c \
    ../s21_valid_normal.c \
    credit_calc.cpp \
    depozit_calc.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../s21_core.h \
    ../s21_err_base.h \
    credit_calc.h \
    depozit_calc.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    credit_calc.ui \
    depozit_calc.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
