#ifndef CAR_H
#define CAR_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

class Car{


public:
    int id;
    int priority;
    int start;
    int destination;

void setCar(int id, int pri, int start, int dest)
{
    this->id = id;
    this->priority = pri;
    this->start = start;
    this->destination = dest;
}

int getRand(int mod)
{
    int val;
    val = rand()%mod;
    return val;
}

void generateCar(int id)
{
    int priority;
    int start;
    int destinantion;
    //time_t tt;
    srand(time(0));

    start = getRand(3);
    destinantion = getRand(3);

    if(start == destinantion) destinantion = (destinantion+1)%3;

    priority = getRand(20);

    if(priority != 1) priority = 0;

    (*this).setCar(id, priority, start, destinantion);

}

void printCar()
{
    printf("id: %d, priority: %d, start: %d, destination: %d\n\n", this->id, this->priority, this->start, this->destination);
}

};


#endif // CAR_H


