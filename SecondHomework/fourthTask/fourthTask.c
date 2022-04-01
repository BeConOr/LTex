#include <stdio.h>

#define N 5

int main(void){
	int count = 1;
	int i = 0;
	int leftRow = 0;
	int rightRow = 0;
	int topRow = 0;
	int bottomRow = 0;
	int a[N][N];
	for(;;){
		for(i = leftRow; i < N-rightRow; ++i){
			a[topRow][i] = count;
			++count;
		}
		if(count > N*N) break;
		++topRow;
		for(i = topRow; i < N-bottomRow; ++i){
			a[i][N-rightRow-1] = count;
			++count;
		}
		if(count > N*N) break;
		++rightRow;
		for(i = N-1-rightRow; i >= leftRow; --i){
			a[N-1-bottomRow][i] = count;
			++count;
		}
		if(count > N*N) break;
		++bottomRow;
		for(i = N-bottomRow-1; i >= topRow; --i){
			a[i][leftRow] = count;
			++count;
		}
		if(count > N*N) break;
		++leftRow;
	}
	for(i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			printf("%-2d ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
