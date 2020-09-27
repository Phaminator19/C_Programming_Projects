#include <stdio.h>
#include <string.h>

void printString(char str[]);
void computeMinMax(double arr[],int length,double * min,double * max);

int main(){
 char s[] = "I like homework";
 printString(s);
 printf("\n");
 double arr[] = {1,-1.1,40,50,3,3,2,3};
 double min,max;
 computeMinMax(arr,8,&min,&max);
 printf("min: %lf max: %lf\n",min,max);
}

void printString(char str[]){
  char *sPtr = str;

  printf("Original Dereferencing pointer: %s\n", sPtr);

  sPtr++;

  printf("After incrementing by 1: %s\n\n", sPtr);
}


void computeMinMax(double arr[],int length, double * min, double * max)
{
  double *i;
  for (i =&arr[0]; i < &arr[length]; i++)
  { 
    if (*i> *max)
    {
      *max = *i;
    }
     else if (*i < *min)
    {
      *min = *i;
    }
  }
}

