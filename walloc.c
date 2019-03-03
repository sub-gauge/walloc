#include<unistd.h>
#include<sys/mman.h>

void *walloc(size_t size)
{
    void *p = sbrk(0);
    if(sbrk(size) == (void *)-1)
    {
        return NULL;
    }
    return p;
}