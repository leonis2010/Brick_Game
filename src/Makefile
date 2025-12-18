.PHONY: all install uninstall dvi dist test gcov_report check rebuild clean

# Целевой исполняемый файл
TARGET = s21_brick_games_terminal_sueannel

# Компиляторы
CC = gcc -g -Wall -Wextra -Werror 
CXX = g++  -g -Wall -Wextra -Werror -std=c++20

# Флаги компиляции
GCOVFLAGS = -fprofile-arcs -ftest-coverage -lncurses
TEST_FLAGS = -D TEST_MODE

# Операционная система
OS=$(shell uname -s)
Gtest=-lgtest -lgtest_main -pthread
LIBS=$(Gtest)
LINUX=$(Gtest) -lm -lpthread -lrt -lsubunit
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 CXX += -D OS_LINUX
endif
ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 CXX += -D OS_MAC
endif

# Поддиректории и заголовочные файлы
SUBDIRS = brick_game/snake/cli_controller \
			brick_game/snake/model \
			gui/cli \
			brick_game/common \
			brick_game/tetris/model \
			brick_game/tetris/controller


# Список исходных файлов
SOURCES = $(shell find $(SUBDIRS) -type f \( -name '*.c' -o -name '*.cpp' \))

# Разделение на C и C++ файлы
C_SOURCES := $(filter %.c,$(SOURCES))
CPP_SOURCES := $(filter %.cpp,$(SOURCES))

# Объектные файлы
C_OBJS := $(patsubst %.c, %.o, $(C_SOURCES))
CPP_OBJS := $(patsubst %.cpp, %.o, $(CPP_SOURCES))
OBJ_LIBRARY := $(C_OBJS) $(CPP_OBJS)

# Статическая библиотека
STATIC_LIB = s21_terminal_lib_game.a

# Тестовые файлы
STUBS = tests/curs_set_stub.c
TEST_SOURCE=$(shell find tests -type f -name '*.c' -o -name '*.cpp' )
TEST = $(filter-out tests/curs_set_stub.c, $(TEST_SOURCE))

# Цели
all: clean $(STATIC_LIB) $(TARGET)

# Создание статической библиотеки
$(STATIC_LIB): $(OBJ_LIBRARY)
	ar rcs $(STATIC_LIB) $(OBJ_LIBRARY)
	ranlib $(STATIC_LIB)
# find . -type f \( -name "*.o" \) -exec rm -f {} \;

# Компиляция C файлов
%.o: %.c
	$(CC) -c $< -o $@

# Компиляция C++ файлов
%.o: %.cpp
	$(CXX) -c $< -o $@

# Создание исполняемого файла
$(TARGET): brick_game/main_menu.o $(STATIC_LIB)
	$(CXX) brick_game/main_menu.o -o $(TARGET) $(STATIC_LIB) -lncurses
	
# Тестирование
test: COMPILE_FLAGS := $(CXX) $(TEST_FLAGS)
test: $(STATIC_LIB)
ifeq ($(OS), Darwin)
	$(COMPILE_FLAGS) $(TEST) $(STUBS) -o test.out $(STATIC_LIB) $(LIBS) -lncurses
else
	$(COMPILE_FLAGS) $(TEST) $(STUBS) -o test.out $(STATIC_LIB) $(LINUX) -lncurses
endif
	./test.out

# Отчет о покрытии кода
gcov_report: $(STATIC_LIB) $(TEST)
	mkdir -p gcov_report
ifeq ($(OS), Darwin)	
	gcc $(TEST_FLAGS) $(GCOVFLAGS) $(TEST) $(STUBS) $(SOURCES) -lstdc++ -o gcov_report/report.out $(LIBS)
else
	gcc $(TEST_FLAGS) $(GCOVFLAGS) $(TEST) $(STUBS) $(SOURCES) -lstdc++ -o gcov_report/report.out $(LINUX)
endif
	./gcov_report/report.out	

	lcov -t "Отчет о покрытии gcov для тестов" -o gcov_report/Coverage_Report.info -c -d . \
	--ignore-errors unused \
	--ignore-errors gcov \
	--ignore-errors mismatch --ignore-errors inconsistent \
	--exclude '*/src/tests/*' \
	--exclude '*/src/List/constructors_and_destructor.cpp' \
    --exclude '*/usr/local/include/c++/*' \
    --exclude '*/usr/local/include/gtest/*'

	genhtml -o gcov_report/report/ gcov_report/Coverage_Report.info
	rm -f *.gcno *.gcda *.info gcov_report/report.out *.gcov

ifeq ($(OS), Darwin)
	open gcov_report/report/index-sort-f.html
else
	xdg-open gcov_report/report/index-sort-f.html
endif

show: test
	echo "$(TEST)"
	#valgrind --trace-children=yes --track-origins=yes --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file="./report.log" ./test.out
	# cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES)
	#CK_FORK=no valgrind -s  --trace-children=yes --track-origins=yes --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=RESULT_VALGRIND.txt $(SOURCES)
	valgrind --leak-check=yes --log-file="./report.log" ./test.out  && sync #утечки каждого теста
	#valgrind --leak-check=full --log-file="./report.log" --quiet ./test.out # минимум только ошибки и утечки

# Цель для сборки Qt версии проекта
qt: 
	@echo "===== Building Qt version of the project ====="
	@cd gui/desktop/launcher && qmake -o Makefile launcher.pro
	@cd gui/desktop/launcher && $(MAKE)
	@echo "===== Cleaning up Qt build artifacts except executable ====="
	@cd gui/desktop/launcher && rm -f *.o moc_*.cpp ui_*.h qrc_*.cpp moc_predefs.h
	@cd gui/desktop/launcher && rm -f Makefile

# Ручная очи	стка Qt-сборки
qt_clean:
	@echo "===== Cleaning Qt build files manually ====="
	@cd gui/desktop/launcher && rm -f *.o moc_*.cpp ui_*.h qrc_*.cpp moc_predefs.h Makefile
	@rm -rf gui/desktop/launcher/GameLauncher.app
	@rm -rf gui/desktop/launcher/GameLauncher
	@rm -rf gcov_report
	@echo "===== Cleaning Qt done ====="

# Установка исполняемых файлов (терминал + Qt .app)
define print_progress
    @printf "Прогресс: [%-20s] %d%%\r" "$(shell printf '=%.0s' {1..$(1)}))" "$(shell echo "$(1)*5" | bc)"
    @sleep 0.1
endef

install: uninstall
	@echo "🚀 Начало установки..."
	@echo "1/4 🔧 Сборка терминальной версии..."
	@$(MAKE) -s $(TARGET)
	@echo "2/4 🎨 Сборка Qt версии..."
	@$(MAKE) -s qt
	@echo "3/4 📂 Создание папки bin в домашнем каталоге..."
	@install -d $(HOME)/bin
	@echo "4/4 📦 Копирование файлов..."
	@install -m 755 $(TARGET) $(HOME)/bin
	# Попытка скопировать GameLauncher.app, если он существует (macOS)
	@cp -R gui/desktop/launcher/GameLauncher.app $(HOME)/bin || true
	@cp -R gui/desktop/launcher/GameLauncher $(HOME)/bin || true
	@echo "✅ Установка успешно завершена!"
	@echo "Исполняемые файлы находятся в: $(HOME)/bin"

# Удаление установленного файла
uninstall: clean qt_clean
	rm -f $(HOME)/bin/$(TARGET)
	rm -rf $(HOME)/bin/GameLauncher.app

# Генерация документации
dvi: clean
	$(HOME)/goinfre/homebrew/bin/doxygen Doxyfile
	open docs/html/index.html

# Создание архива с исходными файлами
dist: clean
	tar -czf s21_tetris_snake.tar.gz \
	$(shell find . -type f \( \
	-name "*.qrc" -o \
	-name "*.user" -o \
	-name "*.pro" -o \
	-name "*.png" -o \
	-name "*.jpg" -o \
	-name "*.jpeg" -o \
	-name "*.c" -o \
	-name "*.cpp" -o \
	-name "*.h" -o \
	-name "Makefile" -o \
	-name "Doxyfile" -o \
	-name "custom.css" \)) \
	$(shell find gui/cli/documentation -type f)

# Проверка форматирования кода
check:
	find . -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" \) -exec clang-format -i {} \;

# Пересборка
rebuild: clean all

# Очистка
clean:
	@find . -type f \( -name "*.o" -o -name "*.a" -o -name "*.gcno" -o -name "*.gcda" -o -name "*.info" -o -name "*.out" -o -name "*.gcov" -o -name "*.log" \) -exec rm -f {} \;
	@rm -rf ./report
	@rm -rf *.dSYM
	@rm -rf ./docs
	@rm -rf ./s21_tetris_snake.tar.gz
	@rm -rf ./$(TARGET).a
	@rm -rf ./$(TARGET)
	@rm -rf gcov_report
	@echo "*****_clean is done!_*****"

print_sources:
	@echo "Found source files:"
	@echo "$(SOURCES)"

