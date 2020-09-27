#include <stdio.h>

void changeVariable (int *ptr); 

void changePointerVariable(int **nPtr, int *m);

int main(void) {
 int n = 15;
 int m = 10;
 int *nPtr = &n;
 

printf("\nThe value of n: %d, and the value of the pointer: %d\n", n, *nPtr);

printf("\nThe address of the value from n: %p\n", &n);

printf("The address of the value from pointer: %p\n", nPtr);
changeVariable(nPtr);

printf("\nThe increment result is %d (n value) or %d", n, *nPtr); 

nPtr = &m;
changePointerVariable(&nPtr, &m);

printf("\n\nThe Pointer Change m is %d",*nPtr);


 return 0;

}

void changeVariable (int *ptr)
{
  (*ptr)++;
  return;
}

void changePointerVariable (int **nPtr, int *m)
{
  *nPtr = m;
}
