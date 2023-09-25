// Fractions.cpp: определяет точку входа для консольного приложения.
// KMBO-03-22 Кромский Петр Вариант 14

#include <iostream>

using namespace std;

class Fraction
{
private:
	//поля: числитель и знаменатель
	int denominator;
	int numerator;
public:
	//конструктор Fraction F;
	Fraction() { numerator = 0; denominator = 1; }
	Fraction(int a) { numerator = 1; denominator = a; }
	Fraction(int a, int b) { numerator = a; denominator = b; }
	//деструктор
	~Fraction() { cout << "\nDestructor is working"; }

	//вывод
	void print()
	{
		std::cout << numerator << "/" << denominator;
	}

	//геттеры и сеттеры
	void setNumerator(int value)
	{
		numerator = value;
	}

	void setDenominator(int value)
	{
		if (value != 0) denominator = value;
	}

	int getNumerator()
	{
		return numerator;
	}

	int getDenominator()
	{
		return denominator;
	}

	Fraction operator* (int alpha)
	{
		Fraction MtR;
		MtR.numerator = this->numerator * alpha;
		return MtR;
	}

	friend Fraction operator* (int alpha, Fraction& Ap)
	{
		Fraction MtR = Ap;
		MtR.numerator = MtR.numerator * alpha;
		return MtR;
	}

	Fraction operator!()
	{
		Fraction Uin(this->numerator, this->denominator);
		if (Uin.numerator != 0)
		{
			int t;
			t = Uin.numerator;
			Uin.numerator = Uin.denominator;
			Uin.denominator = t;
		}
		else
		{
			cout << "Error. Fraction can't be inversed";
		}
		return Uin;
	}
	friend bool operator< (double st1, Fraction sd) // num < fraction
	{
		double Td;
		Td = sd.numerator / sd.denominator;
		if (st1 < Td) return true;
		else return false;
	}
	bool operator< (double Td2) // fraction < num
	{
		double Td1;
		Td1 = this->numerator / this->denominator;
		if (Td1 < Td2) return true;
		else return false;
	}
	bool operator< (Fraction sd) // fraction < fraction
	{
		double Td1, Td2;
		Td1 = this->numerator / this->denominator;
		Td2 = sd.numerator / sd.denominator;
		if (Td1 < Td2) return true;
		else return false;
	}

};


int main()
{
	Fraction F1(2, 3);
	Fraction F2(-1, 3);
	Fraction F = 2 * F2;
	//F1 = F1.Inverse();
	F1 = !F1;
	F.print();
	cout << endl;
	F1.print();
	if (F2 < F1) cout << "\nFine\n";
	char c; std::cin >> c;
	return 0;
}
