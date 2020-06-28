#include "TestHeader.h"
#include <iostream>
using namespace std;
namespace jj09
{
	

	class Foo 
	{
	public: 
		long L;
		string str;
		static allocator myAlloc;
	public:
		Foo(long l) : L(l) {  }
		static void* operator new(size_t size)
		{
			return myAlloc.allocate(size);  	
		}
		static void  operator delete(void* pdead, size_t size)
		{
			myAlloc.deallocate(pdead, size);  
			return ;
		}
	};
	allocator Foo::myAlloc;
	
	class Goo 
	{
	public: 
		complex<double> c;
		string str;
		static allocator myAlloc;
	public:
		Goo(const complex<double>& x) : c(x) {  }
		static void* operator new(size_t size)
		{     
			return myAlloc.allocate(size);  	
		}
		static void  operator delete(void* pdead, size_t size)
		{
			myAlloc.deallocate(pdead, size);  
		}
	};
		
	allocator Goo::myAlloc;
	
	void test_static_allocator_3()
	{
		cout << "\n\n\ntest_static_allocator().......... \n";			
		{	
			Foo* p[100];
			
			int i =0;
			cout << "sizeof(Foo)= " << sizeof(Foo) << endl;
			for (i=0; i<23; ++i) 
			{	//23, arbitrary number, for testing. 
				p[i] = new Foo(i); 
				cout << p[i] << ' ' << p[i]->L << endl;
			}
			//Foo::myAlloc.check();
			
			for (i=0; i<23; ++i)
			{
				delete p[i]; 
			}	
			//Foo::myAlloc.check();
		}
		
		{	
			Goo* p[100];
			
			cout << "sizeof(Goo)= " << sizeof(Goo) << endl;
			int i = 0;
			for (i=0; i<17; ++i) 
			{	//17, arbitrary number, for testing. 
				p[i] = new Goo(complex<double>(i,i)); 
				cout << p[i] << ' ' << p[i]->c << endl;
			}
			//Goo::myAlloc.check();
			
			for (i=0; i<17; ++i) 
			{
				delete p[i]; 
			}	
			//Goo::myAlloc.check();	
		}
	}
}
