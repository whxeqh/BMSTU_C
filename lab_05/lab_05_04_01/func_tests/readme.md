# Тесты для lab_05_04
## Входные данные
Аргументы командной строки

## Выходные данные
Измененный бинарный файл или созданный текстовый файл

## Позитвные тесты:
### Параметр ft (вывод студентов, фамилия которых начинается с заданной подстроки):
#### Один подходящий студент
- 01 - В начале файла
- 02 - В середине файла
- 03 - В конце файла

#### Несколько подходящих студентов
- 04 - Подряд идущие
- 05 - Через одного
- 06 - В начале и в конце файла
- 07 - В начале, конце и середине файла

### Параметр db (Удаление студентов с низким avg из файла):
#### Один студент для удаления
- 8 - В начале файла
- 9 - В середине файла
- 10 - В конце файла

#### Несколько студентов для удаления
- 11 - Подряд идущие
- 12 - Через одного
- 13 - В начале и в конце файла
- 14 - В начале, конце и середине файла

#### Нет студентов для удаления
- 15 - Один студент
- 16 - У всех студентов одинаковый avg 

## Негативные тесты:
- 01 - Недостаточно аргументов
- 02 - Много аргументов
- 03 - Имя файла указано неверно (ft)
- 04 - Пустой файл (ft)
- 05 - Имя файла указано неверно (db)
- 06 - Пустой файл (db)
- 07 - Нет студентов для записи (с заданой подстрокой (ft))