# Тесты для lab_10_01_01
## Входные данные
Аргументы коммандной строки

## Выходные данные
Список продуктов (название, цена)

## Позитвные тесты:

#### FIELD = pb
- 01 - Один элемент
- 02 - Два элемент
- 03 - Три элемент
---

#### FIELD = rv
- 04 - Один элемент
- 05 - Два элемента
- 06 - Три элемента
- 07 - Восемь элементов
---

#### FIELD = s
- 08 - Один элемент
- 09 - Два элемента упорядочены сразу
- 10 - Два элемента не упорядочены сразу
- 11 - Элементы упорядочены по убыванию
- 12 - Элементы упорядочены по возрастанию
- 13 - Элементы упорядочены сначала по убыванию, потом по возрастанию 
- 14 - Элементы упорядочены сначала по возрастанию, потом по убыванию 
- 15 - Тест на устойчивость сортировки
---

## Негативные тесты:
- 01 - Мало аргументов ( < 4 )
- 02 - Много аргументов ( > 4 )
- 03 - Неверный первый аргумент
- 04 - Пустой входной файл
- 05 - Пустое поле "название"
- 06 - Пустое поле "цена"
- 07 - Несуществующий входной файл