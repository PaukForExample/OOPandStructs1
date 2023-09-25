#include<iostream>
using namespace std;
class A1
{
protected:
	int a1;
public:
	A1(int V1 = 0) { a1 = V1; cout << "\nClass A1 constructor"; }
	virtual void print() { cout << "\nVariable of A1 class"; }
	virtual void show() { cout << "\na1 = " << a1; }
};
class A2
{
protected:
	int a2;
public:
	A2(int V1 = 1) { a2 = V1; cout << "\nClass A2 constructor"; }
	virtual void print() { cout << "\nVariable of A2 class"; }
	virtual void show() { cout << "\na2 = " << a2; }
};
class A3
{
protected:
	int a3;
public:
	A3(int V1 = 2) { a3 = V1; cout << "\nClass A3 constructor"; }
	virtual void print() { cout << "\nVariable of A3 class"; }
	virtual void show() { cout << "\na3 = " << a3; }
};
class B1 : virtual public A1, virtual public A2, virtual public A3
{
protected:
	int b1;
public:
	B1(int V1 = 3, int V2 = 4, int V3 = 5, int V4 = 6) : A1(V2), A2(V3), A3(V4) {
		b1 = V1; cout <<
			"\nClass B1 constructor";
	}
	virtual void print() { cout << "\nVariable of B1 class"; }
	virtual void show()
	{
		cout << "\nb1 = " << b1 << ", a1 =" << a1 << ", a2=" << a2 << ", a3=" << a3;
	}
};
class B2 : virtual public A1, virtual public A2, virtual public A3
{
protected:
	int b2;
public:
	B2(int V1 = 4, int V2 = 5, int V3 = 6, int V4 = 7) : A1(V2), A2(V3), A3(V4) {
		b2 = V1; cout << "\nClass B2 constructor";
	}
	virtual void print() { cout << "\nVariable of B2 class"; }
	virtual void show() {
		cout << "\nb2 = " << b2 << ", a1 = " << a1 << ", a2=" << a2 << ", a3=" << a3;
	}
};
class B3 : virtual public A1, virtual public A2, virtual public A3
{
protected:
	int b3;
public:
	B3(int V1 = 5, int V2 = 6, int V3 = 7, int V4 = 8) :A1(V2), A2(V3), A3(V4)
	{
		b3 = V1;
		cout << "\nClass B3 constructor";
	}
	virtual void print() { cout << "\nVariable of B3 class"; }
	virtual void show() {
		cout << "\nb3 = " << b3 << ", a1 = " << a1 << ", a2=" << a2 << ", a3=" << a3;
	}
};
class C1 : virtual public B1, virtual public B2, virtual public B3
{
protected:
	int c1;
public:
	C1(int V1 = 9, int V2 = 10, int V3 = 11, int V4 = 12) :B1(V2), B2(V3), B3(V4)
	{
		c1 = V1;
	}
	virtual void print() { cout << "\nVariable of C1 class"; }
	virtual void show() {
		cout << "\nc1 = " << c1 << ", a1 = " << a1 << ", a2=" << a2 << ", a3=" << a3 << ", b1 = " << b1 << ", b2=" << b2 << ", b3=" << b3;
	}
};
int main()
{
	B1 test(1, 2);
	test.show();
	test.print();
	C1 d(1, 3, 2, 4);
	A1* ptr = &test; ptr->show(); ptr->print();
	d.show();
	char c; cin >> c;
	return 0;
}