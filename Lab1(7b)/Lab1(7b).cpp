// 7b - Умножить каждое третье число на удвоенную сумму первого и последнего отрицательных чисел.
// контейнер - двусторонняя очередь std::deque.
// Выполнил Светашов Артем, 2 курс, 9 группа.

#include <iostream>
#include <fstream>
#include <ctime>
#include <deque>
#include <algorithm>
#include "transformer.h"
#include <locale>

namespace lab1_7b
{
	// возвращает случайное целое число в диапазоне [-range, +range]
	int get_random_number(const size_t range)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		return static_cast<int>(rand() * fraction * (2 * range + 1) - range);
	}

	// записывает в файл с именем name count случайных чисел в диапазоне [-range, +range]
	std::ofstream generate_file(std::string name, const size_t count, const size_t range)
	{
		std::ofstream out(name);
		srand(time(nullptr));
		for (size_t i = 0; i < count - 1; ++i)
		{
			out << get_random_number(range) << " ";
		}
		out << get_random_number(range);

		return out;
	}

	// читает из файла дек и возвращает его
	std::deque<int> read_file(std::string name)
	{
		std::ifstream in(name);
		std::deque<int> result;
		int buf;
		while (!in.eof())
		{
			in >> buf;
			result.push_back(buf);
		}
		in.close();

		return result;
	}

	// если есть отрицательные числа в контейнере, то возвращает true и записывает их в first и last
	bool get_first_last_negative(std::deque<int>& d, int& first, int& last)
	{
		const size_t len(d.size());
		size_t i(0);
		first = 0, last = 0;
		while (i < len && !first)
		{
			if (d[i] < 0)
				first = d[i];
			++i;
		}
		i = len - 1;
		while (i > 0 && !last)
		{
			if (d[i] < 0)
				last = d[i];
			--i;
		}
		return first;
	}


	// умножение каждого третьего числа на удвоенное произведение первого и последнего отрицательного числа
	// в диапазоне begin end
	std::deque<int>& modify(std::deque<int>& d, const std::deque<int>::iterator& begin,
	                        const std::deque<int>::iterator& end)
	{
		int first(0), last(0);
		get_first_last_negative(d, first, last);

		if (first)
		{
			const int c(2 * (first + last));
			transformer t(c);
			auto it = begin;
			for (; it <= end - 3; it += 3)
				t(*it);
			if (distance(begin, end) % 3 != 0)
				t(*it);
		}

		return d;
	}

	// обработка всего контейнера
	std::deque<int>& modify(std::deque<int>& d)
	{
		return modify(d, d.begin(), d.end());
	}

	// обработка всего контейнера при помощи алгоритма std::transform
	void modify_transform(std::deque<int>& d, const std::deque<int>::iterator& begin,
	                      const std::deque<int>::iterator& end)
	{
		int first(0), last(0);
		get_first_last_negative(d, first, last);
		transformer t(2 * (first + last));
		transform(begin, end, begin, t);
	}

	// обработка всего контейнера при помощи алгоритма std::transform
	void modify_foreach(std::deque<int>& d, const std::deque<int>::iterator& begin,
	                    const std::deque<int>::iterator& end)
	{
		int first(0), last(0);
		get_first_last_negative(d, first, last);
		transformer t(2 * (first + last));
		for_each(begin, end, t);
	}


	// печать дека на экран
	void print_deque(std::deque<int>& d)
	{
		for (auto el : d)
		{
			std::cout << el << " ";
		}
		std::cout << "\n";
	}

	// возвращает сумму всех элементов дека
	int sum(std::deque<int>& d)
	{
		int result(0);
		for (auto el : d)
		{
			result += el;
		}
		return result;
	}

	// среднее значение элементов дека
	float average(std::deque<int>& d)
	{
		const size_t n = d.size();
		return static_cast<float>(sum(d)) / n;
	}

	// считать непустую строку
	std::string read_string(std::string message)
	{
		std::string result;

		std::cout << message << std::endl;
		std::cin >> result;
		while (result.empty())
		{
			std::cout << "Ошибка, введите непустой текст";
			std::cin >> result;
		}

		return result;
	}

	// считать число в диапазоне от min до max
	int32_t read_int(std::string message, int32_t min, int32_t max = INT32_MAX)
	{
		if (!message.empty())
			std::cout << message << " ";
		int32_t number;
		std::cin >> number;
		if (!std::cin.good())
			throw new std::exception("Невозможно прочитать число.");
		if ((number < min) || (number > max))
			throw new std::out_of_range("Число выходит за пределы заданного диапазона.");
		return number;
	}


	// печать меню
	void print_menu(bool is_empty = false)
	{
		std::cout << "1. Заполнить файл случайными числами." << std::endl;
		std::cout << "2. Заполнить deque из файла." << std::endl;
		if (!is_empty)
		{
			std::cout << "3. Вывести deque." << std::endl;
			std::cout << "4. Преобразовать функцией modify." << std::endl;
			std::cout << "5. Преобразовать функцией transform." << std::endl;
			std::cout << "6. Преобразовать функцией for_each." << std::endl;
			std::cout << "7. Найти сумму чисел." << std::endl;
			std::cout << "8. Найти среднее арифметическое чисел." << std::endl;
		}
		std::cout << "0. Выход." << std::endl;
	}

	// выполнить функцию
	void run_function(size_t option, std::deque<int>& d)
	{
		switch (option)
		{
		case (1):
			{
				std::string name = read_string("Введите имя файла:");
				uint32_t count = static_cast<uint32_t>(read_int("Введите количество чисел:", 1));
				uint16_t range = static_cast<uint16_t>(read_int("Введите R:", 1));
				generate_file(name, count, range);
				std::cout << "Файл заполнен." << std::endl;
				break;
			}
		case (2):
			{
				d = read_file(read_string("Введите имя файла:"));
				std::cout << "deque заполнен." << std::endl;
				break;
			}
		case (3):
			{
				std::cout << "Содержимое deque:" << std::endl;
				print_deque(d);
				break;
			}
		case (4):
			{
				modify(d);
				std::cout << "deque преобразован." << std::endl;
				break;
			}
		case (5):
			{
				modify_transform(d, d.begin(), d.end());
				std::cout << "deque преобразован." << std::endl;
				break;
			}
		case (6):
			{
				modify_foreach(d, d.begin(), d.end());
				std::cout << "deque преобразован." << std::endl;
				break;
			}
		case (7):
			{
				std::cout << "Сумма чисел равна: " << sum(d) << std::endl;
				break;
			}
		case (8):
			{
				std::cout << "Среднее арифметическое чисел равно: " << average(d) << std::endl;
				break;
			}
		case (0):
			{
				std::cout << "Программа завершена.";
				break;
			}
		default:
			std::cout << "Неверное значение, программа завершена.";
			break;
		}
	}

	// Главное меню.
	void menu()
	{
		std::deque<int> numbers;
		int32_t option = 0;
		do
		{
			print_menu(numbers.empty());
			try
			{
				option = read_int("Выберите действие:", 0, numbers.empty() ? 2 : 8);
				run_function(option, numbers);
			}
			catch (std::exception* err_ptr)
			{
				std::cout << err_ptr->what() << std::endl;
			}
			catch (...)
			{
				std::cout << "Неизвестная ошибка." << std::endl;
			}
			std::cout << std::endl << std::endl;
		}
		while (option != 0);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	lab1_7b::menu();

	return 0;
}
