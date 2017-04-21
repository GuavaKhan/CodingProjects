// pktemple; Temple, Parker
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cctype>
#include "mafghanistan.h"
#include "handy.h"
using namespace std;

void readIn(int &numCities, int &numOldRoads);
void readIn2(int numCities, int numOldRoads, Road *oldRoads);

void readIn(int &numCities, int &numOldRoads){
	char scan = ' ';
	//Read in numCities
	scan = getchar();
	while(isspace(scan))
		scan = getchar();
	do{
		numCities *= 10;
		numCities += ctoi(scan);
		scan = getchar();
	}while(isdigit(scan));

	//Read in Num Old Roads
	while(isspace(scan))
		scan = getchar();
	do{
		numOldRoads *= 10;
		numOldRoads += ctoi(scan);
		scan = getchar();
	}while(isdigit(scan));
}//readIn

void readIn2(int numCities, int numOldRoads, MinHeap<Road> *&oldRoads){
	char scan = ' ';
	int i = 0, wt = 0, c1 = 0, c2 = 0;
	//Read in all of cities
	i = 0;
	while((scan = getchar()) != EOF && i < numOldRoads){ //maybe prob here with i check?
		wt = 0, c1 = 0, c2 = 0;
		//get first city of road
		while(isspace(scan))
			scan = getchar();
		do{
			c1 *= 10;
			c1 += ctoi(scan);
			scan = getchar();
		}while(isdigit(scan));
		
		//get 2nd city of road
		while(isspace(scan))
			scan = getchar();
		do{
			c2 *= 10;
			c2 += ctoi(scan);
			scan = getchar();
		}while(isdigit(scan));
		
		//get weight of road
		while(isspace(scan))
			scan = getchar();
		do{
			wt *= 10;
			wt += ctoi(scan);
			scan = getchar();
		}while(isdigit(scan));
		
		Road r(wt, c1, c2);
		oldRoads->push(&r);
		i++;
	}//while !EOF
}//readIn2()

bool cycle(Road& r, Sets *&graph){
	int x1 = graph->collapsingFind(r.v1), x2 = graph->collapsingFind(r.v2);
	if(x1 != x2){
		graph->weightedUnion(x1,x2);
		return 0;	
	}
	return 1;
}//cycle

void minSpan(Sets *&graph, MinHeap<Road> *&oldRoads, int &numOldRoads, int &numNewRoads, int numCities, Region *&region){
	Road r;
	int n = numOldRoads;
	while(numNewRoads < (n) && numOldRoads != 0){	//switched n-1 to n
		r = oldRoads->top();
		oldRoads->pop();
		numOldRoads--;
		if(!cycle(r, graph)){
			region->push(&r);
			numNewRoads++;
		}
	}//while T < n-1 && E not empty
	
	//T = NULL;
	//While((T contains less than n-1 edges) && (E not empty)){
		//choose an edge (v,w) from E of lowest cost;
		//delete (v,w) from E;
		//if((v,w) does not create a cycle in T) add (v,w) to T;
		//else discard (v,w);
	//}
}//minSpan()

//void getRegions(Region mstree, int &numNewRoads, MinHeap<Region> &regions, Sets &graph, int *cities){
void getRegions(Region *mstree, int &numNewRoads, MinHeap<Region> *&regions, Sets *&graph, int *cities){
	int i = 0;
	int p1 = 0, p2 = 0;
	int arrSize = numNewRoads;
	Road *r = new Road[numNewRoads];

	for(i = 0; i < numNewRoads; i++){
		r[i] = mstree->top();
		if(cities[r[i].v1] == 0)
			cities[r[i].v1] = 1;
		if(cities[r[i].v2] == 0)
			cities[r[i].v2] = 1;
		mstree->pop();
	}//for i < numNewRoads, make arr of roads

	while(arrSize != 0){
		Region reg(arrSize);
		p1 = graph->collapsingFind(r[0].v1);
		for(i = 0; i < arrSize; i++){
			p2 = graph->collapsingFind(r[i].v1);
			if(p1 == p2){
				reg.push(&r[i]);
				deleteCell(r, arrSize, i);
				i--;
			}//if p1==p2
		}//for
		regions->push(&reg);
	}//while
	delete[] r;
}//getRegions()

void printEmptyRegions(int *cities, int &numCities){
	int i;
	for(i = 0; i < numCities; i++)
		if(cities[i] == 0)
			 cout << "<region>\n</region>\n";
}//printEmptyRegions()

int main(){
	//initializations
	int numCities = 0,
			numOldRoads = 0,
			numNewRoads = 0;
	
	//read in input and initilize road,city arrays
	readIn(numCities, numOldRoads);
	if(numOldRoads == 0){
		cout << "<?xml version=\"1.3\"?>\n<country>\n"; 
		for(int i = 0; i < numCities; i++)
			cout << "<region>\n</region>\n";
		cout << "</country>\n";
		exit(0);
	}//if no roads
	MinHeap<Road> *oldRoads = new MinHeap<Road>(numOldRoads);
	readIn2(numCities, numOldRoads, oldRoads);
	
	//min span tree & region computations
	Sets *graph = new Sets(numCities);
	Region *mstree = new Region(numOldRoads);
	minSpan(graph, oldRoads, numOldRoads, numNewRoads, numCities, mstree);
	delete oldRoads;
	int cities[numCities];
	initArray(cities, numCities, 0);
	MinHeap<Region> *regions = new MinHeap<Region>(numNewRoads);
	getRegions(mstree, numNewRoads, regions, graph, cities);

	//output
	cout << "<?xml version=\"1.3\"?>\n<country>\n"; 
	printEmptyRegions(cities, numCities);
	while(!regions->empty()){
		regions->top().output();
		regions->pop();
	}//while
	cout << "</country>\n";

	delete regions;
	delete graph;
	delete mstree;
	return 0;
}//main
