#pragma once

class SharedPointer
{
public:
	SharedPointer(int* ptr = nullptr);
	SharedPointer(SharedPointer& ptr);
	~SharedPointer();

	int* get()
	{
		return pointer_to_int;
	}

	int* operator->()
	{
		return pointer_to_int;
	}

	int& operator*()
	{
		return *pointer_to_int;
	}

private:
	int * count;
	int * pointer_to_int;
};

class PointersLearning
{
	public:
		void PrintPointers();
};