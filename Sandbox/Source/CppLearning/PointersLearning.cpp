#include <iostream>
#include "PointersLearning.h"
#include "FastEngine/Log.h"


void PointersLearning::PrintPointers()
{
	bool isBoolean = true;
	PointersLearning::BoolParameterPointer(&isBoolean);
	bool* isBooleanPointer = &isBoolean;
	PointersLearning::BoolParameterPointer(isBooleanPointer);

	int var = 5;
	std::cout << "var = " << var << " // &var reference = " << &var << std::endl;
	//Create a reference (can be similar to pointer, it's an alias to a variable)
	int &var_ref = var;
	//Access the adress of the variable by &var and store it inside the pointer
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
	
	/*
	* Access content of a pointer 
	*/
	int* var_ptr_3 = new int;
	std::cout << "var_ptr_3 is a simple pointer. " << var_ptr_3 << " " << *var_ptr_3 << std::endl;
	//Output: *var_ptr_3 = 25;
	delete var_ptr_3;

	/*
	* Different types of const pointers
	*/
	int x;
	int *p1 = &x;  // non-const pointer to non-const int
	const int * p2 = &x;  // non-const pointer to const int
	int * const p3 = &x;  // const pointer to non-const int
	const int * const p4 = &x;  // const pointer to const int 

	/*
	* Vectors & Iterators
	*/
	std::vector<int> vect(5, 10);
	std::cout << "Display content of vector with for loop:" << std::endl;
	for(int x : vect)
		std::cout << x << " ";

	std::cout << std::endl;

	/*
	* Create array and use begin and end for revers iteration
	*/
	std::vector<int> myVector;
	myVector.push_back(10);
	myVector.push_back(5);
	myVector.push_back(3);

	//First iterate normally
	std::cout << "Display content of vector with for loop using begin and end:" << std::endl;
	for (auto it = myVector.begin(); it != myVector.end(); it++)
	{
		std::cout << " " << *it;
		if(myVector.back() == *it)
		{
			std::cout << " " << std::endl;
		}
	}

	//Reverse iteration (However I don't understand how it works :))
	for(auto it = myVector.rbegin(); it!= myVector.rend(); it++)
	{
		std::cout <<  " " << *it;
		if (*(myVector.begin()) == *it)
		{
			std::cout << " " << std::endl;
		}
	}

	//Reverse iteration
	for(auto it = myVector.end(); it != myVector.begin();)
	{ 
		std::cout << " " << *(--it);
		if(it == myVector.begin())
		{
			std::cout << std::endl;
		}
	}

	std::cout << std::endl;
	
	/*
	* A Stack is a container where elements are inserted and extracted from one side of the container (generally top)
	* This is LIFO (Last-in first-out)  -> Last product in the stack are the first to get out
	* 
	* Technical objective: 
	**** Store the top (index or pointer) in order to "Push" and "Pop" 
	* 
	* Stack is used for example in game engine to keep a stack of rendering layer (Editor - Render - UI) 
	*/

	std::vector<int> myList;
	//Emplace gets vector iterator and insert 
	/*
	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);
	myList.push_back(99);
	*/

	std::vector<int>::iterator itTopLayer = myList.begin();
	int layerInsertIndex = 0;
	itTopLayer = myList.emplace(itTopLayer, 1);
	std::cout << " " << * myList.begin();
	itTopLayer = myList.emplace(itTopLayer, 2);
	std::cout << " " << * myList.begin();
	itTopLayer = myList.emplace(itTopLayer, 3);
	std::cout << " " << * myList.begin();
	itTopLayer = myList.emplace(itTopLayer, 22);
	std::cout << " " << * myList.begin();
	std::cout << *(itTopLayer) <<std::endl;
	for(auto it = myList.begin(); it != myList.end(); it++)
	{
		std::cout << " " << *(it);
		if(it+1 == myList.end())
		{
			std::cout << std::endl;
		}
	}
	
	//auto tempItToRemove = std::find(myList.begin(), myList.end(), 1);
	//myList.erase(tempItToRemove);
	//itTopLayer--;
	std::cout << *(itTopLayer) <<std::endl;

	for(auto it = myList.begin(); it != myList.end(); it++)
	{
		std::cout << " " << *(it);
	}
	std::cout << std::endl;

	//myList.emplace_back(4);
	//std::cout << *(itTopLayer) << std::endl;
	//myList.emplace_back(5);
	//std::cout << *(itTopLayer) << std::endl;

	itTopLayer = myList.emplace(itTopLayer, 6);
	for(auto it = myList.begin(); it != myList.end();it++)
	{
		std::cout << " " << *(it);
		if(it == myList.end())
			std::cout << " test " << std::endl;
	}
	

	/*
	* Create a custom shared pointer
	*/
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

void PointersLearning::BoolParameterPointer(bool* p_open)
{
	std::cout << *p_open << std::endl;
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
