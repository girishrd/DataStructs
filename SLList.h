/*===================================================================
Author: Girish D.
Desc: A singly linked list implementation 
Last revision:Aug-2013
Notes:  

List of methods:
---------------
cleanupList();
addElement(std::vector<T> data);
addElement(T element)
insertElement(std::vector<T> element, long position)
getElement(int position)
deleteElement(long position)
printList(std::string fileName)
printList()

Unit test stub included:
-----------------------
No
=====================================================================*/
#include<stdlib.h>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#define DEBUG

//global- to keep track of the list size
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

	SLList(){
		head=NULL;
		tail=NULL;	

	}
	SLList(T element){
		struct SLnode * firstnode= new struct SLnode;
		firstnode->nodeData.push_back(element);
		firstnode->next=NULL;
		head=firstnode;
		tail=firstnode;
#ifdef DEBUG
		std::cout<<"created a new head node"<<std::endl;
#endif
 }
~SLList(){}
//method to clean up-------------------------------------------------
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

//method to add an element to the list( adds it to the tail)-------------------------------------------------
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

//insert a new element (at a specified position) 0-index----------------------------

void insertElement(std::vector<T> element, long position){
	if(position > g_LISTSIZE){
		std::cout<<"ERROR: Specified position exceeds size of list! Terminating execution..."<<std::endl;
		exit(1);

	}
	SLnode * newNode;
	try{
		newNode = new SLnode;
	}
	catch(std::bad_alloc* ba){
		std::cout << " OUT OF MEMORY. Terminating execution..."<<std::endl;
		exit(1);
	}
	newNode->nodeData=element; 
	newNode->next=NULL;
	SLnode *temp = head;
	for(long pos=1; pos< position;pos++){
		
		temp=temp->next;
	}
	//insert node
	SLnode *prevNext= temp->next;
	temp->next = newNode;
	newNode->next=prevNext;
#ifdef DEBUG
	std::cout<<"======================================="<<std::endl;
	std::cout<<"DEBUG:Inserted new node at position=["<<position<<"] "<<std::endl;
	std::cout<<"Current list size is"<<g_LISTSIZE+1;
	std::cout<<"======================================="<<std::endl;
#endif
	g_LISTSIZE++;
}

//delete the tail element
void deleteElement(){

	struct SLnode * newNode=head;
	long pos=0;
#ifdef DEBUG
	std::cout<<"the list size is"<<(g_LISTSIZE+1)<<std::endl;
#endif
	while(pos < (g_LISTSIZE-1)){
		newNode=newNode->next;
		pos++;
		}

	std::cout<<"deleting..["<<pos+1<<"]th node"<<std::endl;
		for( std::vector<T>::iterator i = newNode->nodeData.begin(); i != newNode->nodeData.end(); i++){
			std::cout << (*i)<<",";
		
	}	
	newNode->next=NULL;
	delete tail;
	tail =newNode;
	g_LISTSIZE--;
}
//delete an element at a specific position
void deleteElement(long position){

	struct SLnode * newNode=head;
	struct SLnode * newNextnode;
	long pos=1;
#ifdef DEBUG
	std::cout<<"the list size is"<<(g_LISTSIZE+1)<<std::endl;
#endif

	if(head==NULL){
		std::cout<<"No list exists! Exiting..."<<std::endl;
		return;
	}
	if(position > g_LISTSIZE){
		std::cout<<"ERROR: Invalid position specified..."<<std::endl;
		return;
	}
	//delete the specified node
	while(pos < (position-1)){
		newNode=newNode->next;
		pos++;
		}
#ifdef DEBUG
	std::cout<<"deleting node number ["<<position<<"]"<<std::endl;

		for( std::vector<T>::iterator i = newNode->nodeData.begin(); i != newNode->nodeData.end(); i++){
			std::cout << (*i)<<",";
	}
#endif	
	if(newNode->next!=NULL)
	{
		newNextnode=newNode->next;
		newNode->next=newNextnode->next;
		delete newNextnode;
		g_LISTSIZE--;
	
	}
	else{//get rid of the tail
			deleteElement();
	}
			
}


//Retreive an element from a specified position-----------------------------
std::vector<T> getElement(int position){
	if(position > g_LISTSIZE){
			std::cout<<"ERROR: Specified position exceeds size of list! Terminating execution..."<<std::endl;
			exit(1);

	 }
	long pos=1;
	struct SLnode * newNode;
	newNode = head;
	while(pos < position){
		newNode=newNode->next;
		pos++;
		
		}
#ifdef DEBUG
		std::cout<<"Found Element #"<<pos<<">";
		for( std::vector<T>::iterator i = newNode->nodeData.begin(); i != newNode->nodeData.end(); i++){
			std::cout << (*i)<<",";
		}
		std::cout<<std::endl;
#endif
		std::vector<T> data(newNode->nodeData);
		return data;

}
	
//Print entire list to console-----------------------------------
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
std::cout<<"The list has ["<<g_LISTSIZE+1<<"] nodes"<<std::endl;
}


long sizeOFList(){
return g_LISTSIZE;

}

void printList(std::string fileName){
	
	if(head==NULL){
		std::cout<<"ERROR: No list exists!"<<std::endl;
		exit(1);
	}
	std::ofstream DATAFILE;
	DATAFILE.open(fileName);
	if(!DATAFILE.is_open()){
	
		std::cout<<"ERROR: unable to open file. Exiting...";
		exit(1);
	}
	struct SLnode * newNode=head;
	long pos=1;
	while(newNode!=NULL){ //do not use a while(node->next!) type of condition!
			for( std::vector<T>::iterator i = newNode->nodeData.begin(); i != newNode->nodeData.end(); i++){
			DATAFILE << (*i)<<",";
		}
		DATAFILE<<std::endl;
		newNode=newNode->next;
	}
}
	
};//class definition ends here






