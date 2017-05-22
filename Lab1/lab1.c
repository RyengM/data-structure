#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct node {
	int data;
	struct node *next;
}linknode,*link;

link CreatList() {//创建链表
	link h = (link)malloc(sizeof(linknode));//为头节点分配内存空间
	h->next = NULL;//初始化
	link q = h;
	link p;
	do {
		p = (link)malloc(sizeof(linknode));//为新节点分配内存空间
		scanf("%d", &p->data);//输入节点数据
		q->next = p;//将新节点添加到链表尾部
		q = q->next;
	} while (getchar() != '#');//当监测到输入为#时退出输入
	q->next = NULL;
	return h;//返回头指针
}

int Adjmax(link h, int k) {//k为你输入的相邻节点长度，该函数用于找出最大相邻节点和
	int target = 0;
	int max = 0;
	int sum = 0;
	link p = h->next;//指向相邻节点的头部
	link q = h->next;//指向相邻节点的尾部
	for (int i = 0; i < k; i++) {//初始化最大值，就是找前k个节点值之和
		sum += q->data;
		q = q->next;
	}
	max = sum;
	while (q->next != NULL) {//在尾指针的next指向NULL之前
		sum = sum + q->data - p->data;//计算和
		q = q->next;//两个指针随之移动
		p = p->next;
		if (sum > max)//当某和大于当前最大值时
			max = sum;//更新最大值
		target++;
	}
	return target;//返回相邻节点的第一个节点下标
}

void main() {
	int cout = 0,k,target = 1;
	printf("请输入数据\n");
	link L = CreatList();
	link p = L->next;
	for (p; p->next != NULL; p = p->next)
		cout++;
	printf("请输入相邻节点数\n");
	scanf("%d", &k);
	while (k>cout) {
		printf("输入不符合要求，请重新输入\n");
		scanf("%d", &k);
	}
	target = Adjmax( L, k);
	p = L->next;
	for (int i = 1; i < target; i++)
		p = p->next;
	printf("序号%d,data值%d\n", target, p->data);
	p = L->next;
	system("pause");
}