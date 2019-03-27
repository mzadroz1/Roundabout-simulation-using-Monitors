#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/sem.h>
#include<thread>
#include<utility>

#include "monitor.h"
#include "samochod.h"
#include "rondo.h"
#include "kolejka.h"

using namespace std;

class ProQMonitor : Monitor
{
    ProQueue buf;
    Condition full, empty;
    public:
    void put(Car c)
    {
        enter();
        if(buf.getProQueueSize()==PRO_MAX_SIZE)
            wait(full);
            buf.addCarProQueue(c);
        if(buf.getProQueueSize()==1)
            signal(empty);
        leave();
    }
    Car pop()
    {
        Car c;
        enter();
        if(buf.getProQueueSize()==0)
            wait(empty);
            c=buf.removeCarProQueue();
        if(buf.getProQueueSize()==PRO_MAX_SIZE-1)
            signal(full);
        leave();
        return c;
    }
    int getSize()
    {
        int s;
        enter();
        s=buf.getProQueueSize();
        leave();
        return s;
    }
    int priority()
    {
        int p;
        enter();
        p=buf.proPriority();
        leave();
        return p;
    }
};

class QMonitor :Monitor
{
    Queue buf;
    Condition full, empty;
    public:
    void put(Car c)
    {
        enter();
        if(buf.getQueueSize()==MAX_SIZE)
            wait(full);
            buf.addCar(c);
        if(buf.getQueueSize()==1)
            signal(empty);
        leave();
    }
    Car pop()
    {
        Car c;
        enter();
        if(buf.getQueueSize()==0)
            wait(empty);
            c=buf.removeCar();
        if(buf.getQueueSize()==MAX_SIZE-1)
            signal(full);
        leave();
        return c;
    }
    int getSize()
    {
        int s;
        enter();
        s=buf.getQueueSize();
        leave();
        return s;
    }
    int priority()
    {
        int p;
        enter();
        p=buf.priority();
        leave();
        return p;
    }
};

ProQMonitor proQueue[3];
QMonitor queue[3];
bool End=true;


void droga(int CROSS_ID, int CROSS_WITH)
{
    Car car;
    while(End)
    {
        if(proQueue[CROSS_ID].getSize() == 0 && queue[CROSS_WITH].getSize() == 0) continue;


        if(queue[CROSS_WITH].priority() || (queue[CROSS_WITH].getSize() > 0 && proQueue[CROSS_ID].priority() == 0))
        {
            car = queue[CROSS_WITH].pop();
            printf("Samochod o id %d na rondzie dojezdza do skrzyzowania %d\n", car.id,CROSS_ID);
        }
        else
        {
            car = proQueue[CROSS_ID].pop();
            printf("Samochod o id %d przygotowuje sie do wjazdu z kolejki %d na rondo\n", car.id,CROSS_ID);

        }
        sleep(1);

        if(car.destination == CROSS_ID)
        {
            printf("Samochod o id %d zjezdza z ronda zjazdem nr %d\n",car.id,CROSS_ID);
            continue;
        }

        queue[CROSS_ID].put(car);
        printf("Samochod o id %d minal zjazd %d i porusza sie po rondzie\n", car.id,CROSS_ID);
    }
}

void generator(int quantity, float frequency)
{
    Car car;
    for(int id = 1; id <= quantity; id++)
    {
        car.generateCar(id);

        printf("\nDo kolejki %d wjezdza samochod o id %d\n",car.start, car.id);
        car.printCar();
        proQueue[car.start].put(car);

        usleep(frequency*1000000.0);
    }
    sleep(7);
    End=false;
}


int main()
{
    int quantity;
    float frequency;
    printf("Prosze podac ilosc samochodow w symulacji \n");
    scanf("%d", &quantity);
    printf("Prosze podac czestotliwosc z jaka maja sie pojawiac samochody \n");
    scanf("%f", &frequency);
    int n=0;
    std::thread gen(generator,quantity,frequency);
    std::thread droga0(droga,n,n+2);
    std::thread droga1(droga,n+1,n);
    std::thread droga2(droga,n+2,n+1);

    droga0.join();
    droga1.join();
    droga2.join();
    gen.join();
    return 0;
}
