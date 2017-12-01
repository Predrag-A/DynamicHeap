#pragma once
#include <iostream>
#include <queue>
#include <bitset>
#include <string>
#include "Exception.h"
template<class T>
class Node
{
private:
	T data;
	Node<T> *parent, *left, *right;
	Node()
	{
		parent = left = right = NULL;
	}
	Node(T newData, Node<T>* newParent)
	{
		data = newData;
		parent = newParent;
		left = right = NULL;
	}

	~Node() {}
	void visit() { std::cout << "\t" << data; }
	template <class T> friend class DynamicHeap;
};

template<class T>
class DynamicHeap
{
protected:
	Node<T>* root;
	int count;

	//Helper functions for recursion
	void deleteHeap(Node<T>*);
	bool isEmpty();
	void join(Node<T>*);
	void swap(Node<T>*, Node<T>*);
	void pushMin(T);
	void findNodes(Node<T>*&, Node<T>*&);
public:
	//Constructor and destructor
	DynamicHeap() { root = NULL; count = 0; }
	virtual ~DynamicHeap() { deleteHeap(root); }

	//Push, Pop and Print
	void push(T);
	T pop();
	void print();

	//Implemented functions
	void join(DynamicHeap);		//Joining two heaps into one (Destructor crashes)
	void toMinHeap();			//Convert to MinHeap
};

template<class T>
inline void DynamicHeap<T>::deleteHeap(Node<T>* node)
{
	if (node != NULL)
	{
		deleteHeap(node->left);
		deleteHeap(node->right);
		delete node;
	}
}

template<class T>
inline bool DynamicHeap<T>::isEmpty()
{
	if (count == 0 || root == NULL)
		return true;
	return false;
}

template<class T>
inline void DynamicHeap<T>::join(Node<T>*node)
{
	if (node != NULL)
	{
		push(node->data);
		join(node->left);
		join(node->right);
	}
}

template<class T>
inline void DynamicHeap<T>::swap(Node<T>* n1, Node<T>* n2)
{
	T temp = n1->data;
	n1->data = n2->data;
	n2->data = temp;
}

template<class T>
inline void DynamicHeap<T>::pushMin(T el)
{
	count++;
	if (count == 1)
		root = new Node<T>(el, NULL);
	else
	{
		Node<T> *temp = root, *prev = root;
		findNodes(temp, prev);
		temp = new Node<T>(el, prev);
		if (prev->left == NULL)
			prev->left = temp;
		else
			prev->right = temp;		//Elements are already sorted so no need for a while loop
	}
}

template<class T>
inline void DynamicHeap<T>::findNodes(Node<T>*& temp, Node<T>*& prev)
{
	std::string binary = std::bitset<10>(count).to_string();	//Number of elements->Binary number->String
	std::string::iterator it = binary.begin();					//Iterator for the string
	while (*it != '1')
		it++;													//Until the iterator hits the first digit
	it++;
	for (; it != binary.end(); ++it)
	{
		prev = temp;
		if (*it == '0')											//If 0, go left, else go right
			temp = temp->left;
		else
			temp = temp->right;
	}
}



template<class T>
inline void DynamicHeap<T>::push(T el)
{
	count++;
	if (count == 1)
		root = new Node<T>(el, NULL);
	else
	{
		Node<T> *temp = root, *prev = root;
		findNodes(temp, prev);			//Finds the insertion location
		temp = new Node<T>(el, prev);
		if (prev->left == NULL)
			prev->left = temp;
		else
			prev->right = temp;
		while (temp != root && temp->data > temp->parent->data)
		{
			swap(temp, temp->parent);
			temp = temp->parent;
		}
	}

}

template<class T>
inline T DynamicHeap<T>::pop()
{
	if (isEmpty())
		throw new Exception("Heap je prazan.");
	T el = root->data;
	if (root->left == NULL && root->right == NULL)
	{
		count--;
		delete root;
		return el;
	}
	Node<T> *temp = root, *prev;
	findNodes(temp, prev);
	root->data = temp->data;
	if (prev->left->data == temp->data)
		prev->left = NULL;
	else
		prev->right = NULL;
	delete temp;
	count--;
	temp = root;
	while (!(temp->left == NULL && temp->right == NULL))	//Until a terminal node is found
	{
		if (temp->right == NULL)		//Left is checked in the while condition. Right is checked due to the program
		{								//crashing when checking temp->right-data if temp->right is NULL
			if (temp->data < temp->left->data)
			{
				swap(temp, temp->left);
				temp = temp->left;
			}
			else
				break;
		}
		else if (temp->data < temp->left->data && temp->left->data > temp->right->data)
		{
			swap(temp, temp->left);		//When el is smaller than left and left is larger than right
			temp = temp->left;
		}
		else if (temp->data < temp->right->data && temp->right->data >temp->left->data)
		{
			swap(temp, temp->right);	//Right larger than left and el smaller than right
			temp = temp->right;
		}
		else if (temp->data > temp->right->data && temp->data > temp->left->data)
		{
			break;						//El larger than both left and right
		}
		else
		{
			swap(temp, temp->left);		//Else swap with left
			temp = temp->right;
		}
	}
	return el;
}

template<class T>
inline void DynamicHeap<T>::join(DynamicHeap heap)
{
	if (!heap.isEmpty())
	{
		this->join(heap.root);
	}
}

template<class T>
inline void DynamicHeap<T>::toMinHeap()
{
	if (isEmpty())
		throw new Exception("The heap is empty.");
	int n = count;
	T* arr = new T[n];
	for (int i = 0; i < n; i++)
		arr[i] = pop();
	for (int i = n - 1; i >= 0; i--)
		pushMin(arr[i]);
	delete[] arr;
}



template<class T>
inline void DynamicHeap<T>::print()
{
	if (isEmpty())
		throw new Exception("The heap is empty.");
	std::cout << "Level order traversal: ";
	std::queue<Node<T>*> queue;
	queue.push(root);
	Node<T>* temp;
	while (!queue.empty())
	{
		temp = queue.front();
		queue.pop();
		temp->visit();
		if (temp->left != NULL)
			queue.push(temp->left);
		if (temp->right != NULL)
			queue.push(temp->right);
	}
	std::cout << std::endl;
}

