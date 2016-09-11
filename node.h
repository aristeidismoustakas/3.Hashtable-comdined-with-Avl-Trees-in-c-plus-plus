#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>

using namespace std;

class node
{
    public:
        node(int x,int w);
        ~node();

        node *left;
        node *right;
        int weight;
        int value;

};

#endif // NODE_H
