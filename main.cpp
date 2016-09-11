#include <iostream>
#include "HashTable.h"
#include "node.h"
#include "mystack.h"
#include <fstream>
#include <string.h>

using namespace std;

int main()
{
    ifstream in,com;
    ofstream out;
    char command[20];
    char input[50];
    HashTable mytable;
    com.open("commands.txt",ios::in);
    out.open("output.txt",ios::out);
    bool done=false;
    int a,b,c;
    com>>command>>input;
    in.open(input,ios::in);
    while(!in.eof())
    {
        in>>a>>b>>c;
        mytable.insertBoth(a,b,c);
    }
    while(!com.eof())
     {
         com>>command;
         if(strcmp("INSERT_LINK",command)==0)
         {
         com>>a>>b>>c;
         mytable.insertBoth(a,b,c);
         }
         else
            if(strcmp("DELETE_LINK",command)==0)
            {
            com>>a>>b;
            mytable.deleteBoth(a,b);
            }
            else
            if(strcmp("MST",command)==0)
            {
            mytable.runprim(out);
            }
            else
            if(strcmp("CN",command)==0)
            {
            com>>a>>b;
            mytable.samefriends(a,b,out);
            }
            else
            if(strcmp("SP",command)==0)
            {
            com>>a;
            mytable.dijkstra(a,out);
            }
     }

}
