#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stack>
using namespace std;

typedef struct Bnode{
    char data[20];
    struct Bnode *Lchild,*Rchild;
}BTnode,*BTptr;

BTptr CreatLBtree(char word[][20],int k){//建立排序二叉树
    BTptr BT = (BTptr)malloc(sizeof(BTnode));
    BTptr p,q;
    int i = 0;
    while (k--){
        p = (BTptr)malloc(sizeof(BTnode));
        strcpy(p->data,word[i]);
        p->Lchild = p->Rchild = NULL;
        i++;
        if (i == 1) BT = p;
        else{
            q = BT;
            while (1){//进行数据插入
                if (strcmp(p->data,q->data)<0){
                    if (q->Lchild != NULL) q = q->Lchild;
                    else {q->Lchild = p;break;}
                }
                else if (strcmp(p->data,q->data)>0){
                    if (q->Rchild != NULL) q = q->Rchild;
                    else {q->Rchild = p;break;}
                }
                else break;//查找到相同数据，无需插入
            }
        }
    }
    return BT;
}

void Inorder(BTptr T){//进行中序遍历
    BTptr p = T;
    stack<BTnode*> s;
    if (T=NULL) return;
    while (p||!s.empty()){
        if (p){
            s.push(p);
            p = p->Lchild;
        }
        else{
            p = s.top();
            s.pop();
            cout<<p->data<<"  ";
            p = p->Rchild;
        }
    }
}

void freeBtree(BTptr BT){
    if (BT!=NULL){
        freeBtree(BT->Lchild);
        freeBtree(BT->Rchild);
        free(BT);
    }
}

int main(){
    char word[40][20];
    BTptr BT;
    cout<<"Please input a sentence"<<endl;;
    int i=0,j=0;
    while(1){
        word[i][j] = cin.get();
        if (word[i][j] == ' ') {word[i][j]='\0';i++; j=0;}
        else if (word[i][j] == '\n') {word[i][j] = '\0'; break;}
        else j++;
    }
    BT = CreatLBtree(word,i+1);
    Inorder(BT);
    cout<<endl;
    system("pause");
    return 0;
}