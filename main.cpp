#include <iostream>   //Vad faen är knas här. 
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include "Task.h"
#include "Games.h"

using namespace std;

class Task;

bool comparedBefore(string currentTask, vector<string>& otherTasks){
    for(auto t: otherTasks)
    {
        if(currentTask == t)
            return true;
    }
    return false;
}

void displayChoice(Task& currentTask, Task& compareTask){
    
    cout << "[1] " << currentTask.name << " eller " << "[2] " << compareTask.name << endl << endl;
    
}

void compared(Task &task, Task &otherTask){
    task.compared.push_back(otherTask.name);
    task.comparisons++;
    otherTask.comparisons++;
    otherTask.compared.push_back(task.name);  
}


void choiceHandling(Task &currentTask, Task &compareTask, int choice) {
    compared(currentTask, compareTask);
    (choice == 1) ? currentTask.points++ : compareTask.points++;   //if choice == 1, currentTask.points++, else compareTask.points++
}

void selection(Task &currentTask, Task &compareTask){
    int crash = 0;
    
    int selection;
    
    do {       
        cin >> selection;
        
        if (selection != 1 && selection != 2){
            cout <<"Fel val"<< endl;
            crash++;
        }
        if(crash > 5){
            break;
        }
        
    }while (selection != 1 && selection != 2);
    
    
    choiceHandling(currentTask, compareTask, selection);
   
}

bool doneComparisons(Task* task){
    
    if (task == NULL)
    return true;
    else
        return false;
    
}

Task* returnTask(vector<Task*> taskList, Task* firstTask, string lastTask, string lastCompared){
    
    for(auto &t : taskList){
             
        if (t->name != firstTask->name &&
                    find(firstTask->compared.begin(), firstTask->compared.end(), t->name) == firstTask->compared.end()) {
                    return t;
                }
    }
    return nullptr;
}

bool allCompared(vector<Task*> tasks){
    
    for(auto t: tasks){
        if(t->comparisons != tasks.size() - 1)
            return false;
    }
    return true;
}


int main() {
    
    random_device rd;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<Task*> tasks = listChoice(2);
  
     
    
    vector<Task*> comparisons = tasks;
    
    shuffle(comparisons.begin(), comparisons.end(), mt19937(seed));
       
    
    int taskNumber = tasks.size();
    
    
    
    cout << "Välkommen till din todo-lista!" << endl << endl;
    

    cout << "Vilka av dessa två aktiviteter är viktigast?" <<endl <<endl;
    
    
    string lastTask;
    string lastCompare;
    
   
    
    bool done = false;
    
    
    while(!done){
        

        for (int i = 0; i < taskNumber; i++) {  
         
            shuffle(comparisons.begin(), comparisons.end(), mt19937(seed));
            
            if(tasks[i]->comparisons == taskNumber - 1){
                continue;
            }
            
            Task* comparedTask = returnTask(comparisons, tasks[i], lastTask, lastCompare);
          
            displayChoice(*tasks[i], *comparedTask);
            
            selection(*tasks[i], *comparedTask);
            
            lastTask = tasks[i]->name;
            lastCompare = comparedTask->name;
            
        
        }
        done = allCompared(tasks);
    }
    
    sort(tasks.begin(), tasks.end(), [](Task* a, Task* b) {
            return a->points > b->points;
        });
    
    printTasks(tasks);

    return 0;
}
