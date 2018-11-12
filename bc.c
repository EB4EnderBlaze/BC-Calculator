#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bc.h"

void initInteger(Integer *a) {
	node *p;
	p = (node *)malloc(sizeof(node));
	p->ch = '0';
	p->prev = p->next = NULL; //Given that Integer is singly linked NULL terminated
	a->head = a->tail = p;
	//Will initialise integer by creating one node which has value zero stored in it. The head, tail, prev and next pointers all point to the same node in this case
}

void append(Integer *a, char c) {
	node *tmp;
	if(a->head->ch == '0' && a->tail->ch == '0') {
		a->head->ch = c;
	}
	else {
		tmp = (node *)malloc(sizeof(node));
		tmp->ch = c;
		tmp->next = NULL;
		a->tail->next = tmp;
		tmp->prev = a->tail;
		a->tail = tmp;
	}
}

Integer *addnum(Integer *l1, Integer *l2) {
	Integer *result;
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	result = (Integer *)malloc(sizeof(Integer));
	initInteger(result);
	if(dec(l1) > dec(l2)) {
		int i;
		int y = (dec(l1) - dec(l2));
		for(i = 0; i < y; i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(dec(l2) > dec(l1)) {
		int i;
		int y = (dec(l2) - dec(l1));
		for(i = 0; i < y; i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	
	if(l1->sign != l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			result = subnum(l2, l1);
			l1->sign = sign1;
			return result;
		}
		else if(l2->sign == -1) {
			l2->sign = 1;
			result = subnum(l1, l2);
			l2->sign = sign2;
			return result;
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1)
			result->sign = -1;
		else
			result->sign = 1;
		int num = 0, i, j;
		i = length(l1);
		j = length(l2);
		int carry = 0;
		while(i != 0 || j != 0) {
			if(i == 0) {
				num = show(l2, j - 1) + carry;
				j--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else if(j == 0) {
				num = show(l1, i -1) + carry;
				i--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else {
				num = show(l1, i - 1) + show(l2, j - 1) + carry;
				i--;
				j--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0 , num);
			}
		}
		result->dec = dec(l1);
		if(carry != 0)
			insert(result, 0, carry);
	}
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}

Integer *subnum(Integer *l1, Integer *l2) {
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	/*Make no of digits after decimal equal*/
	if(dec(l1) > dec(l2)) {
		int i;
		int y = (dec(l1) - dec(l2));
		for(i = 0; i < y; i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(dec(l2) > dec(l1)) {
		int i;
		int y = (dec(l2) - dec(l1));
		for(i = 0; i < y; i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	int num;
	static int flag = 0;
	Integer *result;
	result = (Integer *)malloc(sizeof(Integer));
	initInteger(result);
	if(l1->sign != l2->sign) {
		if(l2->sign == -1) {
			l2->sign = 1;
			result = addnum(l1, l2);
			result->sign = 1;
		}
		if(l1->sign == -1) {
			l1->sign = 1;
			result = addnum(l1, l2);
			result->sign = -1;
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			l2->sign = 1;
			result = subnum(l2, l1);
		}
		if(l1->sign == 1) {
			if(compare(l1, l2) >= 0) {
				if(flag != 1)
					result->sign = 1;
				else
					result->sign = -1;
				int b = 0;
				int m,n;
				m = length(l1) - 1;
				n = length(l2) - 1; 
				while(m != -1 || n != -1) {
					if(n == -1) {
						num = show(l1, m);m--;
						insert(result, 0, num);
					}
					else {
						int a = show(l1, m);m--;
						int c = show(l2, n);n--;
						if(a >= c) {
							num = a - c;
							insert(result, 0, num);
						}
						else {
							int d = 0;
							while(!(b = remov(l1, m))) {
								m--;
								d++;
							}
							m--;
							m++;
							insert(l1, m, b - 1);
							int i;
							for(i = 0; i < d; i++) {
								m++;
								insert(l1, m, 9);
							}
							num = 10 + a - c;
							insert(result, 0, num);
						}
					}
				}
			}
			else if(compare(l1, l2) < 0) {
				flag = 1;
				result = subnum(l2, l1);
				result->sign = -1;
			}
		}
	}
	result->dec = l1->dec;
	flag = 0;
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}

Integer *mulnum(Integer *l1, Integer *l2) {
	Integer *result;
	result = (Integer *)malloc(sizeof(Integer));
	initInteger(result);
	int tempsign, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(checkzero(l1) == 0)
		return l1;
	if(checkzero(l2) == 0)
		return l2;	
	if(l1->sign == l2->sign) {
		tempsign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		tempsign = -1;
		l1->sign = l2->sign = 1;
	}
	int x = length(l1) - length(l2);
	if(x < 0) {
		result = mulnum(l2, l1);
		return result;
	}
	else {
		int n = length(l2) - 1, j, i;
		int a = length(l2), b = length(l1);
		int arr[2 * b];
		for( i = 0; i < 2 * b; i++)
			arr[i] = 0;
		int num1 = 0, num2 = 0;
		int k = 2 * b - 1;
		for( i = 0; i < a; i++) {
			int m = length(l1) - 1;
			int carry1 = 0, carry2 = 0;
			for( j = k - i; j > b - 2; j--) {
				if(m != -1 && n != -1) {
					num1 = show(l1, m) * show(l2, n) + carry1;
					m--;
					carry1 = num1 / 10;
					num1 = num1 % 10;
					num2 = arr[j] + num1 + carry2;
					carry2 = num2 / 10;
					num2 = num2 % 10;
					arr[j] = num2;
				}
				else {
					break;
				}
			}
			arr[j] = carry1 + carry2 + arr[j];
			b--; n--;
		}
		j = 0;
		for( i = 2 * length(l1) - 1; i > b - 1 && i >= 0; i--) {
			insert(result, 0, arr[i]); j++;
		}
		result->dec = l1->dec + l2->dec;
		result->sign = tempsign;
		l1->sign = sign1;
		l2->sign = sign2;
		return result;
	}
}

Integer *division(Integer *l1, Integer *l2) {
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:dividing by zero");
		return NULL;
	}
	Integer *result;
	result = (Integer *)malloc(sizeof(Integer));
	Integer *temp;
	temp = (Integer *)malloc(sizeof(Integer));
	initInteger(temp);
	initInteger(result);
	int m, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}
	int a, b;
	m = l1->dec - l2->dec;
	int i, j, k, num;
	
	a = l1->dec;
	b = l2->dec;
	l1->dec = l2->dec = 0;
	for(i = 0; i < length(l1); i++) {
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l2) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = subnum(temp, l2);
				d++;
				if(compare(temp, l2) < 0)
					break;
					
			}
			printf("d:%d\n",d);
			append(result, d);
		}
	}
	j = 0; k = 0;
	while(j < 6) {
		append(temp, 0);
		int d = 0;
		while(compare(temp, l2) >= 0) {
			temp = subnum(temp, l2);
			d++;
		}
		append(result, d);
		k++;j++;
	}
	result->dec = 6 + m;
	printf("re->dec%d\n",result->dec);
	l1->dec = a;
	l2->dec = b;
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}

void printInteger(Integer *a) {
	node *tmp;
	tmp = a->head;
	while(tmp != NULL) {
		printf("%c", tmp->ch);
		tmp = tmp->next;
	}
	printf("\n");
}

void destroyInteger(Integer *a) {
	node *tmp, *p;
	int i = 0;
	tmp = a->head;
	do {
		p = tmp;
		tmp = tmp->next;
		free(p);
	} while(tmp != NULL);
	initInteger(a);
}

void init(stack **s) {
	*s = NULL;
}

void charinit(cstack **s) {
	*s = NULL;
}

void push(stack **s, Integer *n) {
	stack *t;
	t = (stack *)malloc(sizeof(stack));
	t->next = NULL;
	t->a = *n;
	if(*s == NULL) {
		*s = t;
	}
	else {
		t->next = (*s);
		(*s) = t;
	}
}

void charpush(cstack **s, char n) {
	cstack *t;
	t = (cstack *)malloc(sizeof(cstack));
	t->next = NULL;
	t->b = n;
	if(*s == NULL) {
		*s = t;
	}
	else {
		t->next = (*s);
		(*s) = t;
	}
}

Integer *pop(stack **s) {
	Integer *ch;
	stack *t;
	ch = &((**s).a);
	t = *s;
	*s = (*s)->next;
	free(t);
	return ch;
}

char charpop(cstack **s) {
	char ch;
	cstack *t;
	ch = (*s)->b;
	t = *s;
	*s = (*s)->next;
	free(t);
	return ch;
}

int isempty(stack *s) {
	if(s == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int charisempty(cstack *s) {
	if(s == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int dec(Integer *a) {
	node *p;
	p = (node *)malloc(sizeof(node));
	int dec_count = 0;
	p = a->head;
	while(p->ch != '.') {
		p = p->next;
	}
	while(p != NULL) {
		dec_count++;
		p = p->next;
	}
	free(p);
	return dec_count;
}

int show(Integer *a, int n) {
	node *p;
	p = (node *)malloc(sizeof(node));
	int i;
	char ch;
	p = a->head;
	for(i = 0; (i < n) && p != NULL; i++) {
		ch = p->ch;
		p = p->next;
	}
	if(ch == '.') { //It's not possible that the number in the Integer ends in a decimal point because that would be invalid
		p = p->next; //So here p never goes beyond a->tail.
		ch = p->ch;
	}
	free(p);
	return atoi(&ch);
}

int checkzero(Integer *a) {
	int len = length(a);
	int i = 0;
	node *p = (node *)malloc(sizeof(node));
	p = a->head;
	while(p->ch != '.') {
		if(p->ch == '0')
			p = p->next;
		else
			return 1;
	}
	p = p->next;
	while(p != NULL) {
		if(p->ch == '0')
			p = p->next;
		else
			return 1;
	}
	return 0;
}

int remov(Integer *l, int pos) {
	char *s = (char *)malloc(sizeof(char) * 100);
	if(pos < 0)
		return 0;
	node *temp = l->head;
	node *temp2;
	if(pos == 0) {
		if(l->head == NULL)
			return 0;
		strcpy(s, &(temp->ch));
		l->head = temp->next;
		free(temp);
		return atoi(s);
	}
	pos--;
	while(pos) {
		temp = temp->next;
		pos--;
	}
	temp2 = temp->next;
	strcpy(s, &(temp2->ch));
	//temp->prev = temp2->prev;
	temp->next = temp2->next;
	free(temp2);
	return atoi(s);
}

int length(Integer *a) {
	node *p;
	p = (node *)malloc(sizeof(node));
	int len = 0;
	p = a->head;
	while(p != NULL) {
		len++;
		p = p->next;
	}
	free(p);
	return len - 1; //one for the decimal symbol
}

int compare(Integer *a, Integer *b) {
	node *p, *q;
	p = (node *)malloc(sizeof(node));
	q = (node *)malloc(sizeof(node));
	p = a->head;
	q = b->head;
	while(p != a->tail && q != b->tail) {
		if(atoi(&(p->ch)) == atoi(&(q->ch))) {
			p = p->next;
			q = q->next;
		}
		if(atoi(&(p->ch)) > atoi(&(q->ch))) {
			return 1;
			break;
		}
		if(atoi(&(p->ch)) < atoi(&(q->ch))) {
			return -1;
			break;
		}
	}
	return 0;
}

void insert(Integer *l, int pos, char num) {
	if(pos < 0)
		return;
	node *temp = l->head;
	node *new = (node *)malloc(sizeof(node));
	strcpy(&(new->ch), &num);
	if(pos == 0) {
		if(l->head == NULL) {
			l->head = l->tail = new;
			new->next = new->prev = NULL;
			return;
		}
		new->next = l->head;
		l->head = new;
		return;
	}
	pos--;
	while(pos) {
		temp = temp->next;
		pos--;
	}
	new->next = temp->next;
	temp->next = new;
}
