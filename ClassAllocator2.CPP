#include "TestHeader.h"
#include <cstddef>
#include <iostream>
using namespace std;
namespace jj05
{
	Airplane* Airplane::headOfFreeList;  
	const int Airplane::BLOCK_SIZE = 512;   
	
	void* Airplane::operator new(size_t size)
	{
		//Fallback to use operator new. if the size is not correctly passed in. 
		if (size != sizeof(Airplane))
			return ::operator new(size);
		
		Airplane* p = headOfFreeList;  
		
		// If valid p exists, move list's head to next position. 
		if (p)
			headOfFreeList = p->next;
		else {
			//The free list is empty. Allocate a large buck of memory. 
			//So that BLOCK_SIZE of Aireplane can be kept. 
			Airplane* newBlock = static_cast<Airplane*>
				(::operator new(BLOCK_SIZE * sizeof(Airplane)));
			
			//Generate a free list to maintain the allocated memory. 
			for (int i = 1; i < BLOCK_SIZE-1; ++i)
				newBlock[i].next = &newBlock[i+1];
			newBlock[BLOCK_SIZE-1].next = 0; //end with NULL
			
			// Move p to the head. Then move the head to next node
			p = newBlock;
			headOfFreeList = &newBlock[1];
		}
		return p;
	}
	
	// Operator delete to delete memory directly if allocated by global function new. 
	// Or add the memory back to free list so that can be further reuse.
	void Airplane::operator delete(void* deadObject,
		size_t size)
	{
		if (deadObject == 0) return;          
		if (size != sizeof(Airplane)) {   
			::operator delete(deadObject);
			return;
		}
		
		Airplane *carcass =
			static_cast<Airplane*>(deadObject);
		
		carcass->next = headOfFreeList;
		headOfFreeList = carcass;
	}
	
	//-------------
	void test_per_class_allocator_2() 
	{	
		cout << "\ntest_per_class_allocator_2().......... \n";		
		
		cout << sizeof(Airplane) << endl;    //8
		
		size_t const N = 100;
		Airplane* p[N];	
		int i = 0;
		for (i=0; i< N; ++i)
			p[i] = new Airplane;     
		
		
		//Random testing. 
		p[1]->set(1000,'A'); 	
		p[5]->set(2000,'B');
		p[9]->set(500000,'C');
		cout << p[1] << ' ' << p[1]->getType() << ' ' << p[1]->getMiles() << endl;
		cout << p[5] << ' ' << p[5]->getType() << ' ' << p[5]->getMiles() << endl;
		cout << p[9] << ' ' << p[9]->getType() << ' ' << p[9]->getMiles() << endl; 
		
		//Output first 10 pointer to check interval. 
		for (i=0; i< 10; ++i)  	   
			cout << p[i] << endl; 		 
		
		for (i=0; i< N; ++i)
			delete p[i]; 	
	}
}