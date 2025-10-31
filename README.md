## UNT-OSD-Project-1-Scheduling-Algorithms

### The Project is built with 6 Programing file, among these 6 files, 1 file is a header file – which is commonly used among all the other 5 files. The common header file is a time_reader file that is used to print the processing time of each process. The other 5 files are the CPU scheduling algorithm files coded in C++.

#### `The Header File – time_reader.h`: This is a common file used by all the 5 - CPU scheduling algorithms, the main task of this header file is to calculate different metrics and display them in the execution terminal.  This contains 2 functions. 
1. A `parseScheduleFile()` function that reads input from the schedule file and initializes task values.
2. A `printMetrics()` function that calculates and displays waiting time, turnaround time, and response time for each task, along with their averages.

#### First Come First Serve (FCFS) – fcfs.cpp
> The `fcfs.cpp` is used to implement the First Come First Serve - CPU scheduling algorithm. 

#### Shortest Job First (SJF) – sjf.cpp
> The Shortest Job First – `sjf.cpp` file is used to execute a Non-preemptive scheduling algorithm. 

#### Priority Scheduling – priority.cpp
> The `priority.c++` file is used to implement the Non-Preemptive Priority Scheduling algorithm.
> Key Execution Pattern: At the beginning of the algorithm the algorithm starts to sort the processes by considering their priority values, The task with the highest priority value is consider processing at the beginning of the algorithm. The process is sorted in descending order.

#### Round Robin (RR) Scheduling – rr.cpp
> This `rr.cpp` file implements the Round Robin scheduling algorithm with a time quantum of 10 ms.

#### Priority Round Robin Scheduling – priority_rr.cpp
> The `pirority_rr.cpp` file as the name suggests is a mix of both priority scheduling algorithm and the round robin algorithm. 

### Code Execution
#### Deploying the Code
1. > `git clone https://github.com/PCTEJA/UNT-OSD-Project-1-Scheduling-Algorithms.git`
2. > cd `UNT-OSD-Project-1-Scheduling-Algorithms`

#### Generating the executable file
#### Format `g++ -o <Scheduling algorithm name> <Scheduling algorithm File name>`
> **Example:** `g++ -o fcfs fcfs.cpp`

#### Test Case Execution
##### Execution Format
`./<Scheduling Algorithm Name> <Scheduling Test Case Path>`

##### Example
##### Running the `schedule1.txt` file using the `FCFS Scheduling algorithm` 
`./fcfs schedules/schedule1.txt`


