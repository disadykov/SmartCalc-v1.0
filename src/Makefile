KBUILD_CFLAGS += -w
GCC = gcc
FLAG_GCOV = --coverage
FLAGS = -Wall -Werror -Wextra
TESTFILE = test/s21_SmartCalc
DIST_DIR=s21_SmartCalc-1.0
WORK_DIR=smart_calc
INST_DIR=~/SmartCalc-1.0

PATH_PROJECT = $(shell pwd)
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LIBS_OS_CHECK = -lcheck -lsubunit -lm -lpthread -lrt
	OSLINUX = 1
else
	LIBS_OS_CHECK = -lcheck -lm -lpthread
	OSLINUX = 0
endif

all: clean dist install gcov_report 

test: clean
	cp s21*.c test/
	cp s21*.h test/
	bash test/check_test.sh $(GCC) "$(FLAGS)" "$(LIBS_OS_CHECK)" $(FLAG_GCOV)

leak_test: clean
	cp s21*.c test/
	cp s21*.h test/
	bash test/leaks_test.sh $(GCC) "$(FLAGS)" "$(LIBS_OS_CHECK)" $(FLAG_GCOV) "$(OSLINUX)"

gcov_report: test
	bash test/gcov_print.sh
	gcov test/s21_*.gcda	
	lcov -t "s21_SmartCalc" -o $(TESTFILE).info -c -d .
	genhtml -o report $(TESTFILE).info

open_report:
	open $(PATH_PROJECT)/report/index.html

check:
	clang-format -n --style=Google *.h *.c
	clang-format -n --style=Google smart_calc/*.cpp
	clang-format -n --style=Google smart_calc/*.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.h
	cppcheck --enable=all --suppress=missingIncludeSystem test/*.check

clean: uninstall
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt a.out.dSYM tests main 
	-rm -rf test/*.gcda test/*.info test/*.gcno test/*.c test/*.o test/*.h
	-rm -rf report
	-rm -rf $(WORK_DIR)/smart_calc
	-rm -rf *.tar
	-rm -rf manual

dev: clean
	$(GCC) $(FLAGS) -c *.c -fsanitize=address -g
	$(GCC) $(FLAGS) *.c -o main $(LIBS_OS_CHECK)
	clear
	./main

install:
	@echo "===>    Installation has started     <==="
	cd $(WORK_DIR); qmake $(WORK_DIR).pro
	cd $(WORK_DIR); make
	cd $(WORK_DIR); make clean 
	cd $(WORK_DIR); rm -rf Makefile
	cd $(WORK_DIR); rm -rf .qmake.stash
	-mkdir $(INST_DIR)
	cd $(WORK_DIR); mv smart_calc $(INST_DIR)/s21_smart_calc
	open $(INST_DIR)

uninstall:
	-rm -rf $(INST_DIR)

dist:
	-mkdir $(DIST_DIR)
	-mkdir $(DIST_DIR)/$(WORK_DIR)
	cp *.c *.h Makefile $(DIST_DIR)
	cp -R $(WORK_DIR) $(DIST_DIR)
	tar --totals -cvf $(DIST_DIR).tar $(DIST_DIR)
	-rm -rf $(DIST_DIR)

run: install
	$(INST_DIR)/./s21_smart_calc

dvi:
	makeinfo manual.texi --html
	open ./manual/index.html