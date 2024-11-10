#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
//#include <io.h>
#else
#include <unistd.h>
#endif


void waitReturn()
{
	printf("[Press RETURN key]\n");
	char buff;
	read(0, &buff, 1);

}

int main() {
	printf("Creating array X[10]. ");
	char * x = malloc(10);

	printf(" Array X[10] created. It uses memory range  %p - %p\n", x, x+10);
	int i;
	for (i = 0; i < 10; i++) {
		printf(" write X[%d] access at %p (legal)", i, &x[i]);
		x[i] = i;
		printf("SUCCEESS\n");
	}
	printf("%d Legal accesses from %p - %p \n", i, &x[0], &x[i]);
	printf("Can we access outside of that region?\n");
	waitReturn();
	int illegal = 0;

	for (; i < 20 ; i++) {
		printf(" write X[%d] access at %p (illegal)", i, &x[i]);
		x[i] = -1;
		printf("SUCCEESS! What?\n");
		illegal ++;
	}
	printf("OMG! %d illegal accesses! How far can we go?\n", illegal);
	waitReturn();

	for (;; i++) {
		printf(" write X[%d] access at %p ( %d illegal accesses)", i, &x[i], illegal);
		x[i] = -1;
		printf("SUCCEESS! What?\n");
		illegal ++;
	}
	printf("This point in code is never achieved :( \n");
	waitReturn();

	exit(1);
}
