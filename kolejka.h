#ifndef PROQUEUE_H
#define PROQUEUE_H

#define PRO_MAX_SIZE   10

#include <stdio.h>
#include <stdlib.h>
#include "samochod.h"

class ProQueue
{
public:

    struct Car table[PRO_MAX_SIZE];
    int head;
    int tail;
    int Size;


ProQueue()
{
    this->head = 0;
    this->tail = 0;
    this->Size = 0;
}

int getProQueueSize()
{
    return this->Size;
}

void addCarProQueue(Car c)
{
    if(c.priority == 1)
    {
        this->head = (this->head - 1);
        if(this->head < 0) this->head = PRO_MAX_SIZE - 1;
        this->table[this->head] = c;
    }
    else
    {
        this->table[this->tail] = c;
        this->tail = (this->tail + 1) % PRO_MAX_SIZE;
    }

    this->Size++;


}

Car removeCarProQueue()
{
    Car c;
    c = this->table[this->head];
    this->head = (this->head + 1) % PRO_MAX_SIZE;
    this->Size--;

    return c;
}

int proPriority()
{
    if(this->Size == 0) return 0;
    return this->table[this->head].priority;
}

};



#endif // PROQUEUE_H
