#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > get_precedence_input_matrix(){
    //gets the input from user and generates a precedence matrix
    int n; //no of activities
    cin>>n;
    //precedence relation is stored in a nXn matrix where 1 represents task precedence between ith(row) task and jth(col) task and 0 represents no precedence between ith(row) task and jth(col) task
    vector<vector<int> > pre_matrix(n, vector<int> (n,0));
    for(int i=0;i<n;i++){
        cout<<"ENTER PRECEDENCE TASKS FOR TASK "<<i+1<<": (enter 0 if no precedence):\n";
        int a;
        while(true){
            cin>>a;
            if(a==0) break;
            pre_matrix[i][a-1] = 1;
            //if precedence relation between ith row and jth col, then it means that to perform jth task, ith task must be completed
        }
    }
    return pre_matrix;
}



vector<int> generate_sequence_randomly(vector<vector<int> > pre){
    //generates one random feasible sequence from the precedence matrix
    vector<int> sequence;
    //"rand()%x" gives a random number between 0 and x
    unordered_set<int> s; //set to store available tasks that can be allocated whose precedence relations are satisfied
    //finding the tasks which can be started with
    unordered_set<int> assigned_tasks;
    int no_of_tasks = pre.size();
    for(int i=0;i<no_of_tasks;i++){
        bool flag = true;
        for(int j=0;j<no_of_tasks;j++){
            if(pre[i][j]==1){
                flag = false;
                break;
            }
        }
        if(flag) s.insert(i+1);
    }
    int n = 0; //number of assigned tasks
    while(n<no_of_tasks){
        //geenrating a random number to select a random task
        int x = s.size();
        int random = rand()%x;
        n = n + 1;
        //selecting the task at xth position in the availabe tasks set
        int task;
        for(int t: s){
            if(random<=0){
                sequence.push_back(t);
                assigned_tasks.insert(t);
                task = t;
                break;
            }
            random--;
        }
        //removing the assigned task from the available tasks set and inserting the tasks that had this task as its precedence requirement
        s.erase(task);
        task = task - 1; //task holds assigned task in the sequence
        //editing the precedenc matrix according to the assigned task
        for(int i=0;i<no_of_tasks;i++){
            pre[i][task] = 0;
        }
        for(int i=0;i<no_of_tasks;i++){
        bool flag = true;
            for(int j=0;j<no_of_tasks;j++){
                if(pre[i][j]==1){
                    flag = false;
                    break;
                }
            }
            if(flag){
                if(assigned_tasks.find(i+1)==assigned_tasks.end()) s.insert(i+1);
            }
        }
    }
    return sequence;
}


int main()
{
   srand(time(0));
   vector<vector<int> > pre = get_precedence_input_matrix();
   for(int i=0;i<pre.size();i++){
       for(int j=0;j<pre.size();j++){
           cout<<pre[i][j]<<" ";
       }
       cout<<endl;
   }
   cout<<"\nRANDOMLY GENERATED SEQUENCES:\n"
   for(int i=0;i<5;i++){
       vector<int> seq = generate_sequence_randomly(pre);
       for(int i=0;i<seq.size();i++){
           cout<<seq[i]<<" ";
       }
       cout<<endl;
   }
   
   return 0;
}
