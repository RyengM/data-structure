#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char data;
	struct node *next;
}snode,*slink;

char Pop(slink *top) {
	char e;
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

void Push(slink *top, char e) {
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
		Pop(top);
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

int Precede(char x, char y) {
	switch (x) {
        case '#': x = -1;break;
		case '(': x = 0; break;
		case '+':
		case '-': x = 1; break;
		case '*':
		case '/': x = 2; break;
	}
	switch (y) {
		case '+':
		case '-': y = 1; break;
		case '*':
		case '/': y = 2; break;
		case '(': y = 3; break;
	}
	if (x >= y) return 1;
	else return 0;
}

void mid_post(char post[], char mid[]) {
	int i = 0, j = 0;
	char x;
	slink S = NULL;
	Push(&S, '#');
	do {
		x = mid[i++];
		switch (x) 
		{
			case '#': {
				while (!EmptyStack(S))
					post[j++] = Pop(&S);
			}break;
			case  ')': {
				post[j++] = ' ';
				while (GetsTop(S) != '(')
					post[j++] = Pop(&S);
				Pop(&S);
				post[j++] = ' ';
			}break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			{
				while (Precede(GetsTop(S), x))
					post[j++] = Pop(&S);
				Push(&S, x);
				if (post[j-1] != ' ')
					post[j++] = ' ';
			}break;
			default:post[j++] = x;
		}
	} while (x != '#');
    for (int t=0;post[t]!='#';t++) printf("%c",post[t]);
    printf("\n");
}

double PostCount(char post[]) {
	int i = 0,j = 0,k,flag=0;
	double cont = 1,num[10];
	char x;
	memset(num,0,sizeof(double)*10);
	while (post[i] != '#') {
		x = post[i];
		switch (x) {
			case ' ': { if (post[i-1] >= '0' && post[i-1] <='9') {cont=1;j++;flag=0;}
						break;
			}			
			case '.': flag = 1; cont = 0.1; break;
			case '+': num[j-2] = num[j-1]+ num[j-2];j--;num[j]=0;break;
			case '-': num[j-2] = num[j-1]- num[j-2];j--;num[j]=0;break;
			case '*': num[j-2] = num[j-1]* num[j-2];j--;num[j]=0;break;
			case '/': num[j-2] = num[j-1]/ num[j-2];j--;num[j]=0;break;
			default: {	k = post[i] - '0'; 
						if (!flag){
							num[j] = num[j]*cont + k;
							cont *= 10;
						}
						else{
							num[j] = num[j]+ k*cont;
							cont *= 0.1;
						}
			}
		}
		i++;
	}
	return num[j-1];
}

int main() {
	slink top = NULL;
	int i = 0;
	double result;
	char a[100];
	char b[100];
	printf("Please enter the expression\n");
	while(1) {
		scanf("%c",&a[i]);
		if ((a[i] > 47 && a[i] < 58) || a[i] == 43 || a[i] == 45 || a[i] == 47 || a[i] == 42 || a[i] == 40 || a[i] == 41|| a[i] == 46) {
			i++;
		}
		else if (a[i] == 10) continue;
		else if (a[i] == 35) break;
		else {
			printf("the expression you enput is illegal,please input again\n");
			i = 0;
			memset(a, 0, 100 * sizeof(char));
		}
	}
	mid_post(b,a);
	result = PostCount(b);
	printf("%llf\n", result);
	system("pause");
	return 0;
}