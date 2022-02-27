#include<stdio.h>
#include<stdlib.h>

// 다항식의 리스트 노드 정리
typedef struct Node {
	int coef;	// 계수
	int expo;	// 지수
	struct Node* link;
}Node;

typedef struct ListHead {
	Node* head;
}ListHead;

// 공백 다항식 리스트 생성 연산
ListHead* createLinkedList(void) {
	ListHead* L;
	L = (ListHead*)malloc(sizeof(ListHead));
	L->head = NULL;
	return L;
}

// 다항식 리스트에 마지막 노드 연산
void addListNode(ListHead* L, int coef, int expo) {
	Node* newNode;
	Node* p;
	newNode = (Node*)malloc(sizeof(Node));
	newNode->coef = coef;
	newNode->expo = expo;
	newNode->link = NULL;
	if (L->head == NULL) {
		L->head = newNode;
		return;
	}
	else {
		p = L->head;
		while (p->link != NULL) {
			p = p->link;
		}
		p->link = newNode;
	}
}

// 두 다항식의 합을 구하는 연산
void addPoly(ListHead* A, ListHead* B, ListHead* C) {
	Node* pA = A->head;
	Node* pB = B->head;
	int sum;

	while (pA && pB) {
		if (pA->expo == pB->expo) {
			sum = pA->coef + pB->coef;
			addListNode(C, sum, pA->expo);
			pA = pA->link;
			pB = pB->link;
		}
		else if (pA->expo > pB->expo) {
			addListNode(C, pA->coef, pA->expo);
			pA = pA->link;
		}
		else {
			addListNode(C, pB->coef, pB->expo);
			pB = pB->link;
		}
	}
	for (; pA!= NULL; pA = pA->link)
		addListNode(C, pA->coef, pA->expo);
	for (; pB != NULL; pB = pB->link)
		addListNode(C, pB->coef, pB->expo);
}

// 두 다항식의 빼기 연산
void subtractPoly(ListHead* A, ListHead* B, ListHead* C) {
	Node* pA = A->head;
	Node* pB = B->head;
	int def = 0;
	int subtract;

	while (pA && pB) {
		if (pA->expo == pB->expo) {
			subtract = pA->coef - pB->coef;
			addListNode(C, subtract, pA->expo);
			pA = pA->link;
			pB = pB->link;
		}
		else if (pA->expo > pB->expo) {
			addListNode(C, pA->coef, pA->expo);
			pA = pA->link;
		}
		else {
			subtract = def - pB->coef;
			addListNode(C, subtract, pB->expo);
			pB = pB->link;
		}
	}
	for (; pA != NULL; pA = pA->link)
		addListNode(C, pA->coef, pA->expo);
	for (; pB != NULL; pB = pB->link)
		addListNode(C, pB->coef, pB->expo);
}

// 다항식 리스트 출력
void printPoly(ListHead* L) {
	Node* p = L->head;
	for (; p; p = p->link) {
		printf("%3.0dx^%d", p->coef, p->expo);
	}
}

int main(void) {
	// 리스트 생성
	ListHead *A, *B, *Add, *Sub;
	// 공백 다항식 리스트 A, B, C 생성
	A = createLinkedList();
	B = createLinkedList();
	Add = createLinkedList();
	Sub = createLinkedList();

	addListNode(A, 3, 14);
	addListNode(A, 2, 8);
	addListNode(A, 1, 0);
	printf("A = ");
	printPoly(A);

	addListNode(B, 8, 14);
	addListNode(B, -3, 10);
	addListNode(B, 10, 6);
	printf("\nB = ");
	printPoly(B);

	addPoly(A, B, Add);
	printf("\nA + B = ");
	printPoly(Add);

	subtractPoly(A, B, Sub);
	printf("\nA - B = ");
	printPoly(Sub);
}