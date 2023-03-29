/*
 M | 0  1  2  3  4  5  6  7
 --------------------------
 0 | 0  0  0  1  0  0  0  0
 1 | 0  1  1  1  0  0  1  0
 2 | 0  1  0  1  0  0  1  0
 3 | 0  1  0  1  1  1  1  0
 4 | 0  1  0  0  0  0  1  1
 5 | 0  1  1  0  1  1  1  0
 6 | 0  0  0  0  1  0  0  0
 7 | 0  0  0  0  1  0  0  0
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LINKED_STACK_NODE_s *LINKED_STACK_NODE;
typedef struct LINKED_STACK_NODE_s {
	LINKED_STACK_NODE next;
	void *data;
} LINKED_STACK_NODE_t[1];

typedef struct LINKED_STACK_s {
	LINKED_STACK_NODE head;
} LINKED_STACK_t[1], *LINKED_STACK;

typedef struct{
	int R;
	int C;
}POS_t[1], *POS;

int linked_stack_is_empty(LINKED_STACK stack) {
	return stack->head == NULL;
}

LINKED_STACK linked_stack_init() {
	LINKED_STACK stack = malloc(sizeof(LINKED_STACK_t));
	stack->head = NULL;
	return stack;
}

void linked_stack_push(LINKED_STACK stack, void *data) {
	LINKED_STACK_NODE new = malloc(sizeof(LINKED_STACK_NODE_t));
	if (new != NULL) {
		new->data = data;
		new->next = stack->head;
		stack->head = new;
	} else {
		printf("Memory allocation error!\n");
		exit(0);
	}
}

void *linked_stack_pop(LINKED_STACK stack) {
	LINKED_STACK_NODE temp;
	void *result = NULL;
	if (stack->head != NULL) {
		temp = stack->head;
		stack->head = temp->next;
		result = temp->data;
		free(temp);
	} else {
		printf("Stack is empty\n");
		exit(0);
	}
	return result;
}

void linked_stack_free(LINKED_STACK stack) {
	while (stack->head != NULL) {
		linked_stack_pop(stack);
	}
	free(stack);
}

void linked_stack_print2(LINKED_STACK s, int M[8][8]){
	LINKED_STACK_NODE node = s->head;
	while(node != NULL){
		POS pos = (POS)node->data;
		printf("(%d,%d)=%d ", pos->R, pos->C, M[pos->R][pos->C]);
		node = node->next;
	}
	printf("\n");
}

void solve_maze(){
	int M[8][8] = { \
	/******   0  1  2  3  4  5  6  7   */
	/* 0 */ { 0, 0, 0, 1, 0, 0, 0, 0 }, \
	/* 1 */ { 0, 1, 1, 1, 0, 0, 1, 0 }, \
	/* 2 */ { 0, 1, 0, 1, 0, 0, 1, 0 }, \
	/* 3 */ { 0, 1, 0, 1, 1, 1, 1, 0 }, \
	/* 4 */ { 0, 1, 0, 0, 0, 0, 1, 1 }, \
	/* 5 */ { 0, 1, 1, 0, 1, 1, 1, 0 }, \
	/* 6 */ { 0, 0, 0, 0, 1, 0, 0, 0 }, \
	};
	int I, J, R = 0, C = 3;
	LINKED_STACK stack = linked_stack_init();
	POS pos = (POS)malloc(sizeof(POS_t));
	pos->R = R;
	pos->C = C;
	linked_stack_push(stack,pos);
	M[pos->R][pos->C] = 2;
	do{
		I = R;
		J = C;
		if((R-1 >= 0) && (M[R-1][C] == 1)){
			I = R-1;
			J = C;
		}
		else if((C+1 <= 7) && (M[R][C+1] == 1)){
			I = R;
			J = C+1;
		}
		else if((R+1<=7) && (M[R+1][C] == 1)){
			I = R + 1;
			J = C;
		}
		else if((R+1 <= 7) && (M[R][C-1] == 1)){
			I = R;
			J = C-1;
		}
		else{
			M[I][J] = -1;
			C = -1;
			R = -1;
			pos = (POS)linked_stack_pop(stack);
			linked_stack_print2(stack, M);
		}
		if(I != -1 || J != -1){
			M[I][J] = 2;
			pos =(POS)linked_stack_pop(stack);
			pos->R = I;
			pos->C = J;
			linked_stack_push(stack, pos);
			linked_stack_print2(stack, M);
		}
		pos = (POS)stack->head->data;
		R = pos->R;
		C = pos->C;
	}while((R!=0) && (C!=0) && (R!=7) && (C != 7));
	while(stack->head != NULL){
		pos = linked_stack_pop(stack);
		printf("%d,%d", pos->R, pos->C);

	}
}

int main(){
	solve_maze();

	return 0;
}
