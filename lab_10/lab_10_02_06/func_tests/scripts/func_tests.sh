#!/bin/bash

total_positive_tests=0
total_negative_tests=0
positive_tests_passed=0
negative_tests_passed=0

# Проверка, есть ли флаг "--valgrind" среди аргументов
use_valgrind=""
for arg in "$@"; do
    if [ "$arg" == "--valgrind" ]; then
        use_valgrind=$arg
        break
    fi
done

# Проверка, есть ли флаг "--verbose" среди аргументов
verbose=false
for arg in "$@"; do
    if [ "$arg" == "--verbose" ]; then
        verbose=true
        break
    fi
done


echo
echo -e "\e[32mI LOVE YOU!\e[0m"
echo

# Получаем путь к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

# Функция для запуска позитивных тестов
run_positive_tests() {
    if $verbose; then  
        echo "----------------------"
        echo "RUNNING POSITIVE TESTS"
        echo
    fi

    # Проверка наличия файлов args
    args_files_found=false
    for args_file in "$SCRIPT_DIR"/../data/pos_*_args.txt; do
        if [ -f "$args_file" ]; then
            args_files_found=true
            break
        fi
    done

    if $args_files_found; then
        # Если есть args файлы, обрабатываем их
        for args_file in "$SCRIPT_DIR"/../data/pos_*_args.txt; do
            ((total_positive_tests++))
            in_file="${args_file/_args/_in}"
            out_file="${args_file/_args/_out}"

            if "$SCRIPT_DIR"/pos_case.sh true "$args_file" "$use_valgrind"; then
                ((positive_tests_passed++))
                if $verbose; then
                    echo -e "$(basename "$in_file"): \e[32mPASSED\e[0m"
                fi
            else
                if $verbose; then
                    echo -e "$(basename "$in_file"): \e[31mFAILED\e[0m"
                    echo
                    echo -e "Input data:\n$(sed 's/^/\t/' "$in_file")"
                    echo -e "Expected output:\n$(sed 's/^/\t/' "$out_file")"
                    echo -e "Actual output:\n$(sed 's/^/\t/' "$SCRIPT_DIR"/../../out/output.txt)"
                    echo
                fi
            fi
        done
    else
        # Если нет args файлов, проверяем только in/out файлы
        for in_file in "$SCRIPT_DIR"/../data/pos_*_in.txt; do
            out_file="${in_file/_in/_out}"

            if [ -f "$in_file" ] && [ -f "$out_file" ]; then
                ((total_positive_tests++))
                if "$SCRIPT_DIR"/pos_case.sh false "$in_file" "$out_file" "$use_valgrind"; then
                    ((positive_tests_passed++))
                    if $verbose; then
                        echo -e "$(basename "$in_file"): \e[32mPASSED\e[0m"
                    fi
                else
                    if $verbose; then
                        echo -e "$(basename "$in_file"): \e[31mFAILED\e[0m"
                        echo
                        echo -e "Input data:\n$(sed 's/^/\t/' "$in_file")"
                        echo -e "Expected output:\n$(sed 's/^/\t/' "$out_file")"
                        echo -e "Actual output:\n$(sed 's/^/\t/' "$SCRIPT_DIR"/../../out/output.txt)"
                        echo
                    fi
                fi
            fi
        done
    fi
}


# Функция для запуска негативных тестов
run_negative_tests() {
    if $verbose; then  
        echo "----------------------"
        echo "RUNNING NEGATIVE TESTS"
        echo
    fi
    
    # Проверка наличия файлов args
    args_files_found=false
    for args_file in "$SCRIPT_DIR"/../data/neg_*_args.txt; do
        if [ -f "$args_file" ]; then
            args_files_found=true
            break
        fi
    done

    if $args_files_found; then
        # Если есть args файлы, обрабатываем их
        for args_file in "$SCRIPT_DIR"/../data/neg_*_args.txt; do
            ((total_negative_tests++))
            in_file="${args_file/_args/_in}"

            if "$SCRIPT_DIR"/neg_case.sh true "$args_file" "$use_valgrind"; then
                ((negative_tests_passed++))
                if $verbose; then
                    echo -e "$(basename "$in_file"): \e[32mPASSED\e[0m"
                fi
            else
                if $verbose; then
                    echo -e "$(basename "$in_file"): \e[31mFAILED\e[0m"
                    echo
                    echo -e "Input data:\n$(sed 's/^/\t/' "$in_file")"
                    echo -e "Actual output:\n$(sed 's/^/\t/' "$SCRIPT_DIR"/../../out/output.txt)"
                    echo
                fi
            fi
        done
    else
        # Если нет args файлов, проверяем только in/out файлы
        for in_file in "$SCRIPT_DIR"/../data/neg_*_in.txt; do
            if [ -f "$in_file" ]; then
                ((total_negative_tests++))
                if "$SCRIPT_DIR"/neg_case.sh false "$in_file" "$use_valgrind"; then
                    ((negative_tests_passed++))
                    if $verbose; then
                        echo -e "$(basename "$in_file"): \e[32mPASSED\e[0m"
                    fi
                else
                    if $verbose; then
                        echo -e "$(basename "$in_file"): \e[31mFAILED\e[0m"
                        echo
                        echo -e "Input data:\n$(sed 's/^/\t/' "$in_file")"
                        echo -e "Actual output:\n$(sed 's/^/\t/' "$SCRIPT_DIR"/../../out/output.txt)"
                        echo
                    fi
                fi
            fi
        done
    fi
}

# Запуск позитивных тестов
positive_tests_exist=false
for file in "$SCRIPT_DIR"/../data/pos*_in.txt; do
    if [ -f "$file" ]; then
        positive_tests_exist=true
        break
    fi
done

if $positive_tests_exist; then
    run_positive_tests
else
    if $verbose; then
        echo '-----------------------------'
        echo "Positive tests were not found"
        echo
    fi
fi

# Запуск негативных тестов
negative_tests_exist=false
for file in "$SCRIPT_DIR"/../data/neg*_in.txt; do
    if [ -f "$file" ]; then
        negative_tests_exist=true
        break
    fi
done

if $negative_tests_exist; then
    run_negative_tests
else
    if $verbose; then
        echo '-----------------------------'
        echo "Negative tests were not found"
        echo
    fi
fi

# Вывод статистики
echo "================================"
echo "TESTING IS OVER"
echo "STATS DOWN BELOW"
echo "================================"
echo
echo "Total positive tests: $total_positive_tests"
if [ "$positive_tests_passed" -eq "$total_positive_tests" ]; then
    echo -e "Positive tests passed: \e[32m$positive_tests_passed/$total_positive_tests\e[0m"
else
    echo -e "Positive tests passed: \e[31m$positive_tests_passed\e[0m/\e[32m$total_positive_tests\e[0m"
fi
echo "--------------------------------"
echo
echo "Total negative tests: $total_negative_tests"
if [ "$negative_tests_passed" -eq "$total_negative_tests" ]; then
    echo -e "Negative tests passed: \e[32m$negative_tests_passed/$total_negative_tests\e[0m"
else
    echo -e "Negative tests passed: \e[31m$negative_tests_passed\e[0m/\e[32m$total_negative_tests\e[0m"
fi
echo "--------------------------------"
echo
echo "======================================"
if [ "$((positive_tests_passed + negative_tests_passed))" -eq "$((total_negative_tests + total_positive_tests))" ]; then
    echo -e "\e[32mALL TESTS HAVE BEEN PASSED\e[0m"
else
    echo -e "\e[31mNOT ALL TESTS HAVE BEEN PASSED\e[0m"
fi
echo "======================================"
echo
