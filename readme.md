THE CODE IS NOT FINISHED


# Dining philosophers problem

The Dining Philosopher Problem is a classic computer science problem that illustrates the challenges of **synchronizing multiple threads or processes that compete for shared resources.** The problem involves a **group of philosophers** sitting around a circular table, each with a **plate of spaghetti** and **a fork**. There are as many forks as there are philosophers, but philosophers **needs two forks to be able to eat spaghetti**, meaning that two adjacent **philosophers must share theirs forks to eat**. The goal is for each philosopher to eat and think without deadlocking or starving to death. [Add img]


# Ecole 42 version of the problem

- **One or more philosophers** sits at a **round table**. There is a large bowl of spaghetti in the middle of the table.
- **The philosophers** alternatively **eat, think, or sleep**. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. **There are as many forks as philosophers.**
- Because serving and eating spaghetti with only one fork is very inconvenient, a **philosopher takes their right and their left forks to eat, one in each hand.**
- **When a philosopher has finished eating, they put their forks back on the table and start sleeping**. Once awake, they start thinking again. **The simulation stops when a philosopher dies of starvation**. 
- Every philosopher **needs to eat** and **should never starve**. 
-  Philosophers **don’t speak with each other**.
- Philosophers **don’t know if another philosopher is about to die**.
- No need to say that philosophers should **avoid dying!**

You can check the subject file here.


## Solution with threads and mutexes

To solve the Dining Philosopher Problem, we need to ensure that the philosophers can eat without deadlocking or starving. One way to solve the problem is to use mutexes and threads. A mutex is a type of lock that is used to ensure that only one thread can access a shared resource at a time.

To use mutexes to solve the Dining Philosopher Problem, we can represent each fork as a mutex and each philosopher as a struct that contains a thread id and last time of meal. When a philosopher wants to eat, they must first acquire the mutexes for both forks they need. If the philosopher cannot acquire both mutexes, they must wait until they can. Once a philosopher has both mutexes, they can eat. After eating, the philosopher releases the mutexes for the forks, allowing other philosophers to use them. There should be another thread that checks if a philosopher died or not using their last meal date. Don't forget to create a mutex to print the events too.

## Solution with processes and semaphores



## Useful stuff

The Youtube playlist that i created for the project:



