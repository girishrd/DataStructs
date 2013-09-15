/*===================================================================
Author: Girish D.
Desc: A basic min heap implementation ( note that this is not a 'growing' heap)
Last revision:Sep-2013
Notes:

List of methods:
---------------
void heapifyUp();
void heapifyDown();
long returnHeapSize();
void insertElement(T element);
void deleteMinElement();
void printHeap();

Unit test stub included:
-----------------------
No
=====================================================================*/

#include"stdafx.h"
#include<stdlib.h>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#define DEBUG

const int MAX_HEAP_SIZE=10;//the max number of elements that can be stored

using namespace std;
template<typename T>
class HeapMin{
protected:
	long currentHeapSize; //the number of elements that are currently in the heap
	T *heapdata;//data array
	T *heapRoot;
	void heapifyUp();
	void heapifyDown();

public:
	HeapMin();
	HeapMin(long size);
	HeapMin(const HeapMin<T> &anotherHeapMin);
	~HeapMin();
	long returnHeapSize();
	void insertElement(T element);
	void deleteMinElement();
	void printHeap();
}; 


/*------------------------------------------
Constructors
---------------------------------------------*/
template<class T>
HeapMin<T>::HeapMin(){

	try{
		heapdata= new T[MAX_HEAP_SIZE];
	}
	catch(std::bad_alloc& exc){
	
		cout<<"ERROR: Out of memory! Unable to initalize heap. Exiting..."<<endl;
		exit(1);
	}
	
	for(long c=0; c< MAX_HEAP_SIZE; c++){
		heapdata[c]=0.0;
	}
	currentHeapSize=0;
	heapRoot=&heapdata[0];

}

template<class T>
HeapMin<T>::HeapMin(long size){


	if(size <= 0)
	{
		cout<<"WARNING: Specified invalid size- defaulting to heap size of"<<MAX_HEAP_SIZE<<endl;
		size=MAX_HEAP_SIZE;
	}
	if(size > MAX_HEAP_SIZE)
	{
		cout<<"WARNING: Specified size exceeds MAX size- defaulting to heap size of"<<MAX_HEAP_SIZE<<endl;
		size=MAX_HEAP_SIZE;
	}
	else{

		try{
		heapdata= new T[size];
	}
	catch(std::bad_alloc& exc){
			cout<<"ERROR: Out of memory! Unable to initalize heap. Exiting..."<<endl;
		exit(1);
	}
	
	for(unsigned int c=0; c< size; c++){
		heapdata[c]=0.0;
		
	}
	currentHeapSize=0;
	heapRoot=&heapdata[0];	
	}
		
}
//---copy ctor
template<class T>
HeapMin<T>::HeapMin(const HeapMin<T> &anotherHeapMin) {

	if(anotherHeapMin.currentHeapSize <=0 ){
			return();
	}

	try{
		heapdata= new T[anotherHeapMin.currentHeapSize];
	}
	catch(std::bad_alloc& exc){
	
		cout<<"ERROR: Out of memory! Unable to initalize heap. Exiting..."<<endl;
		exit(1);
	}
	currentHeapSize=anotherHeapMin.currentHeapSize; 
	for(long c=0; c< anotherHeapMin.currentHeapSize; c++){
		heapdata[c]=anotherHeapMin.heapdata[c];
	}
	heapRoot=&heapdata[0]; //init root ptr
}


//-------------------------

template<class T>
HeapMin<T>::~HeapMin(){
	if(heapdata){
#ifdef DEBUG
		cout<<"Cleaning up..."<<endl;
#endif
		delete[] heapdata;
	}
}
//------------------------------
template<class T>
long HeapMin<T>::returnHeapSize(){

	return currentHeapSize;
}

//-insert element into the heap

template<class T>
void HeapMin<T>::insertElement(T element){

	if(currentHeapSize == MAX_HEAP_SIZE){
	
		cout<<"Heap size has reached the maximum limit!"<<endl;
		exit(1);
	}
	currentHeapSize++;
	
	heapdata[currentHeapSize-1]=element;
	heapifyUp();
}



template<class T>
void HeapMin<T>::heapifyUp(){
	long currentParentIndex=((currentHeapSize/2)-1); 
	long currentElementIndex=(currentHeapSize-1);

	T * parentElement= &heapdata[currentParentIndex];
	T* currentElement=&heapdata[currentElementIndex];
	
	while(currentElement!=heapRoot){
		if( *(parentElement) > *(currentElement) ){
		
			T temp = *(parentElement);
			*(parentElement) = *(currentElement);
			*(currentElement)=temp;
		}
	 
	 currentParentIndex=currentParentIndex/2;
	 currentElement=parentElement;
	 parentElement=&heapdata[currentParentIndex];
	
	}

}

//---heapify down
template<class T>
void HeapMin<T>::deleteMinElement(){

long currentElementIndex=0;
long leftChildIndex=(2*currentElementIndex) + 1; //root's left child
long rightChildIndex=(2*currentElementIndex) + 2;//root's right child
long minelement=heapdata[currentElementIndex];


while(currentElementIndex < (currentHeapSize-1)){
		if( heapdata[leftChildIndex] > heapdata[rightChildIndex]){//left child is greater

			heapdata[currentElementIndex]=heapdata[rightChildIndex];
			heapdata[rightChildIndex]=0;
			currentHeapSize--;
			currentElementIndex=rightChildIndex;
		}
		else if( heapdata[leftChildIndex] > heapdata[rightChildIndex]){//right child is greater

			heapdata[currentElementIndex]=heapdata[leftChildIndex];
			heapdata[leftChildIndex]=0;
			currentHeapSize--;
			currentElementIndex=leftChildIndex;
		}
		else{
			//maintain stability
			heapdata[currentElementIndex]=heapdata[leftChildIndex];
			currentElementIndex=leftChildIndex;
		}

	}
#ifdef DEBUG
std::cout<<"Deleted the minimum element ["<<minelement<<"] from the heap"<<endl;
#endif

}






template<class T>
void HeapMin<T>::printHeap(){

	cout<<"The current heap is:"<<endl;
	for(long c=0;c<currentHeapSize;c++){
	
		cout<<heapdata[c]<<endl;
	
	}
}





