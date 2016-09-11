#include "HashTable.h"
#include "mystack.h"
#include "link.h"
#include "primnode.h"
#include "heapNode.h"
#include "BinaryHeap.h"
#include <ctime>
#include <cstdlib>


HashTable::HashTable()
{
    size=10000;
    elements=0;
    table=new link[size];
}


HashTable::~HashTable()
{
    //dtor
}

void HashTable::insertBoth(int val1,int val2,int weight)
{
  int x,y;
  x=add(val1,table);
  y=add(val2,table);
  insertnode(table[x].filos,val2,weight);
  insertnode(table[y].filos,val1,weight);
  check();
}

void HashTable::deletetest(int i)
{ bool a=true;
    int pos;
    i++;
    while(a)
    {
        if(i==size)
        i=0;
        if(table[i].added==true)
        {
        table[i].added=false;
        pos=add(table[i].value,table);
        if(pos!=i) table[pos].filos=table[i].filos;
        elements--;
        i++;
        }
        else a=false;
    }
}
void HashTable::deleteBoth(int val1,int val2)
{
  int x,y;
  x=find(val1);
  y=find(val2);
  if((x!=-1)&&(y!=-1))
 {deletenode(table[x].filos,val2);
  deletenode(table[y].filos,val1);
  if(table[x].filos==NULL)
  {table[x].added=false;
    deletetest(x);
    elements--;}
  if(table[y].filos==NULL)
  {table[y].added=false;
  deletetest(y);
  elements--;}
  }

}

void HashTable::print()
{
    cout<<"Number of Elements: "<<elements<<" Size of array: "<<size<<" Load Factor: "<<(float)elements/size<<endl;
    for(int i=0;i<size;i++)
    {
        if(table[i].added)
        {
            cout<<"Cell "<<i<<" contains "<<table[i].value<<" Neighbours: ";
            inorder(table[i].filos);
            cout<<endl;
        }
    }
}

int HashTable::add(int value,link *hashArray)
{
  int i=hash(value);
  int j=0,a;
  bool done=false;
  if(table==hashArray)
  {
  a=find(value);
  if(a!=-1) return a;
  }
  j=i;
  while(!done)
  {
    done=!hashArray[j].added;
    if(!done)
    {
    if(j==size-1) j=0;
    else j+=1;
    }
  }
  elements+=1;
  hashArray[j].added=true;
  hashArray[j].value=value;
  return j;
}

int HashTable::check()
{
  factor=(float) elements/size;
  link *copyTable;
  int pos;
  if(factor>=0.5)
  {
   copyTable=new link[2*size];
   size=size*2;
   elements=0;
   for(int i=0;i<size/2;i++)
   {
     if(table[i].added)
     {
         pos=add(table[i].value,copyTable);
         copyTable[pos].filos=table[i].filos;
         copyTable[pos].added=true;
     }
   }
  delete [] table;
  table=copyTable;
  }
}

int HashTable::find(int value)
{
  bool done=false;
  int i=hash(value);
  int counter=0;
  while(counter<size)
  {if(table[i].added==false) return -1;
    if(table[i].value==value) return i;
    else
    {
    if(i==size-1) i=0;
    else i+=1;
    }
    counter+=1;
  }
  return -1;
}

int HashTable::hash(int value)
{
  return (2*value+19)%size;
}



void HashTable::aresame(node *a,node *b,ofstream &k)
{
    mystack A,B;
    int op1=1,op2=1;
    int x,y,en1,en2;
    bool run=true,there=false;
    en1=rightMostLeaf(a)->value;
    en2=rightMostLeaf(b)->value;
        x=getNext(A,a);
        y=getNext(B,b);
        if(x==en1) op1=2;
        if(x==en2) op2=2;
    while(run){
    if(x==y)
        {k<<x<<"   ";
        there=true;
         if(op1!=2)
            x=getNext(A,a);
            else run=false;
            if(op2!=2) y=getNext(B,b);
            else run=false;
            }
            else if(x>y)
                {
                if(op2!=2) y=getNext(B,b);
                else run=false;
                }
                else
                {
                if(op1!=2)
                x=getNext(A,a);
                else run=false;
                }
        if(x==en1) op1=2;
        if(y==en2) op2=2;
}
if(!there) k<<"none"<<endl;
}


node * HashTable::elaborofstack(mystack &astack,node *&current,int &x)
{
    node *t;

    while(current!=NULL){
            astack.push(current);
            current=current->left;
        }
    if(astack.head!=NULL)
    {astack.pop(t);
    x=t->value;
    current=t->right;
    }
    return current;

}
int HashTable::getNext(mystack &a,node *&r)
{
    int g;
    r=elaborofstack(a,r,g);
    return g;

}

void HashTable::samefriends(int a,int b,ofstream &k)
{
    int x,y;
    x=find(a);
    y=find(b);
    if(x!=-1&&y!=-1){
    k<<"Common neighbours of "<<a<<" and "<<b<<" are  ";
    aresame(table[x].filos,table[y].filos,k);
    k<<endl;}

}

bool HashTable::startprim(ofstream &k)
{
    bool yparxei=true;
    int sum=0;
    primnode *primtable;
    BinaryHeap Q(elements);
    primtable=new primnode[elements];
    int j=0;
    for(int i=0;i<size;i++)
    {
        if(table[i].added)
        {
            primtable[j].value=table[i].value;
            primtable[j].color=0;
            primtable[j].key=-1;
            primtable[j].prev=-1;
            primtable[j].thesi=j;
            primtable[j].deiktisfilwn=table[i].filos;
           table[i].deiktisseprim=&(primtable[j]);
           j++;  }
    }
    srand(time(NULL));
   int u=rand()%elements;
   primtable[u].color=1;
    primtable[u].key=0;
    Q.insert(primtable,u,0);
    primalgorithm(Q,primtable);
    for(int i=0;((i<elements)&&yparxei);i++)
    {
            sum+=primtable[i].key;
            if((primtable[i].prev==-1)&&primtable[i].key==-1)
                yparxei=false;
    }
    if(!yparxei)
        k<<"den uparxei elaxisto dentro giati o grafos einai mi sunektikos"<<endl;
    else
        k<<"to kostos tou elaxistou dentrou einai "<<sum<<endl;
    return yparxei;
}




void HashTable::primalgorithm(BinaryHeap &Q,primnode *&primtable)
{
    int a,pos,i=0;
    bool b;
    while(!Q.isempty())
    {
        a=Q.extractMin();
        elaborofprim(Q,primtable,a, primtable[a].deiktisfilwn);
    }
}

void HashTable::elaborofprim(BinaryHeap &Q,primnode *&primtable,int &a,node *&filos)
{

    int th;
    primnode *ga;
    if(filos==NULL)
    {   primtable[a].color=2;
        return;}
    th=find(filos->value);
    ga=table[th].deiktisseprim;
    if(ga->color==0)
    {
        ga->color=1;
        Q.insert(primtable,ga->thesi,filos->weight);
        ga->prev=primtable[a].value;
        ga->key=filos->weight;
    }else if(ga->color==1)
        {
            if((ga->key)>filos->weight)
            {

                (ga->key)=(filos->weight);
                ga->prev=primtable[a].value;

               Q.decreasekey(ga->heapthesi,filos->weight);
            }
        }

    elaborofprim(Q,primtable,a,filos->left);
    elaborofprim(Q,primtable,a,filos->right);

}



    void HashTable::runprim(ofstream &k)
    {
          clock_t begin = clock();
          startprim(k);
          clock_t end = clock();
          double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
          k<<"o xronos pou xreiastike gia tin euresi tou einai   "<<elapsed_secs<<"  sec "<<endl;
    }


//***********************
//DIJKSTRA'S ALGORITHM

void HashTable::print(int output[],ofstream &k,int x)
{
    cout<<"o komvos "<<x<<" apexei apo ton ";
    for(int i=0;i<size;i++)
    {
        if(table[i].added&&output[i]!=-1)
        {
            k<<"Node:"<<table[i].value<<" Cost:"<<output[i]<<" ,";
        }
    }
    cout<<endl;
}

void HashTable::InitForDijkstra(int indices[],int output[],int color[])
{
    for(int i=0;i<size;i++)
    {
        indices[i]=-1;
        output[i]=-1;
        color[i]=0;//0-Δεν τον επισκεφθήκαμε,1-τον επισκεφθήκαμε,2 για τον πρωτο κομβο
    }
}

void HashTable::inorderadd(node *root,BinaryHeap &heap,int x,int indices[],int output[],int color[])
{
    if(root==NULL) return;
    inorderadd(root->left,heap,x,indices,output,color);
    if(root!=NULL)
    {
    int temp=find(root->value);
    int temp1=find(x);

    if(color[temp]==0)
    {
    heap.insert(root->value,root->weight,temp,indices);
    output[temp]=output[temp1]+root->weight;
    color[temp]=1;
    }
    else if(color[temp]==1) heap.relax(output,indices,temp,temp1,root->weight);
    }
    inorderadd(root->right,heap,x,indices,output,color);
}

void HashTable::dijkstra(int x,ofstream &k)
{
    BinaryHeap heap(elements,size);
    int indices[size];
    int output[size];
    int color[size];
    InitForDijkstra(indices,output,color);
    int xIndex=find(x);
    output[xIndex]=0;
    color[xIndex]=2;
    inorderadd(table[xIndex].filos,heap,x,indices,output,color);
    while(!heap.isempty())
    {
    x=heap.extractMin(indices);
    xIndex=find(x);
    inorderadd(table[xIndex].filos,heap,x,indices,output,color);
    }
    print(output,k,x);
}
//***********************


//Συναρτήσεις για δένδρο

bool balanced;
int counter;//Μετρητής για να ξέρω σε ποιο επίπεδο της αναδρομής είμαι μετά την εισαγωγή


bool HashTable::insertnode(node* &root,int key,int weight)
{
    if(root==NULL){ root=new node(key,weight);
    counter=0;
    balanced=false;
    }
    else
    {
        if(root->value>key) {
        insertnode(root->left,key,weight);
        counter+=1;
        }
        else if(root->value<key) {
        insertnode(root->right,key,weight);
        counter+=1;
        }
        else if(root->value==key) return false;
         if(counter>=2&&!balanced)
        {
          balanced=testnode(root);
        }
    }

    return true;
}

node* HashTable::findnode(node *root,int key)
{
    if(root==NULL)
        return NULL;
    if(root->value==key)
        return root;
    if(root->value>key)
       return findnode(root->left,key);
    else
       return findnode(root->right,key);
}

node** nodeParent;
bool HashTable::deletenode(node * &root,int key)
{
    if(root->value==key)
        {deletenoderoot(root);
            return true;}
    if (root==NULL) return false;
    node **child,*temp,*A;
    bool left;

if(key<root->value){
    child=&(root->left);
    nodeParent=&(root);
    left=true;
}else{
    child=&(root->right);
    nodeParent=&(root);
    left=false;

}
if((*child)->value==key)
{
    if((*child)->left==NULL) temp=(*child)->right;
    else if((*child)->right==NULL) temp=(*child)->left;
    else
    if(left){
      temp=(*child)->right;
      A=leftMostLeaf(temp);
      A->left=(*child)->left;
    }
    else{
        temp=(*child)->left;
        A=rightMostLeaf(temp);
        A->right=(*child)->right;
    }
    delete (*child);
    *child=temp;
    if(*nodeParent!=NULL)
    testnode(*nodeParent);
    if(*child!=NULL)
    testnode(*child);
    return true;
}
else
{
    deletenode(*child,key);
    if(root!=NULL) testnode(root);
}
}

void HashTable::deletenoderoot(node* &root)
{
    int tempVal;
    if((root->left==NULL) && (root->right==NULL))
        {root=NULL;
        return;}
        node *temp;
        if(root->left!=NULL) temp=(rightMostLeaf(root->left));

        else
        if(root->right!=NULL) temp=(leftMostLeaf(root->right));
        if(temp!=NULL){
        {
            tempVal=temp->value;
            int temp2=root->value;
            deletenode(root,temp->value);
            findnode(root,temp2)->value=tempVal;
        }
 }
}

node* HashTable::leftMostLeaf(node *root)
{
    if(root==NULL) return NULL;
    if(root->left==NULL) return root;
    return leftMostLeaf(root->left);
}

node* HashTable::rightMostLeaf(node *root)
{
    if(root==NULL) return NULL;
    if(root->right==NULL) return root;
    return rightMostLeaf(root->right);
}

void HashTable::rightRotnode(node* &root)
{
   node *temp1,*temp2;
   temp1=root;
   temp2=root->left->right;
   root=root->left;
   root->right=temp1;
   temp1->left=temp2;
}

void HashTable::leftRotnode(node* &root)
{
    node *temp1,*temp2;
    temp1=root;
    temp2=root->right->left;
    root=root->right;
    root->left=temp1;
    temp1->right=temp2;
}

void HashTable::rightLeftRotnode(node* &root)
{
    rightRotnode(root->right);
    leftRotnode(root);
}

void HashTable::leftRightRotnode(node* &root)
{
    leftRotnode(root->left);
    rightRotnode(root);
}

int HashTable::Heightnode(node* root)
{
    int left, right;

     if(root==NULL)
         return 0;
     left = Heightnode(root->left);
     right = Heightnode(root->right);
  if(left > right)
            return left+1;
         else
            return right+1;
}

bool HashTable::testnode(node *&root)
{
        int a=Heightnode(root->left);
        int b=Heightnode(root->right);
    if(a-b==2)
    {
        if(Heightnode(root->left->left)-Heightnode(root->left->right)==-1) leftRightRotnode(root);
        else rightRotnode(root);
        return true;
        }
    else
        if(a-b==-2)
    {
        if(Heightnode(root->right->left)-Heightnode(root->right->right)==1) rightLeftRotnode(root);
        else leftRotnode(root);
        return true;
    }
    return false;

}
void HashTable::inorder(node *root)
{
if (root==NULL)
return;
inorder(root->left);
cout<<root->value<<" ";
inorder(root->right);
}
