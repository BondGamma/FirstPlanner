#include "planner.h"

Planner::Planner(const std::string& nickname)
    : m_tasks(), m_nickName(nickname)
{}

void Planner::addTask(const std::string& task){
    m_tasks.push_back(task);
}

bool Planner::deleteTask(std::size_t index){
    if (index >= m_tasks.size()) return false;
    m_tasks.erase(m_tasks.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

void Planner::displayTasks() const{
    if (m_tasks.empty()){
        std::cout << m_nickName << "- no tasks.\n";
        return;
    }
    std::cout << "Tasks for " <<m_nickName << ":\n";
    for (std::size_t i = 0; i < m_tasks.size(); ++i){
        std::cout << (i + 1) << ". " << m_tasks[i] << '\n';
    }
}

const std::string& Planner::getNickName() const noexcept {
    return m_nickName;
}

const std::string& Planner::getTaskName(std::size_t index) const noexcept{
    static const std::string err = "error";
    if (index > taskCount()){
        std::cout << "Index larger than size of tasks.\n";
        return err;
    } else {
        return m_tasks[index];
    }
}

std::size_t Planner::taskCount() const noexcept {
    return m_tasks.size();
}
