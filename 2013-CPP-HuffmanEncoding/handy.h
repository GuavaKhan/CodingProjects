#ifndef HANDY_H
	#define HANDY_H
	
#include <string.h>
#include <stdlib.h>
using namespace std;

int ctoi(char c){
	return (int) (c - '0');
}//ctoi

template <class T>
void swap(T* a, T* b){
	T c = *b;
	*b = *a;
	*a = c;
}//swap(a,b)

template <class T>
const T& tmin(const T& x, const T& y){
	if(x <= y)
		return x;
	else
		return y;
}//min()

template <class T>
const T& tmax(const T& x, const T& y){
	if(x >= y)
		return x;
	else
		return y;
}//min()

template <class T>
void resizeArray(T *arr, int &inpSize){
	int newSize = inpSize*2;
	T* newArr = new T[newSize];
	memcpy(newArr, arr, inpSize * sizeof(T));
	inpSize = newSize;
	delete []arr;
	arr = newArr;
}//resizeArray()

typedef unsigned char byte;
typedef TreeNode<byte> tnb;
void resizeArray(tnb **arr, int inpSize){
	int newSize = inpSize*2;
	tnb** newArr = new tnb*[newSize];
	memcpy(newArr, arr, inpSize * sizeof(tnb*));
	inpSize = newSize;
	delete []arr;
	arr = newArr;
}//resizeArray()

void resizeArray(tnb *arr, int inpSize){
	int newSize = inpSize*2;
	tnb* newArr = new tnb[newSize];
	memcpy(newArr, arr, inpSize * sizeof(tnb));
	inpSize = newSize;
	delete []arr;
	arr = newArr;
}//resizeArray()

void resizeArray(int *arr, int inpSize){
	int newSize = inpSize*2;
	int* newArr = new int[newSize];
	memcpy(newArr, arr, inpSize * sizeof(int));
	inpSize = newSize;
	delete []arr;
	arr = newArr;
}//resizeArray()

void resizeArray(char *arr, int inpSize){
	char newSize = inpSize*2;
	char* newArr = new char[newSize];
	memcpy(newArr, arr, inpSize * sizeof(char));
	inpSize = newSize;
	delete []arr;
	arr = newArr;
}//resizeArray()

template <class T>
void deleteCell(T *array, int &inpSize, int key){
	for(int i = key; i < inpSize-1; i++)
		array[i] = array[i+1];
	inpSize--;
}//deleteCell

void initArray(int *arr, int inpSize, int val){
	int i = 0;
	for(i = 0; i < inpSize; i++)
		arr[i] = val;
}//initArray()

void initArray(unsigned int *arr, int inpSize, unsigned int val){
	int i = 0;
	for(i = 0; i < inpSize; i++)
		arr[i] = val;
}//initArray()

template <class T>
void Adjust(T *a, const int root, const int n){
	T e = a[root];
	int j;
	for(j = 2*root; j <= n; j *= 2){
		if(j < n && a[j] < a[j+1]) j++;
		if(e >= a[j]) break;
		a[j/2] = a[j];
	}//j = 2*root
	a[j/2] = e;
}//Adjust()

template <class T>
void HeapSort(T *a, const int n){
	int i;
	for(i = n/2; i >= 1; i--)
		Adjust(a, i, n);

	for(i = n - 1; i >= 1; i--){
		//swap(a[1],a[i+1]);
		T temp = a[1];
		a[1] = a[i+1];
		a[i+1] = temp;
		Adjust(a,1,i);
	}//for i = n-1
}//HeapSort()
#endif
