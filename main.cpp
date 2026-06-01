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
void printasperstatus(map<int,goal>& todolist);
void printtodolist(map<int,goal>& todolist);
void saveToFile(map<int,goal>& todoList);
void loadFromFile(map<int,goal>& todolist);
void printasperdifficulty(map<int,goal>& todolist);
void removetask(map<int,goal>& todolist);
string lower(string s);

int main(){
    map<int,goal> todolist;

    loadFromFile(todolist);
    cin.clear();

    int choice;
    do{
        cout<<endl<<"             ------TODO LIST MANAGER -------"<<endl;
        cout<<"             1.add new goal to TODO list"<<endl;
        cout<<"             2.update status of a goal"<<endl;
        cout<<"             3.print tasks as per status"<<endl;
        cout<<"             4.print whole Todolist"<<endl;
        cout<<"             5.print tasks as per difficulty "<<endl;
        cout<<"             6.remove task"<<endl;
        cout<<"             7.exit"<<endl<<endl;

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
            printasperstatus(todolist);
            break;
        case 4:
            printtodolist(todolist);
            break;
        case 5:
            printasperdifficulty(todolist);
            break;
        case 6:
            removetask(todolist);
            break;
        case 7:
            saveToFile(todolist);
            cout<<"data saved sucessfully"<<endl;
            break;
        default:
            cout<<"please enter valid choice"<<endl;
            break;
        }
        cout<<endl<<endl;
    }while(choice != 7);
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

    if(!outFile) return;

    long long nextbaseid = 1;
    if (!todolist.empty()) {
        nextbaseid = todolist.rbegin()->first + 1;
    }

    outFile << nextbaseid << "\n"; 

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

    cin.ignore(1000, '\n');

    long long assignedid = 1;
    while (todolist.count(assignedid) > 0) {
        assignedid++;
    }

    cout<<"status of new task will be set to pending by default"<<endl;
    newgoal.status="pending";
    todolist[assignedid]=newgoal;
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

void printasperstatus(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your TodoList is empty"<<endl;
        return;
    }

    string stat;
    do{
        cout<<"enter the status of tasks which u want to print"<<endl;
        cin>>stat;
        stat=lower(stat);
    }while(stat!="done" && stat!="pending");

    bool found=false;

    for(auto& task:todolist){
        if(lower(task.second.status) == stat){
            found=true;
            cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<" Difficulty: "<<task.second.difficulty<<" Status: "<<task.second.status<<endl;
        }
    }
    if(!found){
        cout<<"There are no tasks having status "<<stat<<endl;
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

void printasperdifficulty(map<int,goal>& todolist){
    if(todolist.empty()){
        cout<<"Your todo list is Empty"<<endl;
        return;
    }

    string diff;
    do{
        cout<<"enter the difficulty level of tasks which u want to print "<<endl;
        cin>>diff;
        diff=lower(diff);
    }while(diff!="easy" && diff!="medium" && diff!="hard");

    int choice;
    cout<<"                 1. print completed tasks with difficulty :: "<< diff <<" : "<<endl;
    cout<<"                 2. print all pending tasks with difficulty :: "<<diff <<" : "<<endl;
    cout<<"                 ***any numeric key to print all tasks with difficulty :: "<<diff<<" : "<<endl;

    cout<<"enter your choice"<<endl;
    cin>>choice;

    cin.ignore(1000,'\n');

    bool found=false;

    switch(choice){
        case 1:
            cout<<"Your completed tasks with difficulty level : "<< diff <<" are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.status) == "done" && lower(task.second.difficulty) == diff){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no completed tasks with difficulty level : " <<diff<< " in your todo list "<<endl;
            }
            break;
        case 2:
            cout<<"Your pending tasks with difficulty level : "<<diff<<" are :: "<<endl;;
            for(auto& task: todolist){
                if(lower(task.second.status) == "pending" && lower(task.second.difficulty) == diff){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no pending tasks with difficulty level : "<<diff<<" in your todo list "<<endl;
            }
            break;
        default:
            cout<<"Your tasks with difficulty level : " <<diff<<" are :: "<<endl;
            for(auto& task: todolist){
                if(lower(task.second.difficulty) == diff){
                    found=true;
                    cout<<"Task ID: "<<task.first<<" Task: "<<task.second.name<<endl;
                }
            }

            if(!found){
            cout<<"There are no tasks with difficulty level : "<<diff<<" in your todo list "<<endl;
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