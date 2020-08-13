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
    arg->slot[i].p = &(arg->memArray[((i) << 5)]);
  }

  return;
} 

static unsigned int *pmalloc(struct memblock *arg)
{
    unsigned int i = 0;

    if (i >= (numOfSlots)) return 0;

    for (i = 0; i<numOfSlots; i++)
    {
        printf("Searching free slot i:%d @: %d --- \n",i, (int)&(arg->memArray[((i) << 5)-1]));
        if(arg->slot[i].isfree == true)
        {
            arg->slot[i].isfree = false;
            return (arg->slot[i].p);
        }
    }
    return 0;
    }

// Return the slot number that has been freed or '-1' if input pointer is not ok.
static unsigned int ppfree(struct memblock *arg, unsigned int *p)
{
    unsigned int i, ret;
    for (i = 0; i<numOfSlots; i++)
    {
        if(arg->slot[i].p == p)
        {
            arg->slot[i].isfree = true;
            // Might want to 
            ret = i;
            break;
        }
        else
        {
            ret = -1;
        }
    }

  return ret;
}


int main(void)
{
  struct memblock mem;

  printf("Global array pointer: %d \n", (int)mem.memArray);

  initMem(&mem);
  
  unsigned int *temp;
  unsigned int *tempTestFree;
  
  for (int i = 0; i < 5; i++)
  {
    temp = pmalloc(&mem);
    printf("Allocated pointer: %d  diff: %d \n", (int)temp, ((int)temp - (int)&mem.memArray[0])/4);
    if(i==2) tempTestFree = temp;
  }

  ppfree(&mem, tempTestFree);
  for (int i = 0; i < 10; i++)
  {
    printf("After free %d - %d \n", i, (int)mem.slot[i].isfree);
  }
}