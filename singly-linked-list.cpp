/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
    int key;
    struct Node* link;
} listNode;

typedef struct Head {
    struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
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
		printf("2019038090 -----------------------�̼���-------------------------\n");
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

    /* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
    if(h != NULL)
        freeList(h);

    /* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode* h){
    /* h�� ����� listNode �޸� ����
     * headNode�� �����Ǿ�� ��.
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
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) 
{

    listNode* node = (listNode*)malloc(sizeof(listNode));  //node�� �����Ҵ��ؼ� ������ش�.
    
	node->key = key;     //����� Ű���� �Է¹޾Ҵ� Ű�� �ִ´�.
	node->link = h->first; // ��尡 �Ǿ��� ����Ű�� �����Ϳ� ��� ��带 ����Ű���Ѵ�.
    h->first = node; // �Ǿ��� ����Ű�� �����Ͱ� ��带 ����Ű���� �ٲ۴�.

    return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) 
{


	listNode*pre_node = (listNode*)malloc(sizeof(listNode));
	listNode*node = (listNode*)malloc(sizeof(listNode));
	node->key = key;  //����� Ű���� �Է¹޾Ҵ� Ű�� �ִ´�.
	pre_node = h->first; // pre_node�� �� ���� ����Ű�� �����͸� ����Ű���� �ٲ۴�.

	if (h->first == NULL)  //ù��° ��尡 NULL�̸� insertFirst�Լ��� �ҷ��´�.
	{
		insertFirst(h, key); 
	}
	else if (pre_node == NULL)     //pre_node�� NULL�̸� �Ǿ��� ����Ű�� �����Ͱ� ��带 ����Ű���� �ٲ۴�.
	{
		h->first = node; 
	}

	else							//�׷��� �ʴٸ� ��尡 pre_node�� ����Ű���� �ϰ� pre_node�� ��带 ����Ű���� �ٲ۴�.
	{ 
		node->link = pre_node->link;
		pre_node->link = node;
	}
	

	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) 
{
	listNode *node = (listNode*)malloc(sizeof(listNode));
	listNode *last = (listNode*)malloc(sizeof(listNode));

	node->key = key; //����� Ű���� �Է¹޾Ҵ� Ű�� �ִ´�.
	last = h->first;// last�� �� ���� ����Ű�� �����͸� ����Ű���� �ٲ۴�.

	if (h->first == NULL)    //�� ���� ����Ű�� �����Ͱ� NULL�̸� insertFirst�Լ��� �ҷ��´�.
	{
		insertFirst(h, key);    

	}
	else if (last->link == NULL)   //last��尡 ����Ű�°� NULL�̸� node�� last�� ����Ű���� �ϰ� last�� ��带 ����Ű���� �ٲ۴�.
	{
		node->link = last->link;
		last->link = node;
	}


	return 0;
}
/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) 
{

	listNode *node = (listNode*)malloc(sizeof(listNode));

	node = h->first; //��忡 �� ���� ����Ű�� �����͸� ����Ű���� �ٲ۴�.
	h->first = node->link; //���ο� ��尡 ù��° ���� �ٲ�Եȴ�.

	free(node); //��� �޸𸮸� �������ش�.


	return 0;
}



/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) 
{

	listNode *node = (listNode*)malloc(sizeof(listNode));
	listNode *pre_node = (listNode*)malloc(sizeof(listNode));
	pre_node = h->first;   //pre_node�� �� ���� ����Ű�� �����͸� ����Ű���� �ٲ۴�.
	node = pre_node->link; // node�� pre_node�� ����Ű�� ������ �ٲ۴�.
	if (h->first->key == NULL)   // �� ���� �����Ͱ� ����Ű�� Ű���� NULL�̸� �Ʒ��� ������ ����Ѵ�.
	{
		printf("����Ʈ�� �ƹ��͵� �����ϴ�.\n");
		return 0;
	}
	
	while(1)
	{
		if (key == h->first->key) // key���� �� ���� �����Ͱ� ����Ű�� Ű���� ���ٸ� deleteFirst �Լ��� �ҷ��´�.
		{
			deleteFirst(h);
			break;
		}
		else if ((key == node->key) && (node->link == NULL)) //key���� node�� key���� ���� node�� ����Ű�� ���� NULL�̸� deleteLast�Լ��� �ҷ��´�.
		{
			deleteLast(h);
			break;
		}
		else if (key == node->key)  //key���� node�� ker���� ���ٸ� pre_node�� ����Ű�� ���� node�� ����Ű�� ������ �ٲٰ� node�� �������ش�.
		{
			pre_node->link = node->link;
			free(node);
			break;
		}
		else if ((key != node->key) && (node->link == NULL))  //key���� node�� key���� �ٸ��� node�� ����Ű�� ���� NULL�̸� �Ʒ��� ������ �����Ѵ�.
		{
			printf("�����Ͱ��� �������� �ʽ��ϴ�\n.");
			break;
		}
		pre_node = pre_node->link; //pre_node�� pre_node�� ����Ű�� ������ �ٲ۴�.
		node = pre_node->link; // node�� pre_node�� ����Ű�� ������ �ٲ۴�.
	}

    return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h)
{
	listNode *node = (listNode*)malloc(sizeof(listNode));
	listNode *pre_node = (listNode*)malloc(sizeof(listNode));

	pre_node = h->first; //pre_node�� �� ���� ����Ű�� �����͸� ����Ű���� �ٲ۴�.
	node = pre_node->link; // node�� pre-node�� ����Ű�� ���� ����Ű���� �ٲ۴�.

	while(1)
	{
	if (node->link == NULL) //node�� ����Ű�� ���� NULL�� �� pre_node�� ����Ű�� ���� NULL�̸� node�� �����Ѵ�.
	{
		pre_node->link = NULL;
		free(node);
		break;
	}
	 
		pre_node = pre_node->link; //pre_node�� pre_node�� ����Ű�� ������ �ٲ۴�.
		node = pre_node->link; // node�� pre_node�� ��Ű���� ������ �ٲ۴�.
	}


    return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	listNode *a = (listNode*)malloc(sizeof(listNode));
	listNode *b = (listNode*)malloc(sizeof(listNode));
	listNode *c = (listNode*)malloc(sizeof(listNode));
	//�������� ��ġ�ϱ����ؼ� ���ο� �����ͺ���3���� �������ش�.

	a = h->first;   //������ a�� ù ��° ��忡 �����Ѵ�.
	b = NULL;
	c = NULL;

	while (a != NULL)   /*����Ʈ ù ��° ���κ��� ��Ʈ�� ���� ���� ���� �̵��ϸ鼭 ��尣�� ������ �ٲٴ� �Լ��̴�.*/
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