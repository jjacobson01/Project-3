#include "scheduler.h"
#include "sched_impl.h"
#include "list.h"
/* Fill in your scheduler implementation code below: */

static void init_thread_info(thread_info_t *info, sched_queue_t *queue)
{
	/*...Code goes here...*/
	info->queue = queue;
	info->elt = NULL;
	sem_init(&info->cpu_sem, 0, 0);
}

static void destroy_thread_info(thread_info_t *info)
{
	/*...Code goes here...*/
}

/*...More functions go here...*/
static void enter_sched_queue(thread_info_t *info)
{
	sem_wait(&info->queue->admit_sem);

	pthread_mutex_lock(&info->queue->lock);

	info->elt = malloc(size(list_elem_t));
	info->elt->datum = info;
	list_insert_tail(&info->queue->lst, info->elt);

	pthread_mutex_unlock(&info->queue->lock);

	sem_post(&info->queue->ready_sem);
}

static void leave_sched_queue(thread_info_t *info)
{
	sem_wait(&info->queue->ready_sem);

	pthread_mutex_lock(&info->queue->lock);
	
	info->elt->datum = NULL;

	pthread_mutex_unlock(&info->queue->lock);

	sem_post(&info->queue->admit_sem);
}
static void wait_for_cpu()
{
}
static void release_cpu()
{
}


static thread_info_t* next_worker_fifo(sched_queue_t* queue)
{
	thread_info_t* info = NULL;

	pthread_mutex_lock(&queue->lock);

	if(queue->lst.head == NULL)
	{
		info = NULL;

	}
	else
		info = queue->lst.head->datum;

}

static void init_sched_queue(sched_queue_t *queue, int queue_size)
{
	/*...Code goes here...*/
}

static void destroy_sched_queue(sched_queue_t *queue)
{
	/*...Code goes here...*/
}

static void signal_worker()
{
}
static void wait_for_worker()
{
}

static void next_worker_fifo()
{


}

static void wait_for_queue()
{
}
/*...More functions go here...*/

/* You need to statically initialize these structures: */
sched_impl_t sched_fifo = {
				 {init_thread_info, destroy_thread_info, enter_sched_queue, leave_sched_queue, wait_for_cpu, release_cpu},
				 {init_sched_queue, destroy_sched_queue, signal_worker, wait_for_worker, next_worker_fifo, wait_for_queue}},
			 sched_rr = {{init_thread_info, destroy_thread_info /*, enter_sched_queue, leave_sched_queue, wait_for_cpu, release_cpu...etc... */}, {init_sched_queue, destroy_sched_queue /*, signal_worker, wait_for_worker, next_worker_rr, wait_for_queue...etc... */}};
