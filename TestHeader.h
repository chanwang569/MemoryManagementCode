#ifndef TEST_HEADER_H
#define TEST_HEADER_H
#include <cstdio>
#include <iostream>
namespace jj01
{
	void test_primitives();
}

namespace jj02
{	
	void test_call_ctor_directly();
}

#include <cstddef>
#include <iostream>
namespace jj04
{
	class Screen {
	public:
		Screen(int x) :next(nullptr), i(x) { };
		int get() { return i; }
		
		void* operator new(size_t);
		void  operator delete(void*, size_t);	//(2)
		//! void  operator delete(void*);			//(1) 二擇一. 若(1)(2)並存,會有很奇怪的報錯 (摸不著頭緒) 
		
	private:
		Screen* next;
		static Screen* freeStore;
		static const int screenChunk;
	private:
		int i;
	};
	void test_per_class_allocator_1();
} //namespace

namespace jj05
{
	//ref. Effective C++ 2e, item10
	//per-class allocator 
	
	class Airplane {   // customized memory management
	private:
		struct AirplaneRep {
			unsigned long miles;
			char type;
		};
		private:
			union {
				AirplaneRep rep;  // used object
				Airplane* next;   // free list
			};
		public:
			unsigned long getMiles() { return rep.miles; }
			char getType() { return rep.type; }
			void set(unsigned long m, char t)
			{
				rep.miles = m;
				rep.type = t;
			}
		public:
			static void* operator new(size_t size);
			static void  operator delete(void* deadObject, size_t size);
		private:
			static const int BLOCK_SIZE;
			static Airplane* headOfFreeList;
	};
	void test_per_class_allocator_2();
}
#include <string>
namespace jj06
{	
	void test_overload_operator_new_and_array_new();
	
}
#include <complex>
namespace jj09
{
	using namespace std;
	class allocator
	{
	private:
		struct obj {
			struct obj* next;  //embedded pointer
		};
	public:
		void* allocate(size_t size)
		{
			obj* p;

			if (!freeStore) {
				//Empty 
				size_t chunk = CHUNK * size;
				freeStore = p = (obj*)malloc(chunk);

				//cout << "empty. malloc: " << chunk << "  " << p << endl;

				// Use embedded pointer to maintain the memory link list. 
				for (int i = 0; i < (CHUNK - 1); ++i) {
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
		void  deallocate(void* p, size_t)
		{
			// Recyle the object, insert to the front of free list. 
			((obj*)p)->next = freeStore;
			freeStore = (obj*)p;
		}
		void  check()
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

	private:
		obj* freeStore = nullptr;
		const int CHUNK = 5;
	};

	void test_static_allocator_3();
}
namespace jj10
{
	void test_macros_for_static_allocator();
}
#endif