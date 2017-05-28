#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char data;
    struct node *next;
}Qnode,*Qlink;

typedef struct{
    Qnode *front,*rear;
}linkqueue;

void CreatQueue(linkqueue *q){
    q->front = (Qlink)malloc(sizeof(Qnode));
    q->front->next = NULL;
    q->rear = q->front;
}

int EmptyQueue(linkqueue *q){
    if (q->front == q->rear) return (1);
    else return (0);
}

void ClearQueue(linkqueue *q){
    Qlink p,r;
    q->rear = q->front;
    p = q->front->next;
    q->front->next = NULL;
    while (p != NULL){
        r = p;
        p = p->next;
        free(r);
    }
}

void EnQueue(linkqueue *q,char e){
    Qlink p;
    p = (Qlink)malloc(sizeof(Qnode));
    p->data = e;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
}

char DeQueue(linkqueue *q){
    Qlink p;
    if (q->front == q->rear) return 0;
    else{
        p = q->front;
        q->front = p->next;
        free(p);
        return (q->front->data);
    }
}

void main(){
    char c,target;
    linkqueue *q;
    Qlink p;
    CreatQueue(q);
    while (1){
        scanf("%c",&c);
        if (c == '0'){//输入为0时栈顶出栈
            printf("execution of dequeue\n");
            printf("%c\n\n",DeQueue(q));
        }
        else if (c == '\n'|| c==' ') continue;
        else if (c == '@'){//输入为@时全部出栈
            printf("execution of dequeue\n");
            p = q->front->next;
            while (p != NULL){
                printf("%c\t",DeQueue(q));
                q->front = p;
                p = p->next;
            }
            printf("\n\n");
            ClearQueue(q);
        }
        else{//入栈
            EnQueue(q,c);
        }
    }
}