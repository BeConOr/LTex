#include <stdio.h>

#define N 5

int main(void){
	int a[N][N];
	int current = 1;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			a[i][j] = current;
			++current;
		}
	}
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			printf("%2d ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}