/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
    int key;
    struct Node* link;
} listNode;

typedef struct Head {
    struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
    char command;
    int key;
    headNode* headnode=NULL;

    do{
		printf("2019038090 -----------------------이성규-------------------------\n");
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

        switch(command) {
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

    }while(command != 'q' && command != 'Q');

    return 1;
}

headNode* initialize(headNode* h) {

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if(h != NULL)
        freeList(h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode* h){
    /* h와 연결된 listNode 메모리 해제
     * headNode도 해제되어야 함.
     */
    listNode* p = h->first;

    listNode* prev = NULL;
    while(p != NULL) {
        prev = p;
        p = p->link;
        free(prev);
    }
    free(h);
    return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) 
{

    listNode* node = (listNode*)malloc(sizeof(listNode));  //node를 동적할당해서 만들어준다.
    
	node->key = key;     //노드의 키값에 입력받았던 키를 넣는다.
	node->link = h->first; // 노드가 맨앞을 가리키는 포인터에 담긴 노드를 가리키게한다.
    h->first = node; // 맨앞을 가리키는 포인터가 노드를 가리키도록 바꾼다.

    return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) 
{


	listNode*pre_node = (listNode*)malloc(sizeof(listNode));
	listNode*node = (listNode*)malloc(sizeof(listNode));
	node->key = key;  //노드의 키값에 입력받았던 키를 넣는다.
	pre_node = h->first; // pre_node가 맨 앞을 가리키는 포인터를 가리키도록 바꾼다.

	if (h->first == NULL)  //첫번째 노드가 NULL이면 insertFirst함수를 불러온다.
	{
		insertFirst(h, key); 
	}
	else if (pre_node == NULL)     //pre_node가 NULL이면 맨앞을 가리키는 포인터가 노드를 가리키도록 바꾼다.
	{
		h->first = node; 
	}

	else							//그렇지 않다면 노드가 pre_node를 가리키도록 하고 pre_node가 노드를 가리키도록 바꾼다.
	{ 
		node->link = pre_node->link;
		pre_node->link = node;
	}
	

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) 
{
	listNode *node = (listNode*)malloc(sizeof(listNode));
	listNode *last = (listNode*)malloc(sizeof(listNode));

	node->key = key; //노드의 키값에 입력받았던 키를 넣는다.
	last = h->first;// last가 맨 앞을 가리키는 포인터를 가리키도록 바꾼다.

	if (h->first == NULL)    //맨 앞을 가리키는 포인터가 NULL이면 insertFirst함수를 불러온다.
	{
		insertFirst(h, key);    

	}
	else if (last->link == NULL)   //last노드가 가리키는게 NULL이면 node가 last를 가리키도록 하고 last가 노드를 가리키도록 바꾼다.
	{
		node->link = last->link;
		last->link = node;
	}


	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) 
{

	listNode *node = (listNode*)malloc(sizeof(listNode));

	node = h->first; //노드에 맨 앞을 가리키는 포인터를 가리키도록 바꾼다.
	h->first = node->link; //새로운 노드가 첫번째 노드로 바뀌게된다.

	free(node); //노드 메모리를 해제해준다.


	return 0;
}



/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) 
{

	listNode *node = (listNode*)malloc(sizeof(listNode));
	listNode *pre_node = (listNode*)malloc(sizeof(listNode));
	pre_node = h->first;   //pre_node가 맨 앞을 가리키는 포인터를 가리키도록 바꾼다.
	node = pre_node->link; // node가 pre_node가 가리키는 곳으로 바꾼다.
	if (h->first->key == NULL)   // 맨 앞의 포인터가 가리키는 키값이 NULL이면 아래의 문장을 출력한다.
	{
		printf("리스트에 아무것도 없습니다.\n");
		return 0;
	}
	
	while(1)
	{
		if (key == h->first->key) // key값이 맨 앞의 포인터가 가리키는 키값과 같다면 deleteFirst 함수를 불러온다.
		{
			deleteFirst(h);
			break;
		}
		else if ((key == node->key) && (node->link == NULL)) //key값이 node의 key값과 같고 node가 가리키는 것이 NULL이면 deleteLast함수를 불러온다.
		{
			deleteLast(h);
			break;
		}
		else if (key == node->key)  //key값이 node의 ker값과 같다면 pre_node가 가리키는 것이 node가 가리키는 곳으로 바꾸고 node를 해제해준다.
		{
			pre_node->link = node->link;
			free(node);
			break;
		}
		else if ((key != node->key) && (node->link == NULL))  //key값이 node의 key값과 다르고 node가 가리키는 것이 NULL이면 아래의 문장을 실행한다.
		{
			printf("데이터값이 존재하지 않습니다\n.");
			break;
		}
		pre_node = pre_node->link; //pre_node는 pre_node가 가리키는 곳으로 바꾼다.
		node = pre_node->link; // node는 pre_node가 가리키는 곳으로 바꾼다.
	}

    return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h)
{
	listNode *node = (listNode*)malloc(sizeof(listNode));
	listNode *pre_node = (listNode*)malloc(sizeof(listNode));

	pre_node = h->first; //pre_node가 맨 앞을 가리키는 포인터를 가리키도록 바꾼다.
	node = pre_node->link; // node가 pre-node가 가리키는 곳을 가리키도록 바꾼다.

	while(1)
	{
	if (node->link == NULL) //node가 가리키는 곳이 NULL일 때 pre_node가 가리키는 곳이 NULL이면 node를 해제한다.
	{
		pre_node->link = NULL;
		free(node);
		break;
	}
	 
		pre_node = pre_node->link; //pre_node가 pre_node가 가리키는 곳으로 바꾼다.
		node = pre_node->link; // node를 pre_node가 가키리는 곳으로 바꾼다.
	}


    return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode *a = (listNode*)malloc(sizeof(listNode));
	listNode *b = (listNode*)malloc(sizeof(listNode));
	listNode *c = (listNode*)malloc(sizeof(listNode));
	//역순으로 배치하기위해서 새로운 포인터변수3개를 선언해준다.

	a = h->first;   //포인터 a를 첫 번째 노드에 설정한다.
	b = NULL;
	c = NULL;

	while (a != NULL)   /*리스트 첫 번째 노드로부터 링트를 따라 다음 노드로 이동하면서 노드간의 연결을 바꾸는 함수이다.*/
	{
		c = b;
		b = a;
		a = a->link;
		b->link = c;
	}
	h->first = b;

    return 0;
}


void printList(headNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if(h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while(p != NULL) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }

    printf("  items = %d\n", i);
}