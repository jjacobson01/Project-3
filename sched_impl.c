//Name: Jonathan Jacobson
//Partner Name: Jose Aguilar

#include "scheduler.h"
#include "sched_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

sem_t admit_sem, ready_sem, cpu_sem;

/* Fill in your scheduler implementation code below: */

/*...Code goes here...*/
static void init_thread_info(thread_info_t *info, sched_queue_t *queue)
{
	info->queue = queue->list;
	info->elt = NULL;
	sem_init(&info->cpu_sem, 0, 0);
}

/* Release the resources associated with a thread_info_t */
static void destroy_thread_info(thread_info_t *info)
{
	/*...Code goes here...*/
	free(info->elt);
}

/*...More functions go here...*/
static void enter_sched_queue(thread_info_t *info)
{
	sem_wait(&admit_sem);

	//pthread_mutex_lock(&info->queue->lock);

	info->elt = (list_elem_t *)malloc(sizeof(list_elem_t));
	list_elem_init(info->elt, (void *)info);

	list_insert_tail(info->queue, info->elt);

	sem_post(&ready_sem);

	//pthread_mutex_unlock(&info->queue->lock);
}


static void leave_sched_queue(thread_info_t *info)
{
	list_remove_elem(info->queue, info->elt);
	sem_post(&admit_sem);
}


static void wait_for_cpu(thread_info_t *info)
{
	sem_wait(&info->cpu_sem);
}


static void release_cpu(thread_info_t *info)
{
	sem_post(&cpu_sem);
	sched_yield();
}

static void init_sched_queue(sched_queue_t *queue, int queue_size)
{
	/*...Code goes here...*/

	queue->current = NULL;
	queue->next = NULL;
	queue->list = (list_t *)malloc(sizeof(list_t));
	list_init(queue->list);
	sem_init(&admit_sem, 0, queue_size);
	sem_init(&cpu_sem, 0, 0);
	sem_init(&ready_sem, 0, 0);
}

static void destroy_sched_queue(sched_queue_t *queue)
{
	/*...Code goes here...*/
	list_elem_t *temp;
	while ((temp = list_get_head(queue->list)) != NULL)
	{
		list_remove_elem(queue->list, temp);
		free(temp);
	}
	free(queue->list);
}

/*...More functions go here...*/
static void wake_up_worker(thread_info_t *info)
{
	sem_post(&info->cpu_sem);
}

static void wait_for_worker(sched_queue_t *queue)
{
	sem_wait(&cpu_sem);
}

static thread_info_t *next_worker_rr(sched_queue_t *queue)
{
	if (list_size(queue->list) == 0)
	{
		return NULL;
	}

	if (queue->current == NULL)
	{
		queue->current = list_get_head(queue->list);
	}
	else if (queue->next == NULL)
	{
		if (queue->current == list_get_tail(queue->list))
		{
			queue->current = list_get_head(queue->list);
		}
		else
		{
			queue->current = list_get_tail(queue->list); 
		}
	}
	else
	{
		queue->current = queue->next;
	}

	queue->next = queue->current->next;
	return (thread_info_t *)queue->current->datum;
}

static thread_info_t *next_worker_fifo(sched_queue_t *queue)
{
	if (list_size(queue->list) == 0)
	{
		return NULL;
	}
	else
	{
		return (thread_info_t *)(list_get_head(queue->list))->datum;
	}
}

static void wait_for_queue(sched_queue_t *queue)
{
	sem_wait(&ready_sem);
}
/* You need to statically initialize these structures: */
sched_impl_t sched_fifo = {
				 {init_thread_info, destroy_thread_info, enter_sched_queue, leave_sched_queue, wait_for_cpu, release_cpu},
				 {init_sched_queue, destroy_sched_queue, wake_up_worker, wait_for_worker, next_worker_fifo, wait_for_queue}},
			 sched_rr = {{init_thread_info, destroy_thread_info, enter_sched_queue, leave_sched_queue, wait_for_cpu, release_cpu},
			  {init_sched_queue, destroy_sched_queue, wake_up_worker, wait_for_worker, next_worker_rr, wait_for_queue}};
