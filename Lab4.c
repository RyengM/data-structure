#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bnode{
    char data[20];
    struct Bnode *Lchild,*Rchild;
}BTnode,*BTptr;

typedef struct node {
	BTptr *next;
}*stack;

stack Pop(stack *top) {
	stack p,e;
	if (*top == NULL) return NULL;
	else {
		strcpy(e->data,(*top)->data);
		p = (*top);
		*top = (*top)->next;
		free(p);
		return e;
	}
}

void Push(stack *top, BTptr e) {
	stack p;
	p = (stack)malloc(sizeof(snode));
	strcpy(p->data,e->data);
	p->next = *top;
	*top = p;
}

void ClearStack(stack *top) {
	stack p;
	while (*top != NULL) {
		p = (*top)->next;
		Pop(top);
		*top = p;
	}
	*top = NULL;
}

int EmptyStack(stack S) {
	if (S == NULL) return 1;
	else return 0;
}

stack GetsTop(stack S) {
	if (S != NULL) return S;
	return (0);
}
void CreatLBtree(BTptr BT,char word[][20],int k){//建立排序二叉树
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
}

void visit(BTptr p){
    printf("%s\t",p->data);
}

void Inorder(BTptr T){//进行中序遍历
    BTptr p,q;
    stack s;
    ClearStack(s);
    Push(s,T);
    while (!EmptyStack(s));{
        while (p!=NULL){
            Push(s,p->Lchild);
            p = p->Lchild;
        }
        p = Pop(s);
        if (!EmptyStack(s)){
            p = Pop(s);
            visit(p);
            Push(s,p->Rchild);
        }
    }
}

void main(){
    char word[40][20];
    BTptr BT = NULL;
    printf("Please input a sentence\n");
    int i=0,j=0;
    while(1){
        scanf("%c",&word[i][j]);
        if (word[i][j] == ' ') {word[i][j]='\0';i++; j=0;}
        else if (word[i][j] == '\n') break;
        else j++;
    }
    CreatLBtree(BT,word,i+1);
    Inorder(BT);
    system("pause");
}