#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int cont;
    char data[20];
    struct node *next;
}linknode,*link;

link CreatArticle(){//分割单词，建立链表
    int i = 0,flag = 0;
    char temp;
    link h = (link)malloc(sizeof(linknode));
    h->next = NULL;
    link q = h;
    link p;
    FILE *fp = fopen("D:\\Lab6.txt","r");
    p = (link)malloc(sizeof(linknode));
    while (!feof(fp)){
        fscanf(fp,"%c",&temp);
        if ((temp>='0'&&temp<='9')||temp=='_'||(temp>='a'&&temp<='z')){
            p->data[i] = temp;
            i++;flag = 0;
        }
        else if (temp>='A'&&temp<='Z'){
            p->data[i] = temp+32;
            i++;flag = 0;
        }
        else if (!flag){
            p->data[i] = '\0';
            q->next = p;
            q = q->next;
            p = (link)malloc(sizeof(linknode));
            i = 0;flag = 1;
        }
    }
    if ((temp>='0'&&temp<='9')||temp=='_'||(temp>='a'&&temp<='z')||(temp>='A'&&temp<='Z')){
        p->data[i-1] = '\0';
        q->next = p;
        q = q->next;
        q->next = NULL;
    }
    else q->next = NULL;
    fclose(fp);
    ///////////输出
    p = h->next;
    for (p;p!=NULL;p=p->next){
        printf("%s\n",p->data);
    }
    printf("\n");
    ///////////
    free(p);
    return h;
}

link SortArticle(link head){//进行单词字典序的链表排序
    link L = (link)malloc(sizeof(linknode));//新建表头
    L->next = NULL;
    link pre = L;//q指针的前驱
    link q = L->next;
    link p;//进行链表操作
    link t = head->next;//从未排序的链表中取单词
    while (t!=NULL){//排序
        int flag = 0;
        if(L->next == NULL){//若为空表直接插入单元
            p = (link)malloc(sizeof(linknode));
            strcpy(p->data,t->data);
            p->cont = 0;
            pre->next = p;
            pre = pre->next;
            pre->next = NULL;
        }
        else{//若不为空表
            pre = L;
            q = L->next;
            p = (link)malloc(sizeof(linknode));
            strcpy(p->data,t->data);
            while (q!=NULL){//遍历链表
                if (strcmp(p->data,q->data)==0){//去除重复单词并计数
                    q->cont++;flag = 1;
                    break;
                }
                else if (strcmp(p->data,q->data)<0){//插入目标单词，做到排序
                    p->cont = 0;
                    pre->next = p;
                    pre = pre->next;
                    pre->next = q;
                    flag = 1;
                    break;
                }
                else{
                    pre = pre->next;
                    q = q->next;
                    if (q!=NULL) q->cont = 0;
                }
            }
            if (!flag){
                p->cont = 0;
                q = p;
            }
        }
        t = t->next;//查找下一个单词
    }    
    /////////////输出
    p = L->next;
    printf("\n");
    for (p;p!=NULL;p=p->next){
        printf("%s\n",p->data);
    }
    printf("\n");
    /////////////
    free(p);
    return L;
}

void FindGiggestNumber(link L){//根据出现次数进行链表排序
    link s = (link)malloc(sizeof(linknode));
    s->next = NULL;
    link pre = s;
    link q = s->next;
    link p;
    link t = L->next;
    while (t!=NULL){
        int flag = 0;
        if (s->next == NULL){
            p = (link)malloc(sizeof(linknode));
            strcpy(p->data,t->data);
            p->cont = 0;
            pre->next = p;
            pre = pre->next;
            pre->next = NULL;
        }
        else{
            pre = L;
            q = L->next;
            p = (link)malloc(sizeof(linknode));
            strcpy(p->data,t->data);
            while (q!=NULL){//遍历链表
                if (p->cont<q->cont){
                    pre->next = p;
                    pre = pre->next;
                    pre->next = q;
                    flag = 1;
                    break;
                }
                else if (p->cont==q->cont && q->next!=NULL){
                    q->next = p;
                    q->next = q->next->next;
                    flag = 1;
                    break;
                }
                else if (p->cont>q->cont){
                    pre = pre->next;
                    q = q->next;
                }
                if (!flag) q = p;
            }
        }
        t = t->next;
    }
    /////////////输出
    p = s->next;
    printf("\n");
    for (int i=0;p!=NULL&&i<10;p=p->next,i++){
        printf("%s\t%d\n",p->data,p->cont);
    }
    printf("\n");
    /////////////
    free(p);
}

void main(){
    link head = CreatArticle();
    link L = SortArticle(head);
    FindGiggestNumber(L);
    system("pause");
}