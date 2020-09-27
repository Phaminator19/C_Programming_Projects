#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void print_string(char str[]);
int is_identical(char str1[], char str2[]);
int is_palindrome(char str[]);
int isFiller (char c);
int compareChars(char c1, char c2);


int main(void) {
  char str1[]="Hello World";
  char str2[] = "Madam, I'm Adam!";
  char str3[] = "hello world";

  print_string(str1);
  printf("\n");
  print_string(str2);
  printf("\n");
  print_string(str3);
  printf("\n");

  (is_identical(str1,str2))?printf("They are Identical!\n"): printf("They are Not identical!\n");
  (is_identical(str1,str3))?printf("They are (str1 and 3) Identical!\n"): printf("They are (str1 and 3) Not identical!\n");
  (is_palindrome(str1))?printf("The string 1 is Palindrome\n"): printf("The string 1 is Not palindrome!\n");
  (is_palindrome(str2))?printf("The string 2 is Palindrome\n"): printf("The string 2 is Not palindrome!\n");
}


void print_string(char str[])
{
  printf("%s", str);
  printf("\nThe string length is %ld\n",strlen(str));
}

int is_identical(char str1[], char str2[])
{
  int answer, i,j;
  if (str1 == str2) 
  {
    return answer = 1;
  }
  else {
    return answer = 0;
  }
}

int is_palindrome(char str[])
{
  int i, j, answer;

  answer = 1;
  i = 0;
  j = strlen(str)-1;
   
  if (strlen(str)==1)
  {
    if(isFiller(str[0]==1))
    return -1;
    else return 1;
  }
  while (isFiller(str[i])==1 && i<=strlen(str) - 2)
  i++;
  
  while (isFiller(str[j])==1&&j>=1)
  j--;

  if (i>j)
  return -1;

  if(i==j)
  return 1;

  while (i < j){
    if (compareChars(str[i], str[j]) == 0)
    answer = 0;

    i++;
    j--;

    while (isFiller(str[i])==1 && i<=strlen(str) -2)
    i++;

    while (isFiller(str[j])==1 &&j>=1)
    j--;
  }
return answer;
}

int isFiller (char c)
{
  int result;

  if ((c >= 'a' && c <= 'z')|| (c>='A' && c <= 'Z')||(c>='0'&&c<='9')){
    result = 0;
  }
  else {result = 1;}

  return result; 
}

int compareChars(char c1, char c2){
int result; 
if (c1 >= 'A'&& c1 <= 'Z')
  {
    c1 += 32;
  }
if (c2 >= 'A' && c2<= 'Z')
 {
   c2 += 32;
 }

if (c1==c2) result=1;
else  result= 0;
return result; 
}