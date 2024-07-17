#!/bin/bash

VERBOSE=false
total_positive_tests=0
total_negative_tests=0
positive_tests_passed=0
negative_tests_passed=0

# Проверяем, задан ли не тихий режим
if [[ "$1" == "-v" ]]; then
    VERBOSE=true
fi

# Получаем путь к каталогу скрипта
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

# Функция для запуска позитивных тестов
run_positive_tests() 
    if $VERBOSE; then  
        echo "----------------------"
        echo "RUNNING POSITIVE TESTS"
        echo
    fi

    for in_file in "$SCRIPT_DIR"/../data/pos_*_in.txt; do
        # Проверяем, существует ли соответствующий файл с ожидаемым выходом
        out_file="${in_file/_in/_out}"
        if [ ! -f "$out_file" ]; then
            continue
        fi

        # Проверяем, существует ли соответствующий файл с аргументами
        ((total_positive_tests++))
        args_file="${in_file/_in/_args}"
        if [ -f "$args_file" ]; then
            if "$SCRIPT_DIR"/pos_case.sh "$in_file" "$out_file" "$args_file"; then
                ((positive_tests_passed++))
                if $VERBOSE; then
                    echo -e "$(basename "$in_file"): \e[32mPASSED\e[0m"
                fi
            else
                if $VERBOSE; then
                    echo -e "$(basename "$in_file"): \e[31mFAILED\e[0m"
                    echo
                    echo -e "Input data:\n$(sed 's/^/\t/' "$in_file")"
                    echo -e "Expected output:\n$(sed 's/^/\t/' "$out_file")"
                    echo -e "Actual output:\n$(sed 's/^/\t/' output.txt)"
                    echo
                fi
            fi
        else
            if "$SCRIPT_DIR"/pos_case.sh "$in_file" "$out_file"; then
                ((positive_tests_passed++))
                if $VERBOSE; then
                        echo -e "$(basename "$in_file"): \e[32mPASSED\e[0m"
                    fi
                else
                    if $VERBOSE; then
                        echo -e "$(basename "$in_file"): \e[31mFAILED\e[0m"
                        echo
                        echo -e "Input data:\n$(sed 's/^/\t/' "$in_file")"
                    echo -e "Expected output:\n$(sed 's/^/\t/' "$out_file")"
                    echo -e "Actual output:\n$(sed 's/^/\t/' output.txt)"
                    echo
                fi
            fi
        fi
    done

# Функция для запуска негативных тестов
run_negative_tests() {
    if $VERBOSE; then  
        echo "----------------------"
        echo "RUNNING NEGATIVE TESTS"
        echo
    fi
    
    for in_file in "$SCRIPT_DIR"/../data/neg_*_in.txt; do
        ((total_negative_tests++))
        args_file="${in_file/_in/_args}"
        if [ -f "$args_file" ]; then
            if "$SCRIPT_DIR"/neg_case.sh "$in_file" "$args_file"; then
                ((negative_tests_passed++))
                if $VERBOSE; then
                    echo -e "$(basename "$in_file"): \e[32mPASSED\e[0m"
                fi
            else
                if $VERBOSE; then
                    echo -e "$(basename "$in_file"): \e[31mFAILED\e[0m"
                    echo
                    echo -e "Input data:\n$(sed 's/^/\t/' "$in_file")"
                    echo -e "Actual output:\n$(sed 's/^/\t/' output.txt)"
                    echo
                fi
            fi
        else
            if "$SCRIPT_DIR"/neg_case.sh "$in_file"; then
                ((negative_tests_passed++))
                if $VERBOSE; then
                    echo -e "$(basename "$in_file"): \e[32mPASSED\e[0m"
                fi
            else
                if $VERBOSE; then
                    echo -e "$(basename "$in_file"): \e[31mFAILED\e[0m"
                    echo
                    echo -e "Input data:\n$(sed 's/^/\t/' "$in_file")"
                    echo -е "Actual output:\n$(sed 's/^/\t/' output.txt)"
                    echo
                fi
            fi
        fi
    done
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
    if $VERBOSE; then
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
    if $VERBOSE; then
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
    echo -е "Negative tests passed: \e[31m$negative_tests_passed\e[0m/\e[32m$total_negative_tests\e[0m"
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
