#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define POOLSIZE    2048
#define SLOTSIZE      32

struct slot{
  unsigned int *p;
  bool isfree;
};

struct memblock{
  unsigned int memArray[POOLSIZE];
  struct slot slot[POOLSIZE/SLOTSIZE];
};
/*
static unsigned int memArray[POOLSIZE];
static struct slot slot[POOLSIZE/SLOTSIZE];
*/
static unsigned int numOfSlots = POOLSIZE/SLOTSIZE;

static void initMem(struct memblock *arg)
{
  for(int i = 0; i<POOLSIZE; i++)
  {
    arg->memArray[i] = 0;
  }
  for(int i = 0; i<numOfSlots; i++)
  {
    arg->slot[i].isfree = true;
  }

  return;
} 

static unsigned int *pmalloc(struct memblock *arg)
{
  static unsigned int i = 0;

  if (i >= (numOfSlots)) return 0;

  printf("i:%d --- ",i);

  if(i == 0) 
  {
    arg->slot[0].isfree = false;
    return &arg->memArray[i++];
  }
  unsigned int temp = ((i++) << 5) ;
  printf("temp:%d --- ",temp);
  return (&arg->memArray[temp-1]);
}

static unsigned int pfree(unsigned int *arg)
{

}


int main(void)
{
  struct memblock mem;

  printf("Global array pointer: %d \n", (int)mem.memArray);

  initMem(&mem);
  
  unsigned int *temp;
  for (int i = 0; i < numOfSlots; i++)
  {
    temp = pmalloc(&mem);
    printf("Allocated pointer: %d  diff: %d \n", (int)temp, ((int)temp - (int)&mem.memArray[0])/4);

  }


}