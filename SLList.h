//#include "stdafx.h"
#include<stdlib.h>
#include<vector>
#include<string>
#include<iostream>
#define DEBUG

long g_LISTSIZE=0;

#ifdef DEBUG
	long deallocCount=1;
#endif


//----list class--------------------------------------------------------
template <typename T>
class SLList{
private:

	//simple node structure -- add more data fields if required later
struct SLnode                                                
{                                                               
      std::vector<T> nodeData;               
      SLnode *next;             
};



struct SLnode* head;
struct SLnode* tail;


public:
//-------------------------------------------
SLList(){
std::cout<<"called default ctor"<<std::endl;
head=NULL;
tail=NULL;	

}


SLList(T element){

		std::cout<<"called param ctor"<<std::endl;
		struct SLnode * firstnode= new struct SLnode;
		
		firstnode->nodeData.push_back(element);
		firstnode->next=NULL;

		head=firstnode;
		tail=firstnode;
#ifdef DEBUG
		std::cout<<"created a new head node"<<std::endl;
#endif
 }
	

//--dtor----------------------------------------------------------
~SLList(){
	std::cout<<"called dtor"<<std::endl;
	
	}



void cleanupList(){
	struct SLnode *current=NULL;
	struct SLnode *nextnode=NULL;
	if(head==NULL){ return;
		}
	else{
				current=head;		
				while(current->next!=NULL)
				{		
					nextnode=current->next;
					delete current;
					current=nextnode;
					#ifdef DEBUG
						deallocCount++;
					#endif

				}
			}
	head=NULL;
	tail=NULL;
#ifdef DEBUG
	std::cout<<"======================================="<<std::endl;
	std::cout<<"DEBUG:Deallocated ["<<deallocCount<<"] nodes"<<std::endl;
	std::cout<<"======================================="<<std::endl;
#endif



}

//---add a single element to the linked list-------------------------------
void addElement(T element){


	if(head==NULL){//no list exists -- create one!
	
					struct SLnode * newNode;
					try{
						newNode = new SLnode;
					}
					catch(std::bad_alloc* ba){
					std::cerr << " OUT OF MEMORY. Terminating execution..."<<std::endl;
					exit(1);
					}
					newNode->next=NULL;
					head=newNode;
					tail=newNode;
					newNode->nodeData.push_back(element);
					g_LISTSIZE++;

	
	
	}
	else{
		std::cout<<" list exists"<<std::endl;
					struct SLnode * newNode;
					try{
						newNode = new SLnode;
					}
					catch(std::bad_alloc* ba){
					std::cerr << " OUT OF MEMORY. Terminating execution..."<<std::endl;
					exit(1);
					}
					newNode->nodeData.push_back(element);
					newNode->next=NULL; // this is important! (might mess up the clean method otherwise)
					tail->next=newNode;
					tail=tail->next;
					g_LISTSIZE++;
	}


}



void addElement(std::vector<T> data){

	if(head==NULL){//no list exists -- create one!
	
			struct SLnode * newNode;
			try{
				newNode = new SLnode;
			}
			catch(std::bad_alloc* ba){
			std::cerr << " OUT OF MEMORY. Terminating execution..."<<std::endl;
			exit(1);
			}
			newNode->next=NULL;
			head=newNode;
			tail=newNode;
			newNode->nodeData=data;
			g_LISTSIZE++;

	
	
	}
	else{
			std::cout<<" list exists"<<std::endl;
			struct SLnode * newNode;
			try{
				newNode = new SLnode;
			}
			catch(std::bad_alloc* ba){
			std::cerr << " OUT OF MEMORY. Terminating execution..."<<std::endl;
			exit(1);
			}
			newNode->nodeData=data;
			newNode->next=NULL; // this is important! (might mess up the 'clean' method otherwise)
			tail->next=newNode;
			tail=tail->next;
			g_LISTSIZE++;
		}

}

//---insert a new element at a specific position----------------------------

void insertElement(std::vector<T> element, long position){

	if(position > g_LISTSIZE){
		cout<<"ERROR: Specified position exceeds size of list! Terminating execution..."<<std::endl;
		exit(1);

	}

	SLnode * newNode;
	try{
		newNode = new SLnode;
	}
	catch(std::bad_alloc* ba){
		std::cerr << " OUT OF MEMORY. Terminating execution..."<<std::endl;
		exit(1);
	}
	newNode->nodeData=element; 
	newNode->next=NULL;
	SLnode *temp = head;
	for(long pos=0, pos< position;pos++){
		
		temp=temp->next;
	}
	//insert node
	SLnode *prevNext= temp->next;
	temp->next = newNode;
	newNode->next=prevNext;
#ifdef DEBUG
	cout<<"======================================="<<std::endl;
	cout<<"DEBUG:Inserted new node at position=["<<position<<"] "<<std::endl;
	cout<<"Current list size is"<<g_LISTSIZE;
	cout<<"======================================="<<std::endl;
#endif
	g_LISTSIZE++;


}
//--retreive an element from a specified position-----------------------------
std::vector<T> getElement(int position){
	
	if(position > g_LISTSIZE){
			cout<<"ERROR: Specified position exceeds size of list! Terminating execution..."<<std::endl;
			exit(1);

	 }

		SLnode * newNode;
		newNode = head;
		while(pos < position){
			newNode=newNode->next;
			pos++;
		
		}
		std::vector<T> data(newNode->nodeData);
		return data;


}
	
//-----print entire list to console-----------------------------------
void printList(){
	if(head==NULL){
		std::cout<<"ERROR: No list exists!"<<std::endl;
		exit(1);
	}
	struct SLnode * newNode=head;
	long pos=1;
	while(newNode!=NULL){ //do not use a while(node->next!) type of condition!
	
		std::cout<<"Element #"<<pos<<">";
		for( std::vector<T>::iterator i = newNode->nodeData.begin(); i != newNode->nodeData.end(); i++){
			std::cout << (*i)<<",";
		}
		std::cout<<std::endl;
		pos++;
		newNode=newNode->next;

	}
std::cout<<"The list has ["<<g_LISTSIZE<<"] nodes"<<std::endl;
}

//void printList(std::string fileName);

	
};






