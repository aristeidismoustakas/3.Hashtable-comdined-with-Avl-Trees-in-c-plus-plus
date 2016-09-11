#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "link.h"
#include "mystack.h"
#include "primnode.h"
#include "heapNode.h"
#include "BinaryHeap.h"

class HashTable
{
    public:
        HashTable();
        ~HashTable();
    bool insertnode(node* &root,int key,int weight);//Εισαγωγή
    node* findnode(node *,int );//Αναζήτηση
    bool deletenode(node *&,int);//Διαγραφή κόμβου
    void deletenoderoot(node* &);//Διαγραφή ρίζας
    node *leftMostLeaf(node *root);//αριστερά φύλλο
    node *rightMostLeaf(node *root);//δεξιά φύλλο
    void rightRotnode(node* &);//Right rotation για node
    void leftRotnode(node* &);//Left rotation για node
    void rightLeftRotnode(node* &);//Right left rotation για node
    void leftRightRotnode(node* &);//Left right rotation για node
    int Heightnode(node* root);//Ύψος για node
    bool testnode(node* &root);//Έλεγχος αν το δένδρο είναι ισορροπημένο
    int add(int value,link *table);
    int find(int value);
    int hash(int value);
    int check();
    void ektupwsi(int i);
    bool startprim(ofstream &);
    void primalgorithm(BinaryHeap &,primnode *&);
    void elaborofprim(BinaryHeap &,primnode *&,int &,node *&);
    void runprim(ofstream &);
    void insertBoth(int val1,int val2,int weight);
    void deleteBoth(int val1,int val2);
    void deletetest(int i);
    void print();
    void inorder(node *root);
    void aresame(node *,node *,ofstream &k);
    node * elaborofstack(mystack &, node *&,int &);
    int getNext(mystack &,node *&);
    void samefriends(int,int,ofstream &);
    //******Dijkstra******
    void dijkstra(int startPoint,ofstream &);
    void InitForDijkstra(int indices[],int output[],int color[]);
    void inorderadd(node *root,BinaryHeap &heap,int x,int indices[],int output[],int color[]);
    //void print(int indices[],int output[]);
    void print(int output[],ofstream &k,int x);

    link *table;

    protected:
    private:
    int size;
    int elements;
    double factor;



    //Συναρτήσεις για δένδρο




};

#endif // HASHTABLE_H
