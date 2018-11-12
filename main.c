#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "bc.h"

#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400

int rst;
typedef struct token {
	int type;
	Integer val;
	char op;
}token;
token t;
enum state { NUMBER, OP, FINISH, ERROR, SPC };
token gettoken(char *expr) {
	static int i = 0, j = 1;
	//static Integer no;
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	if(j == 1 || rst == 1)
		initInteger(&(t.val));
	j = 2;
	if(rst == 1) {
		currstate = SPC;
		rst = 0;
		i = 0;
	}
	while(1) {
		currchar = expr[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':case '.':
						nextstate = NUMBER;
						currstate = nextstate;
						append(&(t.val), currchar);
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(': case ')':
						nextstate = OP;
						t.type = OPERAND;
						currstate = nextstate;
						i++;
						j = 1;
						return t;
						
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						currstate = nextstate;
						i++;
						return t;
						break;
					default:
						nextstate = ERROR;
						t.type = OPERAND;
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':case '.':
						append(&(t.val), currchar);
						t.type = OPERATOR;
						t.op = expr[i - 1];
						nextstate = NUMBER;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '+': case '*': case '/': case '%': case '(': case ')':
						nextstate = OP;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '-':
						nextstate = OP;
						(t.val).sign = -1;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					default:
						nextstate = ERROR;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
					 	break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						append(&(t.val), currchar);
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(': case ')':
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;
					default: // anything else
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}

int prec(char opr) {
	switch(opr) {
		case '+': case '-':
			return 1;
			break;	
		case '*': case '/':
			return 2;
			break;	
		case '(':
			return 0;
			break;
		default:
			return 5;
			break;
	}
	return 4;
}

char getprevop(cstack **s1) {
	char c;
	c = charpop(s1);
	charpush(s1, c);
	return c;
}

int calculate(stack **top1, char opr) {
	Integer *op1;
	Integer *op2, *result;
	initInteger(op1);
	initInteger(op2);
	initInteger(result);
	op1 = pop(top1);
	op2 = pop(top1);
	
	switch(opr) {
		case '+':
			result = addnum(op1,op2);
			break;
			
		case '-':
			result = subnum(op2,op1);
			break;
		
		case '*':
			result = mulnum(op1,op2);
			break;

		case '/':
			result = division(op2,op1);
			break;
	}
	
	push(top1, result);
	return 1;
}


Integer *findinfix(char *expr) {
	token t;
	Integer *fres;
	initInteger(fres);
	char prevop, currchar, opr;
	stack *top1; 
	cstack *top2;
	rst = 1;

	init(&top1);
	charinit(&top2);
	
	while(1) {
		t = gettoken(expr);
		if(t.type == OPERAND) {
			push(&top1, &(t.val));
		} 
		
		else if(t.type == OPERATOR) {
			if(charisempty(top2)) {
				charpush(&top2, t.op);
			}
				
			else {
				prevop = getprevop(&top2); 
				currchar = t.op;
				if(currchar  == '(') 
					charpush(&top2, currchar);
					
				else if(currchar == ')') {
					while(prevop != '(') {
						opr = charpop(&top2);
						calculate(&top1, opr);
						prevop = getprevop(&top2);	
					}
					charpop(&top2);
				}
					
				else if(prec(prevop) >= prec(currchar)) {
					while(prec(prevop) >= prec(currchar) ) {
						opr = charpop(&top2);
						calculate(&top1, opr);
						if(charisempty(top2))
							break;
						else 
							prevop = getprevop(&top2);
					}
					charpush(&top2, currchar);
				}	
				
				else 
					charpush(&top2, currchar);
			}
		}
		else if(t.type == END) {
			while(charisempty(top2) != 1) {
				opr = charpop(&top2);
				//if(opr == '(')
					//return INT_MIN;
				//else
					calculate(&top1, opr);
			}
			
			fres = pop(&top1);
			return fres;
		}
		
		else if(t.type == ERR) {
			//return INT_MIN;
		}
			
	}
	rst = 0;
	//return 1;
	
}

int readline(char *line, int len) {
	int i;
	char ch;
	i = 0;
	while(i < len - 1) {
		ch = getchar();
		if(ch == '\n') {
			line[i++] = '\0';
			return i - 1;
		}
		else
			line[i++] = ch;
	}
	line[len - 1] = '\0';
	return len - 1;
}

int main(int argc, char *argv[]) {
	char line[128];
	Integer *r;
	initInteger(r);
	printf("A");
	while(readline(line, 128)) {
		r = findinfix(line);
		//if(r != INT_MIN)
			printInteger(r);
		//else
		//	fprintf(stderr, "Error in postfix expr\n");
	}
	return 0;
}
