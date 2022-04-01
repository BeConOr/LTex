#include <stdio.h>

int main(void){
	int a = 0x00CCAABB;
	for(int i = 0; i < 4; ++i){
		printf("Byte #%d of a: %x\n", i+1, ((a >> (i << 3)) & 0x000000FF));
	}
	a = (a & 0xFF00FFFF) | 0x00DD0000;
	printf("New a: 0x%x\n", a);
}