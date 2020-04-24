#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;     //typedef를 사용해 char를 별칭 element로 정의한다. 
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;   //typedef를 사용해 구조체의 별칭을 QueueType으로 정의한다.


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;

	printf("201908390 ------ 이성규\n");

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;  //Queue를 가리키는 포인터 cQ를 선언한다.
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ에 동적메모리 할당을 한다.
	cQ->front = 0; //front의 초기값을 0으로한다.
	cQ->rear = 0; //rear의 초기값을 0으로한다.
	return cQ; // cQ값을 반환한다. 
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)   //원형큐가가 비어있는지 확인하는 함수를 구현한다.
{
	if (cQ->front == cQ->rear)   //front 값과 rear값이 같으면 안내문을 출력하고 1을 리턴한다.
	{
		printf("Queue가 비어있습니다.\n");
		return 1;
	}
	else
		return 0;
}

/* complete the function */
int isFull(QueueType *cQ)   //원형큐가 함수가 가득 찼는지 검사하는 함수를 구현한다.
{
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front)
	{
		printf("\n Queue가 가득 찼습니다.\n");
		return 1;
		//rear값을 증가시키고 모듈 연산을 한 다음 front와 같으면 원형큐가 가득 찬 상태이면 안내문을 출력하고 1을 리턴한다.

	}
	else

		return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)  //원형큐에 rear원소를 삽입하는 함수이다.
{
	if (isFull(cQ)) return;  //원형큐가 포화상태이면 원소를 삽입하는 것을 중단한다.
	

	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //나머지연산자를 이용해서 rear의 값을 조정한다.
		cQ->queue[cQ->rear] = item; //cQ[rear]에 원소 item을 삽입한다.
	}

	
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{

	if (isEmpty(cQ)) exit(1);
	

	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->front];
	}
}


void printQ(QueueType *cQ)  //현재 원형큐의 상태를 보여주는 함수이다.
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //원형큐안의 값들을 보여주는 함수이다.
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

