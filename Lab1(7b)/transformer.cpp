#include "transformer.h"

namespace lab1_7b {

	transformer::transformer(int coef, bool every_n, size_t n) : _coef(coef), _count(0), _n(n), _every_n(every_n)
	{

	}

	// �������� ������ n-��� ����� �� _coef, ���� ����� ���� _every_n
	// ����� �������� �� _coef ��� �����
	int transformer::operator()(int& number)
	{
		if (!_every_n || _count % _n == 0)
			number *= _coef;
		++_count;
		return number;
	}
}
