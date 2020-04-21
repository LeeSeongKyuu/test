#include <stdio.h>
#include <stdlib.h>

void main(){

    int list[5]; //배열의 크기가 5인 list라는 배열을 선언한다.
    int *plist[5]; // 배열의 크기가 5인 plist라는 포인터배열을 선언한다.

    list[0] = 10; // lsit[0]에 10을 대입한다.
    list[1] = 11; // lsit[1]에 11을 대입한다.

    plist[0] = (int*)malloc(sizeof(int)); 
//plist[0]에 malloc을 통해서 int만큼의 사이즈를 heap영역에서 받아서 주소를 넘겨준다. 동적할당

    printf("[----- [이성규] [2019038090] -----]\n");
    printf("list[0] \t= %d\n", list[0]); // list[0]의 값을 출력한다.
    printf("address of list \t= %p\n", list); // list의 주소값을 출력한다.
    printf("address of list[0]  \t= %p\n",&list[0]); 
//list[0]의 주소값을 출력한다.
    printf("address of list + 0 \t= %p\n",list+0); 
//list+0의 주소값을 출력한다. 
    printf("address of list + 1 \t= %p\n",list+1); 
//list+1의 주소값을 출력한다. 이때 list+1는 list[1]를 의미한다.
    printf("address of list + 2 \t= %p\n",list+2); 
//list+2의 주소값을 출력한다. 이때 list+2는 list[2]를 의미한다.
    printf("address of list + 3 \t= %p\n",list+3); 
//list+3의 주소값을 출력한다. 이때 list+3는 list[3]를 의미한다.
    printf("address of list + 4 \t= %p\n",list+4); 
//list+4의 주소값을 출력한다. 이때 list+4는 list[4]를 의미한다.
    printf("address of list[4] \t= %p\n",&list[4]); 
//list[4]의 주소값을 출력한다. 

    free(plist[0]);  // plist[0]의 동적할당을 해제해준다.
    

}
