#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct node {
	int data;
	struct node *next;
}linknode,*link;

link CreatList() {//��������
	link h = (link)malloc(sizeof(linknode));//Ϊͷ�ڵ�����ڴ�ռ�
	h->next = NULL;//��ʼ��
	link q = h;
	link p;
	do {
		p = (link)malloc(sizeof(linknode));//Ϊ�½ڵ�����ڴ�ռ�
		scanf("%d", &p->data);//����ڵ�����
		q->next = p;//���½ڵ���ӵ�����β��
		q = q->next;
	} while (getchar() != '#');//����⵽����Ϊ#ʱ�˳�����
	q->next = NULL;
	return h;//����ͷָ��
}

int Adjmax(link h, int k) {//kΪ����������ڽڵ㳤�ȣ��ú��������ҳ�������ڽڵ��
	int target = 0;
	int max = 0;
	int sum = 0;
	link p = h->next;//ָ�����ڽڵ��ͷ��
	link q = h->next;//ָ�����ڽڵ��β��
	for (int i = 0; i < k; i++) {//��ʼ�����ֵ��������ǰk���ڵ�ֵ֮��
		sum += q->data;
		q = q->next;
	}
	max = sum;
	while (q->next != NULL) {//��βָ���nextָ��NULL֮ǰ
		sum = sum + q->data - p->data;//�����
		q = q->next;//����ָ����֮�ƶ�
		p = p->next;
		if (sum > max)//��ĳ�ʹ��ڵ�ǰ���ֵʱ
			max = sum;//�������ֵ
		target++;
	}
	return target;//�������ڽڵ�ĵ�һ���ڵ��±�
}

void main() {
	int cout = 0,k,target = 1;
	printf("����������\n");
	link L = CreatList();
	link p = L->next;
	for (p; p->next != NULL; p = p->next)
		cout++;
	printf("���������ڽڵ���\n");
	scanf("%d", &k);
	while (k>cout) {
		printf("���벻����Ҫ������������\n");
		scanf("%d", &k);
	}
	target = Adjmax( L, k);
	p = L->next;
	for (int i = 1; i < target; i++)
		p = p->next;
	printf("���%d,dataֵ%d\n", target, p->data);
	p = L->next;
	system("pause");
}