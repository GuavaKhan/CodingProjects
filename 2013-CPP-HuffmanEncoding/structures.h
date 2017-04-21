// pktemple; Temple, Parker

#ifndef STRUCTURES_H
	#define STRUCTURES_H

#include <iostream>
#include <string>
using namespace std;
typedef unsigned char byte;

class Obj{
	public:
	int x;
	Obj(){
		x = 0;
	}//Obj
	void setX(int i){
	x = i;
	}//setX
};//Object

class HuffChar{
	public:
	byte b;
	string code;
	HuffChar(byte bite, string c){
		b = bite;
		code = c;
	}
	HuffChar(){
		b = 0;
		code = "";
	}
	void append(byte b){
		code += (char) b;
	}
	HuffChar& operator=(HuffChar o){
		b = o.b;
		code = o.code;
		return *this;
	}//operator=
	void print(){
		cout << "Char: " << b << ", Code: " << code << endl;
	}//print()
};//HuffChar

template <class T>
class TreeNode{
	public:
	unsigned int weight;
	T data;
	TreeNode<T> *leftChild;
	TreeNode<T> *rightChild;

	//constructor
	TreeNode(TreeNode<T> *first, TreeNode<T> *second, T d, unsigned int w){
		leftChild = first;
		rightChild = second;
		data = d;
		weight = w;
	}//TreeNode(first,second,d)

	//Comparisons
	TreeNode(){ }
	bool operator<(TreeNode o){
		if(weight < o.weight){
			return 1;
		}else if(weight == o.weight && data < o.data){
			return 1;
		}
		return 0;
	}//operator>
	bool operator<=(TreeNode o){
		if(weight < o.weight)
			return 1;
		else if(weight == o.weight && data <= o.data)
			return 1;
		return 0;
	}//operator>

	void print(){
		cout << "Wt: " << weight << ", Data: " << (int) data;
	}//print()

	bool operator>(TreeNode o){
		if(weight > o.weight)
			return 1;
		else if(weight == o.weight && data > o.data)
			return 1;
		return 0;
	}//operator>
	bool operator>=(TreeNode o){
		if(weight > o.weight){
			return 1;
		}
		else if(weight == o.weight && data >= o.data){
			return 1;
		}
		return 0;
	}//operator>
	TreeNode& operator=(TreeNode o){
		data = o.data;
		leftChild = o.leftChild;
		rightChild = o.rightChild;
		weight = o.weight;
		return *this;
	}//operator=
	bool isLeaf(){
		if(leftChild == NULL && rightChild == NULL)
			return 1;
		return 0;
	}//isLeaf()
};//TreeNode

template <class T>
class Tree{
	public:
	TreeNode<T> *root;
};//Tree

typedef TreeNode<byte> tnb;
template <class T>
class MinHeap{
	public:
	T *heap;
	int heapSize;
	int cap;
	//functions
	MinHeap(int theCap);
	~MinHeap();
	T& top();
	bool empty();
	void push(T e);
	void pop();
	bool traverse(tnb* node, byte key, string* str);
	MinHeap<T>& operator=(MinHeap<T> o){
		heapSize = o.heapSize;
		cap = o.cap;
		memcpy(heap, o.heap, o.heapSize * sizeof(T));
		return *this;
	}
	void print(){
		for(int i = 1; i < heapSize; i++){
			heap[i]->print();
			cout << ", ";
			}//for
	}//print()
};//MinHeap

TreeNode<byte>* highPriority(TreeNode<byte>* a, TreeNode<byte>* b){
	if(*a < *b)
		return a;
	else
		return b;
}//priority()
TreeNode<byte>* lowPriority(TreeNode<byte>* a, TreeNode<byte>* b){
	if(*a >= *b)
		return a;
	else
		return b;
}//priority()

template <class T>
const T& ucmin(const T& x, const T& y){
	if(x <= y)
		return x;
	else
		return y;
}//min()

//HERE check which tree, left or right, has higher priority.
void Huffman(MinHeap<TreeNode<byte>*> *heap, int n){
	for(int i = 0; i < n-1; i++){
		TreeNode<byte> *first = heap->top();
		heap->pop();
		TreeNode<byte> *second = heap->top();
		heap->pop();
		
		TreeNode<byte>* bt = new TreeNode<byte>(lowPriority(first,second), highPriority(first,second), 
			ucmin(first->data, second->data), first->weight + second->weight);
		heap->push(bt);
	}//for i
}//Huffman()

template<class T>
MinHeap<T>::MinHeap(int theCap){
	cap = theCap;
	heapSize = 0;
	heap = new T[cap+1];
}//MinHeap()
	
template<class T>
MinHeap<T>::~MinHeap(){
	delete[] heap;
}//~MinHeap()

template<class T>
T& MinHeap<T>::top(){
	return heap[1];
}//top()

template<class T>
bool MinHeap<T>::empty(){
	if(heapSize)
		return 0;
	return 1;
}//empty()

template<class T>
void MinHeap<T>::push(T e){
		//resize if heapSize equiv to max size
		if(heapSize == cap){
			resizeArray(heap, cap*2);
		}

		//push
		int currentNode = ++heapSize;
    while(currentNode != 1 && higherPriority(heap[currentNode/2], e)){
      heap[currentNode] = heap[currentNode/2];
      currentNode /= 2;
    }//while
    heap[currentNode] = e;
}//push(T e)

template <class T>
void hswap(T* a, T* b){
	T c = *b;
	*b = *a;
	*a = c;
}//swap(a,b)

bool higherPriority(TreeNode<byte>* a, TreeNode<byte>* b){
	if(*a < *b)
		return 0;
	else
		return 1;
}//priority()

template<class T>
void MinHeap<T>::pop(){
	if(!heapSize){
		cout << "Heap is empty. Cannot delete." << endl;
		throw "Heap is empty. Cannot delete.";
	}

  T lastE= heap[heapSize--];

  int currentNode = 1;
  int child = 2;
  while(child <= heapSize){
    if(child < heapSize && higherPriority(heap[child],heap[child+1])) child++;
    if(! higherPriority(lastE, heap[child])) break;
    heap[currentNode] = heap[child];
    currentNode = child; child*=2;
   }
  heap[currentNode] = lastE;
}//pop()

template<class T>
bool MinHeap<T>::traverse(tnb* root, byte key, string* str){
	//
	if(root == NULL)
		return 0;
	if(root->isLeaf() && key == root->data){
		return 1;
	}
	if(traverse(root->leftChild, key, str)){
		str->insert(str->begin(), '0');
		return 1;
	}
	if(traverse(root->rightChild, key, str)){
		str->insert(str->begin(), '1');
		return 1;
	}
	return 0;
}//traverse()
#endif
