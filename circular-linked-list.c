/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� */

typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;



/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
    char command;
    int key;
    listNode* headnode = NULL;

    do {
        printf("-----------2019038090---------------------�̼��� ----------------\n");
        printf("----------------------------------------------------------------\n");
        printf("                  Doubly Circular Linked List                   \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            initialize(&headnode);
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


int initialize(listNode** h) {

    /* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
    if (*h != NULL)
        freeList(*h);

    /* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {

    listNode* node = h->rlink;
    listNode* prev = NULL;

    if (h->rlink == h)
    {
        free(h);
        return 0;
    }

    while (node != NULL)
    {
        prev = node;
        node = node->rlink;
        free(prev);
    }

    free(h);

    return 0;

}



void printList(listNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if (h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->rlink;

    while (p != NULL && p != h) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }
    printf("  items = %d\n", i);


    /* print addresses */
    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

    i = 0;
    p = h->rlink;
    while (p != NULL && p != h) {
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
        p = p->rlink;
        i++;
    }

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {



    if (h->rlink == h)   //h->rlink�� h�� ����ų�� �ʱ�ȭ�� ���� ��
    {
        /*insertFirst�Լ� ���� */
        listNode* node = (listNode*)malloc(sizeof(listNode));
        listNode* new = (listNode*)malloc(sizeof(listNode));

        node = h;
        new->key = key;

        new->llink = node;
        new->rlink = node->rlink;
        node->rlink->llink = new;
        node->rlink = new;

        return 1;
    }

    listNode* node = (listNode*)malloc(sizeof(listNode));//��� ��带 ����
    listNode* new = (listNode*)malloc(sizeof(listNode)); //Ű���� ���� ���

    node = h;
    new->key = key;

    new->llink = node->llink;
    new->rlink = node;
    node->llink->rlink = new;
    node->llink = new;
    return 1;
    
    /* �׷��� �������� insertFirst�� ������ ���θ��� ���� �� ��带 �������ִ� �����̱� ������ insertFirst�� ������ �����Ѵ�.*/
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
     
    if (h->rlink == h) //h->rlink�� h�� ����ų�� �ʱ�ȭ�� ���� ��
    {
        printf("���ﰪ�� �����ϴ�.\n");
        return 0;
    }

    listNode* n = h->rlink; 
    listNode* trail = NULL; 

    if (n->rlink == h) { // ������ ����� ���
        h->rlink = h; //h->rlink�� h�� ����Ű�� �ϰ�
        h->llink = h; //h->llink�� h�� ����Ű�� �ϰ�
        n->rlink = NULL; //���� ���ְ�
        n->llink = NULL; //���� ���ְ�
        free(n); //�޸� ������ �ϸ� ���� ��������.
        return 0;
    }

    while (n->rlink != h) { //������ ��尡 �ƴҰ���
        trail = n; //�� ��带 �ϳ��� n�� �����ϰ�
        n = n->rlink; //n->rlink�� ����Ű�� ���� n���� �ű�� 
    }
    // �� ��� n�� �� ������ �ǰ� trail�� �� ������ �ȴ�.

    trail->rlink = h; // trali->rlink�� ����Ű�� ���� h�� �ű��
    h->llink = trail; // h->llink�� ����Ű�� ���� trail�� �ű��
    n->llink = NULL; //���� ���ְ�
    n->rlink = NULL; //���� ���ְ�
    free(n); //�޸� ������ �ϸ� ���� ��������.

    return 1;
}


   

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

    listNode*node= (listNode*)malloc(sizeof(listNode));
    listNode* new = (listNode*)malloc(sizeof(listNode));

    node = h; // node���� �������ش�.
    new->key = key; //������ ��忡 key���� �־��ش�.

    new->llink = node; //���ο� ��带 �����ϸ� new->llink�� node�� �����Ѵ�.
    new->rlink = node->rlink; //new->rlink�� node�� ����Ű�� ������ new->rlink�� node�� ����Ű�� �ȴ�.
    node->rlink->llink = new; //node->rlink->llink�� node->rlink�� node�� ����Ű�� ������ node->llink�� ���� �ǹ̸�  node->llink�� new ���� �����
    node->rlink = new; // node->rlink�� new�� ����ȴ�.
    
     
    return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

    if (h->rlink == h) //h->rlink�� h�� ����ų �� �ʱ�ȭ�� �Ǿ����� �� 
    {
        printf("����� �����ϴ�.");
        return 0;
    }

    listNode* n = h->rlink;

    h->rlink = n->rlink; // ó������ ����Ű�� ���� n->rlink�� �ű��
    n->rlink->llink = h; //n��尡 �� ó���� ���� �ű��
    free(n); //�����ϸ� ù ��尡 �������.

    return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

    if (h->rlink == h) //ó������ null���϶�
    {
        printf("����Ʈ�� ���� ������ �������ּ���.\n");
        return 0;
    }

    listNode* first = (listNode*)malloc(sizeof(listNode));
    listNode* mid = (listNode*)malloc(sizeof(listNode));
    listNode* last = (listNode*)malloc(sizeof(listNode));

    first = h;
    mid = first->llink;

    /* �߰����� �յڸ� �ٲ۴� */
    if (first != h) {
        last = mid;
        mid = first;
        first = first->rlink;
        mid->llink = first;
        mid->rlink = last;
    }

    return 0;
}
 


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

    if ((h->rlink == h) || (h->rlink->key >= key)) {  //����Ʈ�� ���� ���ų� ù��° ��尡 Ű������ Ŭ ��� �Ǿտ� ��带 �����Ѵ�.
        insertFirst(h, key);
        return 0;
    }

    listNode* node = (listNode*)malloc(sizeof(listNode));
    listNode* new = (listNode*)malloc(sizeof(listNode));
    node = h->rlink;
    new->key = key;

    while (node->rlink != h) { // ����Ʈ�� ���� ���� ���

        if (key <= node->rlink->key) {//Ű���� ����� Ű������ ũ�ų� �������
            node->rlink->llink = new;      
            new->rlink = node->rlink;     
            node->rlink = new;            
            new->llink = node;             
            return 0;
        }
       node = node->rlink;
    }

    insertLast(h, key); //������ ����� ���� Ű������ ���� �� �ݺ����� ��������

    return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

    if (h->rlink == h)
    {
        printf("���ﰪ�� �����ϴ�.\n");
        return 0;
    }

    listNode* n = h->rlink;

    while (n != h) { //n�� null���� �ƴϸ�
        if (n->key == key) { //n->key���� key���� ���ٸ�

            deleteFirst(h); //ù��° ��带 ����� �����Ѵ�
            free(n);

            return 0;
        }
        else//�׷��� �ʴٸ�
        {
            deleteLast(h); //������ ��带 ����� �����Ѵ�.
            free(n);
            return 0;

        }

    }

    printf("��忡 �ش��ϴ� Ű���� ã�� �� �����ϴ� = %d\n", key);

    return 1;
}
