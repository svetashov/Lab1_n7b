#include "transformer.h"

namespace lab1_7b {

	transformer::transformer(int coef, bool every_n, size_t n) : _coef(coef), _count(0), _n(n), _every_n(every_n)
	{

	}

	// умножает каждое n-ное число на _coef, если стоит флаг _every_n
	// иначе умножает на _coef все числа
	int transformer::operator()(int& number)
	{
		if (!_every_n || _count % _n == 0)
			number *= _coef;
		++_count;
		return number;
	}
}
