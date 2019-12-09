#include <stdio.h>

void TestFunc(void)
{
	unsigned char b[10];
	int i, j;

	printf("Address - %p\n", b);

	for(i = 0; scanf("%d", &b[i]) !=0; i++);
	
	for(j = 0; j <= i; j++){
		printf("%d\n", b[j]);
	}

	rewind(stdin);
	getchar();
}

void main(void)
{
	TestFunc();
}

// 1 2 3 4 5 6 7 8 9 10 11 12 03 16 64 00 a

//or 

// 1 2 3 4 5 6 7 8 9 10 11 12 00 16 64 00 a