#pragma once
#include <stdexcept>
#include "Node.h"


template <class T>
class Stack
{
	size_t count;
	Node<T>* last;

public:
	~Stack() 
	{
		while (last != nullptr)
		{
			Node<T>* prevNode = last->GetNext();
			delete last;
			last = prevNode;
		}
	}
	Stack() : count(0), last(nullptr)  {}

	//**************************************************************//
	//********ACHTUNG!!! HERE REAL STACK FUNCTIONS COME!!!**********//
	//**************************************************************//
	//**************************************************************//

	void Push(T value)
	{
		Node<T>* newNode = new Node<T>(value);

		if (last != nullptr)
			newNode->SetNext(last);

		last = newNode;
		count++;
	}
	T Pop()
	{
		Node<T>* toPop = last;

		if (toPop != nullptr)
		{
			T data = toPop->GetData();
			last = toPop->GetNext();
			count--;

			delete toPop;
			return data;
		}
		else
			throw std::exception("Can't pop empty stack!");


	}
	T Peek()
	{
		Node<T>* toPeek = last;

		if (toPeek != nullptr)
			return toPeek->GetData();
		else
			throw std::exception("Can't peek empty stack!");
	}
	size_t GetSize()
	{
		return count;
	}



};