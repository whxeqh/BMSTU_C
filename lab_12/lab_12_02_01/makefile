# Используемые директории основной программы
SRC_DIR := src/
SRC_PY_DIR := src_py/
OUT_DIR := out/
LIB_DIR := libs/
INC_DIR := inc/
UNIT_DIR := unit_tests/
FUNC_TESTS_DIR := func_tests/scripts/

# Ключи для санитайзеров
ASAN_FLAGS  := -fno-omit-frame-pointer -fsanitize=address
MSAN_FLAGS  := -fno-omit-frame-pointer -fsanitize=memory -fPIE
UBSAN_FLAGS := -fno-omit-frame-pointer -fsanitize=undefined

# Ключи для основной программы
CC := gcc
PY := python3
CFLAGS := -std=c99 -Wall
LDFLAGS := -lm
UNIT_LDFLAGS := -lcheck -lm -lsubunit
DEBUG := -g -O0
LOCAL := -DLOCAL_BUILD
FUNC_FLAGS :=

# Исходные файлы и зависимости
SRCS := $(wildcard $(SRC_DIR)*.c)
OBJS := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.o, $(SRCS))
DEPS := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.d, $(SRCS))

UNIT_SRCS := $(wildcard $(UNIT_DIR)*.c)
UNIT_OBJS := $(patsubst $(UNIT_DIR)%.c, $(OUT_DIR)%.o, $(UNIT_SRCS))
UNIT_DEPS := $(patsubst $(UNIT_DIR)%.c, $(OUT_DIR)%.d, $(UNIT_SRCS))

# Файл для функциональных тестов
TEST_EXEC := func_tests.sh
BASH := bash
VERBOSE := --verbose
VALGRIND := --valgrind

# Исполняемые файл
UNIT_EXEC := unit_tests.exe
APP := main.py

#Файл библиотеки:
NAME_MY_DYN_LIB := mylib
MY_DYN_LIB := lib$(NAME_MY_DYN_LIB).so
NAME_CHECK_DYN_LIB := checkmylib
CHECK_DYN_LIB := lib$(NAME_CHECK_DYN_LIB).so

#---------------------------------------------------------------------------------------------------------------------
.PHONY: debug release func func-v clean asan msan ubsan unit coverage research create_dirs valgrind_app valgrind_unit
#---------------------------------------------------------------------------------------------------------------------

#Цель по умолчанию
release: $(APP) 

#Сборка с отладочной печатью и информацией
local: CFLAGS += $(DEBUG) $(LOCAL)
local: $(EXEC)

#Сборка только с отладочной информацией
debug: CFLAGS += $(DEBUG)
debug: $(EXEC)

#Сборка юнит тестов
unit: CFLAGS += $(DEBUG)
unit: $(UNIT_EXEC)
	./$<

#Запуск программы с тестами под ub-санитайзером
ubsan: CFLAGS += $(DEBUG) $(UBSAN_FLAGS) 
ubsan: CC := clang
ubsan: func-v
ubsan: clean

#Запуск программы с тестами под adress-санитайзером
asan: CFLAGS += $(DEBUG) $(ASAN_FLAGS) 
asan: CC := clang
asan: func-v
asan: clean

#Запуск программы с тестами под memory-санитайзером
msan: CFLAGS += $(DEBUG) $(MSAN_FLAGS) 
msan: CC := clang
msan: func-v
msan: clean

#Запуск функциональных тестов
func: $(EXEC)
	$(BASH) $(FUNC_TESTS_DIR)$(TEST_EXEC) $(FUNC_FLAGS)

#Запуск функциональных тестов в режиме verbose
func-v: FUNC_FLAGS += $(VERBOSE)
func-v: func

#Запуск юнит тестов под valgrind
valgrind_unit: CFLAGS += $(DEBUG)
valgrind_unit: $(UNIT_EXEC)
	@valgrind --leak-check=full --show-error-list=yes --quiet ./$(UNIT_EXEC)

#Запуск функциональных тестов под valgrind
valgrind_app: CFLAGS += $(DEBUG)
valgrind_app: FUNC_FLAGS += $(VERBOSE) $(VALGRIND)
valgrind_app: func
  
#Сборка с покрытием программы
gcov: CFLAGS += --coverage
gcov: LDFLAGS += --coverage
gcov: $(EXEC)

#Запуск программы с функциональными тестами для проверки покрытия кода
coverage: gcov
coverage: func
coverage: 
	@mv $(wildcard $(OUT_DIR)*.gcno) $(SRC_DIR)
	@mv $(wildcard $(OUT_DIR)*.gcda) $(SRC_DIR)
	@gcov $(SRCS)

#Сборка исполняемых файлов
$(APP): $(LIB_DIR)$(MY_DYN_LIB)
	$(PY) $(SRC_PY_DIR)$@

$(UNIT_EXEC): $(OUT_DIR)check_main.o $(LIB_DIR)$(CHECK_DYN_LIB) $(LIB_DIR)$(MY_DYN_LIB)
	$(CC) -o $@ $^ $(UNIT_LDFLAGS)

#Компиляция файлов для юнит тестов
$(OUT_DIR)%.o: $(UNIT_DIR)%.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -fPIC -c -MMD $< -o $@

#Компиляция файлов для программы
$(OUT_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -fPIC -c -MMD $< -o $@

#Сборка библиотеки
$(LIB_DIR)$(MY_DYN_LIB): $(filter-out $(OUT_DIR)main.o, $(OBJS))
	@mkdir -p $(LIB_DIR)
	$(CC) -o $@ -shared $^

#Сборка библиотеки для тестирования
$(LIB_DIR)$(CHECK_DYN_LIB): $(filter-out $(OUT_DIR)main.o, $(UNIT_OBJS))
	@mkdir -p $(LIB_DIR)
	$(CC) -o $@ -shared $^

# Включение файлов зависимостей
include $(wildcard $(OUT_DIR)*.d)

clean:
	rm -f $(OUT_DIR)*.txt $(OUT_DIR)*.d $(OUT_DIR)*.o $(OUT_DIR)*.gcno $(OUT_DIR)*.gcda
	rm -f $(LIB_DIR)*.so
	rm -f *.o *.exe *.txt *.d *.gcov
	rm -f $(SRC_DIR)*.gcno $(SRC_DIR)*.gcda
