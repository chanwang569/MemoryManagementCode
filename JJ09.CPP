#include "TestHeader.h"
#include <iostream>
using namespace std;
namespace jj09
{

	void* allocator::allocate(size_t size)
	{
		obj* p;

		if (!freeStore) {
			//linked list 是空的，所以攫取一大塊 memory
			size_t chunk = CHUNK * size;
			freeStore = p = (obj*)malloc(chunk);

			//cout << "empty. malloc: " << chunk << "  " << p << endl;

			//將分配得來的一大塊當做 linked list 般小塊小塊串接起來
			for (int i = 0; i < (CHUNK - 1); ++i) {  //沒寫很漂亮, 不是重點無所謂.  
				p->next = (obj*)((char*)p + size);
				p = p->next;
			}
			p->next = NULL;  //last       
		}
		p = freeStore;
		freeStore = freeStore->next;

		//cout << "p= " << p << "  freeStore= " << freeStore << endl;

		return p;
	}

	void allocator::deallocate(void* p, size_t)
	{
		//將 deleted object 收回插入 free list 前端
		((obj*)p)->next = freeStore;
		freeStore = (obj*)p;
	}

	void allocator::check()
	{
		obj* p = freeStore;
		int count = 0;

		while (p) {
			cout << p << endl;
			p = p->next;
			count++;
		}
		cout << count << endl;
	}

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
			{	//23,任意數, 隨意看看結果 
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
			{	//17,任意數, 隨意看看結果 
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
