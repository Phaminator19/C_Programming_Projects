#include <stdio.h>

void PrintUp(int n);
void PrintDown(int n);


int main(void) {
  PrintUp(6);
  PrintDown(7);
}

void PrintUp(int n)
{
  if (n >= 1)
  {
  PrintUp(n-1);
  printf("%d\n", n);
  }
}

void PrintDown(int n)
{
  if (n < 1)
  {
    return;
  }
  printf("\n%d", n);
  return PrintDown(n-1); 
}
