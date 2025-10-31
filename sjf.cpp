#include "time_reader.h"

bool compareSJF(const Task& a, const Task& b) {
    // This compares the burst time and sorts.
    if (a.burst != b.burst) {
        return a.burst < b.burst;
    }
    // Tie-breaker: FCFS
    return a.original_index < b.original_index;
}

/**
 * @brief Simulates non-preemptive SJF scheduling.
 * @param tasks Vector of tasks, will be modified in-place with metrics.
 */
void schedule_sjf(std::vector<Task>& tasks) {
    std::sort(tasks.begin(), tasks.end(), compareSJF);

    int current_time = 0;
    
    for (auto& task : tasks) {
        task.ST = current_time;
        task.RT = task.ST;
        task.WT = task.ST;

        current_time += task.burst;
        
        task.CT = current_time;
        task.TT = task.CT;
    }
}

int main(int argc, char* argv[]) {
    // This checks for the schedule file argument name
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <schedule_file.txt>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Task> tasks = parseScheduleFile(filename);
    // This will output the Results Heading
    std::cout << "SJF Scheduling Results" << std::endl;
    
    schedule_sjf(tasks);
    
    printMetrics(tasks);
    
    return 0;
}