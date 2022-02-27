#include<stdio.h>
#include<stdlib.h>

// ���׽��� ����Ʈ ��� ����
typedef struct Node {
	int coef;	// ���
	int expo;	// ����
	struct Node* link;
}Node;

typedef struct ListHead {
	Node* head;
}ListHead;

// ���� ���׽� ����Ʈ ���� ����
ListHead* createLinkedList(void) {
	ListHead* L;
	L = (ListHead*)malloc(sizeof(ListHead));
	L->head = NULL;
	return L;
}

// ���׽� ����Ʈ�� ������ ��� ����
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

// �� ���׽��� ���� ���ϴ� ����
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

// �� ���׽��� ���� ����
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

// ���׽� ����Ʈ ���
void printPoly(ListHead* L) {
	Node* p = L->head;
	for (; p; p = p->link) {
		printf("%3.0dx^%d", p->coef, p->expo);
	}
}

int main(void) {
	// ����Ʈ ����
	ListHead *A, *B, *Add, *Sub;
	// ���� ���׽� ����Ʈ A, B, C ����
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