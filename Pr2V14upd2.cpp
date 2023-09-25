// Inhearitance_Array.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

//КМБО-03-22 Кромский Петр Вариант 14

#include <iostream>
#include <cmath>

using namespace std;

class MyArrayParent
{
protected: // было private
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;

public:
	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100)
	{
		cout << "\nMyArrayParent constructor";
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	/*MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor";
		capacity = len;
		ptr = new double[len];
		count = len;
		for (int i = 0; i < len; i++)
		{
			ptr[i] = arr[i];
		}
	}*/
	MyArrayParent(const MyArrayParent& arr)
	{
		cout << "\nMyArrayParent constructor";
		capacity = arr.capacity;
		count = arr.count;
		ptr = new double[arr.capacity];
		for (int i = 0; i < count; i++)
		{
			ptr[i] = arr.ptr[i];
		}
	}
	//деструктор
	~MyArrayParent()
	{
		cout << "\nMyArrayParent destructor";
		//освободить память, выделенную под ptr
		delete[] ptr;
	}

	//обращение к полям
	int Capacity() { return capacity; }
	int GetSize() { return count; }
	void SetSize(int s2) { if (s2 < capacity) count = s2; }
	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		else
		{
			cout << "Wrong index" << endl;
		}
	}

	//добавление в конец нового значения
	void push(double value)
	{
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
		}
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count > 0)
		{
			count--;
		}
		else
		{
			cout << "array length is 0" << endl;
		}
	}

	double& operator[](int index)
	{
		return ptr[index];
	}

	MyArrayParent operator=(MyArrayParent Arr)
	{
		delete[] ptr;
		capacity = Arr.count;
		count = capacity;
		ptr = new double[count];
		for (int i = 0; i < count; i++)
		{
			ptr[i] = Arr.ptr[i];
		}
		return Arr;
	}

	/*friend MyArrayParent operator+(double& arr[sizeof(arr) / sizeof(double)], MyArrayParent arr2)
	{
		int arrlength = sizeof(arr) / sizeof(double);
		MyArrayParent Result(arrlength + arr2.count);
		for (int i = 0; i < arrlength; i++)
		{
			Result.push(arr[i]);
		}
		for (int i = 0; i < arr2.count; i++)
		{
			Result.push(arr2[i]);
		}
		return Result;
	}
		MyArrayParent operator+ (double& arr)
	{
		int arrlength = sizeof(arr) / sizeof(double);
		MyArrayParent Result(arrlength + count);
		for (int i = 0; i < count; i++)
		{
			Result.push(ptr[i]);
		}
		for (int i = 0; i < arrlength; i++)
		{
			Result.push(arr[i]);
		}
		return Result;
	}*/
	friend MyArrayParent operator+ (double value, MyArrayParent arr)
	{
		MyArrayParent Result(arr.count + 1);
		for (int i = 0; i < arr.count; i++)
		{
			Result.push(arr[i]);
		}
		Result.count++;
		for (int i = Result.count - 1; i > 0; i--)
		{
			Result[i] = Result[i - 1];
		}
		Result[0] = value;
		return Result;
	}
	MyArrayParent operator+ (MyArrayParent arr)
	{
		MyArrayParent Result(count + arr.count);
		for (int i = 0; i < count; i++)
		{
			Result.push(ptr[i]);
		}
		for (int i = 0; i < arr.count; i++)
		{
			Result.push(arr[i]);
		}
		return Result;
	}
	MyArrayParent operator+(double value)
	{
		MyArrayParent Result(count + 1);
		for (int i = 0; i < count; i++)
		{
			Result.push(ptr[i]);
		}
		Result.push(value);
		return Result;
	}

	int IndexOf(double value, bool bFindFromStart = true)
	{
		if (bFindFromStart)
		{
			for (int i = 0; i < count; i++)
			{
				if (ptr[i] == value) { return i; }
			}
			return -1;
		}
		else {
			for (int i = (count - 1); i >= 0; i--)
			{
				if (ptr[i] == value) { return i; }
			}
			return -1;
		}
	}


	void RemoveAt(int index)
	{
		if (!(count == 0 || index < 0 || index >= count))
		{
			for (int i = index; i < (count - 1); i++)
			{
				ptr[i] = ptr[i + 1];
			}
		}
		else cout << "Element does not exist" << endl;
	}


	/*MyArrayParent& operator=(const Vector& V)
	{
		//оператор =
		//arr1 = arr2 = arr3; где arr_i - объекты нашего класса
		for (int i = 0; i < this->count; i++)
		{

		}
	}

	MyArrayParent(const Vector& V)
	{
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
	}*/

	void print()
	{
		cout << "\nMyArrParent, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}
	MyArrayParent Subsequence(MyArrayParent arr, int startInd, int finalInd)
	{
		MyArrayParent Subs(finalInd - startInd + 1);
		for (int i = startInd; i <= finalInd; i++)
		{
			Subs.push(arr[i]);
		}
		return Subs;
	}

};

class MyArrayChild : public MyArrayParent
{
public:
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }
	MyArrayChild(const MyArrayChild& arr) : MyArrayParent(arr) { cout << "\nnMyArrayChild constructor"; };
	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//вставка элемента
	void InsertAt(double value, int index = -1)
	{
		if (index == -1)
		{
			push(value);
		}
		else
		{
			if ((index < 0) || (index >= count)) return;
			SetSize(count++);
			for (int i = count - 1; i > index; i--)
			{
				ptr[i] = ptr[i - 1];
			}
			ptr[index] = value;
			/*
			for (int i = this->GetSize - 1; i > index; i--)
			{
				this->SetComponent(i, this->GetComponent(i - 1));
			}
			this->SetComponent(index, value);
			*/
		}
	}
	MyArrayChild AboveMids()
	{
		MyArrayChild ArrF(count);
		double MidTrg = 1;
		for (int i = 0; i < count; i++) MidTrg *= ptr[i];
		MidTrg = pow(MidTrg, (double)1 / count);
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] > MidTrg) ArrF.push(ptr[i]);

		}
		return ArrF;
	}
};
class MySortedArray : public MyArrayChild
{
public:
	MySortedArray(int Dimension = 100) :MyArrayChild(Dimension) { cout << "\nMySortedArray constructor"; }
	MySortedArray(const MySortedArray& arr) :MyArrayChild(arr) {
		cout << "\nMySortedArray constructor";
	}
	~MySortedArray() { cout << "\nMySortedArray constructor"; }

	MySortedArray AboveMids()
	{
		MySortedArray ArrF(this->count);
		double MidTrg = 1;
		for (int i = 0; i < count; i++) MidTrg *= ptr[i];
		MidTrg = pow(MidTrg, (double)1 / count);
		int f2arr = 0;
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] > MidTrg)
			{
				ArrF.push(ptr[i]);
			}
		}
		return ArrF;
	}
	void push(double value)
	{
		if (count == capacity) return;
		if (value > ptr[count - 1])
		{
			count++;
			ptr[count - 1] = value;
			return;
		}
		if (value < ptr[0])
		{
			count++;
			for (int i = count - 1; i > 0; i--)
			{
				ptr[i] = ptr[i - 1];
			}
			ptr[0] = value;
			return;
		}
		int left = 0, right = count - 1, mid;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (ptr[mid] == value) break;
			if ((ptr[mid] > value) && (ptr[mid - 1] < value)) break;
			if (ptr[mid] > value) right = mid - 1;
			else left = mid + 1;
		}
		InsertAt(value, mid);
	}

	int IndexOf(double value, bool bFindFromStart = true)
	{
		int left = 0, right = count - 1, mid;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (ptr[mid] == value) return mid;
			if (ptr[mid] > value) right = mid - 1;
			else left = mid + 1;
		}
		return -1;
	}

};

int main()
{
	
}

