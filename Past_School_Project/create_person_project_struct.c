#include <stdio.h>
#include <string.h>

typedef struct{
  char name[20];
  int age;
  double score;
}Person;

Person createPerson(char name[],int age,double score); 
void printPerson(Person p); 
void changeAge(Person * p,int newAge); 
void printPeople(Person people[],int length);

int main(void) {
  Person p = createPerson("Rickard",31,100);
  printPerson(p);
  changeAge(&p,30);
  printPerson(p);
  Person people[3];
  people[0] = createPerson("John",22,83);
  people[1] = createPerson("Danny",24,63); 
  people[2] = createPerson("Marry",20,81); 
  printPeople(people,3);
};


Person createPerson(char name[],int age,double score)
{
  Person p;
  strcpy(p.name, name);
  p.age = age;
  p.score = score;
return p;
}

void printPerson(Person p)
{
  printf("Name: %s\nAge: %d\nScore: %.2lf\n\n", p.name, p.age, p.score);
} 

void changeAge(Person * p,int newAge)
{
  p -> age = newAge;
}

void printPeople(Person people[],int length)
{
  
  for (int i = 0; i <= length; i++){
  printf("Person %d: \n", i+1);
  printPerson(people[i]);
  }
}