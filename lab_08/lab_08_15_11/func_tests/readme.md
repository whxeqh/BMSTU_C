# Тесты для lab_08_15_11
## Входные данные
Аргументы коммандной строки: app.exe action mtr_1.txt [mtr_2.txt] res.txt
В файлах mtr_1.txt и mtr_2.txt в первой строке записаны размеры матрицы, затем сама матрица.

## Выходные данные
Результат сложения, умножения или нахождения обратной матрицы, записанный в файл res.txt

## Позитвные тесты:
### Сложение
- 01 - Матрицы 1x1
- 02 - Матрицы 5x5
- 03 - Матрицы 1x5
- 04 - Матрицы 5x1
- 05 - Матрицы 7x15
- 06 - Матрицы 15x7
---
### Умножение
- 07 - Матрицы 1x1
- 08 - Матрицы 5x5
- 09 - Матрицы 1x5 и 5x1
- 10 - Матрицы 5x1 и 1x5
- 11 - Матрицы 7x15 и 15x7
- 12 - Матрицы 15x7 и 7x15

### Обартная матрица
- 13 - Матрица 1x1
- 14 - Матрица 5x5
- 15 - Единияная матрица 10x10
- 16 - Разреженная матрица 15x15
- 17 - Плотная матрица 15x15
- 18 - Присутствуют нули на диагональных элементах. Матрица: 12x12

## Негативные тесты:
### Общие
- 01 - Три аргумента
- 02 - Шесть аргументов
- 03 - Вторым аргументом передан невалидный вариант действия
- 04 - Пустой файл mtr_1.txt
- 05 - Пустой файл mtr_2.txt
- 06 - В файле есть символы, кроме пробельных
- 07 - Нулевой размер матрицы 
---
### Сложение
- 08 - Матрицы разных размеров
---
### Умножение
- 09 - Не совпадают ни строки, ни столбцы
- 10 - Есть совпадающие размеры, но кол-во столбцов первой матрицы не равно кол-ву строк второй 
---
### Нахождение обратной матрицы
- 11 - Не квадратная матрица
- 12 - Вырожденная матрица