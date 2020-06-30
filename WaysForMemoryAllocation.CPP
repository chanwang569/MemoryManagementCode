#include <iostream>
#include <complex>
#include <memory>	
#include "TestHeader.h"
using namespace std;
void jj01::test_primitives()
{
	cout << "\n Ways we can use to allocate memory. \n";

	void* p1 = malloc(512);	
	free(p1);

	// C++  expression new & delete
	complex<int>* p2 = new complex<int>; 
	delete p2;

	// Global operator new & delete. 
	void* p3 = ::operator new(512); 
	::operator delete(p3);


#ifdef _MSC_VER		
	//allocate() methond is non-satic, so we have to create a object then use it. 
	// We allocate 3 int. 
	//Note here, the allocator is defined in C++, but VS, GCC, etc may have different API. 
	int* p4 = allocator<int>().allocate(3, (int*)0); //The allocate method actually call operator new. 
	allocator<int>().deallocate(p4, 3);
#endif
}
/*VS 2019 debug
complex<int>* p2 = new complex<int>;
>	VCTest.exe!heap_alloc_dbg_internal(const unsigned int size, const int block_use, const char * const file_name, const int line_number) Line 322	C++
	VCTest.exe!heap_alloc_dbg(const unsigned int size, const int block_use, const char * const file_name, const int line_number) Line 450	C++
	VCTest.exe!_malloc_dbg(unsigned int size, int block_use, const char * file_name, int line_number) Line 495	C++
	VCTest.exe!malloc(unsigned int size) Line 23	C++
	VCTest.exe!operator new(unsigned int size) Line 35	C++
	VCTest.exe!jj01::test_primitives() Line 14	C++
	VCTest.exe!main(int argc, char * * argv) Line 9	C++

*/
/* VS 2019 debug * x86 line 26 call stack 
	VCTest.exe!heap_alloc_dbg_internal(const unsigned int size, const int block_use, const char * const file_name, const int line_number) Line 312	C++
	VCTest.exe!heap_alloc_dbg(const unsigned int size, const int block_use, const char * const file_name, const int line_number) Line 450	C++
	VCTest.exe!_malloc_dbg(unsigned int size, int block_use, const char * file_name, int line_number) Line 495	C++
	VCTest.exe!malloc(unsigned int size) Line 23	C++
	VCTest.exe!operator new(unsigned int size) Line 35	C++
	VCTest.exe!std::_Default_allocate_traits::_Allocate(const unsigned int _Bytes) Line 51	C++
	VCTest.exe!std::_Allocate<8,std::_Default_allocate_traits,0>(const unsigned int _Bytes) Line 180	C++
	VCTest.exe!std::allocator<int>::allocate(const unsigned int _Count) Line 784	C++
	VCTest.exe!std::allocator<int>::allocate(const unsigned int _Count, const void * __formal) Line 790	C++
>	VCTest.exe!jj01::test_primitives() Line 26	C++

*/