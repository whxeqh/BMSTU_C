# Используемые директории основной программы
SRC_DIR := src/
OUT_DIR := out/
INC_DIR := inc/
UNIT_DIR := unit_tests/
FUNC_TESTS_DIR := func_tests/scripts/

# Директории для исследования
RESEARCH_DIR := research/
SCRIPTS_DIR := $(RESEARCH_DIR)scripts/
RESEARCH_SRC_DIR := $(RESEARCH_DIR)src/
RESEARCH_INC_DIR := $(RESEARCH_DIR)inc/
RESEARCH_OUT_DIR := $(RESEARCH_DIR)out/

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
DEPS := $(patsubst $(SRC_DIR)%.c, $(OUT_DIR)%.d, $(SRCS))

UNIT_SRCS := $(wildcard $(UNIT_DIR)*.c)
UNIT_OBJS := $(patsubst $(UNIT_DIR)%.c, $(OUT_DIR)%.o, $(UNIT_SRCS))
UNIT_DEPS := $(patsubst $(UNIT_DIR)%.c, $(OUT_DIR)%.d, $(UNIT_SRCS))

RESEARCH_SRCS := $(wildcard $(RESEARCH_SRC_DIR)*.c)
RESEARCH_DEPS := $(patsubst $(RESEARCH_SRC_DIR)%.c, $(RESEARCH_OUT_DIR)%.d, $(RESEARCH_SRCS))
RESEARCH_OBJS := $(patsubst $(RESEARCH_SRC_DIR)%.c, $(RESEARCH_OUT_DIR)%.o, $(RESEARCH_SRCS))

# Файл для функциональных тестов
TEST_EXEC := func_tests.sh
BASH := bash
VERBOSE := --verbose
VALGRIND := --valgrind

# Исполняемые файл
EXEC := app.exe
UNIT_EXEC := unit_tests.exe
RESEARCH_EXEC := research.exe

#Цель по умолчанию
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: debug release func func-v clean asan msan ubsan unit coverage research create_dirs valgrind_app valgrind_unit

local: CFLAGS += $(DEBUG) $(LOCAL)
local: $(EXEC)

debug: CFLAGS += $(DEBUG)
debug: $(EXEC)

release: $(EXEC)

create_dirs:
	mkdir -p $(RESEARCH_DIR)data/mysort/random_order
	mkdir -p $(RESEARCH_DIR)data/mysort/reverse_order
	mkdir -p $(RESEARCH_DIR)data/mysort/sorted_order
	mkdir -p $(RESEARCH_DIR)data/qsort/random_order
	mkdir -p $(RESEARCH_DIR)data/qsort/reverse_order
	mkdir -p $(RESEARCH_DIR)data/qsort/sorted_order
	mkdir -p $(RESEARCH_DIR)plots

$(RESEARCH_EXEC): $(RESEARCH_OBJS) out/array.o
	$(CC) $^ -o $@

research: $(RESEARCH_EXEC) create_dirs  
	./$<
	@$(BASH) $(SCRIPTS_DIR)makeplots.sh

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

$(RESEARCH_OUT_DIR)%.o: $(RESEARCH_SRC_DIR)%.c
	@mkdir -p $(RESEARCH_OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(RESEARCH_INC_DIR) -c -MMD $< -o $@


# Включение файлов зависимостей
include $(wildcard $(OUT_DIR)*.d)

clean:
	rm -f $(OUT_DIR)*.txt $(OUT_DIR)*.d $(OUT_DIR)*.o $(OUT_DIR)*.gcno $(OUT_DIR)*.gcda
	rm -f *.o *.exe *.txt *.d *.gcov
	rm -f $(SRC_DIR)*.gcno $(SRC_DIR)*.gcda
	$(BASH) $(SCRIPTS_DIR)clean.sh
