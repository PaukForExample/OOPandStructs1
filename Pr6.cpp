#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

template<class T>
class Element
{
protected:
	Element* next;
	Element* prev;
	T info;
public:

	Element(T data)
	{
		next = prev = NULL;
		info = data;
	}

	Element(Element* Next, Element* Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}

	T getInfo() { return info; }
	void setInfo(T value) { info = value; }
	Element<T>* getNext() { return next; }
	void setNext(Element<T>* value) { next = value; }
	Element<T>* getPrev() { return prev; }
	void setPrev(Element<T>* value) { prev = value; }

	template<class T1>
	friend ostream& operator<<(ostream& s, Element<T1>& el);

};

template<class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << el.info;
	return s;
}

template<class T>
class LinkedList
{
protected:
	Element<T>* head;
	Element<T>* tail;
	int count;
public:
	//переместить в protected

	LinkedList()
	{
		head = tail = NULL;
		count = 0;
	}

	LinkedList(T* arr, int len)
	{
		//...
	}

	virtual Element<T>* pop() = 0;
	virtual Element<T>* push(T value) = 0;

	Element<T>& operator[](int index)
	{
		//if(index<0 || index>=count) throw ?;

		Element<T>* current = head;

		for (int i = 0;
			current != NULL && i < index;
			current = current->next, i++);

		return *current;
	}

	virtual bool isEmpty() { return (LinkedList<T>::count == 0); }

	template<class T1>
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);

	virtual ~LinkedList()
	{
		cout << "\nBase class destructor";
		Element<T>* previous;
		for (Element<T>* current = head; current != NULL;)
		{
			previous = current;
			current = current->getNext();
			delete previous;
		}

	}
};

template<class T1>
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
	Element<T1>* current;
	for (current = el.head; current != NULL; current = current->getNext())
		s << *current << "; ";
	return s;
}

template<class T>
class Stack : public LinkedList<T>
{
public:
	Stack<T>() : LinkedList<T>() {}
	virtual ~Stack() { cout << "\nStack class destructor"; }

	virtual Element<T>* pop()
	{
		Element<T>* res = LinkedList<T>::tail;

		if (LinkedList<T>::tail == NULL) return NULL;

		if (LinkedList<T>::head == LinkedList<T>::tail)
		{
			LinkedList<T>::count = 0;
			res = LinkedList<T>::tail;
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
			return res;
		}

		Element<T>* current;
		for (current = LinkedList<T>::head; current->getNext() != LinkedList<T>::tail; current = current->getNext());
		current->setNext(NULL);
		LinkedList<T>::count--;
		LinkedList<T>::tail = current;
		return res;
	}
	virtual Element<T>* push(T value)
	{
		Element<T>* newElem = new Element<T>(value);
		if (LinkedList<T>::tail != NULL)
		{
			LinkedList<T>::tail->setNext(newElem);
			LinkedList<T>::tail = LinkedList<T>::tail->getNext();
		}
		else
			LinkedList<T>::head = LinkedList<T>::tail = newElem;

		LinkedList<T>::count++;
		return LinkedList<T>::tail;
	}
};

class my_class
{
public:
	int data;
	my_class(int v = 0) { data = v; cout << "\nmy_class constructor"; }
	my_class(const my_class& m) { data = m.data; cout << "\nmy_class copy constructor"; }

	~my_class() { cout << "\nmy_class destructor"; }

	friend ostream& operator<<(ostream& s, my_class& value);

};

ostream& operator<<(ostream& s, my_class& value)
{
	s << value.data;
	return s;
}

template <class T>
struct Vektor
{
	int Dimension;
	int Length = 0;
	//queue<T> cfs;
	T* cfs;

	Vektor(int Dim = 2, bool irn=false)
	{
		Dimension = Dim;
		cfs = new int[Dimension];
		if (irn)
		{
			cout << "input coefs 1 by 1" << "\n";
			for (int i = 0; i < Dimension; i++) cin >> cfs[i];
		}
		else
		{
			for (int i = 0; i < Dimension; i++) cfs[i] = 1;
		}
		Length = recountlen();
	}

	void recountlen()
	{
		if (*cfs == NULL) return;
		int res = 0;
		for (int i = 0; i < Dimension; i++)
		{
			res += (coef[i] * coef[i]);
		}
		res = sqrt(res);
		Length = res;
	}

	void enqueue(T data)
	{
		//cfs.push(data);
		if (*cfs == NULL)
		{
			cfs = new int[100];
			cfs[0] = data;
			return;
		}
		T* cfs2 = new int[Dimension + 1];
		for (int i = 0; i < Dimension; i++)
		{
			cfs2[i+1] = cfs[i];
		}
		cfs2[0] = data;
		cfs = new int[Dimension + 1];
		for (int i = 0; i < Dimension; i++)
		{
			cfs[i] = cfs2[i];
		}
		Dimension++;
		delete[] cfs2;
		Length = recountlen();
	}

	void dequeue()
	{
		//cfs.pop();
		if (*cfs == NULL)
		{
			return;
		}
		if (*cfs[1] == NULL)
		{
			delete[] cfs;
			return;
		}
		T* cfs2 = new T[Dimension - 1];
		for (int i = 0; i < Dimension-1; i++)
		{
			cfs2[i] = cfs[i + 1];
		}
		delete[]cfs;
		Dimension--;
		T* cfs = new int[Dimension];
		for (int i = 0; i < Dimension; i++)
		{
			cfs[i] = cfs2[i];
		}
		delete[] cfs2;
		Length = recountlen();
	}

	Vektor findamonglist(LinkedList<Vektor<T>> List, int len)
	{
		LinkedList <Vektor<T>> List2 = List;
		while (List.tail->getInfo.Length!=len)
		{
			List2.pop
		}
	}

	void DimFilt(LinkedList<Vektor<T>> List)
	{

	}

};


int main()
{

	if (false)
	{
		cout << "\nmy_class Stack test\n";
		Stack<my_class> Q;
		for (int i = 3; i < 100; i += 5)
			Q.push(my_class(i));
		cout << Q;
	}
	char c; cin >> c;
	return 0;
}