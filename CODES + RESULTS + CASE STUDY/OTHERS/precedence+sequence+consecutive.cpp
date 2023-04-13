#include <bits/stdc++.h>

using namespace std;

class PSO{
    
    //variables and parameters used in PSO
public:
    int no_of_tasks;
    int no_of_stations;
    int p; //no of particles in the swarm
    vector<vector<int> > population; //stores the population 
    vector<vector<int> > input_data
    {
        {81, 109, 65, 51, 92, 77, 51, 50, 43, 45, 76}, //Robot 1's time taken for ith activity
        {37, 101, 80, 41, 36, 65, 51, 42, 76, 46, 38},
        {51, 90, 38, 91, 33, 83, 40, 34, 41, 41, 83},
        {49, 42, 52, 40, 25, 71, 49, 44, 33, 77, 87}
    };
    unordered_map<int, unordered_set<int> > pre_graph;
    
    
    //getting input from user
    void get_input(){
    //gets the input from user and generates a precedence graph
        cout<<"Enter number of tasks : ";
        cin>>no_of_tasks;
        cout<<"Enter number of stations : ";
        cin>>no_of_stations;
        for(int i=1;i<=no_of_tasks;i++){
            cout<<"ENTER PRECEDENCE TASKS FOR TASK "<<i<<": (enter 0 if no precedence):\n";
            int a;
            while(true){
                cin>>a;
                if(a==0) break;
                pre_graph[i].insert(a);
            }
        }

    }
    
    
    //function that generates a single sequnce according to the given precedence relations
    vector<int> generate_sequence_randomly(unordered_map<int, unordered_set<int> > pre){
    
        vector<int> seq;  //holds the sequence generated
        unordered_set<int> s; //available set that holds tasks that can be assigned
        unordered_set<int> assigned; //holds the already assigned tasks
        int n = 0; //number of tasks in the sequence(assigned)
        //creating the available set
        for(int i=1;i<=no_of_tasks;i++){
            if(pre[i].size()==0){
                s.insert(i);
            }
        }
        while(n<no_of_tasks){
            n = n + 1;
            int x = s.size();
            int random = rand()%x;
            unordered_set<int>::iterator it = s.begin();
            advance(it, random);
            seq.push_back(*it);
            assigned.insert(*it);
            //removing the assigned task from available set and adding the tasks that had this task as its precedence in the available set
            int task = *it;
            s.erase(it);
        
            for(int i=1;i<=no_of_tasks;i++){
                if(assigned.find(i)==assigned.end()){
                    if(pre[i].find(task)!=pre[i].end()) pre[i].erase(task);
                    if(pre[i].size()==0) s.insert(i);
                }
            }
        
        }

        return seq;
    }
    
    
    //generates multiple sequences according to the population size
    void generate_population(){
        cout<<"Enter the population size : ";
        cin>>p;
        for(int i=0;i<p;i++){
            population.push_back(generate_sequence_randomly(pre_graph));
        }    
    }
    
    
    //objective function calculation (cycle time)
    int objective_function(vector<int> tasks){
    //(i,j) -> i defines the robot number and j defines the activity number (input_data)
    
    //tasks = given sequence of task allocation by the optimization algorithm
    
        int cycle_time = 0;  
        int no_robots = input_data.size(); //no of rows in the input_data matrix
        int no_tasks = input_data[0].size();  //no of cols in the input_data matrix
    
    //for getting the min time possible for that allocation (using the formula given in slides)
        for(int j=0;j<no_tasks;j++){
            int min_time = INT_MAX;   //min time taken by the robots to complete the ith task
            for(int i=0;i<no_robots;i++){
                min_time = min(min_time, input_data[i][j]);
            }
            cycle_time+=min_time;
        }
        cycle_time = cycle_time / no_of_stations;
    
        //cout<<endl<<"INITIAL CYCLE TIME : "<<cycle_time<<endl;
        while(true){
        //assigning the start task for the robots
            int start = 0;
            int si;
        //iterating through each station for given cycle time
            for(int s=0;s<no_of_stations;s++){
                si = start;  //si = start index
        
            //if all tasks assigned, the while loop ends
                if(si>=no_tasks) break;
            
                int n = 0; //most no of tasks assigned to a robot in that station
                for(int  r = 0; r<no_robots; r++){
                    int t = 0; //respective time taken by that robot in that station
                    si = start;
                    while(t<cycle_time){
                        if(si>=no_tasks) break;
                        t+=input_data[r][tasks[si]-1];  
                        if(t>cycle_time) break;
                        si++;
                    }
            
                    n = max(n, si-start); //(si-start)= no of tasks assigned to that particular robot
                }
            
                start+=n;
            }
        
            if(start>=no_tasks){
                break;
            }
            else cycle_time++;
        }
    
        return cycle_time;
    }
    
    
    //to print the current population and its function value
    void print_population(){
        for(int i=0;i<population.size();i++){
            for(int j=0;j<population[i].size();j++){
                cout<<population[i][j]<<" ";
            }
            cout<<"  =  "<<objective_function(population[i]);
            cout<<endl;
        }
    }
    
    
    
    
};


int main()
{
   srand(time(0));
   PSO object;
   object.get_input();
   object.generate_population();
   object.print_population();
   
   return 0;
}
