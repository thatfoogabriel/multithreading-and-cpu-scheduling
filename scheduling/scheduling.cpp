#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

// Struct for each task
struct Task {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int start_time;
    int completion_time;
};

// Print task progress at each time unit
void printProgress(const vector<Task>& tasks, int currentTime) {
    cout << "Time " << currentTime << ":" << endl;
    cout << "PID\tArrival Time\tBurst Time\tPriority\tRemaining Time\tWaiting Time\tStart Time\tCompletion Time" << endl;
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << tasks[i].pid << "\t" << tasks[i].arrival_time << "\t\t" << tasks[i].burst_time << "\t\t" 
            << tasks[i].priority << "\t\t" << tasks[i].remaining_time << "\t\t" << tasks[i].waiting_time << "\t\t" 
            << (tasks[i].start_time == -1 ? 0 : tasks[i].start_time) << "\t\t" << tasks[i].completion_time << "\t\t" << endl;
    }
    cout << endl;
}

void FCFS(vector<Task>& tasks) {
    // Sort by arrival time
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Calculate initial values
    for (auto& task : tasks) {
        task.remaining_time = task.burst_time;
        task.start_time = -1;
        task.waiting_time = 0;
    }

    int currentTime = 0;
    // Print initial state
    printProgress(tasks, currentTime);

    while (true) {
        bool allTasksCompleted = true;
        bool taskExecuted = false;

        for (size_t i = 0; i < tasks.size(); ++i) {
            // Check if task is ready and not completed
            if (currentTime >= tasks[i].arrival_time && tasks[i].remaining_time > 0) {
                allTasksCompleted = false;
                if (!taskExecuted) {
                    // Mark start time and initial wait time
                    if (tasks[i].start_time == -1) {
                        tasks[i].start_time = currentTime;
                        tasks[i].waiting_time = currentTime - tasks[i].arrival_time;
                    }

                    // Execute task for one time unit
                    tasks[i].remaining_time--;
                    currentTime++;

                    // Increment waiting time for other ready tasks
                    for (size_t k = 0; k < tasks.size(); ++k) {
                        if (k != i && currentTime >= tasks[k].arrival_time && tasks[k].remaining_time > 0) {
                            tasks[k].waiting_time++;
                        }
                    }

                    // Update completion time on complete
                    if (tasks[i].remaining_time == 0) {
                        tasks[i].completion_time = currentTime;
                    }

                    // Mark task as complete and print progress
                    printProgress(tasks, currentTime);
                    taskExecuted = true;
                }
            }
        }
        if (allTasksCompleted) {
            break;
        }
    }
}

void SJF(vector<Task>& tasks) {
    // Sort by arrival time
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Calculate initial values
    for (auto& task : tasks) {
        task.remaining_time = task.burst_time;
        task.start_time = -1;
        task.waiting_time = 0;
    }

    int currentTime = 0;
    // Print initial state
    printProgress(tasks, currentTime);

    while (true) {
        bool allTasksCompleted = true;
        bool taskExecuted = false;
        size_t shortestJobIndex = -1;

        // Find shortest ready task
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (currentTime >= tasks[i].arrival_time && tasks[i].remaining_time > 0) {
                if (shortestJobIndex == -1 || tasks[i].remaining_time < tasks[shortestJobIndex].remaining_time) {
                    shortestJobIndex = i;
                }
            }
        }

        if (shortestJobIndex != -1) {
            // Increment waiting time for other ready tasks
            for (size_t k = 0; k < tasks.size(); ++k) {
                if (k != shortestJobIndex && currentTime >= tasks[k].arrival_time && tasks[k].remaining_time > 0) {
                    tasks[k].waiting_time++;
                }
            }

            // Mark starting time
            if (tasks[shortestJobIndex].start_time == -1) {
                tasks[shortestJobIndex].start_time = currentTime;
            }

            // Execute task for one time unit
            tasks[shortestJobIndex].remaining_time--;
            currentTime++;

            // Update completion time on complete
            if (tasks[shortestJobIndex].remaining_time == 0) {
                tasks[shortestJobIndex].completion_time = currentTime;
            }

            // Mark task as complete and print progress
            printProgress(tasks, currentTime);
            taskExecuted = true;
        }

        // Check if all tasks are completed
        for (const auto& task : tasks) {
            if (task.remaining_time > 0) {
                allTasksCompleted = false;
                break;
            }
        }

        if (allTasksCompleted) {
            break;
        }
    }
}


void PreemptivePriority(vector<Task>& tasks) {
    // Sort by arrival time
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Calculate initial values
    for (auto& task : tasks) {
        task.remaining_time = task.burst_time;
        task.start_time = -1;
        task.waiting_time = 0;
    }

    int currentTime = 0;
    // Print initial state
    printProgress(tasks, currentTime);

    while (true) {
        bool allTasksCompleted = true;
        bool taskExecuted = false;

        for (size_t i = 0; i < tasks.size(); ++i) {
            // Check if task is ready and not completed
            if (currentTime >= tasks[i].arrival_time && tasks[i].remaining_time > 0) {
                allTasksCompleted = false;
                if (!taskExecuted) {
                    int highestPriorityTaskIndex = i;
                    // Find task with highest priority
                    for (size_t j = i + 1; j < tasks.size(); ++j) {
                        if (currentTime >= tasks[j].arrival_time && tasks[j].remaining_time > 0 &&
                            tasks[j].priority > tasks[highestPriorityTaskIndex].priority) {
                            highestPriorityTaskIndex = j;
                        }
                    }

                    // Increment waiting time for other ready tasks
                    for (size_t k = 0; k < tasks.size(); ++k) {
                        if (k != highestPriorityTaskIndex && currentTime >= tasks[k].arrival_time && tasks[k].remaining_time > 0) {
                            tasks[k].waiting_time++;
                        }
                    }

                    // Mark starting time
                    if (tasks[highestPriorityTaskIndex].start_time == -1) {
                        tasks[highestPriorityTaskIndex].start_time = currentTime;
                    }

                    // Execute task for one time unit
                    tasks[highestPriorityTaskIndex].remaining_time--;
                    currentTime++;

                    // Update completion time on complete
                    if (tasks[highestPriorityTaskIndex].remaining_time == 0) {
                        tasks[highestPriorityTaskIndex].completion_time = currentTime;
                    }

                    // Mark task as complete and print progress
                    printProgress(tasks, currentTime);
                    taskExecuted = true;
                }
            }
        }
        if (allTasksCompleted) {
            break;
        }
    }
}

void RoundRobin(vector<Task>& tasks, int time_quantum) {
    // Sort tasks by arrival time
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Calculate initial values
    for (auto& task : tasks) {
        task.remaining_time = task.burst_time;
        task.start_time = -1;
        task.waiting_time = 0;
    }

    deque<int> ready_queue;
    int currentTime = 0;
    size_t index = 0;

    // Print initial state
    printProgress(tasks, currentTime);

    while (!ready_queue.empty() || index < tasks.size()) {
        // Add tasks to ready queue
        while (index < tasks.size()) {
            ready_queue.push_back(index);
            index++;
        }

        // Execute tasks in ready queue
        while (!ready_queue.empty()) {
            int task_index = ready_queue.front();
            ready_queue.pop_front();

            // Mark starting time
            if (tasks[task_index].start_time == -1) {
                tasks[task_index].start_time = currentTime;
            }

            // Execute task until completion or until time quantum ends
            int time_executed = min(time_quantum, tasks[task_index].remaining_time);
            for (int i = 0; i < time_executed; ++i) {
                tasks[task_index].remaining_time--;
                currentTime++;

                // Update completion time on complete
                if (tasks[task_index].remaining_time == 0) {
                    tasks[task_index].completion_time = currentTime;
                }

                // Increment waiting time for other ready tasks
                for (size_t k = 0; k < tasks.size(); ++k) {
                    if (k != task_index && currentTime > tasks[k].arrival_time && tasks[k].remaining_time > 0) {
                        tasks[k].waiting_time++;
                    }
                }

                printProgress(tasks, currentTime);
            }
            // Add unfinished task to end of ready queue
            if (tasks[task_index].remaining_time > 0) {
                ready_queue.push_back(task_index);
            }
        }
    }
}

int main() {
    string filename;
    cout << "Enter input file name: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Read from input file
    vector<Task> tasks;
    int pid, arrival_time, burst_time, priority;
    while (infile >> pid >> arrival_time >> burst_time >> priority) {
        tasks.push_back({pid, arrival_time, burst_time, priority, burst_time, 0, 0, 0});
    }
    infile.close();

    // Prompt for scheduling algorithm
    int choice;
    cout 
        << "Choose scheduling algorithm:\n"
        << "1. First Come First Serve (FCFS)\n"
        << "2. Shortest Job First (SJF)\n"
        << "3. Preemptive Priority Scheduling\n"
        << "4. Round Robin (RR)\n";
    cin >> choice;

    // Execute scheduling algorithm
    switch (choice) {
        case 1:
            FCFS(tasks);
            break;
        case 2:
            SJF(tasks);
            break;
        case 3:
            PreemptivePriority(tasks);
            break;
        case 4:
            int time_quantum;
            cout << "Enter time quantum for Round Robin: ";
            cin >> time_quantum;
            RoundRobin(tasks, time_quantum);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }

    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    float total_response_time = 0;
    float total_execution_time = 0;
    float total_time = 0;

    for (const auto& task : tasks) {
        // Calculate statistics
        total_waiting_time += task.waiting_time;
        total_turnaround_time += (task.completion_time - task.arrival_time);
        total_response_time += (task.start_time - task.arrival_time);
        total_execution_time += task.burst_time;
        if (task.completion_time > total_time) {
            total_time = task.completion_time;
        }
    }

    // Output averages
    cout << "Average Waiting Time: " << total_waiting_time / tasks.size() << " ms" << endl;
    cout << "Average Turnaround Time: " << total_turnaround_time / tasks.size() << " ms" << endl;
    cout << "Average Response Time: " << total_response_time / tasks.size() << " ms" << endl;
    cout << "CPU Utilization Rate: " << (total_execution_time / total_time) * 100 << "%" << endl;

    return 0;
}
