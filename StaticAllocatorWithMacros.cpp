#include "TestHeader.h"
#include<iostream>
using namespace std;
namespace jj10
{
	using jj09::allocator;
	using namespace std;
	// DECLARE_POOL_ALLOC -- used in class definition
#define DECLARE_POOL_ALLOC() \
public: \
    void* operator new(size_t size) { return myAlloc.allocate(size); } \
    void operator delete(void* p) { myAlloc.deallocate(p, 0); } \
protected: \
    static allocator myAlloc; 

// IMPLEMENT_POOL_ALLOC -- used in class implementation file
#define IMPLEMENT_POOL_ALLOC(class_name) \
allocator class_name::myAlloc; 


// in class definition file
	class Foo {
		DECLARE_POOL_ALLOC()
	public:
		long L;
		string str;
	public:
		Foo(long l) : L(l) {  }
	};
	//in class implementation file
	IMPLEMENT_POOL_ALLOC(Foo)

		//  in class definition file
		class Goo {
		DECLARE_POOL_ALLOC()
		public:
			complex<double> c;
			string str;
		public:
			Goo(const complex<double>& x) : c(x) {  }
	};
	//in class implementation file
	IMPLEMENT_POOL_ALLOC(Goo)
		void test_macros_for_static_allocator()
	{
		cout << "\n\n\ntest_macro_for_static_allocator().......... \n";

		Foo* pF[100];
		Goo* pG[100];

		cout << "sizeof(Foo)= " << sizeof(Foo) << endl;
		cout << "sizeof(Goo)= " << sizeof(Goo) << endl;

		for (int i = 0; i < 23; ++i) {	//23,任意數, 隨意看看結果 
			pF[i] = new Foo(i);
			pG[i] = new Goo(complex<double>(i, i));
			cout << pF[i] << ' ' << pF[i]->L << "\t";
			cout << pG[i] << ' ' << pG[i]->c << "\n";
		}

		for (int i = 0; i < 23; ++i) {
			delete pF[i];
			delete pG[i];
		}

	}
}