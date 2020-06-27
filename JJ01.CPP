#include <iostream>
#include <complex>
#include <memory>	
#include "TestHeader.h"
using namespace std;
void jj01::test_primitives()
{
		cout << "\n Ways we can use to allocate memory. \n";
		
		void* p1 = malloc(512);	//512 bytes | directly call _nh_malloc_dbg to allocate memory
		free(p1);
		
		complex<int>* p2 = new complex<int>; //operator new -> _nh_malloc_dbg -> constructor
		delete p2;             
		
		void* p3 = ::operator new(512); //512 bytes | ->_nh_malloc_dbg  
		::operator delete(p3);
		

#ifdef _MSC_VER		
		//allocate() methond is non-satic, so we have to create a object then use it. 
		// We allocate 3 int. 
		//Note here, the allocator is defined in C++, but VS, GCC, etc may have different API. 
		int* p4 = allocator<int>().allocate(3, (int*)0); //The allocate method actually call operator new. 
		allocator<int>().deallocate(p4,3);           
#endif
}
