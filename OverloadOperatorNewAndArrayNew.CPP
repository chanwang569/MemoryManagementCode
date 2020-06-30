#include "TestHeader.h"
#include <iostream>
using namespace std;
namespace jj06
{
	class Foo
	{
	public:
		int _id;
		long _data;
		string _str;

	public:
		static void* operator new(size_t size)
		{
			Foo* p = (Foo*)malloc(size);
			cout << "Foo::operator new(), size=" << size << "\t  return: " << p << endl;

			return p;
		}
		static void  operator delete(void* deadObject, size_t size)
		{
			cout << "Foo::operator delete(), pdead= " << deadObject << "  size= " << size << endl;
			free(deadObject);
		}
		static void* operator new[](size_t size)
		{
			Foo* p = (Foo*)malloc(size); 
			cout << "Foo::operator new[](), size=" << size << "\t  return: " << p << endl;

			return p;
		}
		static void  operator delete[](void* deadObject, size_t size)
		{
			cout << "Foo::operator delete[](), pdead= " << deadObject << "  size= " << size << endl;

			free(deadObject);
		}

		Foo() : _id(0), _data(0)
		{
			cout << "default ctor. this=" << this << " id=" << _id << endl;
		}
		Foo(int i) : _id(i)
		{
			cout << "ctor. this=" << this << " id=" << _id << endl;
		}
		//virtual 
		~Foo()
		{
			cout << "dtor. this=" << this << " id=" << _id << endl;
		}
	};

	void test_overload_operator_new_and_array_new()
	{
		cout << "\ntest_overload_operator_new_and_array_new().......... \n";

		cout << "sizeof(Foo)= " << sizeof(Foo) << endl;

		{
			Foo* p = new Foo(7);
			delete p;

			Foo* pArray = new Foo[5];	// There is no way to pass in initializer to array elements. 
			delete[] pArray;
		}

		{
			cout << "testing global expression ::new and ::new[] \n";
			// Bybass class defined expression new() delete() new[] and delete[]()
			// But, constructor and desturctor will be called. 
			Foo* p = ::new Foo(7);
			::delete p;

			Foo* pArray = ::new Foo[5];
			::delete[] pArray;
		}
	}
}