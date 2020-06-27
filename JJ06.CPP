#include "TestHeader.h"
#include <iostream>
using namespace std;
namespace jj06
{
	void* Foo::operator new(size_t size)
	{
		Foo* p = (Foo*)malloc(size);  
		cout << "Foo::operator new(), size=" << size << "\t  return: " << p << endl;  	
		
		return p;
	}
	
	void Foo::operator delete(void* pdead, size_t size)
	{
		cout << "Foo::operator delete(), pdead= " << pdead << "  size= " << size << endl;
		free(pdead);
	}
	
	void* Foo::operator new[](size_t size)
	{
		Foo* p = (Foo*)malloc(size);  //crash, 問題可能出在這兒 
		cout << "Foo::operator new[](), size=" << size << "\t  return: " << p << endl;  
		
		return p;
	}
	
	void Foo::operator delete[](void* pdead, size_t size)
	{
		cout << "Foo::operator delete[](), pdead= " << pdead << "  size= " << size << endl;
		
		free(pdead);
	}
	
	void test_overload_operator_new_and_array_new() 
	{	
		cout << "\ntest_overload_operator_new_and_array_new().......... \n";		
		
		cout << "sizeof(Foo)= " << sizeof(Foo) << endl;
		
		{	
			Foo* p = new Foo(7);
			delete p;
			
			Foo* pArray = new Foo[5];	//無法給 array elements 以 initializer 
			delete [] pArray;	
		}
		
		{	    
			cout << "testing global expression ::new and ::new[] \n";
			// 這會繞過 overloaded new(), delete(), new[](), delete[]() 
			// 但當然 ctor, dtor 都會被正常呼叫.  
			
			Foo* p = ::new Foo(7);
			::delete p;
			
			Foo* pArray = ::new Foo[5];	
			::delete [] pArray;
		}
	}
}