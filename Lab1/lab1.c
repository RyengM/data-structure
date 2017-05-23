#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct node {
	int data;
	struct node *next;
}linknode,*link;

link CreatList() {
	link h = (link)malloc(sizeof(linknode));
	h->next = NULL;
	link q = h;
	link p;
	do {
		p = (link)malloc(sizeof(linknode));
		scanf("%d", &p->data);
		q->next = p;
		q = q->next;
	} while (getchar() != '#');
	q->next = NULL;
	return h;
}

int Adjmax(link h, int k) {
	int target = 0;
	int max = 0;
	int sum = 0;
	link p = h->next;
	link q = h->next;
	for (int i = 0; i < k; i++) {
		sum += q->data;
		q = q->next;
	}
	max = sum;
	while (q->next != NULL) {
		sum = sum + q->data - p->data;
		q = q->next;
		p = p->next;
		if (sum > max)
			max = sum;
		target++;
	}
	return target;
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
	printf("序号%d,data值ֵ%d\n", target, p->data);
	p = L->next;
	system("pause");
}