#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define POOLSIZE    2048
#define SLOTSIZE      32

struct slot{
  unsigned int *p;
  unsigned int slotpos;
  bool isfree;
};

struct memblock{
  unsigned int memArray[POOLSIZE];
  struct slot slot[POOLSIZE/SLOTSIZE];
};

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
    arg->slot[i].slotpos = i;
  }

  return;
} 

static struct slot *pmalloc(struct memblock *arg)
{
  unsigned int i = 0;

  if (i >= (numOfSlots)) return 0;

  for (i = 0; i<numOfSlots; i++)
  {
    printf("Searching free slot i:%d @: %d --- \n",i, (int)&(arg->memArray[((i) << 5)-1]));
    if(arg->slot[i].isfree == true)
    {
      arg->slot[i].p = &(arg->memArray[((i) << 5)]);
      arg->slot[i].isfree = false;
      arg->slot[i].slotpos = i;
      return ((struct slot *) &(arg->slot[i]));
    }
  }
  return 0;
}

static unsigned int ppfree(struct memblock *arg, unsigned int slotNumber)
{
  arg->slot[slotNumber].isfree = true;
  return 0;
}


int main(void)
{
  struct memblock mem;

  printf("Global array pointer: %d \n", (int)mem.memArray);

  initMem(&mem);
  
  struct slot *temp;
  
  for (int i = 0; i < 5; i++)
  {
    temp = pmalloc(&mem);
    printf("Allocated pointer: %d  diff: %d \n", (int)temp->p, ((int)temp->p - (int)&mem.memArray[0])/4);
  }

  printf("before free \n");

  ppfree(&mem, 1);
  for (int i = 0; i < 10; i++)
  {
    printf("After free %d - %d \n", i, (int)mem.slot[i].isfree);
  }
}