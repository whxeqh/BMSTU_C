# Используемые директории основной программы
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/
LIB_DIR := libs/
UNIT_DIR := unit_tests/
FUNC_TESTS_DIR := func_tests/scripts/

# Ключи для санитайзеров
ASAN_FLAGS  := -fno-omit-frame-pointer -fsanitize=address
MSAN_FLAGS  := -fno-omit-frame-pointer -fsanitize=memory -fPIE
UBSAN_FLAGS := -fno-omit-frame-pointer -fsanitize=undefined

#Названия файлов библиотек:
NAME_MY_DYN_LIB := mydynlib

#Файлы библиотек
MY_DYN_LIB := lib$(NAME_MY_DYN_LIB).so

# Список библиотек для компоновки
LIBS := $(LIB_DIR)$(MY_DYN_LIB)

# Ключи для программы
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -fPIC -g
LD_FLAGS := -lm -L$(LIB_DIR) -l$(NAME_MY_DYN_LIB) -Wl,-rpath=$(LIB_DIR)
UNIT_LD_FLAGS := -lcheck -lm -lsubunit
DEBUG := -g -O0
LOCAL := -DLOCAL_BUILD
FUNC_FLAGS :=

# Исходные файлы и зависимости
SRCS := $(wildcard $(SRC_DIR)*.c)
OBJS := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.o, $(SRCS))
LIB_OBJS := $(filter-out $(OUT_DIR)main.o, $(OBJS))
DEPS := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.d, $(SRCS))

UNIT_SRCS := $(wildcard $(UNIT_DIR)*.c)
UNIT_OBJS := $(patsubst $(UNIT_DIR)%.c, $(OUT_DIR)%.o, $(UNIT_SRCS))
UNIT_LIB_OBJS := $(filter-out $(UNIT_DIR)main.o, $(UNIT_OBJS))
UNIT_DEPS := $(patsubst $(UNIT_DIR)%.c, $(OUT_DIR)%.d, $(UNIT_SRCS))

# Файл для функциональных тестов
TEST_EXEC := func_tests.sh
BASH := bash
VERBOSE := --verbose
VALGRIND := --valgrind

# Исполняемые файлы
EXEC := app.exe
UNIT_EXEC := unit_tests.exe

#--------------------------------------------------------------------------------------------------------------------
.PHONY: debug release func func-v clean asan msan ubsan unit coverage research create_dirs valgrind_app valgrind_unit 
#--------------------------------------------------------------------------------------------------------------------

# Цель по умолчанию
release: $(EXEC)

# Сборка с отладочной печатью и информацией
local: CFLAGS += $(DEBUG) $(LOCAL)
local: $(EXEC)

# Сборка только с отладочной информацией
debug: CFLAGS += $(DEBUG)
debug: $(EXEC)

# Сборка и запуск юнит тестов
unit: CFLAGS += $(DEBUG)
unit: LD_FLAGS += $(UNIT_LD_FLAGS)
unit: $(UNIT_EXEC)
	./$<

# Запуск программы с тестами под ub-санитайзером
ubsan: CFLAGS += $(DEBUG) $(UBSAN_FLAGS) 
ubsan: CC := clang
ubsan: func-v
ubsan: clean

# Запуск программы с тестами под adress-санитайзером
asan: CFLAGS += $(DEBUG) $(ASAN_FLAGS) 
asan: CC := clang
asan: func-v
asan: clean

# Запуск программы с тестами под memory-санитайзером
msan: CFLAGS += $(DEBUG) $(MSAN_FLAGS) 
msan: CC := clang
msan: func-v
msan: clean

# Запуск функциональных тестов
func: $(EXEC)
	$(BASH) $(FUNC_TESTS_DIR)$(TEST_EXEC) $(FUNC_FLAGS)

# Запуск функциональных тестов в режиме verbose
func-v: FUNC_FLAGS += $(VERBOSE)
func-v: func

# Запуск юнит тестов под valgrind
valgrind_unit: CFLAGS += $(DEBUG)
valgrind_unit: LD_FLAGS += $(UNIT_LD_FLAGS)
valgrind_unit: $(UNIT_EXEC)
	@valgrind --leak-check=full --show-error-list=yes --quiet ./$(UNIT_EXEC)

# Запуск функциональных тестов под valgrind
valgrind_app: CFLAGS += $(DEBUG)
valgrind_app: FUNC_FLAGS += $(VERBOSE) $(VALGRIND)
valgrind_app: func

# Сборка с покрытием программы
gcov: CFLAGS += --coverage
gcov: LD_FLAGS += --coverage
gcov: $(EXEC)

# Запуск программы с функциональными тестами для проверки покрытия кода
coverage: gcov
coverage: func
coverage: 
	@mv $(wildcard $(OUT_DIR)*.gcno) $(SRC_DIR)
	@mv $(wildcard $(OUT_DIR)*.gcda) $(SRC_DIR)
	@gcov $(SRCS)

# Сборка исполняемых файлов
$(EXEC): $(OUT_DIR)main.o $(LIBS)
	$(CC) -o $@ $< $(LD_FLAGS)

$(UNIT_EXEC): $(UNIT_OBJS) $(LIBS)
	$(CC) -o $@ $^ $(LD_FLAGS)

# Компиляция файлов для юнит тестов
$(OUT_DIR)%.o: $(UNIT_DIR)%.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -MMD $< -o $@

# Компиляция файлов для программы
$(OUT_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -MMD $< -o $@

# Компиляция файлов для библиотеки
$(OUT_DIR)%.o: $(LIB_SRC_DIR)%.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -MMD $< -o $@

# Сборка статической библиотеки
$(LIB_DIR)%.a: $(LIB_OBJS)
	@mkdir -p $(LIB_DIR)
	ar cr $@ $^
	ranlib $@

# Сборка динамической библиотеки
$(LIB_DIR)%.so: $(LIB_OBJS)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^

# Включение файлов зависимостей
include $(wildcard $(OUT_DIR)*.d)

clean:
	rm -f $(OUT_DIR)*.txt $(OUT_DIR)*.d $(OUT_DIR)*.o $(OUT_DIR)*.gcno $(OUT_DIR)*.gcda
	rm -f $(LIB_DIR)*.a $(LIB_DIR)*.so
	rm -f *.o *.exe *.txt *.d *.gcov
	rm -f $(SRC_DIR)*.gcno $(SRC_DIR)*.gcda
