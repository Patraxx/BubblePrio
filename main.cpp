#include <iostream>   //Vad faen är knas här. 
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>

using namespace std;

class Task {
    public:
        string name;
        int points;
        int comparisons;  //ska vara compared.size -1
        //en kommentar
        //en till kommentar
        bool done = false;
        vector<string> compared;

    Task(string name) {
        this->name = name;
        this->points = 0;
        this->comparisons = 0;
    }
};
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

vector<Task*> listChoice(int selector){
    
    vector<Task*> tasks;
    
    switch(selector){
            
        case 1:  //cleaning
            tasks.push_back(new Task("Städa köket"));
            tasks.push_back(new Task("Fixa Toaletten"));
            tasks.push_back(new Task("Reda upp sovrummet"));
            return tasks;
    
        case 2:
    
            tasks.push_back(new Task("Göra misselistor"));
            tasks.push_back(new Task("Köpa mutor"));
            tasks.push_back(new Task("Inköpslistor till Ica"));
            tasks.push_back(new Task("Inköpslistor till snabbgross"));
            tasks.push_back(new Task("Sy färdigt klänning"));
            tasks.push_back(new Task("Packa"));
            tasks.push_back(new Task("Städa bilen"));
            tasks.push_back(new Task("Kolla upp sociala medier"));
                return tasks;
            
        default : return tasks;
    }
                                      /*
                                       misselistor
                                       köpa mutor
                                       göra inköpslistor till ica
                                       inköpslista till snabbgross
                                       köpa brosch
                                       sy färdigt klänning
                                       packa
                                       köpa smink
                                       städa bilen
                                       kolla upp sociala medier
                                       
                                       
                                       */
                                      
            
    
    
    
}

void printTasks(const vector<Task*>& tasks) {
    for (const auto& task : tasks) {
        cout << task->name << ": " << task->points << endl;
    }
}

void printMatches(const vector<Task*>& tasks) {
    for (const auto& task : tasks) {
        cout << task->name << ": " <<endl;
        for (auto c: task->compared){
            cout << c << endl;
        }
    }
}

Task* returnTask(vector<Task*> taskList, Task* firstTask, string lastTask, string lastCompared){
    
    for(auto &t : taskList){
      /*  if(t->comparisons == taskList.size()-1){
            continue;
        }*/
             
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

void nullDebug(Task* task, Task* compreTask){
    
    if(task == nullptr)
        cout << "task is NULL";
    
    if(compreTask == nullptr)
        cout << "compareTask is NULL";
    
}




int main() {
    random_device rd;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<Task*> tasks = listChoice(2);
    /*
    tasks.push_back(new Task("Söka praktikplats"));
    tasks.push_back(new Task("Städa skrivbordet"));
    tasks.push_back(new Task("Spela in ett riff"));
    tasks.push_back(new Task("Jobba med Ipad appen"));
    tasks.push_back(new Task("Jobba med den här logiken"));
    tasks.push_back(new Task("Fortsätt på synthwavelåten"));
     */
    
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
            
            /*if(lastCompare == tasks[i]->name){
                continue;
            }*/
        //    shuffle(comparisons.begin(), comparisons.end(), mt19937(seed));
            if(tasks[i]->comparisons == taskNumber - 1){
                continue;
            }
            
            
            //shuffle(comparisons.begin(), comparisons.end(), mt19937(seed));
            
            Task* comparedTask = returnTask(comparisons, tasks[i], lastTask, lastCompare);
          
            displayChoice(*tasks[i], *comparedTask);
            
            selection(*tasks[i], *comparedTask);
            
            lastTask = tasks[i]->name;
            lastCompare = comparedTask->name;
            
        
        }
        for(auto & t: tasks){
           cout << t->name << ": "<< t->comparisons << endl;
        }
        
        done = allCompared(tasks);
    }
    
    sort(tasks.begin(), tasks.end(), [](Task* a, Task* b) {
            return a->points > b->points;
        });
    
    printTasks(tasks);

    //printMatches(tasks);
    
    
    
    
    
    



    return 0;
}
