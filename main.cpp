#include<bits/stdc++.h>
using namespace std;

long long taskid=1;

typedef struct{
    string name;
    string difficulty;//easy,medium,hard
    string status;//wheather completed or not
}goal;

void insertgoal(map<int,goal>& todolist);
void updatestatus(map<int,goal>& todolist);
void printpending(map<int,goal>& todolist);
void printdone(map<int,goal>& todolist);
void printtodolist(map<int,goal>& todolist);
void saveToFile(map<int,goal>& todoList);
void loadFromFile(map<int,goal>& todolist);
void printeasy(map<int,goal>& todolist);
void printmedium(map<int,goal>& todolist);
void printhard(map<int,goal>& todolist);
void removetask(map<int,goal>& todolist);
string lower(string s);

int main(){
    map<int,goal> todolist;

    loadFromFile(todolist);
    cout<<endl;
    int choice;
    do{
        cout<<"             ------TODO LIST MANAGER -------"<<endl;
        cout<<"             1.add new goal to TODO list"<<endl;
        cout<<"             2.update status of a goal"<<endl;
        cout<<"             3.print goals which are completed"<<endl;
        cout<<"             4.print goals which are not completed yet"<<endl;
        cout<<"             5.print whole Todolist"<<endl;
        cout<<"             6.print easy tasks"<<endl;
        cout<<"             7.print medium tasks"<<endl;
        cout<<"             8.print hard tasks"<<endl;
        cout<<"             9.remove task"<<endl;
        cout<<"             10.exit"<<endl<<endl;

        cout<<"enter your choice"<<endl;

        if (!(cin >> choice)) {
            cout << "Please enter a valid numeric choice." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cout<<endl;
        
        cin.ignore(1000, '\n');

        switch(choice){
        case 1:
            insertgoal(todolist);
            break;
        case 2:
            updatestatus(todolist);
            break;
        case 3:
            printdone(todolist);
            break;
        case 4:
            printpending(todolist);
            break;
        case 5:
            printtodolist(todolist);
            break;
        case 6:
            printeasy(todolist);
            break;
        case 7:
            printmedium(todolist);
            break;
        case 8:
            printhard(todolist);
            break;
        case 9:
            removetask(todolist);
            break;
        case 10:
            saveToFile(todolist);
            cout<<"data saved sucessfully"<<endl;
            break;
        default:
            cout<<"please enter valid choice"<<endl;
            break;
        }
        cout<<endl<<endl;
    }while(choice != 10);
    return 0;
}

string lower(string s){
    string temp="";
    for(auto& c:s){
        temp+=tolower(c);
    }
    return temp;
}

void saveToFile(map<int, goal>& todolist) {
    ofstream outFile("todo_data.txt");

    outFile << taskid << "\n"; 

    for (auto& pair : todolist) {
        outFile << pair.first << "," 
                << pair.second.name << "," 
                << pair.second.difficulty << "," 
                << pair.second.status << "\n";
    }
    outFile.close();
}

void loadFromFile(map<int,goal>& todolist){
    ifstream inFile("todo_data.txt");
    if (!inFile) return;

    inFile >> taskid;
    inFile.ignore();

    int id;
    char comma;
    goal temp;

    while (inFile >> id >> comma) {
        getline(inFile, temp.name, ',');
        getline(inFile, temp.difficulty, ',');
        getline(inFile, temp.status);
        
        todolist[id] = temp;
    }
    inFile.close();
}

void insertgoal(map<int,goal>& todolist){
    goal newgoal;
    cout<<"enter the name of your new task"<<endl;
    getline(cin,newgoal.name);

    string diff;
    do {
        cout << "Enter difficulty of your task i.e. easy/medium/hard : ";
        cin >> diff;
        diff = lower(diff);
    } while (diff != "easy" && diff != "medium" && diff != "hard");
    newgoal.difficulty = diff;

    cout<<"status of new task will be set to pending by default"<<endl;
    newgoal.status="Pending";
    todolist[taskid]=newgoal;
    taskid++;
}

void updatestatus(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"The list is empty"<<endl;
        return;
    }
    printtodolist(todolist);
    cout<<"enter the taskid of the task which u want to update the status"<<endl;
    long long id;
    cin>>id;
    cin.ignore(1000,'\n');

    if(todolist.count(id) == 0){
        cout<<"[ERROR] Task ID not found!"<<endl;
        return;
    }

    string str;
    cout<<"enter the status which you wnat to set to this task either Done or Pending"<<endl;
    cin>>str;
    todolist[id].status=str;
    cout<<"Updated Sucessfully"<<endl;
}
void printpending(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your TodoList is empty"<<endl;
        return;
    }
    bool found=false;
    for(auto& task:todolist){
        if(lower(task.second.status) == "pending"){
            found=true;
            cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<" Difficulty: "<<task.second.difficulty<<" Status: "<<task.second.status<<endl;
        }
    }
    if(!found){
        cout<<"There are no pending tasks for you "<<endl;
    }
}

void printdone(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your TodoList is empty"<<endl;
        return;
    }
    bool found=false;
    for(auto& task:todolist){
        if(lower(task.second.status) == "done"){
            found=true;
            cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<" Difficulty: "<<task.second.difficulty<<" Status: "<<task.second.status<<endl;
        }
    }
    if(!found){
        cout<<"There are no completed tasks "<<endl;
    }
}

void printtodolist(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your TodoList is empty"<<endl;
        return;
    }
    for(auto& task:todolist){
        cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<" Difficulty: "<<task.second.difficulty<<" Status: "<<task.second.status<<endl;
        
    }
}

void printeasy(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your todo list is Empty"<<endl;
        return;
    }
    int choice;
    cout<<"                 1. print completed tasks with difficulty :: easy "<<endl;
    cout<<"                 2. print all pending tasks with difficulty :: easy "<<endl;
    cout<<"                 ***any numeric key to print all easy tasks"<<endl;

    cout<<"enter your choice"<<endl;
    cin>>choice;

    cin.ignore(1000,'\n');

    bool found=false;

    switch(choice){
        case 1:
            cout<<"Your completed tasks with difficulty level : easy are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.status) == "done" && lower(task.second.difficulty) == "easy"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no completed tasks with difficulty level : easy in your todo list "<<endl;
            }
            break;
        case 2:
            cout<<"Your pending tasks with difficulty level : easy are :: "<<endl;;
            for(auto& task: todolist){
                if(lower(task.second.status) == "pending" && lower(task.second.difficulty) == "easy"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no pending tasks with difficulty level : easy in your todo list "<<endl;
            }
            break;
        default:
            cout<<"Your tasks with difficulty level : easy are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.difficulty) == "easy"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no tasks with difficulty level : easy in your todo list "<<endl;
            }
            break;
    }
}

void printmedium(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your todo list is Empty"<<endl;
        return;
    }
    int choice;
    cout<<"                 1. print completed tasks with difficulty :: medium "<<endl;
    cout<<"                 2. print all pending tasks with difficulty :: medium "<<endl;
    cout<<"                 ***any numeric key to print all medium tasks"<<endl;

    cout<<"enter your choice"<<endl;
    cin>>choice;

    cin.ignore(1000,'\n');

    bool found=false;

    switch(choice){
        case 1:
            cout<<"Your completed tasks with difficulty level : medium are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.status) == "done" && lower(task.second.difficulty) == "medium"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no completed tasks with difficulty level : medium "<<endl;
            }
            break;
        case 2:
            cout<<"Your pending tasks with difficulty level : medium are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.status) == "pending" && lower(task.second.difficulty) == "medium"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no pending tasks with difficulty level : medium "<<endl;
            }
            break;
        default:
            cout<<"Your tasks with difficulty level : medium are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.difficulty) == "medium"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no tasks with difficulty level : medium"<<endl;
            }
            break;
    }
}

void printhard(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your todo list is Empty"<<endl;
        return;
    }
    int choice;
    cout<<"                 1. print completed  tasks with difficulty :: hard"<<endl;
    cout<<"                 2. print pending  tasks with difficulty :: hard "<<endl;
    cout<<"                 ***any numeric key to print all hard tasks"<<endl;

    cout<<"enter your choice"<<endl;
    cin>>choice;

    cin.ignore(1000,'\n');

    bool found=false;

    switch(choice){
        case 1:
            cout<<"Your completed tasks with difficulty level : hard are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.status) == "done" && lower(task.second.difficulty) == "hard"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no completed tasks with difficulty level : hard "<<endl;
            }
            break;
        case 2:
            cout<<"Your pending tasks with difficulty level : hard are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.status) == "pending" && lower(task.second.difficulty) == "hard"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no pending tasks with difficulty level : hard "<<endl;
            }
            break;
        default:
            cout<<"Your tasks with difficulty level : hard are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.difficulty) == "hard"){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no tasks with difficulty level : hard"<<endl;
            }
            break;
    }
}

void removetask(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your TodoList is empty"<<endl;
        return;
    }

    printtodolist(todolist);

    long long id;

    cout<<"enter the Task id of task which u want to remove"<<endl;
    cin>>id;

    cin.ignore(1000,'\n');

    if(todolist.count(id) > 0){
        todolist.erase(id);
        cout<<"Task with Task id : "<<id<<" erased sucsessfully"<<endl;
    }
    else{
        cout<<" [ERROR]Task with Task id : "<<id<<" is not found"<<endl;
    }
}