#include "time_reader.h"

void schedule_fcfs(std::vector<Task>& tasks) {
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

    std::cout << "FCFS Scheduling Results" << std::endl;

    schedule_fcfs(tasks);
    
    printMetrics(tasks);
    
    return 0;
}