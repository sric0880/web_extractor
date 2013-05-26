/*
 * SafeQueue.h
 *
 *  Created on: 2013-5-20
 *      Author: qiong
 */

#ifndef THREADQUEUE_H_
#define THREADQUEUE_H_
#include <semaphore.h>
//#include <sys/types.h>
const int MAX_QUEUE_SIZE = 20;

template<class obj>
class SafeQueue {
public:
	SafeQueue();
	virtual ~SafeQueue();
	void push(const obj& o);//push
	obj* front_pop();//front
	bool isEmpty();//
	//int length();
	void clear();//clear the queue
private:
	int front;
	int rear;
	int size;
	obj list[MAX_QUEUE_SIZE];
	sem_t nempty, nstored;
	sem_t mutex;
};

template<class obj>
SafeQueue<obj>::SafeQueue():front(0),rear(0),size(0) {
	sem_init(&nempty,0,MAX_QUEUE_SIZE);
	sem_init(&nstored,0,0);
	sem_init(&mutex,0,1);
}

template<class obj>
SafeQueue<obj>::~SafeQueue() {
	sem_destroy(&nempty);
	sem_destroy(&nstored);
	sem_destroy(&mutex);
}

template<class obj>
void SafeQueue<obj>::push(const obj& o){
	sem_wait(&nempty);
	sem_wait(&mutex);
	list[rear] = o;
	rear = (rear + 1)%MAX_QUEUE_SIZE;
	++size;
	sem_post(&mutex);
	sem_post(&nstored);
}

template<class obj>
obj* SafeQueue<obj>::front_pop(){
	obj* temp = NULL;
	sem_wait(&nstored);
	sem_wait(&mutex);
	temp = &list[front];
	front = (front + 1)%MAX_QUEUE_SIZE;
	--size;
	sem_post(&mutex);
	sem_post(&nempty);
	return temp;
}

template<class obj>
bool SafeQueue<obj>::isEmpty(){
	if (size == 0)
		return true;
	else
		return false;
}

template<class obj>
void SafeQueue<obj>::clear(){
	rear = front = size = 0;
}

//template<class obj>
//int SafeQueue<obj>::length(){
//}

#endif /* THREADQUEUE_H_ */
