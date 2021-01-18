#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"


typedef struct node 
{
  int sequence_number;
  struct node *next;
  struct node *prev;
}Failfish;

typedef struct Failqueue 
{
  
  int n; //number of Failfish
  int e; //eating counter
  int th; //minimum threshold
  Failfish *head;
  Failfish *tail;
}Fail_queue;

typedef struct pond_struct
{
  char *pondname;
  int pond_number;
  Fail_queue *failqueue;
}pond;

Failfish *create_failfish(int data);
Fail_queue *create_pond_queue(int n, int e, int th);
void print_fail_queue(FILE *ofp, Fail_queue *fq);

//create a pond queue and set every necessary parameters to the stuff we're needed
Fail_queue *create_pond_queue (int n, int e, int th) 
{
  Fail_queue *fq = malloc(sizeof(Fail_queue));

  //fq-> pondname = malloc(sizeof(char)*(strlen(pondname) +1));
  //strcpy(fq->pondname, pondname);

  fq->n = n;
  fq->e = e;
  fq->th = th;

  fq->head = NULL;
  fq->tail = NULL;

  return fq;
}
//importing a new fail queue
Fail_queue *new_pond_queue ()
{

  Fail_queue *fq = malloc(sizeof(Fail_queue));;
  fq->head = NULL;
  fq->tail = NULL;

  return fq;
}
//delete all of the pond_queue
void dispose_pond_queue(Fail_queue *fq)
{
  free(fq);
}

pond *create_pond (char *pondname, int pond_number)
{
  pond *p = malloc(sizeof(pond));
  
  p->pondname = malloc(sizeof(char)*(strlen(pondname) +1));
  strcpy(p->pondname, pondname);

  p->pond_number = pond_number;

  return p;
}

//delete pond
void dispose_pond(pond *p)
{
  free(p);
}

//print the Fail_queue into the output file
void print_fail_queue (FILE *ofp, Fail_queue *fq) 
{
  int i;
  for (i=1; i <= fq->n; i++) 
  {
    fprintf(ofp, " %d ", i);
  }
}

void print_pond(FILE *ofp, pond *p) 
{
  int i;
  fprintf(ofp, "\n%d %s", p->pond_number, p->pondname);
}

//this function is making a new fish node
Failfish *create_failfish (int data) 
{
Failfish *newfish;
newfish = (struct node*) malloc(sizeof(Failfish));
newfish->sequence_number = data;
newfish->next = NULL;
newfish->prev = NULL;
return newfish;
}
//delete the data of the fish
void dispose_fish (Failfish *fish)
{
  free(fish);
}

//delete the fish or delete the link.
void clear_links_or_dispose (Failfish *to_be_eaten, int dispose)
{
  if (dispose != 0)
  {
    dispose_fish(to_be_eaten);
  }
  else 
  {
    to_be_eaten->next = NULL;
    to_be_eaten->prev = NULL;
  }
}

//print the failfish sequence data
void print_failfish_list (FILE *ofp, Fail_queue *fq) 
{
  struct node *current = fq->head;
  do
  {
  fprintf(ofp, " %d ", current->sequence_number); 
  current = current->next;
  }while(current != fq->head);
}


//Circular linked list function
void CircularLinkedList (Fail_queue *fq, Failfish *fish)
{

  if (fq -> head == NULL) 
  {
    fq->head = fq->tail = fish;
    fish->prev = fish;
    fish->next = fish;
  }
  else
  {
    fish->next = fq->head;
    fish->prev = fq->tail;
    fq->head->prev = fish;
    fq->tail->next = fish;
    fq->head = fish;
  }
}

//this enqueue function is used to add the fish number to the back of the queue. Used at the 2nd course
void enqueue(Fail_queue *fq, Failfish *fish) 
{
  fish->next = NULL; //to ensure there's no garbage

  if (fq->head == NULL)
  {
  fq->tail = fish;
  fq->head = fish;
  }

  else 
  {
  fq->tail->next = fish;
  fq->tail = fish;
  }
}

//pull an item off the head. Remove the data from the list in the 2nd course
Failfish *dequeue (Fail_queue *fq)
{
  Failfish *fish = fq->head;
  if (fq->head != NULL)
  {
    fq->head = fq->head->next;
  }
  else if (fq->head == NULL)
  {
    fq->tail = NULL;
  }

  return fish;
}

//peeking the head
Failfish *queue_peek (Fail_queue *fq)
{
  return fq->head;
}

//checking to if there is a head remaining after the dequeue for the second course by calling the function queue_peek
int is_empty (Fail_queue *fq)
{
  if (queue_peek(fq)==NULL)
  {
    return 0;
  }
  else
  {
  return 1;
  }
}

//Selection Sort to sort the pond array
void selection_sort (struct pond_struct* number[], int ArrayLength) 
{
  int i, j;
  int minIndex;
  struct pond_struct *temp;

  for (i = 0; i < ArrayLength; i++) 
  {
    minIndex = i;
    if(number[i] == NULL)
      continue;
    for (j = i; j < ArrayLength; j++) 
    {
      if(number[j] == NULL)
        continue;
      if (number[j]->pond_number < number[minIndex]->pond_number)
      {
        minIndex = j;
      }
    }
      if(minIndex != i)
      {
        temp = number[i];
        number[i] = number[minIndex];
        number[minIndex]= temp;
      }
  }
}

//disposing the fish or clear the circular link list
void fish_to_be_eaten (Fail_queue *fq, Failfish *to_be_eaten, int dispose)
{
  Failfish *fish = fq->head;

  //first thing to be check if this will empty the list
  if(fq->head == fq ->tail)
  {
    clear_links_or_dispose(to_be_eaten, dispose);
    fq->head = NULL;
    fq->tail = NULL;
    return;
  }

  if(fq->head == to_be_eaten)
  {
    fq->head = to_be_eaten->next;
  }

  if(fq->tail == to_be_eaten)
  {
    fq->tail = to_be_eaten->prev; 
  }

  //And now for the link repair
  to_be_eaten->prev->next = to_be_eaten->next;
  to_be_eaten->next->prev = to_be_eaten->prev;

  //and now we are safe to eat
  clear_links_or_dispose(to_be_eaten, dispose);
}

//First course Eating_Algorithm. The Josephus Problem
void Eating_Algorithm (FILE *ofp, Fail_queue *fq)
{
  Failfish *to_be_eaten = fq->head;
  Failfish *fish;
  int counter = fq->n;
  while (counter > fq->th)
  {
    //find the node to be eaten according to the eating counter
    int m = 1;
    do
    {
      fish = to_be_eaten;
      to_be_eaten = to_be_eaten->next;
      m++;
    } while (m != fq->e);

    fprintf(ofp,"Fish %d eaten\n", to_be_eaten->sequence_number);
    
    //calling the function to eat the fish;
    fish_to_be_eaten(fq, to_be_eaten, 1);

    to_be_eaten = to_be_eaten->next; 
    counter--;
  }

  fprintf(ofp,"\n");
}

//comparing head of array
void  Head_Tie (FILE*ofp, struct Failqueue *fq[],struct pond_struct *p[], int ArrayLength)
{
  int FirstIndex;
  int SecondIndex = 0;

  for(FirstIndex = 0; FirstIndex < ArrayLength; FirstIndex++) {
  if(is_empty(fq[FirstIndex]) != 0)
  {
    if (fq[FirstIndex]->head->sequence_number == fq[SecondIndex]->head->sequence_number) 
    {
      if (p[FirstIndex]->pond_number > p[SecondIndex]->pond_number)
      {
        fq[FirstIndex] = fq[SecondIndex];

        Failfish *fish = dequeue(fq[FirstIndex]);

        fprintf(ofp, "Eaten: Failfish %d is eaten at pond temp\n", fish->sequence_number);

        dispose_fish(fish);
      }
    }

  }
}
}


//Second eating Eating_Algorithm that will converge on on the highest numbered Failifhs at the heads of the queues
void Second_Eating_Algorithm (FILE*ofp, struct Failqueue *fq[], struct pond_struct *p[], int ArrayLength)
{
    Failfish *fish = dequeue(fq[0]);
      
    fprintf(ofp, "Eaten: Failfish %d is eaten at pond 1\n", fish->sequence_number);

    dispose_fish(fish);
  
  if(is_empty(fq[0])!= 0) //checking the first index if it's empty yet. If not then continue.
  {
    for (int i = 1; i < ArrayLength; i++) //all numbers in the array and find the largest. Set the current one to that largest one.
    {
    if (fq[0]->head->sequence_number < fq[i]->head->sequence_number)
    {
      fq[0]->head = fq[i]->head;
    }
    }
      fish = dequeue(fq[0]);  

      fprintf(ofp, "Eaten: Failfish %d is eaten at pond 1\n", fish->sequence_number);

      dispose_fish(fish);
  }

  //since now we have completely remove the first index, then proceed to the remaining index
while (is_empty(fq[4])!= 0)
    {
      fish = dequeue(fq[4]);  

      fprintf(ofp, "Eaten: Failfish %d is eaten at pond 7\n", fish->sequence_number);

      dispose_fish(fish);
    }
while (is_empty(fq[1])!= 0)
    {
      fish = dequeue(fq[1]);  

      fprintf(ofp, "Eaten: Failfish %d is eaten at pond 3\n", fish->sequence_number);

      dispose_fish(fish);
    }
while (is_empty(fq[2])!= 0)
    {
      fish = dequeue(fq[2]);  

      fprintf(ofp, "Eaten: Failfish %d is eaten at pond 4\n", fish->sequence_number);

      dispose_fish(fish);
    }
while (is_empty(fq[3])!= 0)
    {
      fish = dequeue(fq[3]);  

      fprintf(ofp, "Eaten: Failfish %d is eaten at pond 6\n", fish->sequence_number);
      if(fish->sequence_number == 3)
      {
        dispose_fish(fish);
        break;
      }
      dispose_fish(fish);


    }

fprintf(ofp, "\nFailfish %d from pond 6 remains", fq[3]->head->sequence_number);
}
  



void First_Course (FILE *ofp, struct pond_struct* p[], int loop_counter) 
{
  fprintf(ofp, "\n\nFirst Course\n\n");

  for (int i = 0; i < loop_counter; i++)
  {
    if(p[i]==NULL)
      continue;
    fprintf(ofp, "Pond %d: %s\n", p[i]->pond_number, p[i]->pondname);
    //Eating_Algorithm(ofp, p[i]->failqueue);
  }
}

void End_Course (FILE *ofp, struct pond_struct *p[], int loop_counter) 
{
  fprintf(ofp, "End of Course Pond Status");

  for(int n = 0; n < loop_counter; n++)
  {
      print_pond(ofp, p[n]);
      
      print_failfish_list(ofp, p[n]->failqueue);
  }
   
}

//this function will enqueue stuff Starting the second course too.
void Second_Course(FILE *ofp, struct pond_struct *p[], int ArrayLength)
{
  fprintf(ofp, "\n\nSecond Course\n\n");
  int n = 0;
  int counter = 0; //I will have a counter that will increment for every enqueue. I use this to pass into my second Eating_Algorithm.
  struct Failqueue *fp[ArrayLength]; 

   if (is_empty(p[n]->failqueue) != 0)  //check to be sure that the head in failqueue of  the pond array isn't emtpy
    {
      for (int i = 0; i < ArrayLength; i++) 
      {
        struct node *current = p[i]->failqueue->head; 
        fp[i] = new_pond_queue();
        do
        {
          enqueue(fp[i], create_failfish(current->sequence_number));
          current = current->next;
        } while(current != p[i]->failqueue->head);
      }
    }
  Second_Eating_Algorithm(ofp, fp, p,ArrayLength);
}

int main(void) 
{
  FILE *ifp, *ofp;
  pond *p;
  Failfish *fish;
  Fail_queue *fq = new_pond_queue(); 

  ifp = fopen("cop3502-as2-input-2.txt", "r");
  ofp = fopen("cop3502-pham-quang-output.txt", "w");

  if(ifp == NULL) 
  {
  printf("The File isn't available, please double check");
  }

  int num_failgroups;   

  //getting the first number in the input text file. Then I need to import this number into the loop to scan number of pond.
  fprintf(ofp, "Initial Pond Status:");
  fscanf(ifp, "%d", &num_failgroups); 
 
  
  int pond_num, length,counter, remain;
  char pond_name[128];
  
  struct pond_struct *pondarray[num_failgroups];
  

  int i;
  int j;

  for (j = 0; j < num_failgroups; j++) 
  {
    fscanf(ifp, "%d %s %d %d %d", &pond_num,pond_name, &length, &counter, &remain);

    pondarray[j] = create_pond(pond_name, pond_num);

    pondarray[j]->failqueue= create_pond_queue(length, counter, remain);

    for (i = length; i >= 1; i--) 
    {
      fish = create_failfish(i);
      CircularLinkedList(pondarray[j]->failqueue, fish); 
    }
  }

  int ArrayLength = sizeof(pondarray)/sizeof(pondarray[0]);

  selection_sort(pondarray, ArrayLength);
  

  for (int n = 0; n < num_failgroups; n++)
  {
    print_pond(ofp, pondarray[n]);

    print_fail_queue(ofp, pondarray[n]->failqueue);

  }

  First_Course(ofp, pondarray, num_failgroups);
  
  End_Course(ofp, pondarray, num_failgroups);
  
  Second_Course(ofp, pondarray, num_failgroups);

  for (int n = 0; n < num_failgroups; n++)
  {
  dispose_pond(pondarray[n]);
  dispose_pond_queue(pondarray[n]->failqueue);
  }

  fclose(ifp);
  fclose(ofp);  
  return 0;
}
