#include "mystack.h"
#include "node.h"
#include <iostream>
using namespace std;

mystack::mystack()
{
    head=NULL;
}

mystack::~mystack()
{
    //dtor
}
int mystack::push(node *a)
{
    mynode *temp,*x;
    x=new mynode;
    x->komvos=a;
    if(head==NULL)
        {head=x;
        x->next=NULL;
        return 1;}
    temp=head;
    head=x;
    head->next=temp;
    //cout<<temp->komvos->value<<endl;
    return 1;
}
int mystack::pop(node *&a)
{
    a=head->komvos;
    mynode *temp;
    temp=head;
    head=head->next;
}
