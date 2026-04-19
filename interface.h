#ifndef INTERFACE_H
#define INTERFACE_H

#include "planner.h"
#include <memory>


class InterfaceTerminal {
private:

    void showMainMenu() const;
    Planner* createPlanner();
    void listPlanners() const noexcept;
    void deletePlanner();
    bool pickPlanner(std::size_t& index);

    void subAddTask();
    void proceedAdd(bool& subRun);
    bool addTask(std::string& taskName, std::size_t& index, bool& subRun);
    void subTasksDisplay(std::size_t& index);
    void subDeleteTask(std::size_t& index);

    void addToFile();
    void taskReader();
    

    std::vector<std::unique_ptr<class Planner>> m_planners;
    bool m_running { true };
    bool subRun { true };
    std::size_t index;


    

public:
    InterfaceTerminal(){
        taskReader();
    }
    ~InterfaceTerminal(){
        addToFile();
    }
    void run();

};


#endif 
