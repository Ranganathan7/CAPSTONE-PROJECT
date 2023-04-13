#include <bits/stdc++.h>

using namespace std;

class PSO{
    
    //variables and parameters used in PSO
public:
    int no_of_tasks;
    int no_of_stations;
    double c1, c2, c3; //co-efficients in the updation formula
    int T; //no of iterations to be performed
    int p; //no of particles in the swarm
    vector<vector<int> > population; //stores the population 
    vector<vector<int> > velocity; //stores the velocity of each particle
    vector<int> obj_value; //holds the objective function values of each particle
    vector<vector<int> > input_data
    {
        {81, 109, 65, 51, 92, 77, 51, 50, 43, 45, 76}, //Robot 1's time taken for ith activity
        {37, 101, 80, 41, 36, 65, 51, 42, 76, 46, 38},
        {51, 90, 38, 91, 33, 83, 40, 34, 41, 41, 83},
        {49, 42, 52, 40, 25, 71, 49, 44, 33, 77, 87}
    };
    
    vector<vector<vector<int> > > seq_dependent_time
    {
        {
            {0, 19, 20, 16, 11, 20, 12, 18, 12, 19, 18},
            {10, 0, 10, 14, 11, 10, 17, 15, 16, 10, 10},
            {10, 10, 0, 12, 17, 19, 20, 15, 12, 15, 12},
            {11, 19, 11, 0, 11, 19, 20, 18, 17, 20, 14},
            {17, 13, 15, 17, 0, 10, 10, 18, 19, 10, 16},
            {15, 12, 11, 11, 20, 0, 14, 12, 16, 13, 11},
            {18, 10, 10, 14, 20, 18, 0, 19, 11, 15, 10},
            {15, 20, 20, 13, 10, 16, 11, 0, 11, 14, 11},
            {10, 15, 19, 15, 17, 20, 19, 19, 0, 16, 19},
            {19, 10, 17, 16, 19, 15, 16, 14, 15, 0, 11},
            {13, 13, 20, 17, 12, 19, 18, 16, 18, 17, 0}

        },
        {
            {0, 11, 16, 13, 20, 12, 11, 14, 10, 20, 12},
            {17, 0, 19, 10, 11, 10, 13, 20, 12, 14, 12},
            {11, 10, 0, 20, 17, 18, 15, 13, 14, 11, 12},
            {18, 14, 11, 0, 14, 13, 10, 13, 13, 15, 19},
            {12, 13, 18, 12, 0, 17, 14, 10, 17, 14, 11},
            {19, 13, 18, 14, 19, 0, 17, 18, 10, 14, 20},
            {20, 14, 13, 13, 12, 17, 0, 15, 13, 16, 19},
            {20, 17, 13, 14, 10, 11, 20, 0, 12, 16, 16},
            {18, 19, 12, 14, 15, 20, 14, 19, 0, 12, 10},
            {19, 13, 10, 13, 17, 16, 16, 13, 12, 0, 20},
            {13, 16, 18, 14, 15, 10, 17, 10, 16, 12, 0}
        },
        {
            {0, 15, 11, 15, 19, 10, 20, 10, 19, 18, 11},
            {20, 0, 19, 13, 15, 20, 13, 18, 17, 16, 13},
            {14, 20, 0, 12, 14, 15, 16, 15, 13, 11, 20},
            {15, 16, 16, 0, 14, 15, 20, 11, 16, 19, 12},
            {14, 20, 17, 13, 0, 12, 18, 16, 14, 12, 14},
            {18, 12, 18, 12, 19, 0, 14, 20, 20, 19, 14},
            {16, 20, 18, 19, 19, 19, 0, 16, 19, 19, 15},
            {13, 20, 14, 14, 18, 20, 18, 0, 13, 15, 18},
            {20, 18, 16, 20, 11, 16, 18, 18, 0, 11, 15},
            {15, 20, 13, 11, 13, 17, 19, 20, 10, 0, 18},
            {14, 15, 13, 13, 10, 19, 15, 14, 16, 12, 0}
        },
        {
            {0, 20, 10, 16, 17, 16, 11, 18, 10, 14, 15},
            {11, 0, 17, 19, 11, 16, 17, 13, 11, 10, 16},
            {14, 11, 0, 10, 14, 19, 17, 16, 18, 17, 16},
            {18, 10, 10, 0, 11, 17, 20, 15, 11, 19, 18},
            {16, 15, 20, 10, 0, 10, 11, 11, 14, 14, 11},
            {19, 14, 15, 17, 19, 0, 14, 15, 13, 20, 15},
            {13, 10, 16, 18, 18, 19, 0, 17, 17, 15, 11},
            {16, 15, 13, 14, 15, 12, 18, 0, 11, 17, 10},
            {17, 13, 18, 14, 16, 12, 17, 15, 0, 20, 14},
            {20, 18, 11, 19, 15, 18, 13, 18, 18, 0, 11},
            {19, 10, 14, 19, 18, 10, 10, 12, 19, 15, 0}

        }
    };
    vector<vector<int> > pre_matrix
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}
    };
    vector<vector<int> > setup_time
    {
        {18, 15, 13, 18, 16, 16, 10, 11, 17, 14, 17}, 
        {10, 11, 16, 16, 14, 16, 10, 18, 14, 13, 20}, 
        {19, 14, 13, 18, 19, 18, 20, 14, 19, 17, 17}, 
        {11, 13, 13, 15, 11, 12, 11, 13, 19, 12, 14} 
    };
    unordered_map<int, unordered_set<int> > pre_graph;
    vector<vector<int> > p_best; //holds the particular particles best position
    vector<int> g_best; //holds the global best so far
    vector<int> p_best_value; //holds the function values of p_best and g_best
    int g_best_value;
    vector<int> best;
    int best_value;
    vector<int> counter; //helps tlbo to escape from local minima
    //getting input from user
    void get_input(){
    //gets the input from user and generates a precedence graph
        cout<<"Enter number of tasks : ";
        cin>>no_of_tasks;
        cout<<"Enter number of stations : ";
        cin>>no_of_stations;
        cout<<"Enter number of iterations : ";
        cin>>T;
        best_value = INT_MAX;
        //assuming c1, c2, c3 values
        c1 = 0.5;
        c2 = 0.7;
        c3 = 0.7;
        for(int i=1;i<=no_of_tasks;i++){
            //cout<<"ENTER PRECEDENCE TASKS FOR TASK "<<i<<": (enter 0 if no precedence):\n";
            for(int j=0;j<no_of_tasks;j++){
                if(pre_matrix[i-1][j]==0) continue;
                pre_graph[i].insert(j+1);
            }
        }

    }
    
    
    //function that generates a single sequnce according to the given precedence relations
    vector<int> generate_sequence_randomly(unordered_map<int, unordered_set<int> > pre){
    
        int n = 0; //number of tasks in the sequence(assigned)
        vector<int> seq;  //holds the sequence generated
        unordered_set<int> s; //available set that holds tasks that can be assigned
        unordered_set<int> assigned; //holds the already assigned tasks

        //creating the available set
        for(int i=1;i<=no_of_tasks;i++){
            if(pre[i].size()==0){
                s.insert(i);
            }
        }
        while(n < no_of_tasks){
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
        
            pre.erase(task);
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
        for(int i=0;i<p;i++){
            obj_value.push_back(objective_function(population[i]));
            counter.push_back(0);
        }
    }
    
    
    
    //objective function calculation (cycle time)
    int objective_function(vector<int> tasks){
    //(i,j) -> i defines the robot number and j defines the activity number (input_data)
    
    //tasks = given sequence of task allocation by the optimization algorithm
    
        int cycle_time = 0;  
        int no_robots = input_data.size(); //no of rows in the input_data matrix 
        int no_tasks = no_of_tasks;  //no of cols in the input_data matrix
    
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
                        //adding the sequence dependent times and setup times of the robot
                        t+=setup_time[r][tasks[si]-1];
                        if(si!=start){
                            t+=seq_dependent_time[r][tasks[si]-1][tasks[si-1]-1];
                        }
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
    vector<int> generate_one_velocity(){
        int n = 0;
        vector<int> v;
        unordered_set<int> s;
        for(int i=1;i<=no_of_tasks;i++){
            s.insert(i);
        }
        while(n<no_of_tasks){
            n = n + 1;
            int x = s.size();
            int random = rand()%x;
            unordered_set<int>::iterator it = s.begin();
            advance(it,random);
            v.push_back(*it);
            s.erase(it);
        }
        return v;
    }
    //generates velocity for the whole swarm
    void generate_velocity(){
        for(int i=0;i<p;i++){
            velocity.push_back(generate_one_velocity());
        }
    }
    
    
    
    //prints the current iteration values
    void print_iteration(int t){
        cout<<endl<<"\n\nITERATION "<<t<<" :\n"<<endl;
        cout<<"population = objective function value(cycle_time) :\n";
        for(int i=0;i<p;i++){
            for(int j=0;j<no_of_tasks;j++){
                cout<<population[i][j]<<" ";
            }
            cout<<"  =  "<<obj_value[i];
            cout<<endl;
        }
        cout<<"\nvelocity vectors of each particle :\n";
        for(int i=0;i<p;i++){
            for(int j=0;j<no_of_tasks;j++){
                cout<<velocity[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"\np_best values for each particle :\n";
        for(int i=0;i<p;i++){
            for(int j=0;j<no_of_tasks;j++){
                cout<<p_best[i][j]<<" ";
            }
            cout<<"= "<<p_best_value[i];
            cout<<endl;
        }
        cout<<"\ng_best for the whole swarm :\n";
        for(int i=0;i<no_of_tasks;i++){
            cout<<g_best[i]<<" ";
        }
        cout<<"= "<<g_best_value;
        cout<<endl;
    }
    
    
    //initialises p_best and g_best values for the population
    void initialise_bests(){
        p_best = population;
        p_best_value = obj_value;
        int min_value = obj_value[0];
        int min_index = 0;
        for(int i=1;i<p;i++){
            if(obj_value[i]<min_value){
                min_value = obj_value[i];
                min_index = i;
            }
        }
        g_best_value = min_value;
        g_best = population[min_index];
    }
    
    
    //for updating the velocity and position in each iteration
    vector<int> subtract_position_position(vector<int> x1, vector<int> x2){
        vector<int> ans;
        for(int i=0;i<no_of_tasks;i++){
            if(x1[i]==x2[i]) ans.push_back(0);
            else{
                ans.push_back(x1[i]);
            }
        }
        return ans;
    }

    vector<int> add_position_velocity(vector<int> pos, vector<int> v){
        vector<int> ans;
        unordered_set<int> s; 
        for(int i=0;i<no_of_tasks;i++){
            if(v[i]==0){
                ans.push_back(pos[i]);
                s.insert(pos[i]);
            }
            else{
                if(s.find(v[i])==s.end()) ans.push_back(v[i]);
                else ans.push_back(0);
            }
        }
        return ans;
    }


    vector<int> multiply_coeff_velocity(double c, vector<int> v){
        vector<int> ans;
        for(int i=0;i<no_of_tasks;i++){
            double random = rand()%11;
            c = c*10;
            if(random<c){
                ans.push_back(v[i]);
            }
            else{
                ans.push_back(0);
            }
        }
        return ans;
    }


    vector<int> add_velocity_velocity(vector<int> v1, vector<int> v2){
        vector<int> ans;
        for(int i=0;i<no_of_tasks;i++){
            if(v1[i]!=0 && v2[i]==0) ans.push_back(v1[i]);
            else if(v1[i]!=0 && v2[i]!=0) ans.push_back(v1[i]);
            else ans.push_back(v2[i]);
        }
        return ans;
    }
    
    
    //updating p_best and g_best in each iteration after calculating the each particles new values
    void update_bests(int index){
        if(obj_value[index]<=p_best_value[index]){
            p_best_value[index] = obj_value[index];
            p_best[index] = population[index];
        }
        if(obj_value[index]<=g_best_value){
            g_best_value = obj_value[index];
            g_best = population[index];
        }
    }
    
    
    //updates the population
    void update_population(){
        for(int i=0;i<p;i++){
            int old_obj_value = obj_value[i];
            //updating velocity vector
            vector<int> first_term = multiply_coeff_velocity(c1, velocity[i]);
            vector<int> second_term = multiply_coeff_velocity(c2, subtract_position_position(p_best[i], population[i]));
            vector<int> third_term = multiply_coeff_velocity(c3, subtract_position_position(g_best, population[i]));
            vector<int> new_v = add_velocity_velocity(second_term, third_term);
            velocity[i] = add_velocity_velocity(first_term, new_v);
            
            //updating position vector
            population[i] = normalise(add_position_velocity(population[i], velocity[i]), pre_graph);
            //update obj_value vector
            obj_value[i] = objective_function(population[i]);
            
            //checks if the ith population is changed in this iteration or not
            if(old_obj_value==obj_value[i]){
                counter[i] = counter[i] + 1;
            }
            
            //updating the personal and global best
            update_bests(i);
        }
    }
    
    
    //to normalise the updated population according to precedence relation
    vector<int> normalise(vector<int> pos, unordered_map<int, unordered_set<int> > pre){
        int n = 0;
        vector<int> seq; 
        unordered_set<int> s; 
        unordered_set<int> assigned; 

   
        for(int i=1;i<=no_of_tasks;i++){
            if(pre[i].size()==0){
                s.insert(i);
            }
        }
        while(n < no_of_tasks && seq.size() < no_of_tasks){
            int task;
            if(s.find(pos[n])!=s.end() && pos[n]!=0){
                seq.push_back(pos[n]);
                assigned.insert(pos[n]);
                task = pos[n];
                s.erase(pos[n]);
                n = n + 1;
            }
            else{
                int x = s.size();
                int random = pos[n]%x;
                unordered_set<int>::iterator it = s.begin();
                advance(it, random);
                seq.push_back(*it);
                assigned.insert(*it);
                task = *it;
                s.erase(it);
            }
        
            pre.erase(task);
            for(int i=1;i<=no_of_tasks;i++){
                if(assigned.find(i)==assigned.end()){
                    if(pre[i].find(task)!=pre[i].end()) pre[i].erase(task);
                    if(pre[i].size()==0) s.insert(i);
                }
            }
        }
        return seq;
    }
    
    void print_solution(){
        int ct = g_best_value;
        vector<int> tasks = g_best;
        cout<<endl;
        if(best_value<=g_best_value){
            ct = best_value;
            tasks = best;
        }
        //assigning the start task for the robots
        int start = 0;
        int si;
        int no_of_robots = input_data.size();
        //iterating through each station for given cycle time
        for(int s=0;s<no_of_stations;s++){
            si = start;  //si = start index
        
            //if all tasks assigned, the while loop ends
            if(si>=no_of_tasks) break;
            int robo_index;
            int n = 0; //most no of tasks assigned to a robot in that station
            for(int  r = 0; r<no_of_robots; r++){
                int t = 0; //respective time taken by that robot in that station
                si = start;
                while(t<ct){
                    if(si>=no_of_tasks) break;
                    t+=input_data[r][tasks[si]-1];  
                    //adding the sequence dependent times and setup times of the robot
                    t+=setup_time[r][tasks[si]-1];
                    if(si!=start){
                        t+=seq_dependent_time[r][tasks[si]-1][tasks[si-1]-1];
                    }
                    if(t>ct) break;
                    si++;
                }
                if((si-start) > n) {
                    robo_index = r;
                    n = si-start;
                }
                
            }
            cout<<"\nstation number "<<s+1<<"'s allocation: "<<endl;
            cout<<"robot assigned : "<<robo_index+1<<endl;
            cout<<"tasks assigned : ";
            int st = 0;
            for(int i=start;i<(start+n);i++){
                cout<<tasks[i]<<" ";
                st+=input_data[robo_index][tasks[i]-1];
                //adding the sequence dependent times and setup times of the robot
                st+=setup_time[robo_index][tasks[i]-1];
                if(i!=start){
                    st+=seq_dependent_time[robo_index][tasks[i]-1][tasks[i-1]-1];
                }
            }
            cout<<endl;
            cout<<"its cycle time : "<<st;
            cout<<endl;
            start+=n;
        }
    }
    
    //to help PSO from trapping a local minima
    void escape_local_minima(){
        //assuming if the value of a student is not changing even after 30% of iterations, its replaced with a random sequence
        bool changed;
        for(int i=0;i<p;i++){
            changed = false;
            if(counter[i]>=floor(0.3*T)){
                changed = true;
                counter[i] = 0;
                if(obj_value[i] <= best_value){
                    best_value = obj_value[i];
                    best = population[i];
                }
                population[i] = generate_sequence_randomly(pre_graph);
                obj_value[i] = objective_function(population[i]);
            }
        }
    }
    
};


int main()
{
   srand(time(0));	
   int t = 1;
   PSO object;
   object.get_input();
   object.generate_population();
   object.generate_velocity();
   object.initialise_bests();
   int T = object.T;
   for(int t=1;t<=T;t++){
       object.print_iteration(t);
       object.update_population();
   }
   object.print_solution();
   return 0;
}
