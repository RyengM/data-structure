#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bnode{
    char data[20];
    struct Bnode *Lchild,*Rchild;
}BTnode,*BTptr;

void CreatLBtree(BTptr BT,char word[][],int k){//建立排序二叉树
    BTptr p,q;
    int i = 0;
    while (k--){
        p = (BTptr)malloc(sizeof(BTndoe));
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
                    if (q->Rchlid != NULL) q = q->Rchild;
                    else {q->Rchild = p;break;}
                }
                else break;//查找到相同数据，无需插入
            }
        }
    }
}

void Inorder(BTptr T){//进行中序遍历
    BTptr p;
}

void main(){
    char word[40][20];
    BTptr BT = NULL;
    printf("Please input a sentence\n");
    int i=0,j=0;
    while(1){
        scanf("%c",&word[i][j]);
        if (word[i][j] == ' ') {i++; j=0;}
        else if (word[i][j] == '\n') break;
        else j++;
    }
    CreatLBtree(BT,word,i+1);
    system("pause");
}