#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define POOLSIZE    2048
#define SLOTSIZE      32

struct slot{
  unsigned int *p;
  bool isfree;
};

static unsigned int memArray[POOLSIZE];
static unsigned int numOfSlots = POOLSIZE/SLOTSIZE;
static struct slot slot[POOLSIZE/SLOTSIZE];



static void initMem(unsigned int *arg)
{
  for(int i = 0; i<POOLSIZE; i++)
  {
    *(arg+i) = 0;
  }
  return;
} 

static unsigned int *pmalloc()
{
  static unsigned int i = 0;

  if (i >= (numOfSlots)) return 0;

  printf("i:%d --- ",i);

  if(i == 0) 
  {
    slot[0].isfree = false;
    return &memArray[i++];
  }
  unsigned int temp = ((i++) << 5) ;
  printf("temp:%d --- ",temp);
  return (&memArray[temp-1]);
}

static unsigned int pfree(unsigned int *arg)
{

}


int main(void)
{
  printf("Global array pointer: %d \n", (int)memArray);

  initMem(memArray);
  
  unsigned int *temp;
  for (int i = 0; i < numOfSlots; i++)
  {
    temp = pmalloc();
    printf("Allocated pointer: %d  diff: %d \n", (int)temp, ((int)temp - (int)&memArray[0])/4);

  }


}