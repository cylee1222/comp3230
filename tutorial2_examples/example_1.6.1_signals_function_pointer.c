#include <stdlib.h>
#include <stdio.h>

int add(int x, int y)
{
	return x+y;
}

typedef int(*Handler)(int, int);
int funcPointer(int x, int y, Handler handler)
{
	return handler(x,y);
}

int main(int argc, char* argv[])
{
	int sum;
	sum = funcPointer(2, 5, add);
	printf("The sum is %d.\n", sum);
	
	return 0;
}
	