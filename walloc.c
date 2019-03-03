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

void *first_block = NULL;

//扩展堆
struct block *extend_heap(struct block *last, size_t s) {
    struct block *b;
    b = sbrk(0);
    if(sbrk(24 + s) == (void *)-1)
        return NULL;
    b->size = s;
    b->next = NULL;
    if(last)
        last->next = b;
    b->free = 0;
    return b;
}

//8字节对齐
size_t align(size_t a) {
    if(a & 0x7 == 0)
        return a;
    return ((a >> 3) + 1) << 3;
}

struct block *find_block(size_t size)
{

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
        p = first_block;
        p = find_block(p, size);
        if(p)
        {

        }
        else()
        {
            p = extend_heap(first_block, size);
            if(!p)
            {
                return NULL;
            }
        }
    }
    else()
    {
        first_block = extend_heap(size);
        return first_block;
    }
    return p -> date;
}
