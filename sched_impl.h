#ifndef   __SCHED_IMPL__H__
#define __SCHED_IMPL__H__
#include "list.h"

struct thread_info {
        struct sched_queue *queue;
        list_elem_t *elt;
        sem_t cpu_sem;//Semaphore to activate or deactivate worker thread.
        
};

struct sched_queue {
        list_elem_t* currentWorker;
        list_elem_t* nextWorker;
        //Insert all semaphores for queue here
        list_t* list, lock;
        /*...Fill this in...*/

        //added semaphores in sched_impl.c instead
		//sem_t admit_sem, ready_sem, cpu_sem;
};
#endif /* __SCHED_IMPL__H__ */

/*

#ifndef	__SCHED_IMPL__H__
#define	__SCHED_IMPL__H__

struct thread_info {

	struct sched_queue *queue;
	struct list_elem_t *elt;
	sem_t cpu_sem;
};

struct sched_queue {

	//mutex
	sem_t admit_sem, ready_sem, cpu_sem;
	list_t lst, lock;
};

#endif /* __SCHED_IMPL__H__ */


