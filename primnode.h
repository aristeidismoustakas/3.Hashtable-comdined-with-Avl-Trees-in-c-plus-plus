#include "node.h"
#ifndef PRIMNODE_H
#define PRIMNODE_H



class primnode
{
    public:
        primnode();
        virtual ~primnode();
        int thesi;
        int value;
        int color;
        int prev;
        int key;
        node *deiktisfilwn=NULL;
        int heapthesi;
    protected:
    private:
};

#endif // PRIMNODE_H
