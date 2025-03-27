<div align="center">
  <img height="200" src="https://raw.githubusercontent.com/Benjamin-poisson/My_image_bank/refs/heads/main/philosophers.png"  />
</div>

# Philosophers - Multithreading and Synchronization

Philosophers is a project that challenges you to solve the famous "Dining Philosophers Problem," a classic exercise in concurrency, synchronization, and resource sharing. This project will strengthen your understanding of threads, mutexes, and the complexities of parallel programming.

## Status
<div align="center">
  <img height="200" src="https://raw.githubusercontent.com/Benjamin-poisson/My_image_bank/refs/heads/main/philosopher_success.png"  />
</div>

## Objectives

The goal of this project is to simulate a scenario where a group of philosophers alternates between eating, thinking, and sleeping. They must share a limited number of forks without causing a deadlock or data race. The project introduces you to multithreading and thread synchronization mechanisms.

## Great Resources

<li><a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem">Dining Philosophers Problem - Wikipedia</a></li>
<li><a href="https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2">Understanding the Dining Philosophers Problem</a></li>
<li><a href="https://nafuka11.github.io/philosophers-visualizer/">Philosophers Visualizer</a></li>

## Mandatory

<table>
  <tr>
    <th>Program name</th>
    <td>philo</td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>All necessary files to compile the program</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td>Yes</td>
  </tr>
  <tr>
    <th>External functions</th>
    <td>malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock</td>
  </tr>
  <tr>
    <th>Libft authorized</th>
    <td>No</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>Simulate the Dining Philosophers Problem with multithreading and proper synchronization.</td>
  </tr>
</table>

- The project must be written in C.
- Code must adhere to the Norm.
- No memory leaks or data races are tolerated.
- Provide a Makefile to compile the program with flags `-Wall -Wextra -Werror`.
- The Makefile must include rules for `all`, `clean`, `fclean`, and `re`.

## Functionality

The program should:

- Simulate a group of philosophers who:
  - Alternate between thinking, eating, and sleeping.
  - Share a limited number of forks (one fork is shared between two philosophers).
- Avoid:
  - Deadlocks.
  - Data races.
- Take the following arguments:
  1. Number of philosophers.
  2. Time to die (in milliseconds).
  3. Time to eat (in milliseconds).
  4. Time to sleep (in milliseconds).
  5. (Optional) Number of times each philosopher must eat.

- Display a log of actions:
  - A philosopher takes a fork.
  - A philosopher starts eating.
  - A philosopher starts sleeping.
  - A philosopher starts thinking.
  - A philosopher dies.

### Example Usage

```bash
$ ./philo 5 800 200 200
```

This command will simulate 5 philosophers with:

    A time to die of 800 ms.
    A time to eat of 200 ms.
    A time to sleep of 200 ms.

$ ./philo 5 800 200 200 7

This version includes the optional argument, requiring each philosopher to eat 7 times before stopping.
Key Constraints

    Philosophers must not die due to starvation unless specified by the parameters.
    Use pthread_mutex to manage forks and protect shared resources.
    Use gettimeofday or similar functions for time tracking.
    Avoid busy waiting (use usleep for precision delays).

##Bonuses

If the mandatory part is completed perfectly, consider the following bonus features:

    Implement the program using processes instead of threads (philo_bonus).
    Use semaphores instead of mutexes for synchronization.
    Enhance performance for larger numbers of philosophers and forks.

Bonus files should be named with the _bonus suffix.
Key Concepts to Master

    Multithreading: Using pthread_create and pthread_join to create and manage threads.
    Mutexes: Protect shared resources and avoid race conditions using pthread_mutex.
    Deadlocks: Prevent scenarios where two or more threads wait indefinitely for resources.
    Time Management: Use gettimeofday for accurate timing of philosopher actions.
    Synchronization: Coordinate actions between threads to ensure proper behavior.

Example Output

```bash
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

This log represents a single philosopher taking forks, eating, sleeping, and thinking, all with timestamps in milliseconds.
