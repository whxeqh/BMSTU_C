# Задание №1
- Для создания локального репозитория использовал команду 'git init'
``` bash 
$ git init
Initialized empty Git repository in /b/work2_2/q/.git/

$ ls -a
.  ..  .git
```
- Затем создал файл *.gitignore*, в котором прописываю строку `**/__pycache__/**` и поместил его под версионный контроль:
``` bash
$ git add .gitignore

$ git commit -m ".gitignore was added."
[master (root-commit) b466b68] .gitignore was added.
 1 file changed, 5 insertions(+)
 create mode 100644 .gitignore
```
- Так как мой вариант 16, то я взял вторую папку, а именно *src_2*, в которой располагались файлы *main.py* и *iarray.py*. После запуска я тоже поместил их под версионный контроль:
``` bash 
$ git status
On branch master
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        iarray.py
        main.py

nothing added to commit but untracked files present (use "git add" to track)

$ git add .

$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   iarray.py
        new file:   main.py

$ git commit -m "Python file was added"
[master 48a2ee4] Python file was added
 2 files changed, 47 insertions(+)
 create mode 100644 iarray.py
 create mode 100644 main.py
```
- Командой 'git branch fix' создаю ветвь с названием fix, а командой 'git checkout fix' перехожу в эту ветвь. Затем командой `git branch` проверяю, что нахожусь в ветви fix:
``` bash 
$ git branch fix

$ git checkout fix
Switched to branch 'fix'

$ git branch
* fix
  master
```
- Проанализировав исходный код программы я понял, что она ищет индекс максимального элемента списка. Функции `get_max_pos` как раз возвращает индекс этого элемента, а `print_array` выводит массив в консоль, в `test_1` находится тест, который проверяет работоспособность программы, а функция `main` всё это организовывает. Я добавил комментарии в файлы *iarray.py* и *main.py* и добавил их под версионный контроль:
``` bash 
$ git add .

$ git commit -m "The program find index of the maximum element in array."
[fix 428bdac] The program find index of the maximum element in array.
 2 files changed, 3 insertions(+), 1 deletion(-)
```
- Затем я добавил тест, демонстрирующий наличие ошибки в программе
``` python 
def test_2():
  arr = list()

  arr.append(10)
  arr.append(5)
  arr.append(3)
  arr.append(8)

  return arr, 4
```
Выводимый результат:
``` bash
Traceback (most recent call last):
...
...
UnboundLocalError: local variable 'j' referenced before assignment
```
Ожидаемый результат:
``` bash 
Source
10 5 3 8
Max pos = 0 
```
Затем поместил изменения под версионный контроль:
``` bash 
$ git commit -m "Test 2 was added and program crahes."
[fix e9ac565] Test 2 was added and program crahes.
 1 file changed, 16 insertions(+)
```
- Я создал issue - https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii/-/issues/4, где описал тест, который выводит неверный результат
- Программа работала неверно из-за того, что переменная j была не инициализирована и из-за этого, при нахождении максимального элемента в начале списка, программа аварийно завершалась
- Затем я зафиксировал изменения:
``` bash 
$ git add iarray.py

$ git status
On branch fix
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   iarray.py

$ git commit -m "Corrected program."
[fix 9c5bf33] Corrected program.
 1 file changed, 1 insertion(+)
``` 
- Описал ошибку в issue https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii/-/issues/4
- Командой `git checkout master` переключился в ветку master и командой `git merge` объединил ветки. Конфликта не было:
``` bash 
$ git checkout master
Switched to branch 'master'

$ git branch
  fix
* master

$ git merge fix
Updating 48a2ee4..9c5bf33
Fast-forward
 iarray.py |  4 +++-
 main.py   | 17 +++++++++++++++++
 2 files changed, 20 insertions(+), 1 deletion(-)
```
- Указал номер ревизии, в которой исправления были перенесены из ветки fix в
ветвь mаster и закрыл issue https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii/-/issues/1 
- Затем проанализировал историю изменений с помощью команды `git log --graph --all --oneline`:
``` bash 
$ git log --graph --all --oneline
* 9c5bf33 (HEAD -> master, fix) Corrected program.
* e9ac565 Test 2 was added and program crahes.
* 428bdac The program find index of the maximum element in array.
* 48a2ee4 Python file was added
* b466b68 .gitignore was added.
```
Изменения, которые происходили в разных ветках перешли в одну в конце, и можно понять
где шло тестирование и исправление ошибок.
# Задание 2
- распаковал репозиторий 
- Командой `git log --name-status --graph --all` проанализировал историю всех изменений в этом репозитории:
``` bash 
$ git log --name-status --graph --all
* commit a52c4ec45e14d5b48095e1bc9c569f06f4838362 (develop)
| Author: Songster <songster@test>
| Date:   Tue Mar 13 17:03:38 2018 +0300
|
|     Couplets #5 and #6.
|
| M     song.txt
|
* commit 2c605117c7fe0fc2452e787b44519f212ce48bcc
| Author: Songster <songster@test>
| Date:   Tue Mar 13 16:59:09 2018 +0300
|
|     Couplet #2.
|
| M     song.txt
|
| * commit 1295f707870f0e1c13e9144b03cbef4bd10b52a7 (HEAD -> master)
| | Author: Minstrel <minstrel@test>
| | Date:   Tue Mar 13 17:01:15 2018 +0300
| |
| |     Couplet #4.
| |
| | M   song.txt
| |
| * commit 4fcbc684b3e8a22c172a218107bd669e0768b9f4
| | Author: Minstrel <minstrel@test>
| | Date:   Tue Mar 13 17:00:30 2018 +0300
| |
| |     Couplet #3.
| |
| | M   song.txt
| |
:
* commit a52c4ec45e14d5b48095e1bc9c569f06f4838362 (develop)
| Author: Songster <songster@test>
| Date:   Tue Mar 13 17:03:38 2018 +0300
|
|     Couplets #5 and #6.
|
| M     song.txt
|
* commit 2c605117c7fe0fc2452e787b44519f212ce48bcc
| Author: Songster <songster@test>
| Date:   Tue Mar 13 16:59:09 2018 +0300
|
|     Couplet #2.
|
| M     song.txt
|
| * commit 1295f707870f0e1c13e9144b03cbef4bd10b52a7 (HEAD -> master)
| | Author: Minstrel <minstrel@test>
| | Date:   Tue Mar 13 17:01:15 2018 +0300
| |
| |     Couplet #4.
| |
| | M   song.txt
| |
| * commit 4fcbc684b3e8a22c172a218107bd669e0768b9f4
| | Author: Minstrel <minstrel@test>
| | Date:   Tue Mar 13 17:00:30 2018 +0300
| |
| |     Couplet #3.
| |
| | M   song.txt
| |
:
```
Отсюда видно, что над проектом работали два пользователя: `Author: Minstrel <minstrel@test>
` и `Author: Songster <songster@test>`.
Чтобы посмотреть количество ветвей и их названия я использовал команду `git log --oneline --graph --all`:
``` bash 
$ git log --oneline --graph --all
* a52c4ec (develop) Couplets #5 and #6.
* 2c60511 Couplet #2.
| * 1295f70 (HEAD -> master) Couplet #4.
| * 4fcbc68 Couplet #3.
| * 122ee3a Couplet #1.
|/
* f739d2e Beginning.
```
Проект имеет две ветви: `master` и `develop`:
В проекте находится один файл `song.txt`. Сначала над проектом начала работать `Minstrel`. Он закоммитил куплет 3 и куплет 4. Последние изменения внёс `Songster`.
- Для объединения веток я использовал команду `git verge develop`, но возник конфликт:
``` bash 
$ git merge develop
error: Merging is not possible because you have unmerged files.
hint: Fix them up in the work tree, and then use 'git add/rm <file>'
hint: as appropriate to mark resolution and make a commit.
fatal: Exiting because of an unresolved conflict.
```
Так в ветке master cуществоввл файл song.txt и в нем было другое содержание текста,
отличавшиеся от файла song.txt в ветке develop 
``` bash 
$ git status
On branch master
You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   song.txt

no changes added to commit (use "git add" and/or "git commit -a")
```
Исходный файл принял вид: 
``` bash 
<<<<<<< HEAD:song.txt
...
=======
...
>>>>>>> deleop:song.txt```
Я поставил куплеты в song.txt в логически правильной последовательности и сделал коммит этого файла:
``` bash 
$ git add song.txt

$ git commit -m "song.txt was changed."
[master c8f08bb] song.txt was changed.

$ git log --oneline --graph --all
*   c8f08bb (HEAD -> master) song.txt was changed.
|\
| * a52c4ec (develop) Couplets #5 and #6.
| * 2c60511 Couplet #2.
* | 1295f70 Couplet #4.
* | 4fcbc68 Couplet #3.
* | 122ee3a Couplet #1.
|/
* f739d2e Beginning.

```
После этого конфликта не было:
``` bash 
$ git merge develop
Already up to date.
```
# Задание 3

## Задание 3.2
- С помощью команды `git clone` клонировал удаленный репозиторий:
``` bash 
$ git clone https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii
Cloning into 'iu7-software-engineering-labs-2024-palladiievgenii'...
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
warning: redirecting to https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii.git/
remote: Enumerating objects: 3, done.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 3
Receiving objects: 100% (3/3), done.
```
- командой `cd` перехожу в эту папку и командой `git branch` создаю две ветви *lab_02_a* и *lab_02_b*: 
``` bash
$ git branch lab_02_a

$ git branch lab_02_b

$ git branch
  lab_02_a
  lab_02_b
* main
```
- командой `git checkout` переключился в ветку lab_02_a
``` bash 
$ git checkout lab_02_a
Switched to branch 'lab_02_a'
```
- Создал .gitignore c содержанием * .exe и текстовой файл lab_02_a.txt с содержанием lab_02_a и затем
фиксирую это и отправляю в удаленный репозиторий и создаю merge A
``` bash 
$ git add .

$ git commit -m "A"
[lab_02_a bfd5071] A
 2 files changed, 2 insertions(+), 5 deletions(-)
 create mode 100644 lab_02_a.txt

$ git push --set-upstream origin lab_02_a
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
warning: redirecting to https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii.git/
Enumerating objects: 6, done.
Counting objects: 100% (6/6), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (4/4), 299 bytes | 149.00 KiB/s, done.
Total 4 (delta 0), reused 0 (delta 0), pack-reused 0
remote:
remote: To create a merge request for lab_02_a, visit:
remote:   https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii/-/merge_requests/new?merge_request%5Bsource_branch%5D=lab_02_a
remote:
To https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii
 * [new branch]      lab_02_a -> lab_02_a
branch 'lab_02_a' set up to track 'origin/lab_02_a'.

$ git push https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii.git
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
Everything up-to-date
```
- Также проделываю с веткой lab_02_b , только в .gitignore - * .o , а в текстовом файле lab_02_b.txt -
'lab_02_b' и создаю merge B
``` bash 
$ git checkout lab_02_b
Switched to branch 'lab_02_b'

$ git status
On branch lab_02_b
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   .gitignore

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        lab_02_b.txt

no changes added to commit (use "git add" and/or "git commit -a")

$ git add .

$ git commit -m "B"
[lab_02_b 5524cef] B
 2 files changed, 2 insertions(+), 5 deletions(-)
 create mode 100644 lab_02_b.txt

$ git push https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii.git
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
Enumerating objects: 6, done.
Counting objects: 100% (6/6), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (4/4), 298 bytes | 149.00 KiB/s, done.
Total 4 (delta 0), reused 0 (delta 0), pack-reused 0
remote:
remote: To create a merge request for lab_02_b, visit:
remote:   https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii/-/merge_requests/new?merge_request%5Bsource_branch%5D=lab_02_b
remote:
To https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii.git
 * [new branch]      lab_02_b -> lab_02_b
```
## Задание 3.3
- Получил копии удаленного репозитория с помощью команды `git clone`
- Создал ветвь lab_02_c и перешел в неё 
``` bash 
$ git branch lab_02_c

$ git checkout lab_02_c
Switched to branch 'lab_02_c'
```
- Создаю файл lab_02_c.txt с содержанием из абзаца 1 и фиксирую этот файл:
``` bash
$ git add lab_02_c.txt

$ git commit -m "file was added."
[lab_02_c 47cb362] file was added.
 1 file changed, 8 insertions(+)
 create mode 100644 lab_02_c.txt

$ git push --set-upstream origin lab_02_c
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
---
 * [new branch]      lab_02_c -> lab_02_c
```
- Затем в файле lab_02_c.txt добавляю текст 3 абзаца и фиксирую эти изменения,
но не отправляю в удаленный репозиторий:
``` bash
$ git add lab_02_c.txt

$ git commit -m "file was changed."
[lab_02_c d5c032e] file was changed.
 1 file changed, 9 insertions(+)
```
- Получил новую копию удаленного репозитория командой `git clone` и переключаюсь на ветвь lab_02_c командой `git checkout lab_02_c`
- Добавил второй абзац, делаю фиксацию и отправляю в удаленный репозиторий:
``` bash
$ git commit -m "file was changed."
[lab_02_c 7d22c42] file was changed.
 1 file changed, 12 insertions(+), 1 deletion(-)

zheny@DESKTOP-CRGUDCG MSYS /b/work2_2/new/iu7-software-engineering-labs-2024-palladiievgenii/iu7-software-engineering-labs-2024-palladiievgenii
$ git push --set-upstream origin lab_02_c
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
...
branch 'lab_02_c' set up to track 'origin/lab_02_c'.
```
- Перешел с прошлую копию удаленного репозитория и попытался отправить изменения в удаленный:
``` bash
$ git push --set-upstream origin lab_02_c
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
To https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii.git
 ! [rejected]        lab_02_c -> lab_02_c (fetch first)
error: failed to push some refs to 'https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```
Как видно, произошел конфликт, так в удаленном репозитории файл lab_02_c.txt совсем не схож с
локальным и там был добавлен коммит, которого нет в локальном репозитории, чтобы решить эту проблему нам
необходимо загрузить те изменения в локальный репозиторий и затем объединить эти изменения и зафиксировать, а
потом уже можно отправлять в удаленный репозиторий:
``` bash
$ git pull --no-rebase origin lab_02_c
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
From https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii
 * branch            lab_02_c   -> FETCH_HEAD
Auto-merging lab_02_c.txt
CONFLICT (content): Merge conflict in lab_02_c.txt
Automatic merge failed; fix conflicts and then commit the result.

$ git status
On branch lab_02_c
Your branch and 'origin/lab_02_c' have diverged,
and have 1 and 1 different commits each, respectively.
  (use "git pull" if you want to integrate the remote branch with yours)

You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both modified:   lab_02_c.txt

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        iu7-software-engineering-labs-2024-palladiievgenii/

no changes added to commit (use "git add" and/or "git commit -a")

$ git add lab_02_c.txt

$ git status
On branch lab_02_c
Your branch and 'origin/lab_02_c' have diverged,
and have 1 and 1 different commits each, respectively.
  (use "git pull" if you want to integrate the remote branch with yours)

All conflicts fixed but you are still merging.
  (use "git commit" to conclude merge)

Changes to be committed:
        modified:   lab_02_c.txt

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        iu7-software-engineering-labs-2024-palladiievgenii/

$ git commit -m "lab_02_c Абзца 3"
[lab_02_c 19e38f3] lab_02_c Абзца 3 

$ git push --set-upstream origin lab_02_c
Username for 'https://git.iu7.bmstu.ru':
Password for 'https://pei23u1524@git.iu7.bmstu.ru':
Enumerating objects: 10, done.
Counting objects: 100% (10/10), done.
Delta compression using up to 4 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (6/6), 772 bytes | 772.00 KiB/s, done.
Total 6 (delta 4), reused 0 (delta 0), pack-reused 0
remote:
remote: To create a merge request for lab_02_c, visit:
remote:   https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii/-/merge_requests/new?merge_request%5Bsource_branch%5D=lab_02_c
remote:
To https://git.iu7.bmstu.ru/iu7-software-engineering/iu7-software-engineering-labs-2024/iu7-software-engineering-labs-2024-palladiievgenii.git
   7d22c42..19e38f3  lab_02_c -> lab_02_c
branch 'lab_02_c' set up to track 'origin/lab_02_c'.
```