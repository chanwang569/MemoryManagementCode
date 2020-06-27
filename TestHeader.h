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
	using namespace std;
	class A
	{
	public:
		int id;
		
		A() : id(0)      { cout << "default ctor. this="  << this << " id=" << id << endl;  }
		A(int i) : id(i) { cout << "ctor. this="  << this << " id=" << id << endl;  }
		~A()             { cout << "dtor. this="  << this << " id=" << id << endl;  }
	};
	
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
		//! void  operator delete(void*);			//(1) ����һ. ��(1)(2)�K��,���к���ֵĈ��e (�������^�w) 
		
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
	
	class Airplane {   //֧Ԯ customized memory management
	private:
		struct AirplaneRep {
			unsigned long miles;
			char type;
		};
		private:
			union {
				AirplaneRep rep;  //��ᘌ� used object
				Airplane* next;   //��ᘌ� free list
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
	using namespace std;
	class Foo
	{
	public:
		int _id;
		long _data;
		string _str;
		
	public:
		static void* operator new(size_t size);
		static void  operator delete(void* deadObject, size_t size);
		static void* operator new[](size_t size);
		static void  operator delete[](void* deadObject, size_t size);	  	  
		
		Foo() : _id(0),_data(0){ cout << "default ctor. this="  << this << " id=" << _id << endl;  }
		Foo(int i) : _id(i) { cout << "ctor. this="  << this << " id=" << _id << endl;  }
		//virtual 
		~Foo()              { cout << "dtor. this="  << this << " id=" << _id << endl;  }
		
		//���� virtual dtor, sizeof = 12, new Foo[5] => operator new[]() �� size ������ 64, 
		//���� virtual dtor, sizeof = 16, new Foo[5] => operator new[]() �� size ������ 84, 
		//���������������� 4 ���ܾ��ǂ� size_t ��λ�Á���� array size. 
	};
	void test_overload_operator_new_and_array_new();
	
}
#include <complex>
namespace jj09
{
	class allocator
	{
	private:
		struct obj {
			struct obj* next;  //embedded pointer
		};
	public:
		void* allocate(size_t);
		void  deallocate(void*, size_t);
		void  check();

	private:
		obj* freeStore = nullptr;
		const int CHUNK = 5;
	};
	void test_static_allocator_3();
}
#endif