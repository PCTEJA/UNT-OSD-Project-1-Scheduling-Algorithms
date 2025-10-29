#ifndef TIME_READER_H
#define TIME_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm> 
#include <queue>     
#include <map>       

// Task structure to hold all process information
struct Task {
    std::string name;
    int priority;
    int burst;
    // remaining burst time
    int RB; 
    int original_index; 

    int ST; // start time
    // Completion Time
    int CT;
    // waiting time
    int WT;
// turnaround time
    int TT;
// response time
    int RT;

    Task(std::string n, int p, int b, int idx)
        : name(n), priority(p), burst(b), RB(b),
          original_index(idx), ST(-1), CT(0),
          WT(0), TT(0), RT(0) {}
};

// This function named parseScheduleFile will read a schedule file and return the task informaiton to be processed.

std::vector<Task> parseScheduleFile(const std::string& filename) {
    
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        // unable to open file and exit
        std::cerr << "file error with filename:  " << filename << std::endl;
        exit(1); 
    }

    // this is task list
    std::vector<Task> tasks;
    
    std::string line;
    int index = 0; 
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;
        
while (std::getline(ss, segment, ',')) {
            // Trim whitespace from each part
            segment.erase(0, segment.find_first_not_of(" \t\n\r\f\v"));
            segment.erase(segment.find_last_not_of(" \t\n\r\f\v") + 1);
            parts.push_back(segment);
        }

        if (parts.size() == 3) {
            try {
                std::string name = parts[0];
                int priority = std::stoi(parts[1]);
                int burst = std::stoi(parts[2]);
                tasks.emplace_back(name, priority, burst, index++);
            } catch (const std::exception& e) {
                std::cerr << "\n" << std::endl;
                std::cerr << "Got an Error in the line:  " << line << std::endl;
            }
        }
    }
    file.close();
    return tasks;
}

// This function prints the metrics of the finished tasks
void printMetrics(const std::vector<Task>& tasks) {
    // if no task
    if (tasks.empty()) {
        std::cout << "No tasks to process." << std::endl;
        return;
    }
// Total Response Time
double TR = 0;
// Total Waiting Time
    double TWT = 0; 
    double TTT = 0; // Total Turnaround Time
    int n = tasks.size();

    std::cout << "\n" << std::endl;
    std::cout << " Task Metrics " << std::endl;
    
    std::cout << std::left << std::setw(10) << "Task" << std::setw(15) << "Waiting Time"
              << std::setw(18) << "Turnaround Time" << std::setw(16) << "Response Time" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& task : tasks) {
        TWT += task.WT;
        TTT += task.TT;
        TR += task.RT;

        std::cout << std::left << std::setw(10) << task.name
                  << std::setw(15) << task.WT
                  << std::setw(18) << task.TT
                  << std::setw(16) << task.RT << std::endl;
    }
    double AWT = TWT / n;
    double ATT = TTT / n;
    double ART = TR / n;
    std::cout << "\n" << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time :     " << AWT << "ms" << std::endl;
    std::cout << "Average Turnaround Time : " << ATT << " ms" << std::endl;
    std::cout << "Average Response Time : " << ART << "ms" << std::endl;
}

#endif