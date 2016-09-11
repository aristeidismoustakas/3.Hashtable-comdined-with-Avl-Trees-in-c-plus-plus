#include "node.h"
#include <iostream>
using namespace std;

node::node(int x,int w)
{
    value=x;
    weight=w;
    left=NULL;
    right=NULL;
}

node::~node()
{
    //dtor
}

