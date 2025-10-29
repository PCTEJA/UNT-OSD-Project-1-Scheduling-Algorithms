#include "time_reader.h"

const int TIME_QUANTUM = 10;

void schedule_priority_rr(std::vector<Task>& tasks) {
    // Map of queues, sorted by priority (highest first)
    std::map<int, std::queue<int>, std::greater<int>> priority_map;

    for (int i = 0; i < tasks.size(); ++i) {
        priority_map[tasks[i].priority].push(i);
    }

    int current_time = 0;
    int tasks_remaining = tasks.size();

    while (tasks_remaining > 0) {
        auto it = priority_map.begin();
        if (it == priority_map.end()) break; 

        std::queue<int>& current_queue = it->second;
        
        int task_index = current_queue.front();
        current_queue.pop();

        Task& current_task = tasks[task_index];

        if (current_task.ST == -1) {
            current_task.ST = current_time;
        }

        int time_slice = std::min(TIME_QUANTUM, current_task.RB);
        
        current_time += time_slice;
        current_task.RB -= time_slice;

        if (current_task.RB == 0) {
            current_task.CT = current_time;
            tasks_remaining--;
        } else {
            current_queue.push(task_index);
        }

        if (current_queue.empty()) {
            priority_map.erase(it);
        }
    }

    for (auto& task : tasks) {
        task.TT = task.CT;
        task.RT = task.ST;
        task.WT = task.TT - task.burst;
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <schedule_file.txt>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Task> tasks = parseScheduleFile(filename);
    
    std::cout << "Priority with Round-Robin (PRR) Scheduling Results" << std::endl;
    
    schedule_priority_rr(tasks);
    
    printMetrics(tasks);
    
    return 0;
}