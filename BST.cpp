// BST.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include<stdlib.h>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include"BST.h"
#define DEBUG

#include "stdafx.h"
using namespace std;

int main(){

	 Tree<int> *t1;
	 t1=new Tree<int>();
	 t1->addNode(10); //root
	 t1->addNode(20);
	 t1->addNode(30);
	 t1->addNode(12);
	 t1->addNode(3);
	// t1->walk(t1->Root());
	  
	 cout<<"Inorder"<<endl;
	 t1->inOrderWalk(t1->Root());
	 cout<<"preorder"<<endl;
	 t1->preOrderWalk(t1->Root());
	 cout<<"postorder"<<endl;
	 t1->postOrderWalk(t1->Root());
	
	 delete t1;
}