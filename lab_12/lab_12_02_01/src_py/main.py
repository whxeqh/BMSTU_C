import tkinter as tk
from tkinter import messagebox
from array_utils import cyclic_shift, filter

def handle_cyclic_shift():
    def perform_cyclic_shift():
        try:
            nums = nums_entry.get().strip()
            if not nums:
                messagebox.showwarning("Ошибка", "Поле для массива не может быть пустым.")
                return

            nums = nums.split()
            if not all(num.isdigit() for num in nums):
                messagebox.showwarning("Ошибка", "Все элементы массива должны быть числами.")
                return

            nums = list(map(int, nums))

            k = k_entry.get().strip()
            if not k.isdigit():
                messagebox.showwarning("Ошибка", "Количество позиций для сдвига должно быть положительным числом.")
                return

            k = int(k)

            result = cyclic_shift(nums, k)
            result_label.config(text=f"Результат циклического сдвига влева: {result}")
        except Exception as e:
            messagebox.showerror("Ошибка", f"Произошла ошибка: {e}")

    shift_window = tk.Toplevel(root)
    shift_window.title("Циклический сдвиг массива влево")

    tk.Label(shift_window, text="Введите элементы массива через пробел:").pack(pady=5)
    nums_entry = tk.Entry(shift_window)
    nums_entry.pack(pady=5)

    tk.Label(shift_window, text="Введите количество позиций для сдвига:").pack(pady=5)
    k_entry = tk.Entry(shift_window)
    k_entry.pack(pady=5)

    result_label = tk.Label(shift_window, text="")
    result_label.pack(pady=10)

    tk.Button(shift_window, text="Рассчитать", command=perform_cyclic_shift).pack(pady=10)
    tk.Button(shift_window, text="Закрыть", command=shift_window.destroy).pack(pady=10)


def handle_filter():
    def perform_filter():
        try:
            nums = nums_entry.get().strip()
            if not nums:
                messagebox.showwarning("Ошибка", "Поле для массива не может быть пустым.")
                return

            nums = nums.split()
            if not all(num.lstrip('-').isdigit() for num in nums):
                messagebox.showwarning("Ошибка", "Все элементы массива должны быть числами.")
                return

            nums = list(map(int, nums))

            rc, result = filter(nums)
            if not len(result):
                    result_label.config(text=f"В массиве нет полных квадратов")
            else:
                result_label.config(text=f"Элементы, являющиеся полными квадратами: {list(result)}")
        except Exception as e:
            messagebox.showerror("Ошибка", f"Произошла ошибка: {e}")

    filter_window = tk.Toplevel(root)
    filter_window.title("Фильтрация массива (полные квадраты)")

    tk.Label(filter_window, text="Введите элементы массива через пробел:").pack(pady=5)
    nums_entry = tk.Entry(filter_window)
    nums_entry.pack(pady=5)

    result_label = tk.Label(filter_window, text="")
    result_label.pack(pady=10)

    tk.Button(filter_window, text="Рассчитать", command=perform_filter).pack(pady=10)
    tk.Button(filter_window, text="Закрыть", command=filter_window.destroy).pack(pady=10)


def main():
    global root
    root = tk.Tk()
    root.title("Работа с массивами")

    tk.Label(root, text="Выберите задачу:").pack(pady=10)

    tk.Button(root, text="Циклический сдвиг массива влево", command=handle_cyclic_shift).pack(pady=5)
    tk.Button(root, text="Фильтрация массива (полные квадраты)", command=handle_filter).pack(pady=5)

    tk.Button(root, text="Выход", command=root.quit).pack(pady=20)

    root.mainloop()


if __name__ == "__main__":
    main()
