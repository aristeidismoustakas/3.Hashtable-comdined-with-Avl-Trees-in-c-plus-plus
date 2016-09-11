#ifndef HEAPNODE_H
#define HEAPNODE_H
#include "primnode.h"


class heapNode
{
    public:
        heapNode(); /*ctor*/
        int value;
        int weight;
        primnode *deiktis_8esis;
        int index;
        int hashTablePos;
};

#endif // HEAPNODE_H
