#ifndef __SCHED_IMPL__H__
#define __SCHED_IMPL__H__

#include "list.h"

// these following semaphores do the following the same listed order
//the admitance semaphore controls how many threads are waiting in queue at
//the same time and limiting access to the queue

//the ready semaphore acts in contrast to the admitance one, making sure that there queue isn't empty

//the cpu semaphore allows a chosen thread to use the CPU, essentially acting as the mutex
sem_t admit_sem, ready_sem, cpu_sem;

struct thread_info
{
	/*...Fill this in...*/

	//we have a queue with a data list to match it for record reasons
	//alongside having a semaphore to start up or end the worker thread.
	struct sched_queue *queue;
	list_elem_t *elt;
	sem_t cpu_sem;
};

struct sched_queue
{
	/*...Fill this in...*/

	//here we have elements for the current and future
	//workers that will be used throughout our threads
	//alongside a list for all the semaphores to begin a
	//queue at
	list_elem_t *current;
	list_elem_t *next;
	list_t *list, *lock;

	//not sure how to get the mutex of lock working
	//added semaphores in sched_impl.h outside the struct instead
	//sem_t admit_sem, ready_sem, cpu_sem;
};
#endif /* __SCHED_IMPL__H__ */
