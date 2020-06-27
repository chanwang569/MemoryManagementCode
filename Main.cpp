#include <iostream>
#include "TestHeader.h"
using namespace std;
int main(int argc, char* argv[])
{
	cout << __cplusplus << endl;
	
	jj01::test_primitives();	
	jj02::test_call_ctor_directly();
	
	//jj03::test_array_new_and_placement_new();	 
	
	jj04::test_per_class_allocator_1();
	
	jj05::test_per_class_allocator_2();	
	
	jj06::test_overload_operator_new_and_array_new();	
	
	jj09::test_static_allocator_3();
	
	jj10::test_macros_for_static_allocator();			
	
	/*jj11::test_G29_alloc();
	
	jj12::test_delete_and_default_for_new();	
	
	jj13::test_set_new_handler();	
	
	jj14::test_G29_alloc_C_version();	*/
	return 0;
}

