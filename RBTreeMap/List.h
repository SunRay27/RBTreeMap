#pragma once
#include <stdexcept>
#include "Node.h"


template <class T>
class List
{
	 size_t curElement; size_t count;
	 Node<T> *head, *tail, *current, *previous;

private:
#pragma region Low-level private functions

	//Basic field accessors
	void SetHeadNode(Node<T>* n) { head = n; }
	void SetTailNode(Node<T>* n) { tail = n; }
	void SetCurrentNode(Node<T>* n) { current = n; }
	void SetCurrentValue(T n) { current->SetData(n); }
	void SetPreviousNode(Node<T>* n) { previous = n; }
	Node<T>* GetHeadNode() { return head; }
	Node<T>* GetTailNode() { return tail; }
	Node<T>* GetCurrentNode() { return current; }
	T GetCurrentValue() { return GetCurrentNode()->GetData(); }
	Node<T>* GetPreviousNode() { return previous; }

	//Some basic movement logic
	Node <T>* GetNode(size_t i)
	{
		if (i<0 || i > count - 1)
			return nullptr;

		if (curElement > i)
			MoveToHead();

		for (size_t j = curElement; j < i; j++)
			MoveForward();

		return GetCurrentNode();
	}
	void MoveForward()
	{
		SetPreviousNode(GetCurrentNode());
		SetCurrentNode(GetCurrentNode()->GetNext());
		curElement++;
	}
	void MoveToHead()
	{
		SetPreviousNode(nullptr);
		SetCurrentNode(head);
		curElement = 0;
	}
	void MoveToTail()
	{
		MoveToHead();
		while (GetCurrentNode()->GetNext() != nullptr)
			MoveForward();
	}

	//and exception thrower
	void CheckBounds(size_t index)
	{
		if (index < 0 || index > count - 1 || count == 0)
			throw std::exception("Index is out of bounds");
	}
#pragma endregion

public:
	~List() {Clear();}
	List() : count(0), curElement(0), head(nullptr), tail(nullptr), current(nullptr), previous(nullptr) {}

	template <class T>
	void AddValues(std::initializer_list<T> list)
	{
		for (auto elem : list)
		{
			Add(elem);
		}
	}

	void RemoveAll(T value)
	{
		for (size_t i = 0; i < GetSize(); i++)
			if (value == At(i))
			{
				Remove(i);
				i--;
			}
	}
	void RemoveFirst(T value)
	{
		for (size_t i = 0; i < GetSize(); i++)
			if (value == At(i))
			{
				Remove(i);
				return;
			}
	}
	T operator[] (size_t index) { return At(index); }


	//**************************************************************//
	//************ACHTUNG!!! HERE REAL FUNCTIONS COME!!!************//
	//**************************************************************//
	//**************************************************************//

	//CHECK IT OUT!!! IT IS NOT MY VARIANT BUT STILL PLS CHECK
	/*+*/void Swap(size_t i, size_t j)
	{
		CheckBounds(i);
		CheckBounds(j);

		//Our job is done here
		if (j == i)
			return;

		//Make i < j because it matters
		if (i > j)
		{
			size_t t = i;
			i = j;
			j = t;
		}

		//Get all usefull nodes
		Node<T>* iNodePrevious = GetNode(i - 1);
		Node<T>* iNode = GetNode(i);
		Node<T>* iNodeNext = GetNode(i + 1);

		Node<T>* jNodePrevious = GetNode(j - 1);
		Node<T>* jNode = GetNode(j);
		Node<T>* jNodeNext = GetNode(j + 1);

		
		

		//swap head/tail if needed
		if (iNode == head)
			head = jNode;
		if (jNode == tail)
			tail = iNode;

		//fix node link which was before iNode
		if (iNodePrevious != nullptr)
			iNodePrevious->SetNext(jNode);

		//if nodes are neighbours we just reassign links
		if (i + 1 == j)
		{
			//just swap
			jNode->SetNext(iNode);
			iNode->SetNext(jNodeNext);
		}
		else
		{
			//fix node link which was before jNode
			if (jNodePrevious != nullptr)
				jNodePrevious->SetNext(iNode);
			//swap
			jNode->SetNext(iNodeNext);
			iNode->SetNext(jNodeNext);
		}

		MoveToHead();
	}

	bool Contains(T value)
	{
		for (size_t i = 0; i < count; i++)
		{
			T checkValue = At(i);

			if (value == checkValue)
				return true;
		}
		return false;
	}

	/*+*/void Add(T value)
	{
		Node<T>* toAdd = new Node<T>(value);

		//Check if list is clean and if so, setup global pointers
		if(IsEmpty())
			head = current = previous = tail = toAdd;
		else
		{
			//or just add new value to tail
			tail->SetNext(toAdd);
			tail = toAdd;
			MoveToHead();
		}
		count++;
		
	}
	/*+*/void InsertFirst(T value)
	{
		Node<T>* toAdd = new Node<T>(value);

		//Check if list is clean and if so, setup global pointers
		// OH IT IS SO GREAT TO HAVE FUNCTIONS, WHICH JUST WORK
		if (IsEmpty())
			head = current = previous = tail = toAdd;
		else
		{
			toAdd->SetNext(head);
			head = toAdd;
			MoveToHead();
		}
		count++;
		
	}
	/*+*/void PopBack()
	{
		Remove(count - 1);

		//Do we really get a perfomance boost by implementing special case of Remove(count - 1) function???
		/*
		if(IsEmpty())
			throw std::invalid_argument("Tried to remove element from empty list");

		Node<T>* previousNode = GetNode(count - 2);
		Node<T>* toDelete = GetNode(count - 1);

		//Fix head/tail pointers if toDelete element is head/tail
		if (toDelete == head)
			head = nullptr;
		if (toDelete == tail)
			tail = previousNode;

		if (previousNode != nullptr)
			previousNode->SetNext(nullptr);

		//Fix curElement pointer (it might be toDelete node)
		MoveToHead();
		count--;
		delete toDelete;
		*/
	}
	/*+*/void PopFront()
	{
		Remove(0);

		//Do we really get a perfomance boost by implementing special case of Remove(0) function???
		/*
		if(IsEmpty())
			throw std::invalid_argument("Tried to remove element from empty list");

		Node<T>* toDelete = GetNode(index);
		Node<T>* nextNode = GetNode(index + 1);

		//Fix head/tail pointers if toDelete element is head/tail
		if (toDelete == head)
			head = nextNode;
		if (toDelete == tail)
			tail = nullptr;

		//Fix curElement pointer (it might be toDelete node)
		MoveToHead();
		count--;
		delete toDelete;
		*/
	}
	/*+*/void Insert(T value, size_t index)
	{
		//Check if index is ok
		CheckBounds(index);

		MoveToHead();

		//previous can be nullptr!!!
		Node<T>* previousNode = GetNode(index - 1);
		Node<T>* moveNode = GetNode(index);
		Node<T>* toInsert = new Node<T>(value);

		//Set new links
		if(previousNode != nullptr)
			previousNode->SetNext(toInsert);
		toInsert->SetNext(moveNode);

		//set global pointers
		if (moveNode == head)
			head = toInsert;

		count++;
		MoveToHead();
	}
	T At(size_t index)
	{
		//Check if index is ok
		CheckBounds(index);

		return GetNode(index)->GetData();

		/*
		//We cant get this element from current position, so MOVE TO HEAD
		if (curElement > index)
			MoveToHead();

		//No need to MOVE TO HEAD every time, we can use curElement to iterate forward
		for (size_t j = curElement; j < index; j++)
			MoveForward();

		return GetCurrentValue();*/
	}
	/*+*/void Remove(size_t index)
	{
		//Check if index is ok
		CheckBounds(index);

		Node<T>* previousNode = GetNode(index - 1);
		Node<T>* toDelete = GetNode(index);
		Node<T>* nextNode = GetNode(index + 1);

		//Fix head/tail pointers if toDelete element is head/tail
		if (toDelete == head)
			head = nextNode;
		if (toDelete == tail)
			tail = previousNode;

		//Connect previousNode with nextNode
		if (previousNode != nullptr)
			previousNode->SetNext(nextNode);

		//Fix curElement pointer (it might be toDelete node)
		MoveToHead();
		count--;
		delete toDelete;
	}
	/*+*/size_t GetSize()
	{
		return count;
	}
	/*+*/void Clear()
	{
		//if head is nullptr, that means list is BROKEN, or just clean
		//But it defenetly cant be broken, I'm sure
		//if (head != nullptr) ---> yeah! I'm so confident! YAY
		if (!IsEmpty())
		{
			//Delete all elements from head
			MoveToHead();
			do
			{
				MoveForward();
				delete GetPreviousNode();
			} while (GetCurrentNode() != nullptr);
		}
		count = 0;
	}
	/*+*/void Replace(T value, size_t index)
	{
		//Check if index is ok
		CheckBounds(index);

		GetNode(index)->SetData(value);
	}
	/*+*/bool IsEmpty()
	{
		return count < 1;
	} 
	
	
	/*+*/size_t FindFirst(List<T>& list)
	{
		//1. go through this list and get first matching element
		//2. then check others in row -> if this contains all -> return first element's index or continue
		//2.5 Consider some special cases, when list is smaller/bigger than this
		size_t firstLength = GetSize();
		size_t secondLength = list.GetSize();

		if ((secondLength > firstLength) || (secondLength == 0 || firstLength == 0))
			return -1;

		for (size_t i = 0; i < firstLength; i++)
		{
			
			for (size_t j = 0; j < secondLength; j++)
			{
				// if elements count from first is already smaller than second's length, we know first doesnt contain it for sure
				if (firstLength - i < secondLength)
					return -1;

				T val1 = At(i);
				T val2 = list.At(j);

				//we have first elements
				if (val1 == val2)
				{
					bool success = true;

					//check others
					for (size_t el = 1; el < secondLength - j; el++)
					{
						T val11 = At(i + el);
						T val22 = list.At(j + el);
						if (val11 != val22)
						{
							success = false;
							break;
						}
					}

					if (success)
						return i;
				}
				else
					break;

			}

		}
	}
	//WHY IS IT HERE
	void PrintToConsole()
	{
		MoveToHead();
		for (size_t i = 0; i < GetSize(); i++)
		{
			std::cout << GetCurrentValue() << ' ';
			MoveForward();
		}
		std::cout << std::endl;
	}
	//for debug only
	void SelfCheck()
	{
		MoveToHead();
		for (size_t i = 0; i < GetSize(); i++)
		{
			T val = GetCurrentValue();
			MoveForward();
		}
	}

	//copy constructor
	List<T>(List<T>& other)
	{
		//this(0, 0, nullptr, nullptr, nullptr, nullptr);
		count = 0;
		curElement = 0;
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		previous = nullptr;
		
		for (size_t i = 0; i < other.count; i++)
		{
			T value = (other).At(i);
			this->Add(value);
		}

		
	}

	List<T>& operator=(const List<T>& other) 
	{
		count = 0;
		curElement = 0;
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		previous = nullptr;

		for (size_t i = 0; i < other.count; i++)
			this->Add(other.At(i));

		return *this;
	}
};