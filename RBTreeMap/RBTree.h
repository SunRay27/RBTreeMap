#pragma once
#include "RBNode.h"
#include "Stack.h"
#include "Queue.h"
#include "List.h"
#include "TreePrinter.h"

#pragma region Tree_Iterator_classes
template <typename TKey, typename TValue>
class Iterator
{
public:
	virtual RBNode<TKey, TValue>* Next() = 0;
	virtual bool HasNext() = 0;
};
template <typename TKey, typename TValue>
class TreeDFTIterator : public Iterator<TKey, TValue>
{
private:
	Stack<RBNode<TKey, TValue>*> stack;
	RBNode<TKey, TValue>* nil;
	void PushToLeft(RBNode<TKey, TValue>* node)
	{
		if (node == nil)
			return;

		stack.Push(node);
		PushToLeft(node->GetLeft());
	}
public:
	TreeDFTIterator(RBNode<TKey, TValue>* start, RBNode<TKey, TValue>* nil)
	{
		this->nil = nil;
		PushToLeft(start);
	}
	RBNode<TKey, TValue>* Next() override
	{
		RBNode<TKey, TValue>* next = stack.Pop();
		PushToLeft(next->GetRight());
		return next;
	}
	bool HasNext() override
	{
		return stack.GetSize() != 0;
	}
};
template <typename TKey, typename TValue>
class TreeBFTIterator : public Iterator<TKey, TValue>
{
private:
	Queue<RBNode<TKey, TValue>*> queue;
	RBNode<TKey, TValue>* nil;
public:
	TreeBFTIterator(RBNode<TKey, TValue>* start, RBNode<TKey, TValue>* nil)
	{
		this->nil = nil;
		if (start == nil)
			return;

		queue.Enqueue(start);
	}
	RBNode<TKey, TValue>* Next() override
	{
		RBNode<TKey, TValue>* next = queue.Dequeue();
		if (next->GetLeft() != nil)
			queue.Enqueue(next->GetLeft());

		if (next->GetRight() != nil)
			queue.Enqueue(next->GetRight());

		return next;
	}
	bool HasNext() override
	{
		return queue.GetSize() != 0;
	}
};
template <typename TKey, typename TValue>
#pragma endregion 

class Map
{
private:
	RBNode<TKey, TValue>* root;
	RBNode<TKey, TValue>* nil;

	RBNode<TKey, TValue>* minKeyNode(RBNode<TKey, TValue>* root)
	{
		RBNode<TKey, TValue>* minv = root;
		while (minv->GetLeft() != nil)
		{
			minv = root->GetLeft();
		}
		return minv;
	}
	RBNode<TKey, TValue>* FindNode(TKey key)
	{
		RBNode<TKey, TValue>* current = root;
		while (current != nil) {
			if (key == current->GetKey())
				return current;
			else
			{
				if (key < current->GetKey())
					current = current->GetLeft();
				else
					current = current->GetRight();
			}
		}
		throw invalid_argument("key is not present in collection");
	}

#pragma region Tree_transformations
	void TransplantNode(RBNode<TKey, TValue>* value, RBNode<TKey, TValue>* replacedBy)
	{
		if (value->GetParent() == nil)
			root = replacedBy;
		else if (value == value->GetParent()->GetLeft())
			value->GetParent()->SetLeft(replacedBy);
		else
			value->GetParent()->SetRight(replacedBy);


		if (replacedBy != nil)
			replacedBy->SetParent(value->GetParent());



	}
	void LeftRotate(RBNode<TKey, TValue>* x)
	{
		RBNode<TKey, TValue>* y = x->GetRight();
		x->SetRight(y->GetLeft());

		if (y->GetLeft() != nil)
			y->GetLeft()->SetParent(x);

		y->SetParent(x->GetParent());

		if (x->GetParent() == nil)
			root = y;
		else if (x == x->GetParent()->GetLeft())
			x->GetParent()->SetLeft(y);
		else
			x->GetParent()->SetRight(y);

		y->SetLeft(x);
		x->SetParent(y);
	}
	void RightRotate(RBNode<TKey, TValue>* x)
	{
		RBNode<TKey, TValue>* y = x->GetLeft();
		x->SetLeft(y->GetRight());

		if (y->GetRight() != nil)
			y->GetRight()->SetParent(x);

		y->SetParent(x->GetParent());

		if (x->GetParent() == nil)
			root = y;
		else if (x == x->GetParent()->GetRight())
			x->GetParent()->SetRight(y);
		else
			x->GetParent()->SetLeft(y);

		y->SetRight(x);
		x->SetParent(y);
	}
	void RebuildTreeInsert(RBNode<TKey, TValue>* currentNode)
	{
		RBNode<TKey, TValue>* uncle = nil;
		while (currentNode->GetParent() != nil && !currentNode->GetParent()->IsBlack())
		{
			if (currentNode->GetParent() != currentNode->GetGrandparent()->GetLeft())
			{
				uncle = currentNode->GetGrandparent()->GetLeft();
				//that means it is empty leaf and it is black
				if (uncle == nil)
				{
					if (currentNode == currentNode->GetParent()->GetLeft())
					{
						currentNode = currentNode->GetParent();
						RightRotate(currentNode);
					}
					currentNode->GetParent()->SetBlack();
					currentNode->GetGrandparent()->SetRed();
					LeftRotate(currentNode->GetGrandparent());
					continue;
				}

				if (!uncle->IsBlack())
				{
					uncle->SetBlack();
					currentNode->GetParent()->SetBlack();
					currentNode->GetGrandparent()->SetRed();
					currentNode = currentNode->GetGrandparent();
				}
				else
				{
					if (currentNode == currentNode->GetParent()->GetLeft())
					{
						currentNode = currentNode->GetParent();
						RightRotate(currentNode);
					}
					currentNode->GetParent()->SetBlack();
					currentNode->GetGrandparent()->SetRed();
					LeftRotate(currentNode->GetGrandparent());
				}
			}
			else
			{
				uncle = currentNode->GetGrandparent()->GetRight();
				//that means it is empty leaf and it is black
				if (uncle == nil)
				{
					if (currentNode != currentNode->GetParent()->GetLeft())
					{
						currentNode = currentNode->GetParent();
						LeftRotate(currentNode);
					}
					currentNode->GetParent()->SetBlack();
					currentNode->GetGrandparent()->SetRed();
					RightRotate(currentNode->GetGrandparent());
					continue;
				}

				if (!uncle->IsBlack()) {
					uncle->SetBlack();
					currentNode->GetParent()->SetBlack();
					currentNode->GetGrandparent()->SetRed();
					currentNode = currentNode->GetGrandparent();
				}
				else
				{
					if (currentNode != currentNode->GetParent()->GetLeft())
					{
						currentNode = currentNode->GetParent();
						LeftRotate(currentNode);
					}
					currentNode->GetParent()->SetBlack();
					currentNode->GetGrandparent()->SetRed();
					RightRotate(currentNode->GetGrandparent());
				}
			}
			if (currentNode == root)
				break;
		}
		root->SetBlack();
	}
	void RebuildTreeDelete(RBNode<TKey, TValue>* currentNode)
	{
		RBNode<TKey, TValue>* brother;
		while (currentNode != root && currentNode->IsBlack())
		{
			if (currentNode == currentNode->GetParent()->GetLeft())
			{
				brother = currentNode->GetParent()->GetRight();

				if (brother->IsBlack() == false)
				{
					brother->SetBlack();
					currentNode->GetParent()->SetRed();
					LeftRotate(currentNode->GetParent());
					brother = currentNode->GetParent()->GetRight();
				}

				if (brother->GetLeft()->IsBlack() && !brother->GetRight()->IsBlack())
				{
					brother->SetBlack();
					currentNode = currentNode->GetParent();
				}
				else
				{
					if (brother->GetRight()->IsBlack())
					{
						brother->GetLeft()->SetRed();
						brother->SetBlack();
						RightRotate(brother);
						brother = currentNode->GetParent()->GetRight();
					}

					brother->SetIsBlack(currentNode->GetParent()->IsBlack());
					currentNode->GetParent()->SetBlack();
					brother->GetRight()->SetBlack();
					LeftRotate(currentNode->GetParent());
					currentNode = root;
				}
			}
			else
			{
				brother = currentNode->GetParent()->GetLeft();

				if (brother->IsBlack())
				{
					brother->SetRed();
					currentNode->GetParent()->SetRed();
					RightRotate(currentNode->GetParent());
					brother = currentNode->GetParent()->GetLeft();
				}

				if (!brother->GetLeft()->IsBlack() && brother->GetRight()->IsBlack())
				{
					brother->SetBlack();
					currentNode = currentNode->GetParent();
				}
				else
				{
					if (brother->GetLeft()->IsBlack())
					{
						brother->GetRight()->SetBlack();
						brother->SetRed();
						LeftRotate(brother);
						brother = currentNode->GetParent()->GetLeft();
					}

					brother->SetIsBlack(currentNode->GetParent()->IsBlack());
					currentNode->GetParent()->SetRed();
					brother->GetLeft()->SetRed();
					RightRotate(currentNode->GetParent());
					currentNode = root;
				}
			}
		}
		currentNode->SetBlack();
	}
#pragma endregion

public:

	Map() { nil = new RBNode<TKey, TValue>(); root = nil; }
	~Map() { Clear(); delete nil; }

	void Insert(TKey key, TValue value)
	{
		if (GetKeys().Contains(key))
			throw std::invalid_argument("Key already exists in map");


		RBNode<TKey, TValue>* newNode = new RBNode<TKey, TValue>(false, key, value, nil, nil, nil);
		RBNode<TKey, TValue>* curNode = root;
		RBNode<TKey, TValue>* target = curNode;

		while (curNode != nil)
		{
			target = curNode;
			if (newNode->GetKey() < curNode->GetKey())
				curNode = curNode->GetLeft();
			else
				curNode = curNode->GetRight();
		}
		if (target == nil)
		{
			newNode->SetBlack();
			root = newNode;
			return;
		}

		newNode->SetParent(target);


		if (newNode->GetKey() < target->GetKey())
			target->SetLeft(newNode);
		else
			target->SetRight(newNode);

		if (newNode->GetGrandparent() == nil)
			return;

		RebuildTreeInsert(newNode);
	}
	TValue Find(TKey key)
	{
		return FindNode(key)->GetValue();
		throw invalid_argument("key is not present in collection");
	}
	List<TKey> GetKeys()
	{
		List<TKey> keys;
		Iterator<TKey, TValue>* bft = CreateBFTIterator();
		while (bft->HasNext())
			keys.Add(bft->Next()->GetKey());
		delete bft;
		return keys;
	}
	List<TValue> GetValues()
	{
		List<TValue> values;
		Iterator<TKey, TValue>* bft = CreateBFTIterator();
		while (bft->HasNext())
			values.Add(bft->Next()->GetValue());
		delete bft;
		return values;
	}
	void Print()
	{
		TreePrinter<TKey, TValue> a;
		cout << endl << endl;
		a.PrintTree(root, nullptr, false);
	}
	void Remove(TKey key)
	{
		RBNode<TKey, TValue>* toDelete = FindNode(key);
		bool originalColorIsBlack = toDelete->IsBlack();
		RBNode<TKey, TValue>* x;
		RBNode<TKey, TValue>* y;

		//transplant left nil node
		if (toDelete->GetLeft() == nil)
		{
			x = toDelete->GetRight();
			TransplantNode(toDelete, x);
		}
		//transplant right nil node
		else if (toDelete->GetRight() == nil)
		{
			x = toDelete->GetLeft();
			TransplantNode(toDelete, x);
		}
		else
		{
			//find smallest key in right subtree and save its color
			y = minKeyNode(toDelete->GetRight());
			originalColorIsBlack = y->IsBlack();

			//x = smallest key right node
			x = y->GetRight();


			if (y->GetParent() == toDelete)
			{
				x->SetParent(y);
			}
			else
			{
				TransplantNode(y, y->GetRight());
				y->SetRight(toDelete->GetRight());
				//if(x != nil)
				y->GetRight()->SetParent(y);
				//if(y != toDelete->GetLeft())
				

			}



			TransplantNode(toDelete, y);
			y->SetLeft(toDelete->GetLeft());
			y->GetLeft()->SetParent(y);
			y->SetIsBlack(originalColorIsBlack);

		}

		//clear toDelete node links before deleting 

		//if (toDelete == toDelete->GetParent()->GetLeft())
		//	toDelete->GetParent()->SetLeft(nil);
		//else
		//	toDelete->GetParent()->SetRight(nil);

		toDelete->SetLeft(nullptr);
		toDelete->SetRight(nullptr);

		delete toDelete;

		//rebuild tree
		if (originalColorIsBlack && x != nil)
			RebuildTreeDelete(x);
	}
	void Clear()
	{
		Iterator<TKey, TValue>* bft = CreateBFTIterator();
		while (bft->HasNext())
			delete bft->Next();

		delete bft;
		root = nil;

	}
	bool Contains(TKey key)
	{
		RBNode<TKey, TValue>* current = root;
		while (current != nil) {
			if (key == current->GetKey())
				return true;
			else
			{
				if (key < current->GetKey())
					current = current->GetLeft();
				else
					current = current->GetRight();
			}
		}
		return false;
	}

	Iterator<TKey, TValue>* CreateDFTIterator() { return new TreeDFTIterator<TKey, TValue>(root,nil); }
	Iterator<TKey, TValue>* CreateBFTIterator() { return new TreeBFTIterator<TKey, TValue>(root, nil); }
};