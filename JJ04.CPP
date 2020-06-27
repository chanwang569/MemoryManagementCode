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
		Screen *p;
		if (!freeStore) {
			//linked list 是空的，所以攫取一大塊 memory
			//以下呼叫的是 global operator new
			size_t chunk = screenChunk * size;
			freeStore = p =
				reinterpret_cast<Screen*>(new char[chunk]);
			//將分配得來的一大塊 memory 當做 linked list 般小塊小塊串接起來
			for (; p != &freeStore[screenChunk-1]; ++p)
				p->next = p+1;
			p->next = 0;
		}
		p = freeStore;
		freeStore = freeStore->next;
		return p;
	}
	
	
	//! void Screen::operator delete(void *p)		//(1)
	void Screen::operator delete(void *p, size_t)	//(2)二擇一 
	{
		//將 deleted object 收回插入 free list 前端
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
		for (i=0; i< N; ++i)
		{
			p[i] = new Screen(i);         
		}
		
		//輸出前 10 個 pointers, 用以比較其間隔 
		for (i=0; i< 10; ++i)
		{
			cout << p[i] << endl;     
		}
		
		for (i=0; i< N; ++i)
		{
			delete p[i];     	
		}
}
}



