// Pr4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstring>
using namespace std;
class BaseString
{
protected:
    char* p;
    int len;
    int capacity;

public:
    BaseString(char* ptr)
    {
        cout << "\nBase Constructor 1\n";
        len = strlen(ptr) + 1;
        capacity = 256;
        p = new char[capacity];
        for (int i = 0; i < len; i++)
        {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }
    BaseString(int Capacity = 256)
    {
        cout << "\nBase Constructor 0\n";
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }
    virtual ~BaseString()
    {
        cout << "\nBase Destructor\n";
        if (p != NULL)
            delete[] p;
        len = 0;
    }
    int Length() { return len; }
    int Capacity() { return capacity; }
    //char* get() {return p;}
    char& operator[](int i) { return p[i]; }
    BaseString& operator=(BaseString& s)
    {
        cout << "\nBase Operator = \n";
        len = s.Length();
        p = new char[s.capacity];
        capacity = s.capacity;
        for (int i = 0; i < s.Length(); i++)
        {
            p[i] = s[i];
        }
        //strcpy(p, s.get());
        p[len - 1] = '\0';
        return *this;
    }
    BaseString(BaseString& s)
    {
        cout << "\nBase Copy Constructor\n";
        len = s.Length();
        p = new char[s.capacity];
        capacity = s.capacity;
        for (int i = 0; i < s.Length() - 1; i++)
        {
            p[i] = s[i];
        }
        p[len - 1] = '\0';
    }
    virtual void print()
    {
        int i = 0;
        while (p[i] != '\0') { cout << p[i]; i++; }
    }
    BaseString operator=(BaseString stg)
    {
        BaseString res(stg.p);
        return res;
    }
};
class String :public BaseString
{
public:
    String(int Capacity = 256) :BaseString(Capacity) { cout << "\nString Constructor 0\n"; }
    String(char* ptr):BaseString(ptr) { cout << "\nString Constructor 1\n"; }
    ~String()
    {
        cout << "\nString Destructor\n";
        if (p != NULL)
            delete[] p;
        len = 0;
    }
};
int main()
{
    char l[3] = {'a','v','\0'};
    cout<<strlen(l);
    BaseString b(l);
    b.print();
}

