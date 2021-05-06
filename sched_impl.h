#ifndef   __SCHED_IMPL__H__
#define __SCHED_IMPL__H__
#include <semaphore.h>
#include "list.h"

struct thread_info {
    /*...Fill this in...*/
        struct sched_queue *queue;
        list_elem_t *elt;
        sem_t cpu_sem;
        
};

struct sched_queue {
    /*...Fill this in...*/

        list_elem_t* current, next;
        list_t* list, lock; //not sure how to get the mutex of lock working
    
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


