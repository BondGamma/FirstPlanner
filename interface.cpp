#include "interface.h"
#include "planner.h"

#include <iostream>
#include <limits>
#include <cstdlib>

void InterfaceTerminal::run(){
    system("clear");
    showMainMenu();
    while (m_running){
        int choice {};
        std::cout << "(for help enter 0 else select menu): ";
        if (!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter correct number.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice){
            case 1: 
                createPlanner(); 
                break;
            case 2: 
                listPlanners(); 
                break;
            case 3: 
                deletePlanner(); 
                break;
            case 4:
                subAddTask();
                break;
            case 5:
                system("clear");
                std::cout << "To delete the task(s) select 6\n";
                subTasksDisplay(index);
                break;
            case 6:
                system("clear");
                subDeleteTask(index);
                break;
            case -1: 
                system("clear");
                m_running = false; 
                break;
            case 0:
                system("clear");
                showMainMenu();
                break;
            default: std::cout << "Unknown choice.\n";
                break;
        }
    }
}

void InterfaceTerminal::showMainMenu() const {
    std::cout << "\n*****Planner Menu*****\n";
    std::cout << "1. Create new planner\n";
    std::cout << "2. List planner(s)\n";
    std::cout << "3. Delete planner(s) \n";
    std::cout << "---Planner Operations---\n";
    std::cout << "4. Add task(s) \n";
    std::cout << "5. View task(s) \n";
    std::cout << "6. Delete task(s)\n";
    std::cout << "0. Main menu \n";
    std::cout << "-1. Exit\n";
}

Planner* InterfaceTerminal::createPlanner() {
    std::string name;
    std::cout << "Enter planner name: ";
    std::getline(std::cin, name);

    if (name.empty()){
        std::cout << "Name cannot be empty. Planner not created.\n";
        return nullptr;
    }

    m_planners.reserve(m_planners.size() + 1);
    m_planners.push_back(std::make_unique<Planner>(name));
    std::cout << "Created planner '" << name << "'. \n";
    return m_planners.back().get();
}

void InterfaceTerminal::listPlanners() const noexcept {
    if(m_planners.empty()){
        std::cout << "No planners created.\n";
        return;
    }
    std::cout << "Your planners:\n";
    for (std::size_t i = 0; i < m_planners.size(); ++i) {
        std::cout << " " << (i + 1) << ". " << m_planners[i]->getNickName() << " (" << m_planners[i]->taskCount() << " tasks)\n";
    }
}

void InterfaceTerminal::deletePlanner(){
    InterfaceTerminal::listPlanners();
    if (!(m_planners.empty())){
        std::cout << "Select planner to delete: ";
        int index;
        try {
            if (!(std::cin >> index)){
                std::cin.clear();  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter correct number.\n";
            }
            std::cout << m_planners.at(index - 1)->getNickName() << " has been deleted.\n";
            m_planners.erase(m_planners.begin() + (index - 1));
            m_planners.resize(m_planners.size());
        }
        catch (const std::out_of_range& d){
            std::cout << "Make sure you the list exists! Try again." << '\n';
        }   
    }
}

bool InterfaceTerminal::pickPlanner(std::size_t& index){
    int userInput;
    while (true){
        InterfaceTerminal::listPlanners();

        if (m_planners.empty()){
            std::cout << "No planners available. Create a planner first.\n";
            return false;
        }
        std::cout << "Please choose planner (-1 to exit)\n: ";
        std::cin >> userInput;
        if (userInput == -1){
            return false;
        } else if (!(userInput)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } 

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (userInput < 1 || userInput > static_cast<int>(m_planners.size())){
            std::cout << "Index out of range. Please enter between 1 and " << m_planners.size() << ".\n";
            continue;
        }
        index = static_cast<std::size_t>(userInput - 1);
        return true;
    }

}

 void InterfaceTerminal::proceedAdd(bool& subRun){
    int intInput;
    while(true){
        std::cout << "Add task (Enter 1-> Yes, 0-> No)\n: ";
        if (!(std::cin >> intInput)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter correct number.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (intInput == 0){
            subRun = false;
            break;
        } else if (intInput == 1){
            subRun = true;
            break;
        } else {
            std::cout << "Please enter either 1 or 0.\n";
        }
    }
}

bool InterfaceTerminal::addTask(std::string& taskName, std::size_t& index, bool& subRun){
    std::cout << "Enter the task (-1 to cancel): ";
    std::getline(std::cin, taskName);
    if (taskName.empty()){
        std::cout << "Name cannot be empty. Task not added.\n";
        subRun = false;
        return subRun;
    }
    if (taskName == "-1"){
        subRun = false;
        return subRun;
    } else {
    m_planners[index]->addTask(taskName);
    std::cout << "Task added!\n";
    return subRun;
    }
}

void InterfaceTerminal::subTasksDisplay(std::size_t& index) {
    pickPlanner(index);
    m_planners[index]->displayTasks();
}

void InterfaceTerminal::subAddTask(){
    std::string taskName;
    if (!(pickPlanner(index))){
        return;
    }
    proceedAdd(subRun);
    while(subRun){
        addTask(taskName, index, subRun);
    }
}

void InterfaceTerminal::subDeleteTask(std::size_t& index){
    int userInput;
    std::size_t taskNum;
    // pickPlanner(index);
    subTasksDisplay(index);

    if ((m_planners[index]->taskCount()) == 0){
        std::cout << "No tasks to delete.\n";
        return;
    }
    // subTasksDisplay(index);
    std::cout << "Enter the task number to delete: ";
    if (!(std::cin >> userInput)) {
        std::cin.clear();  
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter correct number.\n";
        return;
    }
    if (userInput < 1 || userInput > static_cast<int>(m_planners[index]->taskCount())){
        std::cout << "Index out of range. Please enter between 1 and " << m_planners[index]->taskCount() << ".\n";
        return;
    }
    taskNum = static_cast<std::size_t>(userInput - 1);
    m_planners[index]->deleteTask(taskNum);
    std::cout << "Task deleted.\n";
}

void InterfaceTerminal::addToFile(){
    std::fstream myFile;
    myFile.open("testing.txt", std::ios::out);
    if (myFile.is_open()){
        for (std::size_t i = 0; i < m_planners.size(); i++){
            myFile << m_planners[i]->getNickName() << "&";
            for (std::size_t x = 0; x < m_planners[i]->taskCount(); x++){
                myFile << "@" << m_planners[i]->getTaskName(x);
            }
            myFile << "\n";
        }
    }
    myFile.close();
}

void InterfaceTerminal::taskReader(){
    std::fstream myFile;
    std::string tempString;
    std::size_t nickNameFlag = 0;
    std::size_t lineCount = 0;
    std::size_t taskCount = 0;
    myFile.open("testing.txt");
    if (myFile.is_open()){
        std::string line;
        while (getline(myFile, line)){
            // std::cout << line << "\n"; ###### Output for debugging purposes
            if (line.empty()){
                return;
            }
            for (std::size_t i = 0; i < line.length(); i++){
                if (line[i] == '&'){
                    for (int x = 0; x < i; x++){
                        tempString.push_back(line[x]);
                    }
                    m_planners.reserve(m_planners.size()+1);
                    m_planners.push_back(std::make_unique<Planner>(tempString));
                    nickNameFlag++;
                    tempString = "";
                } else if (line[i] == '@'){
                    taskCount++;
                    lineCount = i+1;
                    while ((line[lineCount] != '@') && (lineCount < line.length())){
                     tempString.push_back(line[lineCount]);
                     lineCount++;
                    }
                    m_planners[nickNameFlag-1]->addTask(tempString);
                    tempString = "";
                }
            }
        }
    }
    myFile.close();
}