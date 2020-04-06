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

		// �������� ������ n-��� ����� �� _coef, ���� ����� ���� _every_n
		// ����� �������� �� _coef ��� �����
		int operator()(int& number);
	};
}
