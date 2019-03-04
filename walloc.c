#include<unistd.h>
#include<sys/mman.h>

struct block
{
    size_t size;
    struct block *next;
    int free;
    int prdding;
    char date[1];
};


struct block *first_block = NULL;

//扩展堆
struct block *extend_heap(struct block *first, size_t s) {
    struct block *b;
    b = sbrk(0);
    if(sbrk(24 + s) == (void *)-1)
        return NULL;
    b -> size = s;
    b -> next = first;
    b -> free = 1;
    return b;
}

//8字节对齐
size_t align(size_t a) {
    if(a & 0x7 == 0)
        return a;
    return ((a >> 3) + 1) << 3;
}

struct block *find_block(struct block *p, size_t size)
{
    while(p != NULL)
    {
        if(p -> size >= size && p -> free == 0)
        {
            p -> free = 1;
            return p;
        }
        p = p -> next;
    }
}

void *walloc(size_t size)
{
    struct block *p = NULL;
    if(size == 0)
    {
        return NULL;
    }
    //对齐
    size = align(size);
    if(first_block)
    {
        p = find_block(first_block, size);
        if(p)
        {

        }
        else
        {
            first_block = extend_heap(first_block, size);
            p = first_block;
            if(!p)
            {
                return NULL;
            }
        }
    }
    else
    {
        first_block = extend_heap(p, size);
        return first_block -> date;
    }
    return (void *)(p -> date);
}

