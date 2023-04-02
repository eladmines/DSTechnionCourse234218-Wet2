#include <iostream>
using namespace std;

/* Template Node Class */
template <class T>
class Node {
public:
    Node* left;
    T data;
    Node* right;
    int height;
};


/* Template AVL Tree Class */  
template <class T>
class AVLTree{
public:
    Node<T>* root;
    AVLTree(){ root = NULL; }
    int NodeHeight(Node<T>* p){
    int leftHeight;
    int rightHeight;
    if(p!=NULL && p->left!=NULL){
        leftHeight = p->left->height;
    }
    else{
        leftHeight=0;
    }

    if(p!=NULL && p->right!=NULL){
        rightHeight = p->right->height;
    }
    else{
        rightHeight=0;
    }
    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }
    else{
         return rightHeight + 1;
    }
}

/*Getting the maximum node of an AVL Tree*/
Node<T>* getMax(Node<T>* p)
{   
        Node<T> *temp = p;
        while(temp->right!=NULL){
            temp=temp->right;
        }
        return temp;        
}

/*Calculating the node's BF*/
int BalanceFactor(Node<T>* p){
    int leftHeight;
    int rightHeight;
    if(p!=NULL && p->left!=NULL)
    {
        leftHeight = p->left->height;
    }
    else{
        leftHeight=0;
    }

    if(p!=NULL && p->right!=NULL)
    {
        rightHeight = p->right->height;
    }
    else{
       rightHeight=0;
    }
    return leftHeight - rightHeight;
}

/*Getting a root of an avl tree (or subtree) and find the appropriate element*/
Node<T>* findNode(Node<T>* p,T data){
    Node<T>* temp=p;
    
    while(temp!=NULL){
        if(*(temp->data) == *(data))
        {
            return temp;
        }
       
        else if(*(temp->data) > *(data)){
        
        temp=temp->left;
        }

        else if(*(temp->data) < *(data)){
            temp=temp->right;
        }
    }

    return NULL;
}

    Node<T>* LLRotation(Node<T>* p){
    Node<T>* pl = p->left;
    Node<T>* plr = pl->right;
 
    pl->right = p;
    p->left = plr;
    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);
    if (root == p){
        root = pl;
    }
    return pl;
}

Node<T>* RRRotation(Node<T>* p){
    Node<T>* pr = p->right;
    Node<T>* prl = pr->left;
 
    pr->left = p;
    p->right = prl;
 

    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);

    if (root == p){
        root = pr;
    }
    return pr;
}

Node<T>* LRRotation(Node<T>* p){
    Node<T>* pl = p->left;
    Node<T>* plr = pl->right;
 
    pl->right = plr->left;
    p->left = plr->right;
 
    plr->left = pl;
    plr->right = p;
 

    pl->height = NodeHeight(pl);
    p->height = NodeHeight(p);
    plr->height = NodeHeight(plr);
 

    if (p == root){
        root = plr;
    }
    return plr;
}

Node<T>* RLRotation(Node<T>* p){
    Node<T>* pr = p->right;
    Node<T>* prl = pr->left;
 
    pr->left = prl->right;
    p->right = prl->left;
 
    prl->right = pr;
    prl->left = p;

    pr->height = NodeHeight(pr);
    p->height = NodeHeight(p);
    prl->height = NodeHeight(prl);
 

    if (root == p){
        root = prl;
    }
    return prl;
}
 

Node<T>* GetPredecessor(Node<T>* p){
    while (p && p->right != NULL){
        p = p->right;
    }
    return p;
}

Node<T>* GetSuccessor(Node<T>* p){
    while (p && p->left != NULL){
        p = p->left;
    }
    return p;
}
 
    
Node<T>* insert(Node<T>* p, T key){
    Node<T>* t;
    if (p == NULL){
        t = new Node<T>;
        t->data = key;
        t->left = NULL;
        t->right = NULL;
        t->height = 1;  
        return t;
    }
 
    if (*(key) < *(p->data)){
        p->left = insert(p->left, key);
    } else if (*(key) > *(p->data)){
        p->right = insert(p->right, key);
    }
 

    p->height = NodeHeight(p);
 

    if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 1) 
    {
        return LLRotation(p);
    } 
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == -1)
    {
        return LRRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == -1)
    {
        return RRRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == 1)
    {
        return RLRotation(p);
    }
 
    return p;
}
 

void Inorder(Node<T>* p) {
    if (p!= NULL){
        Inorder(p->left);
        cout << *(p->data) << ", " << flush;
        Inorder(p->right);
    }
}

int treeSize(Node<T>* p)
{
    if (p == NULL)
        return 0;
    else
        return(treeSize(p->left) + 1 + treeSize(p->right));
}

Node<T>** ReverseInOrder(Node<T>* root) {
    if (root== NULL){
       return NULL;
    }
    Node<T>* current = root;
    int size = treeSize(current);
    current = root;
    Node<T>** ptr = new Node<T>*[size];
    int i=0;
    while(current!=NULL){
        if(current->right == NULL){
            ptr[i]=current;
            current = current->left;
            i++;
        }
        else{
            Node<T>* pre = current->right;
            while(pre->left!=NULL && pre->left!=current){
                pre = pre->left;
            }

            if(pre->left == NULL){
                pre->left = current;
                current = current ->right;
                
            }

            else{
                pre->left = NULL;
                ptr[i]=current;
                current = current ->left;
                i++;
            }
        }
    }
    
    
    return ptr;
}


Node<T>** InOrderTreeToArray(Node<T>* root1) {
    if (root1== NULL){
       return NULL;
    }
    Node<T>* current1 = root1;
    int size1 = treeSize(current1);
    current1= root1;
    Node<T>** arr1 = new Node<T>*[size1];
    int i=0;
    while(current1!=NULL){
        if(current1->left == NULL){
            arr1[i]=current1;
            current1 = current1->right;
            i++;
        }
        else{
            Node<T>* pre = current1->left;
            while(pre->right!=NULL && pre->right!=current1){
                pre = pre->right;
            }

            if(pre->right == NULL){
                pre->right = current1;
                current1 = current1 ->left;
                
            }

            else{
                pre->right = NULL;
                arr1[i]=current1;
                current1 = current1 ->right;
                i++;
            }
        }
    }
    return arr1;
}


void Inorder(){ Inorder(root); }


Node<T>* getRoot(){ return root; }

Node<T>* remove(Node<T>* p, T key){
    if (p == NULL){
        return NULL;
    }
 
    if (p->left == NULL && p->right == NULL){
        if (p == root){
            root = NULL;
        }
        delete p;
        return NULL;
    }
 
    if (*(key) < *(p->data)){
        p->left = remove(p->left, key);
    } else if (*(key) > *(p->data)){
        p->right = remove(p->right, key);
    } else {
        Node<T>* q;
        if (NodeHeight(p->left) > NodeHeight(p->right)){
            q = GetPredecessor(p->left);
            p->data = q->data;
            p->left = remove(p->left, q->data);
        } else {
            q = GetSuccessor(p->right);
            p->data = q->data;
            p->right = remove(p->right, q->data);
        }
    }
 
 
    p->height = NodeHeight(p);
 
 //When to execute each Rotation Function   
    if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 1) { 
        return LLRotation(p);
    } 
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == -1)
    {  
        return LRRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == -1)
    { 
        return RRRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == 1)
    { 
        return RLRotation(p);
    } 
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 0)
    { 
        return LLRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == 0)
    { 
        return RRRotation(p);
    }
 
    return p;
}

/*Getting two avl tress and return a new avl tree*/
Node<T>** mergeArrays(Node<T>** arr1,Node<T>** arr2){
    int size1 = treeSize(arr1);
    int size2 = treeSize(arr2);
    int p=0,q=0,k=0;
    Node<T>** arr3 = new Node<T>*[size1+size2];
    
    while ( p < size1 && q < size2) {
            if ((*(arr1[p])->data)< (*(arr2[q])->data)) {
                arr3[k] = arr1[p];
                k++;p++;

            } else {
                
                arr3[k]= (arr2[q]);    
                k++;
                q++;
            }  
        
        }
        while ( p < size1) {
            arr3[k] = arr1[p];
            k++;
            p++;
        }
        while ( q < size2) {
            arr3[k] = arr2[q]; 
            k++;
            q++;
        }

       return arr3;
}

Node<T>* sortedArrayToAvl(Node<T>** arr,int s, int e)
{
    if (s > e)
    return NULL;
    int mid = (s + e)/2;
    Node<T>* root = new Node<T>;
    root->data = arr[mid]->data;
    root->left = sortedArrayToAvl(arr, s,mid - 1);                                 
    root->right = sortedArrayToAvl(arr, mid + 1, e);
    return root;
}

Node<T>* mergeAVL(Node<T>* root1, Node<T>* root2)
{
    int sizeAVL1 = treeSize(root1);
    int sizeAVL2 = treeSize(root2);
    Node<T>** arr1 = InOrderTreeToArray(root1);
    Node<T>** arr2 = InOrderTreeToArray(root2);
    Node<T>** arr3 = mergeArrays(arr1,arr2,sizeAVL1,sizeAVL2);
    Node<T>* newRoot =sortedArrayToAvl(arr3,0,sizeAVL1+sizeAVL2-1);
    return newRoot;
}
};

#endif