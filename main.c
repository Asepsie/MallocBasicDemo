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
    arg->slot[i].slotpos = i;
  }

  return;
} 

static struct slot *pmalloc(struct memblock *arg)
{
  unsigned int i = 0;

  if (i >= (numOfSlots)) return 0;

  printf("i:%d --- ",i);

  for (i = 0; i<numOfSlots; i++)
  {
    if(arg->slot[i].isfree == true)
    {
      arg->slot[i].p = &(arg.memArray[((i++) << 5)-1])
      return ((struct slot *) (arg->slot));
    }
  }
  return 0;
  // return (&arg->memArray[((i++) << 5)-1]);
}

static unsigned int pfree(struct memblock *arg, unsigned int slotNumber)
{
  arg->slot[i].isfree = true;
  arg->slot[i].
  return 0;
}


int main(void)
{
  struct memblock mem;

  printf("Global array pointer: %d \n", (int)mem.memArray);

  initMem(&mem);
  
  struct slot *temp;
  
  for (int i = 0; i < numOfSlots; i++)
  {
    temp.p = pmalloc(&mem);
    printf("Allocated pointer: %d  diff: %d \n", (int)temp.p, ((int)temp.p - (int)&mem.memArray[0])/4);
  }

  free(mem, 1);
  for (int i = 0; i < numOfSlots; i++)
  {
    printf("After free %d - %d \n", i, (int)mem.slot.isfree);
  }
}