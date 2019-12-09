#include <stdio.h>

void TestFunc(void)
{
	unsigned char b[15r];
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


// 184 65 00 00 00 232 165 02 00 00 195 12 13 14 15 16 116 255 13 00 a

//or 

// 1 2 3 4 5 6 7 8 9 10 11 12 00 16 64 00 a