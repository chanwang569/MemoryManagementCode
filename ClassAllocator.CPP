#include <cstddef>
#include <iostream>
#include <cstdio>
#include "TestHeader.h"
using namespace std;
namespace jj04
{
	Screen* Screen::freeStore = 0;
	const int Screen::screenChunk = 24;

	void* Screen::operator new(size_t size)
	{
		Screen* p;
		if (!freeStore) {
			// The link list is empty, so we get a large bulk of memory with global operator new
			size_t chunk = screenChunk * size;
			freeStore = p =
				reinterpret_cast<Screen*>(new char[chunk]);
			// using linked list to create a linked chain to maintain the allocated memory. 
			for (; p != &freeStore[screenChunk - 1]; ++p)
				p->next = p + 1;
			p->next = 0;
		}
		p = freeStore;
		freeStore = freeStore->next;
		return p;
	}


	//! void Screen::operator delete(void *p)		//(1)
	void Screen::operator delete(void* p, size_t)	//(2) both OK. 
	{
		//Recyle the memory and added back to the front of free list. 
		(static_cast<Screen*>(p))->next = freeStore;
		freeStore = static_cast<Screen*>(p);
	}

	void test_per_class_allocator_1()
	{

		cout << "\ntest_per_class_allocator_1().......... \n";
		cout << sizeof(Screen) << endl;		//8	

		size_t const N = 100;
		Screen* p[N];
		int i = 0;
		for (i = 0; i < N; ++i)
		{
			p[i] = new Screen(i);
		}

		// Output the first 10 pointers to check the interval 
		for (i = 0; i < 10; ++i)
		{
			cout << p[i] << endl;
		}

		for (i = 0; i < N; ++i)
		{
			delete p[i];
		}
	}
}



