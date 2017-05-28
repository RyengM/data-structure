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
    char filename[100];
    link h = (link)malloc(sizeof(linknode));
    h->next = NULL;
    link q = h;
    link p;
    FILE *fp;
    printf("Please input the path of the filename\n");
    while (1){
        gets(filename);
        if ((fp=fopen(filename,"r"))==NULL){
            printf("Can't find the file,please input again\n");
        }
        else break;
    }
    
    //FILE *fp = fopen("D:\\Lab6.txt","r");
    p = (link)malloc(sizeof(linknode));
    while (!feof(fp)){//未读到文章结尾则继续循环，将单词进行分割并存入链表
        fscanf(fp,"%c",&temp);
        if ((temp>='0'&&temp<='9')||temp=='_'||(temp>='a'&&temp<='z')){
            p->data[i] = temp;
            i++;flag = 0;
        }
        else if (temp>='A'&&temp<='Z'){
            p->data[i] = temp+32;
            i++;flag = 0;
        }
        else if (!flag){//读取到第一个非指定字符
            p->data[i] = '\0';//\0作为字符串结束的标志
            q->next = p;
            q = q->next;
            p = (link)malloc(sizeof(linknode));
            i = 0;flag = 1;
        }
    }
    if ((temp>='0'&&temp<='9')||temp=='_'||(temp>='a'&&temp<='z')||(temp>='A'&&temp<='Z')){//若最后一个读取的字符为指定字符
        p->data[i-1] = '\0';//\0作为字符串结束的标志
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
            pre->next = p;
            pre = pre->next;
            pre->cont = 1;
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
                    p->cont = 1;
                    pre->next = p;
                    pre = pre->next;
                    pre->next = q;
                    flag = 1;
                    break;
                }
                else{
                    pre = pre->next;
                    q = q->next;
                }
            }
            if (!flag){
                p->cont = 1;
                q = p;
            }
        }
        t = t->next;//查找下一个单词
    }    
    /////////////输出
    //p = L->next;
    //printf("\n");
    //for (p;p!=NULL;p=p->next){
    //    printf("%s\t%d\n",p->data,p->cont);
    //}
    //printf("\n");
    /////////////
    free(p);
    return L;
}

link FindGiggestNumber(link L){//根据出现次数进行链表排序
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
            p->cont = t->cont;
            strcpy(p->data,t->data);
            pre->next = p;
            pre = pre->next;
            pre->next = NULL;
        }
        else{
            pre = s;
            q = s->next;
            p = (link)malloc(sizeof(linknode));
            p->cont = t->cont;
            strcpy(p->data,t->data);
            while (q!=NULL){//遍历链表
                //找到比自己出现次数少的单词则插入到目标前
                if (p->cont>q->cont){
                    pre->next = p;
                    pre = pre->next;
                    pre->next = q;
                    flag = 1;
                    break;
                }
                //找到和自己出现次数相同的单词且目标不在结尾则后插
                else if (p->cont==q->cont && q->next!=NULL){
                    p->next = q->next;
                    q->next = p;
                    q = q->next;
                    flag = 1;
                    break;
                }
                //找到和自己出现次数相同的单词且目标不结尾则插入到表尾
                else if (p->cont==q->cont && q->next==NULL){
                    q->next = p;
                    q = q->next;
                    q->next = NULL;
                    flag = 1;
                    break;
                }
                //若目标出现次数比自己多，则指向下一个单词
                else if (p->cont<q->cont && q->next!=NULL){
                    pre = pre->next;
                    q = q->next;
                }
                else if (p->cont<q->cont && q->next==NULL){
                    q->next = p;
                    q = q->next;
                    q->next = NULL;
                    flag = 1;
                    break;
                }
            }
        }
        t = t->next;
        p=s->next;
    }
    /////////////输出
    p = s->next;
    printf("\n");
    for (int i=0;i<10&&p!=NULL;i++){
        printf("%s\t%d\n",p->data,p->cont);
        p = p->next;
    }
    while (p!=NULL) p=p->next;//将p指针导向表尾
    //printf("\n");
    /////////////
    free(p);
    return s;
}

void ShowResultBefore(){//显示上一次保存的内容
    FILE *fp;
    char temp;
    if ((fp=fopen("D:\\res.txt","r"))!=NULL){
        printf("The last result of ten most frequently occurring words are:\n\n");
        while (!feof(fp)){
            fscanf(fp,"%c",&temp);
            printf("%c",temp);
        } 
        printf("\n");
    }
}

void main(){
    char c;
    ShowResultBefore();
    link head = CreatArticle();
    link L = SortArticle(head);
    link s = FindGiggestNumber(L);
    link p = s->next;
    FILE *fp = fopen("D:\\res.txt","w");
    //////////////输出到txt文件
    for (int i=0;i<10&&p!=NULL;i++){
        fprintf(fp,"%s\t%d\n",p->data,p->cont);
        p = p->next;
    }
    //////////////////////////
    fclose(fp);
    while (1){
        printf("\nPlease choose what you want to do\na: show the article\nb: show the words by lexicographical order\nc: show the words by frequency of occurrence\nd: exit\n");
        c = getch();
        switch (c){
            case 'a': {
                p = head->next;
                printf("\n");
                for (p;p!=NULL;p=p->next){
                    printf("%s ",p->data);
                }
                printf("\n");
                break;
            }
            case 'b': {
                p = L->next;
                printf("\n");
                for (p;p!=NULL;p=p->next){
                    printf("%s\t%d\n",p->data,p->cont);
                }
                printf("\n");
                break;
            }
            case 'c': {
                p = s->next;
                printf("\n");
                for (p;p!=NULL;p=p->next)
                    printf("%s\t%d\n",p->data,p->cont);
                printf("\n");
                break;
            }
            case 'd': exit(0);
        }
    }
    system("pause");
}