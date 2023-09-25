// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;

class Exception : public exception
{
protected:
	//сообщение об ошибке
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class InvalidOperationException : public Exception
{
protected:
	int rows, cols;
public:
	InvalidOperationException(const char* s, int Rows, int Columns) : Exception(s) { rows = Rows; cols = Columns; }
	InvalidOperationException(const InvalidOperationException& e) : Exception(e) { rows = e.rows; cols = e.cols; }
	virtual void print()
	{
		cout << "InvalidOperationException: " << str << "; Rows: " << rows << ", Columns: " << cols << "; " << what();
	}
};

class IndexOutOfBoundsException : public Exception
{
protected:
	int row, column;
public:
	IndexOutOfBoundsException(const char* s, int Row, int Column) : Exception(s) { row = Row; column = Column; }
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) { row = e.row; column = e.column; }
	virtual void print()
	{
		cout << "IndexOutOfBoundsException: " << str << "; Row: " << row << ", Column: " << column << "; " << what();
	}
};

class WrongSizeException : public Exception
{
protected:
	int rows, cols;
public:
	WrongSizeException(const char* s, int Rows, int Columns) : Exception(s) { rows = Rows; cols = Columns; }
	WrongSizeException(const WrongSizeException& e) : Exception(e) { rows = e.rows; cols = e.cols; }
	virtual void print()
	{
		cout << "WrongSizeException: " << str << "; Rows: " << rows << ", Columns: " << cols << "; " << what();
	}
};

class NonPositiveSizeException : public WrongSizeException
{
public:
	NonPositiveSizeException(const char* s, int Rows, int Columns) : WrongSizeException(s, Rows, Columns) { }
	NonPositiveSizeException(const NonPositiveSizeException& e) : WrongSizeException(e) { }
	virtual void print()
	{
		cout << "NonPositiveSizeException: " << str << "; Rows: " << rows << ", Columns: " << cols << "; " << what();
	}
};

class TooLargeSizeException : public WrongSizeException
{
public:
	TooLargeSizeException(const char* s, int Rows, int Columns) : WrongSizeException(s, Rows, Columns) { }
	TooLargeSizeException(const TooLargeSizeException& e) : WrongSizeException(e) { }
	virtual void print()
	{
		cout << "TooLargeSizeException: " << str << "; Rows: " << rows << ", Columns: " << cols << "; " << what();
	}
};

															//TO DO GramException 

template<class T>
class BaseMatrix
{
protected:
	T** ptr;
	int height;
	int width;
public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		//конструктор
		if (Height <= 0 || Width <= 0)
			throw NonPositiveSizeException("Matrix size can't be negative or zero in constructor int, int", Height, Width);
		if (Height > 50 || Width > 50)
			throw TooLargeSizeException("Matrix size can't be more than 50 in constructor int, int", Height, Width);
		height = Height;
		width = Width;
		ptr = new T * [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new T[width];
	}

	BaseMatrix(const BaseMatrix& M)
	{
		//конструктор копий
		height = M.height;
		width = M.width;
		ptr = new T * [height];

		/*
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];

		for (int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
		*/

		for (int i = 0; i < height; i++)
		{
			ptr[i] = new T[width];
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
		}
	}

	virtual ~BaseMatrix()
	{
		//деструктор
		if (ptr != NULL)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			delete[] ptr;
			ptr = NULL;
		}
		cout << "\nBase Destructor";
	}

	void print()
	{
		//вывод
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				cout << ptr[i][j] << " ";
			cout << "\n";
		}
	}

	T* operator[](int index)
	{
		if (index < 0 || index >= height)
			throw IndexOutOfBoundsException("Index out of bounds in operator[]", index, -1);
		return ptr[index];
	}

	T& operator()(int row, int column)
	{
		if (row < 0 || row >= height || column < 0 || column >= width)
			throw IndexOutOfBoundsException("Index out of bounds in operator[]", row, column);
		return ptr[row][column];
	}
};

template<class T>
class Matrix : public BaseMatrix<T>
{
public:
	Matrix<T>(int Height = 2, int Width = 2) : BaseMatrix<T>(Height, Width) { cout << "\nMatrix constructor is working!"; }
	virtual ~Matrix() { cout << "\nDerived Destructor"; }
	T operator*()
	{
		if (BaseMatrix<T>::width != BaseMatrix<T>::height)
			throw InvalidSizeException("Couldn't execute operation for rectangular matrix in operator*()", BaseMatrix<T>::height, BaseMatrix<T>::width);
		T p = 1;
		for (int i = 0; i < BaseMatrix<T>::height; i++)
		{
			p *= this->ptr[i][this->width - 1 - i];
		}
		return p;
	}

	Matrix<T> operator=(Matrix<T> operant)
	{
		*this(operant);
		return *this;
	}
	
	void randomfill()
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				srand(time(0));
				ptr[i][j] = rand();
			}
		}
	}
	template <T> Sfinder(Matrix<T> Gram, Matrix<T> v1, Matrix<T> v2) // TO DO
	{
		return 1;
	}

	template<class T>
	friend ostream& operator<<(ostream& s, Matrix<T> M);
	template<class T>
	friend istream& operator>>(istream& s, Matrix<T>& M);
};

template <class T>
ostream& operator<<(ostream& s, Matrix<T> M)
{
	if (typeid(s) == typeid(ofstream))
	{
		s << M.height << " " << M.width << " ";
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
	}
	else
		for (int i = 0; i < M.height; i++)
		{
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
			s << "\n";
		}
	return s;
}

template <class T>
istream& operator>>(istream& s, Matrix<T>& M)
{
	if (typeid(s) == typeid(ifstream))
	{
		int w, h; s >> h >> w;
		if (h != M.height || w != M.width)
			throw WrongSizeException("Matrices in the code and in file have got different size", h, w);
	}
	for (int i = 0; i < M.height; i++)
		for (int j = 0; j < M.width; j++)
			s >> M.ptr[i][j];
	return s;
}

template<class T, int H = 2, int W = 2>
class Matrix2 : public BaseMatrix<T>
{
public:
	Matrix2<T, H, W>() : BaseMatrix<T>(H, W) { cout << "\nMatrix constructor is working!"; }
	virtual ~Matrix2() { cout << "\nDerived Destructor"; }
	T operator*()
	{
		if (BaseMatrix<T>::width != BaseMatrix<T>::height)
			throw InvalidSizeException("Couldn't execute operation for rectangular matrix in operator*()", BaseMatrix<T>::height, BaseMatrix<T>::width);
		T p = 1;
		for (int i = 0; i < BaseMatrix<T>::height; i++)
		{
			p *= this->ptr[i][this->width - 1 - i];
		}
		return p;
	}

	template<class T, int H, int W>
	friend ostream& operator<<(ostream& s, Matrix2<T, H, W> M);
	template<class T, int H, int W>
	friend istream& operator>>(istream& s, Matrix2<T, H, W>& M);
};

template <class T, int H, int W>
ostream& operator<<(ostream& s, Matrix2<T, H, W> M)
{
	if (typeid(s) == typeid(ofstream))
	{
		s << M.height << " " << M.width << " ";
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
	}
	else
		for (int i = 0; i < M.height; i++)
		{
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
			s << "\n";
		}
	return s;
}

template <class T, int H, int W>
istream& operator>>(istream& s, Matrix2<T, H, W>& M)
{
	if (typeid(s) == typeid(ifstream))
	{
		int w, h; s >> h >> w;
		if (h != M.height || w != M.width)
			throw WrongSizeException("Matrices in the code and in file have got different size", h, w);
	}
	for (int i = 0; i < M.height; i++)
		for (int j = 0; j < M.width; j++)
			s >> M.ptr[i][j];
	return s;
}

template<class T>
void my_swap(T& a, T& b)
{
	cout << "\nT my_swap";
	if (typeid(a) == typeid(int) || typeid(a) == typeid(double))
	{
		a += b;
		b = a - b;
		a -= b;
	}
	else
	{
		T temp = a;
		a = b;
		b = temp;
	}
}

int main()
{
	int x = 1; int y = 2; my_swap(x, y); cout << "\n" << x << "\t" << y;
	double a = 1.1; double b = 2.1; my_swap(a, b); cout << "\n" << a << "\t" << b;
	try
	{
		Matrix2<double, 3, 3> M2;
		cin >> M2;
		cout << "\n" << M2;
		/*BaseMatrix<int>* ptr = new Matrix<int>;
		delete ptr;*/
		/*Matrix M;
		cout << "\n";
		cin >> M;
		cout<<"\n" << M;*/
		Matrix<int>* arr = new Matrix<int>[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i](0, 0) = i;
			arr[i](0, 1) = i + 1;
			arr[i](1, 0) = i + 2;
			arr[i](1, 1) = i + 3;
		}

		ofstream fout("test.txt");
		if (fout)
		{
			//fout << "10\n";
			for (int i = 0; i < 10; i++)
				fout << arr[i] << "\n";
			fout.close();
		}
		ifstream fin("test.txt");
		if (fin)
		{
			Matrix<int> M1; //int n; fin >> n;
			//for (int i = 0; i < n; i++)
			while (!fin.eof())
			{
				try
				{
					fin >> M1;
					cout << "\n" << M1;
				}
				catch (exception e) { cout << "\nException is caught: " << e.what(); }
			}
			fin.close();
		}

		delete[] arr;
	}
	catch (IndexOutOfBoundsException e)
	{
		cout << "\nIndexOutOfBoundsException has been caught: "; e.print();
	}
	catch (InvalidOperationException e)
	{
		cout << "\nInvalidOperationException has been caught: "; e.print();
	}
	catch (WrongSizeException e)
	{
		cout << "\nWrongSizeException has been caught: "; e.print();
	}
	catch (Exception e)
	{
		cout << "\nException has been caught: "; e.print();
	}
	catch (exception e)
	{
		cout << "\nexception has been caught: "; e.what();
	}
	char c; cin >> c;

	return 0;
}