#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include "scheduler.h"

#include <assert.h>
#include <curses.h>
#include <ucontext.h>

#include "util.h"

#include <stdbool.h>
#include <string.h>

#include <time.h>

// This is an upper limit on the number of tasks we can create.
#define MAX_TASKS 128

// This is the size of each task's stack memory
#define STACK_SIZE 65536

// This struct will hold the all the necessary information for each task
typedef struct task_info {
		  // This field stores all the state required to switch back to this task
		  ucontext_t context;

		  // This field stores another context. This one is only used when the task
		  // is exiting.
		  ucontext_t exit_context;
//
// TODO: Add fields here so you can:
//   a. Keep track of this task's state.
			int current_state;
//  		 b. If the task is sleeping, when should it wake up?
			int wake_time;
//   		c. If the task is waiting for another task, which task is it waiting for?
			int task_blocking;
//   		d. Was the task blocked waiting for user input? Once you successfully
//   	   read input, you will need to save it here so it can be returned.
			char input_read;

} task_info_t;

int current_task = 0; //< The handle of the currently-executing task
int num_tasks = 1;    //< The number of tasks created so far

#define STATE_NEW        0
#define STATE_READY      1
#define STATE_WAITING    2
#define STATE_INACTIVE   3
#define STATE_TERMINATED 4

task_info_t tasks[MAX_TASKS]; //< Information for every task
int task_state; //
int default_wait_time;

/**
 * Initialize the scheduler. Programs should call this before calling any other
 * functiosn in this file.
 */
void scheduler_init() {
		  // TODO: Initialize the state of the scheduler
		  memset(tasks, STATE_NEW, sizeof(tasks));
		  task_state = 0;
		  default_wait_time = 10;

}

ucontext_t main_context;
//main_context.uc_stack.ss_sp = malloc(STACK_SIZE);
//main_context.uc_stack.ss_size = STACK_SIZE;

bool from_main = true;


/**
	* This function should loop over "tasks" array and find the next eligible task.
	*
	* In all of our test cases scheduling starts after a task_wait() - so task_wait
	* is what calls the scheduler initially (round-robin after), but you should write
	* a generic scheduler that can (and will) be invoked by other blocking functions
	* as well (task_sleep and task_readchar).
*/
void scheduler() {

			if(tasks[handle] == NULL && handle != 0)

			if(tasks[handle] == NULL && handle == 0) {
				// There are no tasks to run
			}

			task_start(tasks[current_task]);
			current_task++;

			return;

			if(from_main) {
						swapcontext(&main_context, &tasks[current_task].context); // Swaps from main context to current task

						//from_main = false;
			}
			else {
						swapcontext(&main_context, &tasks[current_task].context); // Swaps from current task back to main context
						//from_main = true;
			}

}

void task_start(void (*functionPTR)()) {
	functionPTR();
}

/**
 * This function will execute when a task's function returns. This allows you
 * to update scheduler states and start another task. This function is run
 * because of how the contexts are set up in the task_create function.
 */
void task_exit() {
		  // TODO: Handle the end of a task's execution here
}

/**
 * Create a new task and add it to the scheduler.
 *
 * \param handle  The handle for this task will be written to this location.
 * \param fn      The new task will run this function.
 */
void task_create(task_t* handle, task_fn_t fn) {
		  // Claim an index for the new task
		  int index = num_tasks;
		  num_tasks++;

		  // Set the task handle to this index, since task_t is just an int
		  *handle = index;

		  // We're going to make two contexts: one to run the task, and one that runs at the end of the task so we can clean up. Start with the second

		  // First, duplicate the current context as a starting point
		  getcontext(&tasks[index].exit_context);

		  // Set up a stack for the exit context
		  tasks[index].exit_context.uc_stack.ss_sp = malloc(STACK_SIZE);
		  tasks[index].exit_context.uc_stack.ss_size = STACK_SIZE;

		  // Set up a context to run when the task function returns. This should call task_exit.
		  makecontext(&tasks[index].exit_context, task_exit, 0);

		  // Now we start with the task's actual running context
		  getcontext(&tasks[index].context);

		  // Allocate a stack for the new task and add it to the context
		  tasks[index].context.uc_stack.ss_sp = malloc(STACK_SIZE);
		  tasks[index].context.uc_stack.ss_size = STACK_SIZE;

		  // Now set the uc_link field, which sets things up so our task will go to the exit context when the task function finishes
		  tasks[index].context.uc_link = &tasks[index].exit_context;

		  // And finally, set up the context to execute the task function
		  makecontext(&tasks[index].context, fn, 0);
}

/**
 * Wait for a task to finish. If the task has not yet finished, the scheduler should
 * suspend this task and wake it up later when the task specified by handle has exited.
 *
 * \param handle  This is the handle produced by task_create
 */
void task_wait(task_t* handle) {
		  // TODO: Block this task until the specified task has exited.
		  tasks[current_task].task_blocking = handle;
		  scheduler();

		  // HINTNTNTNNTN
		  // If you are switching to a task that is the same as the current task,
		  // just return from the scheduler instead of calling swapcontext().
}

/**
 * The currently-executing task should sleep for a specified time. If that time is larger
 * than zero, the scheduler should suspend this task and run a different task until at least
 * ms milliseconds have elapsed.
 *
 * \param ms  The number of milliseconds the task should sleep.
 */
void task_sleep(size_t ms) {
		  // TODO: Block this task until the requested time has elapsed.
		  // Hint: Record the time the task should wake up instead of the time left for it to sleep. The bookkeeping is easier this way.
		  if (ms > 0) {
			  tasks[current_task].wake_time = timems()
			  scheduler();
		  }

		  return;
}

/**
 * Read a character from user input. If no input is available, the task should
 * block until input becomes available. The scheduler should run a different
 * task while this task is blocked.
 *
 * \returns The read character code
 */
int task_readchar() {
		  // TODO: Block this task until there is input available.
		  // To check for input, call getch(). If it returns ERR, no input was available.
		  // Otherwise, getch() will returns the character code that was read.
		  return ERR;
}
