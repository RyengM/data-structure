#include <stdio.h>
#include <stdlib.h>

typedef struct Anode{
    int tail,head;
    struct Anode *hlink,*tlink;
}arcnode;

typedef struct Vnode{
    char data;
    arcnode *fin,*fout;
}vexnode;

typedef struct node {
	int data;
	struct node *next;
}snode,*slink;

int pop(slink *top) {
	int e;
	slink p;
	if (*top == NULL) return (-1);
	else {
		e = (*top)->data;
		p = (*top);
		*top = (*top)->next;
		free(p);
		return (e);
	}
}

void push(slink *top, int e) {
	slink p;
	p = (slink)malloc(sizeof(snode));
	p->data = e;
	p->next = *top;
	*top = p;
}

void ClearStack(slink *top) {
	slink p;
	while (*top != NULL) {
		p = (*top)->next;
		pop(top);
		*top = p;
	}
	*top = NULL;
}

int EmptyStack(slink S) {
	if (S == NULL) return 1;
	else return 0;
}

char GetsTop(slink S) {
	if (S != NULL) return (S->data);
	return (0);
}

int locateVex(vexnode G[],char e,int n){
    int i = 0;
    while (G[i].data != e && i<n) i++;
    if (i>=n) printf("can't find the vexnode\n");
    else return i;
}

int CreatTeorlist(vexnode G[]){//建立十字链表
    int i=0,j,n=0;
    arcnode *p;
    char ch,u,v;
    printf("Please input the vexnodes\n");
    ch = getchar();
    while (ch!='#'){//建立顶点表
        if (ch==' ') {ch = getchar(); continue;}
        n++;
        G[i].data = ch;
        G[i].fin = G[i].fout = NULL;
        i++;
        ch = getchar();
    }
    printf("Please input the arcnodes\n");
    getchar();
    u = getchar();
    if (u==' ') u = getchar();
    v = getchar();
    if (v==' ') v = getchar();
    while (u!='#'){
        i = locateVex(G,u,n);
        j = locateVex(G,v,n);
        p = (arcnode*)malloc(sizeof(arcnode));
        p->tail = i;
        p->head = j;
        p->hlink = G[j].fin;
        G[j].fin = p;
        p->tlink = G[i].fout;
        G[i].fout = p;
        u = getchar();
        if (u==' ') u = getchar();
        v = getchar();
        if (v==' ') v = getchar();
    }
    return n;
}

void CreatId(vexnode G[],int n,int id[]){//返回定点入度
    int count,i;
    arcnode *p;
    for (i=0;i<n;i++){
        count = 0;
        p = G[i].fin;
        while (p){
            count++;
            p = p->hlink;
        }
        id[i] = count;
    }
}

void TopSort(vexnode G[],int n){//拓扑排序
    int i,j,k,count,id[50];
    arcnode *p;
    slink s = (slink)malloc(sizeof(snode));
    s->next = NULL;
    CreatId(G,n,id);
    ClearStack(&s);
    for (i=0;i<n;i++)
        if(id[i]==0)
            push(&s,i);
    count = 0;
    while (!EmptyStack(s)){
        j = pop(&s);
        printf("%c\t",G[j].data);
        count++;
        p = G[j].fout;
        while (p){
            k = p->head;
            id[k]--;
            if (id[k] == 0)
                push(&s,k);
            p = p->tlink;
        }
    }
    if (count == n) printf("\nThis graph has no cycle\n");
    else printf("\nThis graph has cycle\n");
}

int main(){
    vexnode G[50];
    int n = CreatTeorlist(G);
    TopSort(G,n);
    system("pause");
    return 0;
}