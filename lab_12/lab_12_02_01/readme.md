# Проект: Лабораторная работа lab_12_02_01

## Описание директорий
1. **src** — исходный код на языке C.
2. **src_py** — исходный код на языке python 

---

## Проверка работоспособности
- **`make`** или **`make release`**: сборка библиотеки и запуск скрипта на языке python c графическим интерфейсом.
- **`make unit`**: запуск юнит-тестов.
- **`make valgrind_unit`**: запуск юнит-тестов под Valgrind для проверки утечек памяти.

---

## Особенности
- файлы библиотек `*.so` или `*.a` после сборки будут находиться  в папке `libs/`.
