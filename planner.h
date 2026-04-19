#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Planner {
public:
    explicit Planner(const std::string& m_nickName);

    void addTask(const std::string& task);
    bool deleteTask(std::size_t index);
    void displayTasks() const;
    std::size_t taskCount() const noexcept;

    
    const std::string& getNickName() const noexcept;
    const std::string& getTaskName(std::size_t index) const noexcept;

    
private:
    std::vector<std::string> m_tasks {};
    std::string m_nickName {};


};

#endif