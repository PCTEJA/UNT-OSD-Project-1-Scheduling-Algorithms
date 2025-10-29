#include "time_reader.h"

bool comparePriority(const Task& a, const Task& b) {
    if (a.priority != b.priority) {
        // Higher numeric value = higher priority
        return a.priority > b.priority;
    }
    // Tie-breaker: FCFS
    return a.original_index < b.original_index;
}


void schedule_priority(std::vector<Task>& tasks) {
    std::sort(tasks.begin(), tasks.end(), comparePriority);

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
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <schedule_file.txt>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Task> tasks = parseScheduleFile(filename);
    
    std::cout << "Priority (Non-Preemptive) Scheduling Results" << std::endl;
    
    schedule_priority(tasks);
    
    printMetrics(tasks);
    
    return 0;
}