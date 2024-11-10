#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#else
#include <unistd.h>
#endif


void waitReturn()
{
	printf("[Press RETURN key]\n");
	char buff;
	read(0, &buff, 1);

}

int main()
{
	printf("Creating array X[10]. ");
	char * x = malloc(10);

	printf(" Array X created. It uses memory range  %p - %p\n", x, x+10);
	int i;
	for (i = 0; i < 10; i++) {
		printf(" X[%d] Legal access at %p ", i, &x[i]);
		x[i] = i;
		printf("SUCCEESS\n");
	}

	printf("%d Legal accesses from %p - %p \n", i, &x[0], &x[i]);
	printf(" Let's free array X. \n");
	waitReturn();


	free(x);

	printf(" Array X freed\n");
	printf(" Let's create another array Y[10]. ");
	waitReturn();


	char * y = malloc(10);

	printf(" Array Y created. It uses memory range  %p - %p\n", y, y+10);
	for (i = 0; i < 10; i++) {
		printf(" write Y[%d] access at %p (legal)", i, &y[i]);
		y[i] = i;
		printf("SUCCEESS\n");
	}

	printf("%d Legal accesses from %p - %p \n", i, &y[0], &y[i]);
	printf(" Can we access it after this position?\n");
	waitReturn();

//for (; i < 8192 ; i++) {
	for (; i < 133000 ; i++) {
		printf(" write Y[%d] access at %p (illegal)", i, &y[i]);
		y[i] = 0;
		printf("SUCCEESS! What?\n");
	}

	printf("Let's free array Y (but memory is corrupted). \n");
	waitReturn();


	free(y);		// THIS WILL FAIL!! Library memory totally corrupted!!

	printf(" Array Y freed\n");
	waitReturn();

	printf("Creating array X[10]. ");

	x = malloc(10);

	printf(" Array X created. It uses memory range  %p - %p\n", x, x+10);
	for (i = 0; i < 10; i++) {
		printf(" write X[%d] access at %p (legal)", i, &x[i]);
		x[i] = -1;
		printf("SUCCEESS\n");
	}

	printf("%d Legal accesses from %p - %p \n", i, &x[0], &x[i]);
	waitReturn();

	exit(1);
}
