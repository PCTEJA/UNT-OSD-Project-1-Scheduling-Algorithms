#include "time_reader.h"

const int TIME_QUANTUM = 10;

void schedule_rr(std::vector<Task>& tasks) {
    std::queue<int> ready_queue;
    for (int i = 0; i < tasks.size(); ++i) {
        ready_queue.push(i);
    }

    int current_time = 0;
    int tasks_remaining = tasks.size();

    while (tasks_remaining > 0) {
        int task_index = ready_queue.front();
        ready_queue.pop();
        
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
            ready_queue.push(task_index);
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

    std::cout << "Round-Robin (RR) Scheduling Results (Quantum=10)" << std::endl;
    
    schedule_rr(tasks);
    
    printMetrics(tasks);
    
    return 0;
}