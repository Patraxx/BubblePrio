#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>

using namespace std;

class Task {
    public:
        string name;
        int points;
        int comparisons;  //ska vara compared.size -1
        //en kommentar
        //en till kommentar
        vector<string> compared;

    Task(string name) {
        this->name = name;
        this->points = 0;
        this->comparisons = 0;
    }
};
void debug(Task task)
{
    cout << task.points <<endl;
}

void debugComparisons(Task task){
    
    cout << "[1] Har redan matchats med: " << endl;
    for(auto c: task.compared){
        cout << c << endl;
    }
}


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
    
      //debug(currentTask);
     // debugComparisons(currentTask);
        
}

void compared(Task &task, Task &otherTask){
    task.compared.push_back(otherTask.name);
    task.comparisons++;
    otherTask.comparisons++;
    otherTask.compared.push_back(task.name);
    
    
    //cout << "Added "<<otherTask.name<< " to compared list of " << task.name<< endl;
  //  cout << "Added "<<task.name<< " to compared list of " << otherTask.name<< endl;
    
}



void choiceHandling(Task &currentTask, Task &compareTask, int choice){
    
    compared(currentTask, compareTask);
    
    if(choice == 1)
    {
        currentTask.points ++;
    }
    else
    {
        compareTask.points++;
    }
}


void selection(Task &currentTask, Task &compareTask){
    
    int selection;
    
    do {
        
        cin >> selection;
        
        if (selection != 1 && selection != 2){
            cout <<"Fel val"<< endl;
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

void printTasks(const vector<Task*>& tasks) {
    for (const auto& task : tasks) {
        cout << task->name << ": " << task->points << endl;
    }
}

Task* returnTask(vector<Task*> taskList, Task* firstTask){
    
    for(auto &t : taskList){
    
        if (t->name != firstTask->name &&
                    find(firstTask->compared.begin(), firstTask->compared.end(), t->name) == firstTask->compared.end()) {
                    return t;
                }
    }
    return nullptr;
}





int main() {
    random_device rd;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<Task*> tasks;
    tasks.push_back(new Task("Söka praktikplats"));
    tasks.push_back(new Task("Städa skrivbordet"));
    tasks.push_back(new Task("Spela in ett riff"));
    tasks.push_back(new Task("Jobba med Ipad appen"));
    tasks.push_back(new Task("Jobba med den här logiken"));
    tasks.push_back(new Task("Fortsätt på synthwavelåten"));
    
    vector<Task*> comparisons = tasks;
       
    
    int taskNumber = tasks.size();
    
    
    
    cout << "Välkommen till din todo-lista!" << endl << endl;
    

    cout << "Vilka av dessa två aktiviteter är viktigast?" <<endl <<endl;
    
   
    
    bool done = false;
    
    
    while(!done){
        
       // shuffle(tasks.begin(), tasks.end(), mt19937(seed));   //Lista av tasks shufflas
        
        
        for (int i = 0; i < taskNumber; i++) {   //Gå igenom listan i ny ordning
            
            shuffle(comparisons.begin(), comparisons.end(), mt19937(seed));
            
            Task* comparedTask = returnTask(tasks, tasks[i]);
            if(comparedTask == NULL){
                done = true;
                break;
            }
                
            
            displayChoice(*tasks[i], *comparedTask);
            
            selection(*tasks[i], *comparedTask);
            
        
        }
       
    }
    
    sort(tasks.begin(), tasks.end(), [](Task* a, Task* b) {
            return a->points > b->points;
        });
    
    printTasks(tasks);
    
    
    
    
    
    



    return 0;
}
