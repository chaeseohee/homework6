/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node
{
	int key;
	struct Node *link;
} listNode;

typedef struct Head
{
	struct Node *first;
} headNode;

/* 함수 리스트 */
headNode *initialize(headNode *h);
int freeList(headNode *h);

int insertFirst(headNode *h, int key);
int insertNode(headNode *h, int key);
int insertLast(headNode *h, int key);

int deleteFirst(headNode *h);
int deleteNode(headNode *h, int key);
int deleteLast(headNode *h);
int invertList(headNode *h);

void printList(headNode *h);

int main()
{
	char command;
	int key;
	headNode *headnode = NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command){
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode *initialize(headNode *h)
{
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode *temp = (headNode *)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode *h)
{
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode *p = h->first; // listNode포인터 p가 첫번째 노드를 가리키도록 하고
	listNode *prev = NULL;	// listNode포인터 prev는 NULL로 초기화

	while (p != NULL) // p가 NULL일 때까지 (이어진 노드가 없을 때까지) 반복
	{
		prev = p;	 // prev에 p와 같은 값을 대입
		p = p->link; // p는 다음 노드를 가리키도록 함
		free(prev);	 // prev가 가리키는 노드의 메모리 해제
	}
	free(h); // headNode의 메모리도 해제
	return 0;
}

/*
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode *h, int key)
{
	listNode *node = (listNode *)malloc(sizeof(listNode)); // 추가할 노드의 메모리를 할당
	node->key = key; // 추가할 노드의 멤버 key에 main()에서 입력받은 key값을 대입

	node->link = h->first; // 추가할 노드의 link값에 headNode의 first값(headNode가 가리키고 있던 노드의 주소)를 대입
	h->first = node; // headNode의 first값에는 Node를 대입(headNode가 추가할 노드를 가리키게 함)

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode)); // 추가할 노드의 메모리를 할당
	node->key = key; // 추가할 노드의 멤버 key에 main()에서 입력받은 key값을 대입
	node->link = NULL; // 추가할 노드의 멤버 link를 NULL로 초기화

	if (h->first == NULL){ // headNode의 first값이 NULL이면(headNode가 아무노드도 가리키고 있지 않으면)
		h->first = node; // headNode의 first의 값에 node의 값을 대입(headNode가 node를 가리키게 함)
		return 0;
	}

	listNode *n = h->first; 
	listNode *trail = h->first; 

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL){ 
		if (n->key >= key){ /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->first){ 
				h->first = node; //headNode의 first가 node를 가리키게 하고
				node->link = n; //node의 link에 n의 값을 대입
			}
			else{ /* 중간이거나 마지막인 경우 */
				node->link = n; //node의 link에 n의 값을 대입하고
				trail->link = node; //trail이 가리키는 노드의 link가 node를 가리키게 함
			}
			return 0;
		}
		trail = n; 
		n = n->link;
	}
	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; //trail이 가리키는노드의 link가 node를 가리키게 함
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode *h, int key)
{
	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode *n = h->first;
	while (n->link != NULL)
	{
		n = n->link;
	}
	n->link = node;
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode *h, int key)
{

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL)
	{
		if (n->key == key)
		{
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->first)
			{
				h->first = n->link;
			}
			else
			{ /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode *h)
{

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if (n->link == NULL)
	{
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while (n->link != NULL)
	{
		trail = n;
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode *h)
{

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode *n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode *h)
{

	if (h->first == NULL)
	{
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while (n != NULL)
	{
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}

void printList(headNode *h)
{
	int i = 0;
	listNode *p;

	printf("\n---PRINT\n");

	if (h == NULL)
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL)
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}