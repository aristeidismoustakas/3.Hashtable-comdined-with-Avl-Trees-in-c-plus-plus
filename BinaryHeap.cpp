#include "BinaryHeap.h"
#include "heapNode.h"
#include <iostream>
#include "primnode.h"

using namespace std;

BinaryHeap::BinaryHeap(int value)
{
    array=new heapNode[value];
    for(int i=0;i<value;i++)
    {
        array[i].value=-1;
        array[i].weight=-1;
    }
    elements=0;
    size=value;
}

BinaryHeap::BinaryHeap(int value,int hts)
{
    array=new heapNode[value];
    for(int i=0;i<value;i++)
    {
        array[i].value=-1;
        array[i].weight=-1;
    }
    elements=0;
    size=value;
    hashTableSize=hts;
}


BinaryHeap::~BinaryHeap()
{
    //dtor
}

int BinaryHeap::leftChild(int index)
{
    int temp=index*2+1;
    if(temp<=size-1&&elements>temp)
    {
        //<<"Elements: "<<elements<<" Temp: "<<temp<<endl;
        return temp;
    }
    else return -1;
}

int BinaryHeap::rightChild(int index)
{
    int temp=index*2+2;
    if(temp<=size-1&&elements>temp) return temp;
    else return -1;
}

void BinaryHeap::makeHeap()
{
    for(int i=(size/2)-1;i>=0;i--)
    {
        Heapify(i);
    }
}

int BinaryHeap::extractMin()
{
    int asa;
    if(elements>0)
    {
    int asa;
    asa=array[0].value;
    array[0]=array[elements-1];
    array[elements-1].weight=-1;
    array[elements-1].value=-1;
    elements-=1;
    Heapify(0);
    return asa;
    }
    return -1;
}


int BinaryHeap::insert(primnode *&primtable,int value,int weight)
{
    int parent;
    int heaptest;
    int index;
    if(elements<=size-1)
    {
        array[elements].value=value;
        array[elements].weight=weight;
        array[elements].deiktis_8esis=&(primtable[value]);
        array[elements].deiktis_8esis->heapthesi=elements;
        if(elements%2==1) parent=(elements-1)/2;
        else parent=(elements-2)/2;
        elements+=1;
        if(parent>=0) heaptest=Heapify(parent);
        if(heaptest!=-1) index=heaptest;
        while(heaptest!=-1)
        {
            if(parent%2==1) parent=(parent-1)/2;
            else parent=(parent-2)/2;
            if(parent>=0)
            {
            heaptest=Heapify(parent);
            if(heaptest!=-1)index=heaptest;
            }
            else {heaptest=-1;}
        }
        return index;
    }
}

int BinaryHeap::Heapify(int index)
{
    int i,j;
    int smallest;
    heapNode temp;
    i=leftChild(index);
    j=rightChild(index);
    smallest=index;
    if(i!=-1)
    {
        if(array[index].weight>array[i].weight) smallest=i;
    }
    if(j!=-1) if(array[j].weight<array[smallest].weight) smallest=j;

    if(smallest!=index)
    {
        temp=array[index];
        array[index]=array[smallest];
        array[index].deiktis_8esis->heapthesi=index;
        array[smallest]=temp;
        array[smallest].deiktis_8esis->heapthesi=smallest;
        Heapify(smallest);

        return smallest;
    }
    else return -1;
}

bool BinaryHeap::isempty()
{
    if(elements==0)
        return true;
    return false;
}

void BinaryHeap::decreasekey(int thesi,int newweight)
{
    int index,heaptest,parent;
    array[thesi].weight=newweight;
    if(thesi%2==1) parent=(thesi-1)/2;
        else parent=(thesi-2)/2;
        if(parent>=0) heaptest=Heapify(parent);
        if(heaptest!=-1) index=heaptest;
        while(heaptest!=-1)
        {
            if(parent%2==1) parent=(parent-1)/2;
            else parent=(parent-2)/2;
            if(parent>=0)
            {
            heaptest=Heapify(parent);
            if(heaptest!=-1)index=heaptest;
            }
            else heaptest=-1;
        }
}


//******Dijkstra******
int BinaryHeap::extractMin(int indices[])
{
    if(elements>0)
    {
    int temp;
    temp=array[0].value;
    array[0]=array[elements-1];
    array[elements-1].weight=-1;
    array[elements-1].value=-1;
    array[elements-1].index=-1;
    elements-=1;
    Heapify(0,indices);
    return temp;
    }
}


int BinaryHeap::insert(int value,int weight,int htp,int indices[])
{
    int parent;
    int heaptest;
    int index;
    if(elements<=size-1)
    {
        array[elements].value=value;
        array[elements].weight=weight;
        array[elements].index=elements;
        array[elements].hashTablePos=htp;
        indices[htp]=elements;
        if(elements%2==1) parent=(elements-1)/2;
        else parent=(elements-2)/2;
        elements+=1;
        if(parent>=0) heaptest=Heapify(parent,indices);
        if(heaptest!=-1) index=heaptest;
        while(heaptest!=-1)
        {
            if(parent%2==1) parent=(parent-1)/2;
            else parent=(parent-2)/2;
            if(parent>=0)
            {
            heaptest=Heapify(parent,indices);
            if(heaptest!=-1)index=heaptest;
            }
            else heaptest=-1;
        }
        return index;
    }
}

int BinaryHeap::Heapify(int index,int indices[])
{
    int i,j;
    int smallest;
    heapNode temp;
    int indexTemp;
    i=leftChild(index);
    j=rightChild(index);
    smallest=index;
    if(i!=-1)
    {
        if(array[index].weight>array[i].weight||array[index].weight==-1) smallest=i;
        if(array[i].weight==-1) smallest=index;
    }
    if(j!=-1)
    {
        if(array[j].weight<array[smallest].weight&&array[j].weight!=-1) smallest=j;
        if(array[smallest].weight==-1) smallest=j;
    }
    if(smallest!=index)
    {
        temp=array[index];
        array[index]=array[smallest];
        array[smallest]=temp;
        indexTemp=array[index].index;
        array[index].index=array[smallest].index;
        array[smallest].index=indexTemp;
        updateIndices(array[smallest].index,array[index].index,array[smallest].hashTablePos,array[index].hashTablePos,indices);
        Heapify(smallest,indices);
        return smallest;
    }
    else return -1;
}

void BinaryHeap::updateIndices(int index1,int index2,int pos1,int pos2,int indices[])
{
       indices[pos1]=index1;
       indices[pos2]=index2;
}

void BinaryHeap::relax(int output[],int indices[],int temp,int cur,int weight)
{
  if(output[temp]>output[cur]+weight)
  {
  int parent,heaptest;
  array[indices[temp]].weight=output[cur]+weight;
  output[temp]=output[cur]+weight;
  if(indices[temp]%2==1) parent=(indices[temp]-1)/2;
        else parent=(indices[temp]-2)/2;
        if(parent>=0)
        {
            heaptest=Heapify(parent,indices);
        }
        while(heaptest!=-1)
        {
            if(parent%2==1) parent=(parent-1)/2;
            else parent=(parent-2)/2;
            if(parent>=0)
            {
            heaptest=Heapify(parent,indices);
            }
            else heaptest=-1;
        }

  }
}

