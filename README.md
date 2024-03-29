Operating Systems Project 1
===========================

# Part 1: Multithreaded Sorting Algorithm

![alt text](https://www.coursehero.com/qa/attachment/17486375/)

**Introduction:**
- This program aims to utilize multiple threads to efficiently sort a set of numbers
- The user provided set of numbers is put into a global array, then is split in half
- After sorting each half is sorted, a final sorted array is built

**Implementation:**
- The user is prompted for some numbers which is parsed into a dynamic vector
- Two threads are created and assigned a half of the vector to sort concurrently
- Once each half is sorted, a third thread is created to join the sorting threads’ results into a single sorted array


# Part 2: CPU Scheduling Simulator

**Introduction:**
* This program aims to simulate various preemptive and non-preemptive CPU scheduling
algorithms
* These include First Come First Serve (FCFS), Shortest Job First (SJF), Preemptive
Priority, and Round Robin scheduling
* Tasks are read from a local text file containing a matrix of values where rows represent a task, and 4 columns represent PID, Arrival Time, Burst Time, Priority
    - **Pid** is a unique numeric process ID.
    - **Arrival_Time** is the time when the task arrives.
    - **Burst_Time** is the CPU time requested by a task.
    - **Priority** is the priority associated with each task with low numbers representing high priority.

**Implementation:**
* User is prompted for their input file, scheduling algorithm, and time quantum if Round
Robin is chosen
* The tasks and their values are parsed into a vector and given default values for remaining,
waiting, start, and completion time

* **First Come First Serve (FCFS):**
    * Current task to execute is chosen as the task that arrived earliest of those that are
ready
    * Each time unit, the current task is executed, its start time is marked if executed for
the first time, remaining time is decremented, and completion time is marked if its
burst is completed
    * If any tasks have arrived and have burst time remaining, their waiting time is
incremented
    * Progress is printed at each time unit

* **Shortest Job First (SJF):**
    * Current task to execute is the shortest burst time task of those that have arrived
    * Each time unit, the current task is executed, its start time is marked if executed for
the first time, remaining time is decremented, and completion time is marked if its
burst is completed
    * If any tasks have arrived and have burst time remaining, their waiting time is
incremented
    * Progress is printed at each time unit

* **Preemptive Priority:**
    * Current task to execute is chosen as the highest priority task of those that have
arrived
    * Each time unit, the current task is executed, its start time is marked if executed for
the first time, remaining time is decremented, and completion time is marked if its
burst is completed
    * If a new task arrives with a higher priority than the current task, it is preempted by
the new task and put in a waiting state
    * If any tasks have arrived and have burst time remaining, their waiting time is
incremented
    * Progress is printed at each time unit

* **Round Robin:**
    * Current task to execute is chosen as the task that arrived earliest of those that are
ready
    * Each time unit, the current task is executed, its start time is marked if executed for
the first time, remaining time is decremented, and completion time is marked if its
burst is completed
    * Current task is executed for as long as the given time quantum or until it’s
completed
    * If a task needs more time to complete after the end of the time quantum, it is
pushed to the back of the ready queue
    * If any tasks have arrived and have burst time remaining, their waiting time is
incremented
    * Progress is printed at each time unit

# How to execute
**Multithreaded Sorting Application**
1. Execute multithread_sort.exe in command line
2. Input a set of numbers with spaces(ex:  7 8 1 9 2 10 4)

**CPU Scheduling Simulator**
1. Execute scheduling.exe in command line
2. Input text file name
3. Input 1, 2, 3, or 4 for a scheduling algorithm to run
4. Input time quantum value if choosing Round Robin(4)

# Conclusion:
- In this project, I successfully implemented multithreaded programming and simulating
CPU scheduling algorithms. This experience gave me a much deeper understanding of these
concepts, especially scheduling. They are simple on paper when only needing to order the
processes or create a Gantt chart, but implementing them in code showed me some of the edge
cases to consider. For example, when using Preemptive Priority if a task is of low priority but no
higher priority tasks are ready, execute it until one does become ready in order to keep CPU
utilization high. Printing the progress of each process at each time unit also helped me visualize
each step of execution and debug my code. This project helped me understand the concepts
taught in class and I feel more confident about my understanding of operating systems.
