#include <stdio.h>

int main(void){
	struct test{
		char a;
		int b;
	};
	
	struct testPack{
		char a;
		int b;
	}__attribute__((packed));
	
	char str[10] = {'A',0,0,0,0,'B',0,0,0,0};
	struct test* ptr1 = (struct test*) str;
	struct testPack* ptr2 = (struct testPack*) str;
	printf("Massiv of packed struct:\n");
	for(int i = 0; i < 2; ++i){
		printf("Element #%d: a = %c, b = %d\n", i+1, (ptr2+i)->a, (ptr2+i)->b);
	}
	
	printf("Massiv of unpacked struct:\n");
	for(int i = 0; i < 2; ++i){
		printf("Element #%d: a = %c, b = %d\n", i+1, (ptr1+i)->a, (ptr1+i)->b);
	}
}