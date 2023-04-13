#include <bits/stdc++.h>

using namespace std;

unordered_map<int, unordered_set<int> > get_precedence_input_graph(int n){
    //gets the input from user and generates a precedence graph
    
    unordered_map<int, unordered_set<int> > pre_graph;
    for(int i=1;i<=n;i++){
        cout<<"ENTER PRECEDENCE TASKS FOR TASK "<<i<<": (enter 0 if no precedence):\n";
        int a;
        while(true){
            cin>>a;
            if(a==0) break;
            pre_graph[i].insert(a);
        }
    }
    return pre_graph;
}

vector<int> generate_sequence_randomly(unordered_map<int, unordered_set<int> > pre, int n){
    
    vector<int> seq;  //holds the sequence generated
    unordered_set<int> s; //available set that holds tasks that can be assigned
    unordered_set<int> assigned; //holds the already assigned tasks
    int no_of_tasks = 0; //number of tasks in the sequence(assigned)
    //creating the available set
    for(int i=1;i<=n;i++){
        if(pre[i].size()==0){
            s.insert(i);
        }
    }
    while(no_of_tasks<n){
        no_of_tasks = no_of_tasks + 1;
        int x = s.size();
        int random = rand()%x;
        unordered_set<int>::iterator it = s.begin();
        advance(it, random);
        seq.push_back(*it);
        assigned.insert(*it);
        //removing the assigned task from available set and adding the tasks that had this task as its precedence in the available set
        int task = *it;
        s.erase(it);
        
        pre.erase(task);
        for(int i=1;i<=n;i++){
            if(assigned.find(i)==assigned.end()){
                if(pre[i].find(task)!=pre[i].end()) pre[i].erase(task);
                if(pre[i].size()==0) s.insert(i);
            }
        }
        
    }

    return seq;
}

int main()
{
    srand(time(0));
    int n; //holds number of tasks
    cout<<"Enter number of tasks : ";
    cin>>n;
    unordered_map<int, unordered_set<int> > pre = get_precedence_input_graph(n);
    for(int i=1;i<=pre.size();i++){
        cout<<i<<"->";
        for(int j:pre[i]){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"\nRANDOMLY GENERATED SEQUENCES:\n";
    for(int i=0;i<5;i++){
        vector<int> seq = generate_sequence_randomly(pre, n);
        for(int i=0;i<seq.size();i++){
            cout<<seq[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
