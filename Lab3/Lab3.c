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
    if (EmptyQueue(q)) printf("the queue is already empty\n");
    else{
        p = q->front;
        q->front = p->next;
        free(p);
        return (q->front->data);
    }
}

int main(){
    char c,target;
    linkqueue *q;
    Qlink p;
    CreatQueue(q);
    while (1){
        scanf("%c",&c);
        if (c == '0'){//输入为0时出队
            printf("execution of dequeue\n");
            printf("%c\n\n",DeQueue(q));
        }
        else if (c == '\n'|| c==' ') continue;
        else if (c == '@'){//输入为@时全部出队
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
        else{//入队
            EnQueue(q,c);
        }
    }
    return 0;
}