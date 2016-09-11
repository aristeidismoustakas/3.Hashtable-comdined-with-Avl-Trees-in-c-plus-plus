#ifndef LINK_H
#define LINK_H
#include "node.h"
#include "primnode.h"



class link
{
    public:
        link();
        ~link();
        int value;
        node *filos;
        primnode *deiktisseprim;
        bool added;
    protected:
    private:
};

#endif // LINK_H
