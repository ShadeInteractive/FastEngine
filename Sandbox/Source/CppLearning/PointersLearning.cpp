#include <iostream>
#include "PointersLearning.h"
#include "FastEngine/Log.h"


void PointersLearning::PrintPointers()
{
	int var = 5;
	std::cout << "var = " << var << " // &var reference = " << &var << std::endl;

	int* var_ptr = &var;
	std::cout << " // var_ptr= adress of variable pointer points to= " << var_ptr << std::endl << " // &var_ptr= adress of the pointer itself= " << &var_ptr << std::endl <<" // *var_ptr= Value of the variable behind adress stored in the pointer: " << *var_ptr << std::endl;
	
	var = 6;
	std::cout << "var = " << var << " // var reference = " << &var << std::endl;
	std::cout << "var_ptr = " << var_ptr << " // var_ptr ref = " << &var_ptr << " // var ptr = " << *var_ptr << std::endl;
	std::string test = "fdjkslfdsjklj";
	std::cout << "sizeof(int)" << sizeof(var) << " // sizeof(ptr): " << sizeof(var_ptr) << " // sizeof(string)" << sizeof(test) << std::endl;

	int* var_ptr_2;
	//In this case, the system dynamically allocates space for five elements of type int and returns a pointer to the first element of the sequence,
	//Therefore, foo now points to a valid block of memory with space for five elements of type int.
	var_ptr_2 = new int[5];
	std::cout << "var_ptr_2 = new int[5]; is an array of pointers. Memory is allocated with 5 elements in ready to be used in memory." << std::endl;
	var_ptr_2[0] = 25;
	var_ptr_2[1] = 10;
	std::cout << "var_ptr_2[0] (" << var_ptr_2[0] << ") = *var_ptr_2 (" << *var_ptr_2 << ")" << " Because new int[5] return the first pointer created in the array." << std::endl;
	int* var_ptr_22 = var_ptr_2;
	++var_ptr_22;
	std::cout << "int* var_ptr_22 = var_ptr_2++ = " << *var_ptr_22 << std::endl;

	//std::cout << "var_ptr_2 is array of pointer. AdressVariable_Id1: " << &var_ptr_2[0] << " - VariableValue_Id1: " << var_ptr_2[0] << " - index 2: " << var_ptr_2[1] << std::endl;
	delete[] var_ptr_2;
	
	int* var_ptr_3 = new int;
	*var_ptr_3 = 25;
	std::cout << "var_ptr_3 is a simple pointer. " << var_ptr_3 << " " << *var_ptr_3 << std::endl;
	delete var_ptr_3;

	int x;
	int *       p1 = &x;  // non-const pointer to non-const int
	const int *       p2 = &x;  // non-const pointer to const int
	int * const p3 = &x;  // const pointer to non-const int
	const int * const p4 = &x;  // const pointer to const int 

	SharedPointer sPtrInt = SharedPointer(new int(12));
	std::cout << "Create a first shared pointer. The value set is: " << * sPtrInt.get() << std::endl;
	
	{
		SharedPointer sPtrInt2 = sPtrInt;
		std::cout << "Create a smart pointer by copy constructor. Value is: " << *sPtrInt2 << std::endl;
		
		{
			SharedPointer sPtrInt3 = sPtrInt2;
			std::cout << "Create a smart pointer by copy constructor. Value is: " << *sPtrInt3 << std::endl;
			*sPtrInt3 = 24;
		}
	}

	std::cout << "Value: " << *sPtrInt << std::endl;
}

SharedPointer::SharedPointer(int* ptr)
{
	this->count = new int;
	*this->count = 1;
	this->pointer_to_int = ptr;
}

SharedPointer::SharedPointer(SharedPointer& ptr)
{
	count = ptr.count;
	(*count)++;
	std::cout << "Increment number of shared pointer linked to that value. " << *count << std::endl;
	pointer_to_int = ptr.pointer_to_int; 
}

SharedPointer::~SharedPointer()
{
	if(*this->count == 1)
	{
		std::cout << "Delete pointer and count because no more reference." << std::endl;
		delete this->count;
		delete this->pointer_to_int;
	}
	else
	{
		(*count)--;
		std::cout << "Decremet number of shared pointers linked to that value. " << *count << std::endl;
	}
}
