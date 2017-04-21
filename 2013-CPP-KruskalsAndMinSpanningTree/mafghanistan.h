// pktemple; Temple, Parker

#ifndef MAFGHANISTAN_H
	#define MAFGHANISTAN_H

#include <iostream>
#include "handy.h"
using namespace std;


class Road{
	public:
	int weight;
	int v1, v2;

	Road(){
		weight = 0;
		v1 = 0;
		v2 = 0;
	}//Road()

	Road(int w, int c1, int c2){
		weight = w;
		if(c1 < c2){
			v1 = c1;
			v2 = c2;
		}
		else{
			v1 = c2;
			v2 = c1;
		}
	}//Road(w,*c1,*c2)
	
	~Road(){
		//
	}//~Road()

	void print(){
		cout << "Road from City " << v1 << " to City " << v2 << " and weight " << weight << endl;
	}//print()

	Road& operator=(const Road& o){
		weight = o.weight;
		v1 = o.v1;
		v2 = o.v2;
		return *this;
	}//operator =

	bool operator>=(const Road& o){
		if(weight > o.weight)
			return 1;
		else if(weight == o.weight){
			if(tmin(v1,v2) > tmin(o.v1,o.v2))
				return 1;
			else if(tmin(v1,v2) == tmin(o.v1,o.v2) && tmax(v1,v2) >= tmax(o.v1,o.v2))
				return 1;
		}//else if ==
		return 0;
	}//operator>=

	bool operator>(const Road& o){
		if(weight > o.weight)
			return 1;
		else if(weight == o.weight){
			if(tmin(v1,v2) > tmin(o.v1,o.v2))
				return 1;
			else if(tmin(v1,v2) == tmin(o.v1,o.v2) && tmax(v1,v2) > tmax(o.v1,o.v2))
				return 1;
		}//else if ==
		return 0;
	}//operator>

	bool operator<=(const Road& o){
		if(weight < o.weight)
			return 1;
		else if(weight == o.weight){
			if(tmin(v1,v2) < tmin(o.v1,o.v2))
				return 1;
			else if(tmin(v1,v2) == tmin(o.v1,o.v2) && tmax(v1,v2) <= tmax(o.v1,o.v2))
				return 1;
		}//else if ==
		return 0;
	}//operator<=
	bool operator<(const Road& o){
		//cout << o.v1 << ' ' << o.v2 << ' ' << o.weight << endl;
		if(weight < o.weight)
			return 1;
		else if(weight == o.weight){
			if(tmin(v1,v2) < tmin(o.v1,o.v2))
				return 1;
			else if(tmin(v1,v2) == tmin(o.v1,o.v2) && tmax(v1,v2) < tmax(o.v1,o.v2))
				return 1;
		}//else if ==
		return 0;
	}//operator<

};//class Road


template <class T>
class MinHeap{
	public:
	T **heap;
	int heapSize;
	int cap;
	T& top(){
		return *heap[1];
	}//top()
	bool empty(){
		if(heapSize)
			return 0;
		return 1;
	}//empty()

	void push(T* e){
		if(heapSize == cap){
			resizeArray(heap, cap);
		}
		int currentNode = ++heapSize;
		while(currentNode != 1 && *heap[currentNode / 2] > *e){
			*heap[currentNode] = *heap[currentNode / 2];
			currentNode /= 2;
		}//while
		*heap[currentNode] = *e;
	}//Push(T)

	void pop(){
		if(!heapSize){
			cout << "Heap is empty. Cannot delete." << endl;
			throw "Heap is empty. Cannot delete.";
		}
		//heap[1]->~T();

		T lastE = *heap[heapSize--];

		int currentNode = 1;
		int child = 2;
		while(child <= heapSize){
			if(child < heapSize && *heap[child] > *heap[child+1]) child++;

			if(lastE <= *heap[child]) break;

			*heap[currentNode] =* heap[child];
			currentNode = child; child *= 2;
		}//while child <= heapSize
		*heap[currentNode] = lastE;
	}//
	
	MinHeap(int theCap){
		cap = theCap;
		heapSize = 0;
		heap = new T*[cap+1];
		for(int i = 0; i < cap+1; i++)
			heap[i] = new T;
	}//MinHeap()
	
	~MinHeap(){
		//delete[] heap;
	}//~MinHeap()
	
};//MinHeap

class Region : public MinHeap<Road> {
	//
	public:
	Region() : MinHeap<Road>(10){	}//Region()
	Region(int theCap) : MinHeap<Road>(theCap){ }//Region(int)
	~Region(){ }

	int getNumCities(){
		return (heapSize + 1);
	}//getNumCities
	
	int getNumRoads(){
		return heapSize;
	}//getNumRoads
	
	Road& getMin(){
		return top();
	}//getMin()

	bool operator>=(Region o){
		if(heapSize > o.heapSize)
			return 1;
		else if(heapSize == o.heapSize && getMin() >= o.getMin())
			return 1;
		return 0;
	}//operator>
	bool operator>(Region o){
		if(heapSize > o.heapSize)
			return 1;
		else if(heapSize == o.heapSize && getMin() > o.getMin())
			return 1;
		return 0;
	}//operator>

	bool operator<=(Region o){
		if(heapSize < o.heapSize)
			return 1;
		else if(heapSize == o.heapSize && getMin() <= o.getMin())
			return 1;
		return 0;
	}//operator>
	bool operator<(Region o){
		if(heapSize < o.heapSize)
			return 1;
		else if(heapSize == o.heapSize && getMin() < o.getMin())
			return 1;
		return 0;
	}//operator>
	
	void output(){
		cout << "<region>\n";
		while((heapSize) != 0){
			cout << "<road>" << top().v1 << ' ' << top().v2 << ' ' << top().weight << "</road>\n";
			pop();
		}//for
		cout << "</region>\n";
	}//output()
};//class Region
#endif

class Sets{
	public:
	int *parent;
	int n;//number of elements

	Sets(int numElements){
		if(numElements < 2) throw "Must have at least 2 elements.";
		n = numElements;
		parent = new int[n];
		fill(parent, parent+n, -1);
	}//Sets(int)

	~Sets(){
		delete []parent;
	}//~Sets

	//set operations
	void print(){
		for(int i = 0; i < n; i++)
			cout << i << ": " << parent[i] << ", ";
		cout << endl;
	}//print()

	void fill(int *p, int *pn, int val){
		for(int i = 0; i < n; i++)
			p[i] = val;
	}//fill(int*,int*,int)

	void simpleUnion(int i, int j){
		parent[i] = j;
	}//simpleUnion(int,int)
	void weightedUnion(int i, int j){
		int temp = parent[i] + parent[j];
		if(parent[i] > parent[j]){
			parent[i] = j;
			parent[j] = temp;
		}//if p[i] > p[j]
		else{
			parent[j] = i;
			parent[i] = temp;
		}//else
	}//weightedUnion(int,int)

	int simpleFind(int i){
		while(parent[i] >= 0) i = parent[i];
		return i;
	}//simpleFind(int)
	int collapsingFind(int i){
		int r;
		for(r = i; parent[r] >= 0; r = parent[r]);
		while(i != r){//collapse
			int s = parent[i];
			parent[i] = r;
			i = s;
		}//while i != r
		return r;
	}//collapsingFind(int)
};//class Sets
