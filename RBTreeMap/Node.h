#pragma once
//Holder class for lists
template <class T>
class Node
{
	Node<T>* next; T data;
public:
	~Node() {}
	Node() : next(nullptr) {}
	Node(T value) : data(value), next(nullptr) {}

	void SetNext(Node<T>* nextElement) { next = nextElement; }
	void SetData(T newData)
	{
		data = newData;
	}
	Node* GetNext() { return next; }
	T GetData() { return data; }
};