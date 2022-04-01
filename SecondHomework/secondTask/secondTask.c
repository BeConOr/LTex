#include <stdio.h>

#define N 5

int main(void){
	int a[N];
	printf("Input massive: ");
	for(int i = 0; i < N; ++i){
		a[i] = i+1;
		printf("%d ", a[i]);
	}
	printf("\nReverse massive: ");
	for(int i = N-1; i >= 0; --i){
		printf("%d ", a[i]);
	}
	return 0;
}