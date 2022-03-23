#include <stdio.h>

#define N 5

int main(void){
	int a[N][N];
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			if(j >= (N-1-i)){
				a[i][j] = 1;
			}
			else{
				a[i][j] = 0;
			}
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