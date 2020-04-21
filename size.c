#include<stdio.h>
#include<stdlib.h>

void main()
{

        int **x;

        printf("[----- [이성규] [2019038090] -----]\n");
        printf("sizeof(x) = %lu\n", sizeof(x)); 
// vscode machine은 32bit이고 주소를 저장하기 때문에  4byte가 나온다.
        printf("sizeof(*x) = %lu\n", sizeof(*x)); 
// *x또한 주소를 저장하기 때문에 4byte가 나온다.
        printf("sizeof(**x) = %lu\n", sizeof(**x)); 
// **x는 두번 참조해서 간 곳에서는 integer로 저장하기 때문에 4byte가 나온다.
}
