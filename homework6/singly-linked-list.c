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
		printf("     Singly Linked List [----- [채서희] [2022041084] -----]     \n");
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
				h->first = node; // headNode의 first가 node를 가리키게 하고
				node->link = n; // node의 link에 n의 값을 대입
			}
			else{ /* 중간이거나 마지막인 경우 */
				node->link = n; // node의 link에 n의 값을 대입하고
				trail->link = node; // trail이 가리키는 노드의 link가 node를 가리키게 함
			}
			return 0;
		}
		trail = n; 
		n = n->link;
	}
	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; // trail이 가리키는노드의 link가 node를 가리키게 함
	return 0;
}

/**
 * list의 마지막에 key에 대한 노드하나를 추가
 */
int insertLast(headNode *h, int key)
{
	listNode *node = (listNode *)malloc(sizeof(listNode)); // 추가할 노드의 메모리를 할당
	node->key = key; // 추가할 노드의 멤버 key에 main()에서 입력받은 key값을 대입
	node->link = NULL; // 추가할 노드의 멤버 link를 NULL로 초기화

	if (h->first == NULL){ // headNode의 first가 NULL이면(리스트에 노드가 하나도 없으면)
		h->first = node; // headNode의 first값에 node값을 대입
		return 0;
	}

	listNode *n = h->first; 
	while (n->link != NULL){ // 마지막 노드로 가서(노드의 link가 NULL일 때까지 다음 link로 이동)
		n = n->link;
	}
	n->link = node; // 마지막 노드의 link값에 node값을 대입(마지막 노드가 추가된 노드를 가리키게 함)
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // headNode의 first의 값이 NULL이면(리스트에 노드가 없으면)
	{
		printf("nothing to delete.\n"); // 리스트에 노드가 없다는 안내문구 출력하고
		return 0; // 함수 종료
	}

	listNode* n = h->first; // listNode 포인터 n이 첫번째 노드를 가리키게 하고
	h->first = n->link; // headNode의 first는 두번째노드를 가리키게 함
	free(n); // 첫번째 노드를 가리키고 있는 listNode포인터를 통해 첫번째 노드 해제

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode *h, int key)
{
	if (h->first == NULL) // headNode의 first의 값이 NULL이면(리스트에 노드가 없으면)
	{
		printf("nothing to delete.\n"); // 리스트에 노드가 없다는 안내문구 출력하고
		return 0; // 함수 종료
	}

	listNode *n = h->first; // listNode포인터 n이 첫번째 노드를 가리키게 하고
	listNode *trail = NULL; // listNode포인터 trail은 아무것도 가리키지 않게 함

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL){ 
		if (n->key == key){ // n이 가리키는 노드의 key값이 삭제할 key값과 같으면 
			/* 첫 노드를 삭제해야할 경우 인지 검사 */
			if (n == h->first){ // 첫번째 노드를 삭제할 경우 
				h->first = n->link; //headNode의 first값을 첫번째 노드가 가리키고 있는 곳의 주소로 바꿈
			} 
			else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; //n이 가리키고 있는 노드의 이전노드의 link를(trail의 link를) n이 가리키고 있는 노드의 다음 노드로 바꿈
			}
			free(n); //n이 가리키고 있는 노드의 메모리 해제
			return 0;
		}
		trail = n; // trail에는 n의 값을 대입하고
		n = n->link; // n은 현재가리키고 있는 노드 뒤의 노드를 가리키게 함
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
	if (h->first == NULL) // headNode의 first의 값이 NULL이면(리스트에 노드가 없으면)
	{
		printf("nothing to delete.\n"); // 리스트에 노드가 없다는 안내문구 출력하고
		return 0; // 함수 종료
	}

	listNode *n = h->first; // listNode포인터 n이 첫번째 노드를 가리키게 하고
	listNode *trail = NULL; // listNode포인터 trail은 아무것도 가리키지 않게 함

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if (n->link == NULL){ // 첫번째 노드의 link값이 NULL이면
		h->first = NULL; // headNode의 first값을 NULL로 바꾸고
		free(n); // 첫번째 노드의 메모리를 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while (n->link != NULL){ // n이 가리키는 노드의 link값이 NULL일 때까지
		trail = n; // trail에는 n의 값을 대입
		n = n->link; // n에는 n이 가리키고 있는 노드의 다음 노드의 link값을 대입
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; // n이전의 노드의 link에 NULL대입
	free(n); //n이 가리키고 있는 노드의 메모리 해제

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode *h)
{
	if (h->first == NULL) // headNode의 first의 값이 NULL이면(리스트에 노드가 없으면)
	{ 
		printf("nothing to invert...\n"); // 리스트에 노드가 없다는 안내문구 출력하고
		return 0; // 함수 종료
	}
	listNode *n = h->first; // listNode포인터 n이 첫번째 노드를 가리키게 하고
	listNode *trail = NULL; // listNode포인터 trail은 NULL로 초기화
	listNode *middle = NULL; // listNode포인터 middle도 NULL로 초기화

	while (n != NULL){ // n이 가리키는 노드가 마지막노드일 때까지
		trail = middle; // trail에는 middle값 대입
 		middle = n; // middle에는 n값 대입
		n = n->link; // n에는 다음 노드의 주소 대입
		middle->link = trail; // middle이 가리키고 있는 노드의 link값에는 trail값 대입 
	}

	h->first = middle; // 헤드노드의 first값에는 middle값 대입
	return 0;
}

void printList(headNode *h)
{
	int i = 0;
	listNode *p;

	printf("\n---PRINT\n");

	if (h == NULL){  
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // p가 첫번째 노드를 가리키게 하고

	while (p != NULL){ // p가 마지막 노드를 가리킬 때까지
		printf("[ [%d]=%d ] ", i, p->key); // 노드의 순번과 key값을 출력
		p = p->link; // p가 다음 노드를 가리키게 하고
		i++; // 몇 번째 노드인지 나타내는 변수 i도 1증가시켜줌
	}

	printf("  items = %d\n", i); // 노드의 개수를 출력
}