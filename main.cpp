#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#define NIL -100
 class Node{
public:
    int value;
    Node* left= nullptr;
    Node* right= nullptr;
    explicit Node(int n) {
        this->value=n;
    }
};
 void swap(Node &n1, Node &n2){
    int temp=n1.value;
    n1.value=n2.value;
    n2.value=temp;
}//swapping of values of 2 nodes
 void PrintWhiteSpace(int x){
     while(x>0){
         std::cout<<" ";
         x--;
     }
 }
 class SNode{
 public:
     Node* SVal;
     SNode *next;
     explicit SNode(Node &x){
         SVal=&x;
         next=nullptr;
     }
 };
 class Queue{
 public:
     SNode* head;
     explicit Queue(Node &k){
         SNode *New= new SNode(k);
         head=New;
         head->next= nullptr;
     }
     void Add(Node &k) const{
         SNode* Next= new SNode(k);
         SNode* ptr=head;
         while(ptr->next!= nullptr){
             ptr=ptr->next;
         }
         ptr->next=Next;
     }
     int pop(){
         int ans=head->SVal->value;
         head=head->next;
         return ans;
     }
     Node* value() const{
         return head->SVal;
     }
 };
 class BST{
public:
    Node *root;
    explicit BST(Node* n){
        root=n;
    }
    void Insert(Node *TempRoot,Node *n){
        Node *ptr=TempRoot;
        if(ptr->value < n->value){
            if(ptr->right!= nullptr){
                Insert(ptr->right,n);
            }
            else{
                ptr->right=n;
            }
        }
        else if(ptr->value > n->value){
            if(ptr->left!= nullptr){
                Insert(ptr->left,n);
            }
            else{
                ptr->left=n;

            }
        }
        else{
            std::cout<<"Value is already inserted\n";
        }
    }
    static void BFS(Queue &queue, std::vector<int> &x) {
        Node *nil= new Node(NIL);
            while(true) {
                queue.value()->left != nullptr ?
                queue.Add(*queue.value()->left) : queue.Add(*nil);
                queue.value()->right != nullptr ?
                queue.Add(*queue.value()->right) : queue.Add(*nil);

                x.push_back(queue.pop());

                if(queue.head->SVal == nil){
                    //delete nil;
                    break;}
            }
    }
    Node *FindParent(Node *TempRoot, int n) {

        Node *ptr = TempRoot;
        if (ptr->left->value == n||ptr->right->value ==n) {
            return ptr;
        }
        else if (ptr->value < n) {
            FindParent(ptr->right, n);
        } else if (ptr->value > n) {
            FindParent(ptr->left, n);
        }
        return nullptr;
    }
    static bool IsLeaf(Node *n){
        if(n->left!= nullptr && n->right != nullptr){
            return false;
        }
        else{return true;}
    }
    Node* FindLastLeaf(Node* N){
        Node* r=N;
        if(r->right==nullptr || r->left== nullptr){
            return r;
        }
        else{
            r = FindLastLeaf(r->right);
        }
        return r;
    }
    void Delete(int i){

        Node *PDnode= FindParent(root,i);
        if(PDnode== nullptr){
            std::cout<<"Not present\n";
        }
        else if(PDnode->left->value==i){
            if(IsLeaf(PDnode->left)){
                 if(PDnode->left->left!=nullptr){
                     PDnode->left=PDnode->left->left;
                 }
                 else{
                     PDnode->left=PDnode->left->right;
                 }
            }//1st category
            else{
                Node *sNode=FindLastLeaf(PDnode->left->left);
                swap(*sNode,*PDnode->left);
                Delete(sNode->value);
            }//2nd category
        }
        else if(PDnode->right->value==i){
            if(IsLeaf(PDnode->right)){
                if(PDnode->right->left != nullptr){
                    PDnode->right=PDnode->right->left;
                }
                else{
                    PDnode->right=PDnode->right->right;
                }
            }//1st category
            else{
                Node *sNode=FindLastLeaf(PDnode->right->left);
                swap(*sNode,*PDnode->right);
                Delete(sNode->value);
            }//2nd category
        }
    }
    void Display() const{
        std::vector<int> arr;
        Queue queue(*root);
        BFS(queue, arr);
        int height= (int)ceil(log2((double)(arr.size()+1)));
        int i=0;
        int j=0;
        while(i<height){
            int TotalSpaces =arr.size();
            int currentSpace=(TotalSpaces-1-(i*2))/(int)pow((double)2,(double)(i+1));//this is correct
            PrintWhiteSpace(currentSpace);
            int Temp=((int)pow((double)2,(double)i))-1;
            if(arr[j]!=0)  {std::cout<<arr[j] ;}
            else{
                std::cout<<'X';
            }
            j++;
            while (Temp>0){
                PrintWhiteSpace(currentSpace);
                std::cout<<" ";
                PrintWhiteSpace(currentSpace);
                if(arr[j]!=0){
                    std::cout<<arr[j];
                }
                else{
                    std::cout<<'X';
                }
                j++;
                Temp--;
            }
            PrintWhiteSpace(currentSpace);

            std::cout<<"\n"<<std::endl;
            i++;
        }
    }
};
int main() {
    std::cout << "Enter the number of value: ";
    int val;
    std::string s;
    std::cin>> val;
    Node node(val);
    BST tree(&node);

    while(getline(std::cin,s)&& !s.empty()){
        int temp;
        std::stringstream ss(s);
        while(ss>>temp) {
            Node *node1 = new Node(temp);
            tree.Insert(&node, node1);
        }
    }
    std::cout<< "What do you want to do? \n";
    while (true) {
        std::cout << "\n1. Insert"
                     "\n2. Delete"
                     "\n3. Display\n else enter any other number to exit\n";
        int Ans;
        std::cin>>Ans;
        if (Ans == 1) {
            std::cout << "what do you want to insert:\t";
            std::cin.get();
            while(getline(std::cin,s)&& !s.empty()){
                int temp;
                std::stringstream ss(s);
                while(ss>>temp) {
                    Node *node1 = new Node(temp);
                    tree.Insert(&node, node1);
                }
            }//inserting all the values
        } else if (Ans == 2) {
            std::cout << "What do you want to delete:\t";
            std::cin.get();
            while(getline(std::cin,s)&& !s.empty()){
                int temp;
                std::stringstream ss(s);
                while(ss>>temp) {
                    tree.Delete(temp);
                }
            }//Deleting a particular value
        } else if (Ans == 3) {
            tree.Display();
        } else {
            break;
        }
    }
    std::cout<<"\nThank you!!";

    return 0;
}