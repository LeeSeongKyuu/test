/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE            13    /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

 /* 필요에 따라 함수 추가 가능 */
int initialize(int** a);
int freeArray(int* a);
void printArray(int* a);

int selectionSort(int* a);
int insertionSort(int* a);
int bubbleSort(int* a);
int shellSort(int* a);
/* recursive function으로 구현 */
int quickSort(int* a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int* a, int** ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int* ht, int key);


int main()
{
    char command;
    int* array = NULL;
    int* hashtable = NULL;
    int key = -1;
    int index = -1;

    srand(time(NULL));

    do {
        printf("----------------------------------2019308090 이성규-------------\n");
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            initialize(&array);
            break;
        case 'q': case 'Q':
            freeArray(array);
            break;
        case 's': case 'S':
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);
            break;
        case 'b': case 'B':
            bubbleSort(array);
            break;
        case 'l': case 'L':
            shellSort(array);
            break;
        case 'k': case 'K':
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            quickSort(array, MAX_ARRAY_SIZE);
            printf("----------------------------------------------------------------\n");
            printArray(array);

            break;

        case 'h': case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;

        case 'e': case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            break;

        case 'p': case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initialize(int** a)
{
    int* temp = NULL;

    /* array가 NULL인 경우 메모리 할당 */
    if (*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    }
    else
        temp = *a;

    /* 랜덤값을 배열의 값으로 저장 */
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int* a)
{
    if (a != NULL) //a가 NULL이 아니면 메모리 해제를 해준다.
        free(a);
    return 0;
}

void printArray(int* a)
{
    if (a == NULL) {
        printf("nothing to print.\n");
        return;
    }
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("a[%02d] ", i);
    printf("\n");
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("%5d ", a[i]);
    printf("\n");
}


int selectionSort(int* a) { //선택 정렬에 관한 함수이다.
    int min;
    int minindex;
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i; //minidex값을 i로 설정한다.
        min = a[i];  // 최소값을 배열의 원소 하나씩 설정한다. (처음에는 배열의 첫번째 원소)
        for (j = i + 1; j < MAX_ARRAY_SIZE; j++)  //마지막 숫자는 자동으로 정렬되기 때문에 1개를 뺴준다.
        {
            if (min > a[j]) // 그 다음부터 비교를 해서 뒤에 있는 것중 가장 작은 값과 바꿔준다. 최솟값을 탐색한다.
            { 
                min = a[j]; 
                minindex = j; 
            }
        }
        a[minindex] = a[i]; 
        a[i] = min;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);
    return 0;
}

int insertionSort(int* a) //삽입 정렬에 관한 함수이다.
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 1; i < MAX_ARRAY_SIZE; i++){
    {
        t = a[i]; //t에 배열의 원소값을 넣어준다.(두번째 배열의 원소부터 시작)
        j = i;
        while (a[j - 1] > t && j > 0) //현재 정렬된 배열은 i-1까지 이므로 i-1번째부터 역순으로 조사한다.        
            a[j] = a[j - 1]; //조건을 만족하면 값을 바꿔준다.(큰값이 앞에 있는 경우)
            j--; //다음으로 넘어가기 위해 j값을 1빼준다.
        }
        a[j] = t; 
    } 

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int bubbleSort(int* a) //버블정렬을 하는 함수이다.
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 1; i < MAX_ARRAY_SIZE; i++) 
    {
        for (j = 1; j < MAX_ARRAY_SIZE; j++)
        {
            if (a[j - 1] > a[j]) //첫 원소부터 시작해서 원소번호가 큰 것이 더 작으면 서로 자리를 바꾸는 연산을 반복한다.
            {
                t = a[j - 1];
                a[j - 1] = a[j];
                a[j] = t;
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int shellSort(int* a) //셀 정렬을 하는 함수를 구현했다.
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2) //초기 값은 배열의 크기를 2로 나눈 값을 사용하며 각 단계 별로 2씩 나눠간다.
    {
        for (i = 0; i < h; i++)
        {
            for (j = i + h; j < MAX_ARRAY_SIZE; j += h)
            {
                v = a[j];
                k = j;
                while (k > h - 1 && a[k - h] > v)//부분 리스트를 삽입 정렬을 이용해서 정렬한다.
                {
                    a[k] = a[k - h];
                    k -= h;
                }
                a[k] = v;
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int quickSort(int* a, int n)
{
    int v, t;
    int i, j;

    if (n > 1) //퀵정렬을 하기위한 기본설정이다.
    {
        v = a[n - 1];
        i = -1;
        j = n - 1;

        while (1)
        {
            while (a[++i] < v); //pivot보다 작은 배열을 찾는 것이다(왼쪽->오른쪽)
            while (a[--j] > v); //pivot보다 큰 배열을 찾는 것이다(오른쪽->왼쪽)

            if (i >= j) break; //i가 j보다 크거나 같으면 
            t = a[i];           // a[i]와 a[j]의 값을 바꾼다.
            a[i] = a[j];
            a[j] = t;
        }
        t = a[i]; //a[i]와 a[n-1]의 값을 바꾼다.
        a[i] = a[n - 1];
        a[n - 1] = t;

        quickSort(a, i);
        quickSort(a + i + 1, n - i - 1);
    }


    return 0;
}

int hashCode(int key) {
    return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int* a, int** ht)
{
    int* hashtable = NULL;

    /* hash table이 NULL인 경우 메모리 할당 */
    if (*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    }
    else {
        hashtable = *ht;    /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
    }

    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;

    /*
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        printf("hashtable[%d] = %d\n", i, hashtable[i]);
    */

    int key = -1;
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key);
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1) 
        {
            hashtable[hashcode] = key;
        }
        else {

            index = hashcode;

            while (hashtable[index] != -1)
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key;
        }
    }

    return 0;
}

int search(int* ht, int key)
{
    int index = hashCode(key);

    if (ht[index] == key)
        return index;

    while (ht[++index] != key)
    {
        index = index % MAX_HASH_TABLE_SIZE;
    }
    return index;
}