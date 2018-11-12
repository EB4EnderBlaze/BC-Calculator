#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bc.h"

void initInteger(Integer *a) {
	node *p;
	p = (node *)malloc(sizeof(node));
	p->ch = '0';
	p->prev = p->next = NULL; //Given that list is singly linked NULL terminated
	a->head = a->tail = p;
	//Will initialise integer by creating one node which has value zero stored in it. The head, tail, prev and next pointers all point to the same node in this case
}

void addDigit(Integer *a, char c) {
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

Integer addIntegers(Integer a, Integer b) {
	Integer sum;
	char num[2], carry = '0';
	int no, flag = 0, flag1 = 0, flag2 = 0;
	node *tmp1, *tmp2, *tmp;
	initInteger(&sum);
	
	tmp1 = a.tail;
	tmp2 = b.tail;
	while(1) {
		if(tmp1 != NULL && tmp2!= NULL)
			no = tmp1->ch + carry + tmp2->ch -'0'-'0'-'0';
		else if(tmp1!=NULL && tmp2 == NULL)
			no = tmp1->ch + carry -'0'-'0';
		else if(tmp1==NULL && tmp2 != NULL)
			no = tmp2->ch + carry -'0'-'0';
		else if(tmp1 == NULL && tmp2 == NULL) {
			flag = 1;
		}
		if(no > 9) {
			if(flag == 1) {
				tmp = (node*)malloc(sizeof(node));
				tmp->ch = '1';
				tmp->next = sum.head;
				tmp->prev = NULL;
				sum.head = tmp;
				return sum;
			}
			carry = '1';
			sprintf(num, "%d", no % 10);
		}
		else {
			if(flag == 1)
				return sum;
			carry = '0';
			sprintf(num, "%d", no);
		}
		if((sum.head)->ch == '0' && (sum.tail)->ch == '0' && flag2 != 1) {
			flag2 = 1;
			(sum.head)->ch = num[0];
		}
		
		else  {
			tmp = (node*)malloc(sizeof(node));
			tmp->ch = num[0];
			tmp->next = sum.head;
			tmp->prev = NULL;
			sum.head = tmp;
		}
		if(tmp1 != NULL)
			tmp1 = tmp1->prev;
		if(tmp2 != NULL)
			tmp2 = tmp2->prev;
	}	
		return sum;
}

Integer substractIntegers(Integer a, Integer b) {
	Integer sub, sub1;
	char num[2], carry = '0';
	int no, flag = 1, number = 0, f = 0;
	node *tmp1, *tmp2, *tmp;
	initInteger(&sub);
	initInteger(&sub1);
	tmp1 = a.tail;
	tmp2 = b.tail;
	while(1) {
		if(tmp1 != NULL && tmp2!= NULL) 
			no = tmp1->ch - carry - tmp2->ch + '0';
		else if(tmp1!=NULL && tmp2 == NULL)
			no = tmp1->ch - carry;
		else if(tmp1==NULL && tmp2 != NULL)
			return sub1;
		else if(tmp1 == NULL && tmp2 == NULL) {
			if(number < 0)
			{
				 f = 1;
			}
			else 
				return sub;
		}
		if(f == 1)
			break;
		if(no < 0) {
			number = no;
			no = 10 + no;
			carry = '1';
			sprintf(num, "%d", no);
		}
		else {
			number = no;
			carry = '0';
			sprintf(num, "%d", no);
		}
		
		if((sub.head)->ch == '0' && (sub.tail)->ch == '0' && flag != 0) {
			flag = 0;
			(sub.head)->ch = num[0];
		}
		
		else  {
			tmp = (node*)malloc(sizeof(node));
			tmp->ch = num[0];
			tmp->next = sub.head;
			tmp->prev = NULL;
			sub.head = tmp;
		}
		if(tmp1 != NULL)
			tmp1 = tmp1->prev;
		if(tmp2 != NULL)
			tmp2 = tmp2->prev;
	}
	
	tmp1 = b.tail;
	tmp2 = a.tail;
	while(1) {
		if(tmp1 != NULL && tmp2!= NULL) 
			no = tmp1->ch - carry - tmp2->ch + '0';
		else if(tmp1!=NULL && tmp2 == NULL)
			no = tmp1->ch - carry;
		else if(tmp1==NULL && tmp2 != NULL)
			return sub1;
		else if(tmp1 == NULL && tmp2 == NULL) {
			if(number < 0)
			{
				 
			}
			else {
				
				return sub;
			}
		}
		if(f == 1)
			break;
		if(no < 0) {
			number = no;
			no = 10 + no;
			carry = '1';
			sprintf(num, "%d", no);
		}
		else {
			number = no;
			carry = '0';
			sprintf(num, "%d", no);
		}
		
		if((sub.head)->ch == '0' && (sub.tail)->ch == '0' && flag != 0) {
			flag = 0;
			(sub.head)->ch = num[0];
		}
		
		else  {
			tmp = (node*)malloc(sizeof(node));
			tmp->ch = num[0];
			tmp->next = sub.head;
			tmp->prev = NULL;
			sub.head = tmp;
		}
		if(tmp1 != NULL)
			tmp1 = tmp1->prev;
		if(tmp2 != NULL)
			tmp2 = tmp2->prev;
	}
}


void printInteger(Integer a) {
	node *tmp;
	tmp = a.head;
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

void push(stack **s, Integer n) {
	stack *t;
	t = (stack *)malloc(sizeof(stack));
	t->next = NULL;
	t->a = n;
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

Integer pop(stack **s) {
	Integer ch;
	stack *t;
	ch = (*s)->a;
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
	while(p != a->tail) {
		dec_count++;
		p = p->next;
	}
	free(p);
	return dec_count;
}
