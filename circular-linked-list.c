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
 /* 필요한 헤더파일 추가 */

typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;



/* 함수 리스트 */
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
        printf("-----------2019038090---------------------이성규 ----------------\n");
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

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

/* 메모리 해제 */
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {



    if (h->rlink == h)   //h->rlink가 h를 가리킬때 초기화만 했을 때
    {
        /*insertFirst함수 구현 */
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

    listNode* node = (listNode*)malloc(sizeof(listNode));//헤더 노드를 복사
    listNode* new = (listNode*)malloc(sizeof(listNode)); //키값을 가진 노드

    node = h;
    new->key = key;

    new->llink = node->llink;
    new->rlink = node;
    node->llink->rlink = new;
    node->llink = new;
    return 1;
    
    /* 그렇지 않을때는 insertFirst의 개념이 새로만든 노드와 앞 노드를 연결해주는 개념이기 때문에 insertFirst의 개념을 적용한다.*/
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
     
    if (h->rlink == h) //h->rlink가 h를 가리킬때 초기화만 했을 때
    {
        printf("지울값이 없습니다.\n");
        return 0;
    }

    listNode* n = h->rlink; 
    listNode* trail = NULL; 

    if (n->rlink == h) { // 마지막 노드일 경우
        h->rlink = h; //h->rlink가 h를 가리키게 하고
        h->llink = h; //h->llink가 h를 가리키게 하고
        n->rlink = NULL; //값을 없애고
        n->llink = NULL; //값을 없애고
        free(n); //메모리 해제를 하면 값이 없어진다.
        return 0;
    }

    while (n->rlink != h) { //마지막 노드가 아닐경우는
        trail = n; //빈 노드를 하나를 n과 같게하고
        n = n->rlink; //n->rlink가 가리키는 것을 n으로 옮기고 
    }
    // 이 경우 n이 맨 끝값이 되고 trail은 그 전값이 된다.

    trail->rlink = h; // trali->rlink가 가리키는 곳을 h로 옮기고
    h->llink = trail; // h->llink가 가리키는 곳을 trail로 옮기고
    n->llink = NULL; //값을 없애고
    n->rlink = NULL; //값을 없애고
    free(n); //메모리 해제를 하면 값이 없어진다.

    return 1;
}


   

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

    listNode*node= (listNode*)malloc(sizeof(listNode));
    listNode* new = (listNode*)malloc(sizeof(listNode));

    node = h; // node값을 설정해준다.
    new->key = key; //이전의 노드에 key값을 넣어준다.

    new->llink = node; //새로운 노드를 삽입하며 new->llink를 node와 연결한다.
    new->rlink = node->rlink; //new->rlink는 node를 가리키기 때문에 new->rlink는 node를 가리키게 된다.
    node->rlink->llink = new; //node->rlink->llink는 node->rlink가 node를 가리키기 때문에 node->llink와 같은 의미며  node->llink는 new 노드와 연결됨
    node->rlink = new; // node->rlink가 new와 연결된다.
    
     
    return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

    if (h->rlink == h) //h->rlink가 h를 가리킬 때 초기화만 되어있을 때 
    {
        printf("지울게 없습니다.");
        return 0;
    }

    listNode* n = h->rlink;

    h->rlink = n->rlink; // 처음값이 가리키는 값을 n->rlink로 옮기고
    n->rlink->llink = h; //n노드가 를 처음으 노드로 옮기고
    free(n); //해제하면 첫 노드가 사라진다.

    return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

    if (h->rlink == h) //처음값이 null값일때
    {
        printf("리스트에 값이 없으니 삽입해주세요.\n");
        return 0;
    }

    listNode* first = (listNode*)malloc(sizeof(listNode));
    listNode* mid = (listNode*)malloc(sizeof(listNode));
    listNode* last = (listNode*)malloc(sizeof(listNode));

    first = h;
    mid = first->llink;

    /* 중간값의 앞뒤를 바꾼다 */
    if (first != h) {
        last = mid;
        mid = first;
        first = first->rlink;
        mid->llink = first;
        mid->rlink = last;
    }

    return 0;
}
 


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

    if ((h->rlink == h) || (h->rlink->key >= key)) {  //리스트에 값이 없거나 첫번째 노드가 키값보다 클 경우 맨앞에 노드를 삽입한다.
        insertFirst(h, key);
        return 0;
    }

    listNode* node = (listNode*)malloc(sizeof(listNode));
    listNode* new = (listNode*)malloc(sizeof(listNode));
    node = h->rlink;
    new->key = key;

    while (node->rlink != h) { // 리스트의 값이 있을 경우

        if (key <= node->rlink->key) {//키값이 노드의 키값보다 크거나 같을경우
            node->rlink->llink = new;      
            new->rlink = node->rlink;     
            node->rlink = new;            
            new->llink = node;             
            return 0;
        }
       node = node->rlink;
    }

    insertLast(h, key); //마지막 노드의 값이 키값보다 작을 때 반복문을 빠져나옴

    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

    if (h->rlink == h)
    {
        printf("지울값이 없습니다.\n");
        return 0;
    }

    listNode* n = h->rlink;

    while (n != h) { //n이 null값이 아니면
        if (n->key == key) { //n->key값이 key값과 같다면

            deleteFirst(h); //첫번째 노드를 지우고 해제한다
            free(n);

            return 0;
        }
        else//그렇지 않다면
        {
            deleteLast(h); //마지막 노드를 지우고 해제한다.
            free(n);
            return 0;

        }

    }

    printf("노드에 해당하는 키값을 찾을 수 없습니다 = %d\n", key);

    return 1;
}
