#pragma once

namespace lab1_7b {
	class transformer
	{
	private:
		int _coef;
		size_t _count;
		size_t _n;
		bool _every_n;

	public:
		transformer(int coef, bool every_n = false, size_t n = 0);

		// умножает каждое n-ное число на _coef, если стоит флаг _every_n
		// иначе умножает на _coef все числа
		int operator()(int& number);
	};
}
