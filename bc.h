#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
	char ch;
	struct node *prev, *next;
}node;

typedef struct Integer {
	node *head, *tail;
	int sign;
	int dec; //no of digits after decimal point.
}Integer;

typedef struct stack {
	Integer a;
	struct stack *next;
}stack;

typedef struct cstack {
	char b;
	struct cstack *next;
}cstack;

void initInteger(Integer *a);
void append(Integer *a, char c);
Integer createIntegerFromString(char *str);
void printInteger(Integer *a);
void destroyInteger(Integer *a);
void init(stack**);
void push(stack**, Integer*);
Integer *pop(stack**);
int isempty(stack*);

void charinit(cstack**);
void charpush(cstack**, char);
char charpop(cstack**);
int charisempty(cstack*);

int dec(Integer *a);
int show(Integer *a, int n);

Integer *addnum(Integer *l1, Integer *l2);
Integer *subnum(Integer *l1, Integer *l2);
Integer *division(Integer *l1, Integer *l2);
Integer *mulnum(Integer *l1, Integer *l2);

int checkzero(Integer *a);
int remov(Integer *l, int pos);
int length(Integer *a);
int compare(Integer *a, Integer *b);
void insert(Integer *l, int pos, char num);

/*Further required : 
 *Stack to store sign of each number that is stored in the Integer stack. When an Integer is popped from the stack, its respective sign shall also be popped from this stack at same time. 
 *The Integer stack we have currently uses character data type to store the data. Hence it will automatically take care of the decimal point as well
*/


