#pragma once
#include <stdexcept>
#include "Node.h"


template <class T>
class Queue
{
	size_t count;
	Node<T>* last, *first;

public:
	~Queue() 
	{
		while (last != nullptr)
		{
			Node<T>* nextNode = first->GetNext();
			delete first;
			first = nextNode;
		}
	}
	Queue() : count(0), last(nullptr), first(nullptr)  {}

	//**************************************************************//
	//********ACHTUNG!!! HERE REAL STACK FUNCTIONS COME!!!**********//
	//**************************************************************//
	//**************************************************************//

	void Enqueue(T value)
	{
		Node<T>* newNode = new Node<T>(value);

		if (GetSize() != 0)
		{
			last->SetNext(newNode);
			last = newNode;
		}
		else
			first = last = newNode;

		count++;
	}
	T Dequeue()
	{
		Node<T>* toPop = first;

		if (toPop != nullptr)
		{
			T data = toPop->GetData();
			first = toPop->GetNext();
			count--;

			delete toPop;
			return data;
		}
		else
			throw std::exception("Can't dequeue empty queue!");


	}
	T Peek()
	{
		Node<T>* toPeek = first;

		if (toPeek != nullptr)
			return toPeek->GetData();
		else
			throw std::exception("Can't peek empty queue!");
	}
	size_t GetSize()
	{
		return count;
	}



};