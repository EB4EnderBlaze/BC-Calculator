#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bc.h"

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

int createintfromInteger(Integer *a) {
	node *p;
	p = (node *)malloc(sizeof(node));
	p = a->head;
	int num;
	int n = length(a), i = 0;
	for(i = 0; i < n; i++) {
		num = num * 10;
		num += atoi(&(p->ch));
	}
	return num;
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
	return len; //one for the decimal symbol
}

/*Integer mulnum(Integer a, Integer b) {
	Integer product;
	initInteger(&product);
	int i = 0;
	for(i = 0; i < createintfromInteger(&b); i++) {
		addIntegers(product,a);
	}
	return product;
}*/

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



void copyInteger(Integer *b, Integer *c) {
	node *p;
	//p = (node *)malloc(sizeof(node));
	//q = (node *)malloc(sizeof(node));
	p = b->head;
	//q = c->head;
	while(p != NULL) {
		//q->ch = p->ch;
		addDigit(c, p->ch);
		p = p->next;
		//q = q->next;
	}
}

int checkzero(Integer *a) {
	node *p;
	p = a->head;
	while(p != NULL) {
		if(p->ch == '0')
			p = p->next;
		else {
			return 1;
			break;
		}
	}
	return 0;
}

void initInteger(Integer *a) {
	a->head = a->tail = NULL;
}

void addDigit(Integer* a, char c) {
	node *temp = (node*)malloc(sizeof(node));
	if(a->head == NULL) {
		a->head = a->tail = temp;
		temp->next = temp->prev = NULL;
		temp->ch = c;
		return;
	}
	temp->next = NULL;
	a->tail->next = temp;
	temp->ch = c;
	temp->prev = a->tail;
	a->tail = temp;
}

Integer createIntegerFromString(char *str) {
	Integer a;
	initInteger(&a);
	int i = 0;
	while(str[i] >= 48 && str[i] <= 57) {//i.e. iterate only if the current character is a ch
		addDigit(&a, str[i]);
		i++;
	}
	return a;
}
Integer addIntegers(Integer a, Integer b) {
	int a_num, b_num, sum, carry = 0;
	char ch;
	Integer c;
	initInteger(&c);
	node *a_temp, *b_temp;
	a_temp = a.tail;
	b_temp = b.tail;
	while(a_temp != NULL || b_temp != NULL) {
		//first number
		if(a_temp == NULL)
			a_num = 0;
		else
			a_num = a_temp->ch - 48;
		//second number
		if(b_temp == NULL)
			b_num = 0;
		else
			b_num = b_temp->ch - 48;
		sum = a_num + b_num + carry;
		if(sum > 9) {
			sum = sum - 10;
			carry = 1;
		}
		else
			carry = 0;
		addDigit(&c, sum + '0');
		if(a_temp != NULL)
			a_temp = a_temp->prev;
		if(b_temp != NULL)
			b_temp = b_temp->prev;
	}
	if(carry)
		addDigit(&c, 1 + '0');
	//reverse the Integer 'c' by swapping the next and previous pointers
	if(c.head != NULL) {
		a_temp = c.head;
		b_temp = c.tail;
		while(1) {//i.e. they cross over
			ch = a_temp->ch;
			a_temp->ch = b_temp->ch;
			b_temp->ch = ch;
			a_temp = a_temp->next;
			b_temp = b_temp->prev;
			if(a_temp == NULL)
				break;
			else if(a_temp->prev == b_temp->next || b_temp->next == a_temp)
				break;
		}
	}
	return c;
}

Integer substractIntegers(Integer a, Integer b) {
	int a_num, b_num, diff, borrow = 0, a_count = 0, b_count = 0, equal_flag = 1;
	char ch;
	Integer c;
	initInteger(&c);
	node *a_temp, *b_temp;
	a_temp = a.head;
	b_temp = b.head;
	//Checking if 'a' is smaller than 'b'
	while(a_temp != NULL) {
		a_temp = a_temp->next;
		a_count++;
	}
	while(b_temp != NULL) {
		b_temp = b_temp->next;
		b_count++;
	}
	a_temp = a.head;
	b_temp = b.head;
	if(a_count < b_count)
		return c;
	else if(a_count == b_count) {
		while(a_temp != NULL) {//as length of 'a' and 'b' is same they will reach null at same time
			if(a_temp->ch < b_temp->ch)
				return c;
			if(a_temp->ch > b_temp->ch)
				equal_flag = 0;
			a_temp = a_temp->next;
			b_temp = b_temp->next;
		}
	}
	else if(a_count > b_count)
		equal_flag = 0;
	if(equal_flag)
		return c;
	//END OF CHECK
	a_temp = a.tail;
	b_temp = b.tail;
	while(a_temp != NULL || b_temp != NULL) {
		//first number
		if(a_temp == NULL)
			a_num = 0;
		else
			a_num = a_temp->ch - 48;
		//second number
		if(b_temp == NULL)
			b_num = 0;
		else
			b_num = b_temp->ch - 48;
		diff = a_num - b_num - borrow;
		if(diff < 0) {
			diff = diff + 10;
			borrow = 1;
		}
		else
			borrow = 0;
		addDigit(&c, diff + '0');
		if(a_temp != NULL)
			a_temp = a_temp->prev;
		if(b_temp != NULL)
			b_temp = b_temp->prev;
	}
	//reverse the Integer 'c'
	if(c.head != NULL) {
		a_temp = c.head;
		b_temp = c.tail;
		while(1) {//i.e. they cross over
			ch = a_temp->ch;
			a_temp->ch = b_temp->ch;
			b_temp->ch = ch;
			a_temp = a_temp->next;
			b_temp = b_temp->prev;
			if(a_temp == NULL)
				break;
			else if(a_temp->prev == b_temp->next || b_temp->next == a_temp)
				break;
		}
	}
	return c;
}

void printInteger(Integer a) {
	node *temp;
	temp = a.head;
	if(temp == NULL) {
		printf("0\n");
		return;
	}
	while(temp != NULL) {
		printf("%c", temp->ch);
		temp = temp->next;
	}
	printf("\n");
}

void destroyInteger(Integer *a) {
	node *temp;
	while(a->tail = NULL) {
		temp = a->tail;
		a->tail = a->tail->prev;
		free(temp);
	}
	a->head = NULL;
}

Integer mulnum(Integer *a, Integer *b) {
	int carry = 0, prod = 0, i = 0, j = 0, k = 0, a_num, b_num,a_len = 0, b_len = 0;
	char ch;
	Integer product, *step;
	initInteger(&product);
	step = (Integer *)malloc(sizeof(Integer) * 1000);
	node *a_temp, *b_temp;
	a_temp = a->tail;
	while(a_temp) {
		a_len++;
		a_temp = a_temp->prev;
	}
	b_temp = b->tail;
	while(b_temp) {
		a_len++;
		b_temp = b_temp->prev;
	}
	if(a_len < b_len)
		a_temp = a->tail;
	else
		a_temp = b->tail;
	while(a_temp) {
		if(a_len < b_len)
			b_temp = b->tail;
		else
			b_temp = a->tail;
		initInteger(step + i);
		while(b_temp) {
			//multiply
			a_num = a_temp->ch - '0';
			b_num = b_temp->ch - '0';
			prod = ((b_num) * (a_num)) + carry;
			addDigit(&step[i], (prod % 10) + '0');
			carry = prod / 10;
			b_temp = b_temp->prev;
		}
		if(carry) {
			addDigit((step + i), carry + '0');
			carry = 0;
		}
		i++;
		a_temp = a_temp->prev;
	}
	for(j = 0; j < i; j++) {
		//reverse the Integer 'c' by swapping the next and previous pointers
		if(step[j].head != NULL) {
			a_temp = step[j].head;
			b_temp = step[j].tail;
			while(1) {//i.e. they cross over
				ch = a_temp->ch;
				a_temp->ch = b_temp->ch;
				b_temp->ch = ch;
				a_temp = a_temp->next;
				b_temp = b_temp->prev;
				if(a_temp == NULL)
					break;
				else if(a_temp->prev == b_temp->next || b_temp->next == a_temp)
					break;
			}
		}
		k = j;
		while(k--)
			addDigit((step + j), '0');
		product = addIntegers(product, step[j]);
	}
	return product;
}
