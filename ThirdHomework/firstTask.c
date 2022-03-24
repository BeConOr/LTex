#include <stdio.h>

int main(void){
	int a = 0x00CCAABB;
	int* p = &a;
	for(int i = 0; i < sizeof(int); ++i){
		printf("byte #%d of a: %hhx\n", (i+1), *((char*)p+i));
	}
	*((char*)p+2) = 0xDD;
	printf("new a: 0x%x\n", a);
	return 0;
}