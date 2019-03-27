#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE      1

#include <stdio.h>
#include <stdlib.h>
#include "samochod.h"

class Queue
{

public:
    Car table[MAX_SIZE];
    int head;
    int tail;
    int Size;


Queue()
{
    this->head = 0;
    this->tail = 0;
    this->Size = 0;
}

int getQueueSize()
{
    return this->Size;
}

void addCar(Car c)
{
    if(c.priority == 1)
    {
        this->head = (this->head - 1);
        if(this->head < 0) this->head = MAX_SIZE - 1;
        this->table[this->head] = c;
    }
    else
    {
        this->table[this->tail] = c;
        this->tail = (this->tail + 1) % MAX_SIZE;
    }

    this->Size++;


}

Car removeCar()
{
    Car c;
    c = this->table[this->head];
    this->head = (this->head + 1) % MAX_SIZE;

    this->Size--;

    return c;
}

int priority()
{
    if(this->Size == 0) return 0;
    return this->table[this->head].priority;
}

};


#endif // QUEUE_H
