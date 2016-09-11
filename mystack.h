#ifndef MYSTACK_H
#define MYSTACK_H
#include "node.h"


class mystack
{
    public:
        mystack();
        virtual ~mystack();
        struct mynode
        {
            node *komvos;
            mynode *next;
        };
        mynode *head;
        int push(node *);
        int pop(node *&);
    protected:
    private:
};

#endif // MYSTACK_H
