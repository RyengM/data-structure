#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char data;
    struct node *next;
}linknode,*link;

typedef struct wnode{
    char word[20];
    struct wnode *next;
}wlinknode,*wlink;

wlink SeparateArticle(link h){
    int i = 0, flag = 0;
    wlink L = (wlink)malloc(sizeof(wlinknode));
    wlink q = L;
    wlink p = (wlink)malloc(sizeof(wlinknode));
    link s = h->next;
    for (s;s->next!=NULL;s=s->next){
        if ((s->data>='0'&&s->data<='9')||(s->data>='a'&&s->data<='z')||
            (s->data>='A'&&s->data<='Z')||s->data=='_'){
                p->word[i] = s->data;
                i++;flag = 0;
            }
        else if (!flag) {
            q->next = p;
            q = q->next;
            p = (wlink)malloc(sizeof(wlinknode));
            i=0;flag = 1;
        }
    }
    if (!flag){
        q->next = p;
        q = q->next;
    }
    q->next = NULL;
    p = L->next;
    for (p;p!=NULL;p=p->next){
       for (int i=0;p->word[i]<='z'&&p->word[i]>='0';i++) printf("%c",p->word[i]);
        printf("\n");
    }
    //free(p);
    return L;
}

link CreatArticle(){
    link h = (link)malloc(sizeof(linknode));
    h->next = NULL;
    link q = h;
    link p;
    FILE *fp = fopen("D:\\Lab6.txt","r");
    while (!feof(fp)){
        p = (link)malloc(sizeof(linknode));
        fscanf(fp,"%c",&p->data);
        q->next = p;
        q = q->next;
    }
    q->next = NULL;
    fclose(fp);
    p = h->next;
    for (p;p->next!=NULL;p=p->next){
        printf("%c",p->data);
    }
    printf("\n");
    //free(p);
    return h;
}

void swap(wlink a,wlink b){//交换表中的值
    char temp[20];
    strcpy(temp,a->word);
    strcpy(a->word,b->word);
    strcpy(b->word,temp);
}

wlink Partion(wlink begin,wlink end){//单链表的快速排序
    char key[20];
    strcpy(key,begin->word);
    wlink p = begin;
    wlink q = p->next;
    wlink pre = begin;
    while (pre!=end){
        if (strcmp(q->word,key)<0){
            p = p->next;
            swap(p,q);
        }
        q = q->next;
        pre = pre->next;
    }
    swap(p,begin);
    return p;
}

void QuickSort(wlink begin,wlink end){//快排递归
    if (begin!=end){
        wlink mid = Partion(begin,end);
        if (mid != end){
            QuickSort(begin,mid);
            QuickSort(mid->next,end);
        }
        else QuickSort(begin,mid);
    }
}

void Sort(wlink A){//得到首尾指针，排序
    wlink p = A->next;
    wlink q = A->next;
    while (q->next!=NULL){
        q = q->next;
    }
    QuickSort(p,q);
}


void main(){
    link head = CreatArticle();
    wlink L = SeparateArticle(head);
    Sort(L);
    wlink q = L->next;
    for (q;q!=NULL;q=q->next){
        for (int i=0;q->word[i]<='z'&&q->word[i]>='0';i++) printf("%c",q->word[i]);
        printf("\n");
    }
    system("pause");
}