# Используемые директории основной программы
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/
UNIT_DIR := unit_tests/
FUNC_TESTS_DIR := func_tests/scripts/

# Ключи для санитайзеров
ASAN_FLAGS  := -fno-omit-frame-pointer -fsanitize=address
MSAN_FLAGS  := -fno-omit-frame-pointer -fsanitize=memory -fPIE
UBSAN_FLAGS := -fno-omit-frame-pointer -fsanitize=undefined

# Ключи для основной программы
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra
LDFLAGS := -lm
UNIT_LDFLAGS := -lcheck -lm
DEBUG := -g -O0
LOCAL := -DLOCAL_BUILD
FUNC_FLAGS :=

# Исходные файлы и зависимости
SRCS := $(wildcard $(SRC_DIR)*.c)
OBJS := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.o, $(SRCS))

UNIT_SRCS := $(wildcard $(UNIT_DIR)*.c)
UNIT_OBJS := $(patsubst $(UNIT_DIR)%.c, $(OUT_DIR)%.o, $(UNIT_SRCS))

# Файл для функциональных тестов
TEST_EXEC := func_tests.sh
BASH := bash
VERBOSE := --verbose
VALGRIND := --valgrind

# Исполняемые файл
EXEC := app.exe
UNIT_EXEC := unit_tests.exe

#Цель по умолчанию
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: debug release func func-v clean asan msan ubsan unit coverage valgrind_app valgrind_unit

local: CFLAGS += $(DEBUG) $(LOCAL)
local: $(EXEC)

debug: CFLAGS += $(DEBUG)
debug: $(EXEC)

release: $(EXEC)

$(UNIT_EXEC): $(filter-out $(OUT_DIR)main.o, $(OBJS)) $(UNIT_OBJS)
	$(CC) $^ -o $@ $(UNIT_LDFLAGS)

unit: CFLAGS += $(DEBUG)
unit: $(UNIT_EXEC)
	./$<

ubsan: CFLAGS += $(DEBUG) $(UBSAN_FLAGS) 
ubsan: CC := clang
ubsan: func-v
ubsan: clean

asan: CFLAGS += $(DEBUG) $(ASAN_FLAGS) 
asan: CC := clang
asan: func-v
asan: clean

msan: CFLAGS += $(DEBUG) $(MSAN_FLAGS) 
msan: CC := clang
msan: func-v
msan: clean

func: $(EXEC)
	$(BASH) $(FUNC_TESTS_DIR)$(TEST_EXEC) $(FUNC_FLAGS)

func-v: FUNC_FLAGS += $(VERBOSE)
func-v: func

valgrind_unit: CFLAGS += $(DEBUG)
valgrind_unit: $(UNIT_EXEC)
	@valgrind --leak-check=full --show-error-list=yes --quiet ./$(UNIT_EXEC)

valgrind_app: CFLAGS += $(DEBUG)
valgrind_app: FUNC_FLAGS += $(VERBOSE) $(VALGRIND)
valgrind_app: func
  
gcov: CFLAGS += --coverage
gcov: LDFLAGS += --coverage
gcov: $(EXEC)

coverage: gcov
coverage: func
coverage: 
	@mv $(wildcard $(OUT_DIR)*.gcno) $(SRC_DIR)
	@mv $(wildcard $(OUT_DIR)*.gcda) $(SRC_DIR)
	@gcov $(SRCS)

$(OUT_DIR)%.o: $(UNIT_DIR)%.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -MMD $< -o $@

$(OUT_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -MMD $< -o $@

# Включение файлов зависимостей
include $(wildcard $(OUT_DIR)*.d)

clean:
	rm -rf $(OUT_DIR)
	rm -f *.o *.exe *.d *.gcov
	rm -f $(SRC_DIR)*.gcno $(SRC_DIR)*.gcda
