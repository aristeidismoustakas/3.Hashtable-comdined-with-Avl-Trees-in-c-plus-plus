#ifndef BINARYHEAP_H
#define BINARYHEAP_H
#include "heapNode.h"


class BinaryHeap
{
    public:
        BinaryHeap(int value);
        BinaryHeap(int value,int hts);
        ~BinaryHeap();
        int insert(primnode *&,int value,int weight);
        int extractMin();
        int leftChild(int index);
        int rightChild(int index);
        void makeHeap();
        int Heapify(int index);
        bool isempty();
        void decreasekey(int,int);
        //******Dijstra******
        int insert(int value,int weight,int htp,int indices[]);
        int extractMin(int indices[]);
        int Heapify(int index,int indices[]);
        void updateIndices(int index1,int index2,int pos1,int pos2,int indices[]);
        void relax(int output[],int indices[],int temp,int cur,int weight);



    protected:
    private:
        heapNode *array;
        int size;
        int elements;
        int hashTableSize;
};

#endif // BINARYHEAP_H
