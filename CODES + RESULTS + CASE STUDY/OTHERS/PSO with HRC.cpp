#include <bits/stdc++.h>

using namespace std;

class PSO{
    
    //variables and parameters used in PSO
public:
    int no_of_tasks;
    int no_of_robots;
    int no_of_stations;
    int CT; //stores c0
    double c1, c2, c3; //co-efficients in the updation formula
    int T; //no of iterations to be performed
    int p; //no of particles in the swarm
    vector<vector<int> > population; //stores the population 
    vector<vector<int> > process_alternatives;

    vector<vector<int> > velocity; //stores the velocity of each particle
    vector<int> obj_value; //holds the objective function values of each particle
    vector<vector<int> > input_data;
    vector<double> energy_consumption;
    vector<vector<vector<int> > > seq_dependent_time;
    vector<vector<int> > pre_matrix;
    vector<vector<int> > setup_time;
    unordered_map<int, unordered_set<int> > pre_graph;
    vector<vector<int> > p_best; //holds the particular particles best position
    vector<vector<int> > p_best_process_alternative;
    vector<int> g_best; //holds the global best so far
    vector<int> g_best_process_alternative;
    vector<int> p_best_value; //holds the function values of p_best and g_best
    int g_best_value;
    
    
    //getting input from user
    void get_input(){
    //gets the input from user and generates a precedence graph
        
        cout<<"Enter number of stations : ";
        cin>>no_of_stations;
        cout<<"Enter number of iterations : ";
        cin>>T;
        cout<<"Enter population size : ";
        cin>>p;
        ifstream file("input_50_4.txt");
		file.seekg(0);
       file>>no_of_tasks;
       file>>no_of_robots;
       vector<vector<int> > temp_input_data(2*no_of_robots + 1, vector<int>(no_of_tasks));
       vector<vector<vector<int> > > temp_seq_dependent_time(no_of_robots, vector<vector<int>>(no_of_tasks, vector<int>(no_of_tasks)));
       vector<vector<int> > temp_setup_time(no_of_robots, vector<int>(no_of_tasks));
       vector<vector<int> > temp_pre_matrix(no_of_tasks, vector<int>(no_of_tasks));
       vector<double> temp_energy_consumption(no_of_robots+1);
       input_data = temp_input_data;
       seq_dependent_time = temp_seq_dependent_time;
       setup_time = temp_setup_time;
       pre_matrix = temp_pre_matrix;
       energy_consumption = temp_energy_consumption;
       //cout<<endl<<"OPERATION TIMES FOR HRC\n";
        for(int i=0;i<(no_of_robots*2 + 1); i++){
            for(int j=0;j<no_of_tasks;j++){
                file>>input_data[i][j];
            }
        }
       //cout<<endl<<"SETUP TIMES FOR ROBOTS\n";
        for(int i=0;i<no_of_robots; i++){
            for(int j=0;j<no_of_tasks;j++){
                file>>setup_time[i][j];
            }
        }
        for(int i=0;i<no_of_robots;i++){
           //cout<<endl<<"SEQUENCE DEPENDENT TIME FOR ROBOT "<<i+1<<endl;
           for(int j=0;j<no_of_tasks;j++){
               for(int k=0;k<no_of_tasks;k++){
                   file>>seq_dependent_time[i][j][k];
               }
           }
           //cout<<endl;
       }
       //cout<<endl<<"PRECEDENCE MATRIX"<<endl;
       for(int i=0;i<no_of_tasks;i++){
           for(int j=0;j<no_of_tasks;j++){
            	file>>pre_matrix[i][j];
    		}
       }
       //cout<<endl<<"ENERGY CONSUMPTION"<<endl;
       for(int i=0;i<(no_of_robots+1);i++){
           file>>energy_consumption[i];
       }
       file.close();
    	
    	calculate_initial_cycle_time();
      
        cout<<endl<<"NUMBER OF TASKS : "<<no_of_tasks;
        cout<<endl<<"NUMBER OF ROBOTS : "<<no_of_robots;
        cout<<endl<<"NUMBER OF STATIONS : "<<no_of_stations;
        cout<<endl<<"NUMBER OF ITERATIONS : "<<T;
        cout<<endl<<"SIZE OF THE POPULATION : "<<p;
        cout<<endl;
        //printing
        cout<<endl<<"OPERATION TIMES FOR HRC\n";
        for(int i=0;i<(2*no_of_robots + 1); i++){
            for(int j=0;j<no_of_tasks;j++){
                cout<<input_data[i][j]<<" ";
            }
            cout<<endl;
        }
        //printing
        cout<<endl<<"SETUP TIMES FOR ROBOTS\n";
        for(int i=0;i<no_of_robots; i++){
            for(int j=0;j<no_of_tasks;j++){
                cout<<setup_time[i][j]<<" ";
            }
            cout<<endl;
        }
        //printing
       for(int i=0;i<no_of_robots;i++){
           cout<<endl<<"SEQUENCE DEPENDENT TIME FOR ROBOT "<<i+1<<endl;
           for(int j=0;j<no_of_tasks;j++){
               for(int k=0;k<no_of_tasks;k++){
                   cout<<seq_dependent_time[i][j][k]<<" ";
               }
               cout<<endl;
           }
           cout<<endl;
       }
        //printing
       cout<<endl<<"PRECEDENCE MATRIX"<<endl;
       for(int i=0;i<no_of_tasks;i++){
           for(int j=0;j<no_of_tasks;j++){
            cout<<pre_matrix[i][j]<<" ";
           }
           cout<<endl;
       }
        //printing
       cout<<endl<<"ENERGY CONSUMPTION"<<endl;
       for(int i=0;i<(no_of_robots+1);i++){
           cout<<energy_consumption[i]<<" ";
       }
       cout<<endl;
       
        //assuming c1, c2, c3 values
        c1 = 0.5;
        c2 = 0.7;
        c3 = 0.7; //c2 + c3 <= const
        for(int i=1;i<=no_of_tasks;i++){
            //cout<<"ENTER PRECEDENCE TASKS FOR TASK "<<i<<": (enter 0 if no precedence):\n";
            for(int j=0;j<no_of_tasks;j++){
                if(pre_matrix[i-1][j]==0) continue;
                pre_graph[i].insert(j+1);
            }
        }

    }
    
    
    vector<int> generate_process_alternative(){
        //geenrates process alternative for each station 
        // 1 = robot
        // 2 = cobot
        // 3 = human
        vector<int> ans;
        for(int i=0;i<no_of_stations;i++){
            if(i==0){
                int random = 1 + rand()%3;
                ans.push_back(random);
            }
            else{
                if(ans[i-1]==1){
                    int random = 2 + rand()%2;
                    ans.push_back(random);
                }
                else if(ans[i-1]==2){
                    int random = 1 + rand()%2;
                    if(random==2){
                        ans.push_back(random+1);
                    }
                    else ans.push_back(random);
                }
                else{
                    int random = 1 + rand()%2;
                    ans.push_back(random);
                }
            }
        }
        return ans;
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
        for(int i=0;i<p;i++){
            population.push_back(generate_sequence_randomly(pre_graph));
            process_alternatives.push_back(generate_process_alternative());
        }   
		for(int i=0;i<p;i++){
            obj_value.push_back(objective_function(population[i], process_alternatives[i]));
           
        } 
    }
    
    
    
    void calculate_initial_cycle_time(){
    //(i,j) -> i defines the robot number and j defines the activity number (input_data)
    
    //tasks = given sequence of task allocation by the optimization algorithm
    
        CT = 0;  
        int no_robots = no_of_robots; //no of rows in the input_data matrix 
        int no_tasks = no_of_tasks;  //no of cols in the input_data matrix
    
    //for getting the min time possible for that allocation (using the formula given in slides)
        for(int j=0;j<no_tasks;j++){
            int min_time = INT_MAX;   //min time taken by the robots to complete the ith task
            for(int i=0;i<(2*no_robots + 1);i++){
                min_time = min(min_time, input_data[i][j]);
            }
            CT+=min_time;
        }
        CT = CT / no_of_stations;
	}
    //objective function calculation (cycle time)
    int objective_function(vector<int> tasks, vector<int> process_alternative){
    
    	int cycle_time = CT;
        int no_robots = no_of_robots; //no of rows in the input_data matrix 
        int no_tasks = no_of_tasks;  //no of cols in the input_data matrix
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
            
                int n = 0; //most no of tasks assigned to a process alternative in that station
                
                if(process_alternative[s]==1){
                //looking for best robot
                for(int  r = 0; r<no_robots; r++){
                    int t = 0; //respective time taken by that robot in that station
                    si = start;
                    while(t<=cycle_time){
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
                }
                
                else if(process_alternative[s]==2){
                //looking for best cobot
                for(int  r = no_robots; r<(2*no_robots); r++){
                    int t = 0; //respective time taken by that cobot in that station
                    si = start;
                    while(t<=cycle_time){
                        if(si>=no_tasks) break;
                        t+=input_data[r][tasks[si]-1];  
                        //adding the sequence dependent times and setup times of the robot
                        t+=setup_time[r-no_of_robots][tasks[si]-1];
                        if(si!=start){
                            t+=seq_dependent_time[r-no_of_robots][tasks[si]-1][tasks[si-1]-1];
                        }
                        if(t>cycle_time) break;
                        si++;
                    }
            
                    n = max(n, si-start); //(si-start)= no of tasks assigned to that particular robot
                }
                }
                
                else{
                //for human
                for(int  r = 2*no_robots; r<(2*no_robots + 1); r++){
                    int t = 0; //respective time taken by that robot in that station
                    si = start;
                    while(t<=cycle_time){
                        if(si>=no_tasks) break;
                        t+=input_data[r][tasks[si]-1];  
                        //adding the sequence dependent times and setup times of the robot
                        if(t>cycle_time) break;
                        si++;
                    }
            
                    n = max(n, si-start); //(si-start)= no of tasks assigned to that particular robot
                }
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
        cout<<"process alternative for each station :\n";
        for(int i=0;i<p;i++){
            for(int j=0;j<no_of_stations;j++){
                cout<<process_alternatives[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
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
        p_best_process_alternative = process_alternatives;
        p_best_value = obj_value;
        int min_value = obj_value[0];
        int min_index = 0;
        for(int i=1;i<p;i++){
            if(obj_value[i]<min_value){
                min_value = obj_value[i];
                min_index = i;
            }
        }
        g_best_process_alternative = process_alternatives[min_index];
        g_best_value = min_value;
        g_best = population[min_index];
    }
    
    
    //for updating the velocity and position in each iteration
    vector<int> subtract_position_position(vector<int> x1, vector<int> x2){
        vector<int> ans;
        for(int i=0;i<x1.size();i++){
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
        for(int i=0;i<pos.size();i++){
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
        for(int i=0;i<v.size();i++){
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
        for(int i=0;i<v1.size();i++){
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
            p_best_process_alternative[index] = process_alternatives[index];
        }
        if(obj_value[index]<=g_best_value){
            g_best_value = obj_value[index];
            g_best = population[index];
            g_best_process_alternative = process_alternatives[index];
        }
    }
    
    
    //updates the population
    void update_population(){
        for(int i=0;i<p;i++){
            //updating velocity vector
            vector<int> first_term = multiply_coeff_velocity(c1, velocity[i]);
            vector<int> second_term = multiply_coeff_velocity(c2, subtract_position_position(p_best[i], population[i]));
            vector<int> third_term = multiply_coeff_velocity(c3, subtract_position_position(g_best, population[i]));
            
         
            vector<int> second_term1 = add_velocity_velocity(process_alternatives[i], p_best_process_alternative[i]);
            vector<int> third_term1 = add_velocity_velocity(second_term1, g_best_process_alternative);
            
          
            vector<int> new_v = add_velocity_velocity(second_term, third_term);
            
			velocity[i] = add_velocity_velocity(first_term, new_v);
            
            //updating position vector
            population[i] = normalise(add_position_velocity(population[i], velocity[i]), pre_graph);
            process_alternatives[i] = normalise_process_alternative(third_term1);
            //update obj_value vector
            obj_value[i] = objective_function(population[i], process_alternatives[i]);
            
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
    
    vector<int> normalise_process_alternative(vector<int> process_alternative){
    	vector<int> ans;
    	if(process_alternative[0]<=0 || process_alternative[0]>3){
    		int random = 1 + rand()%3;
    		ans.push_back(random);
		}
		else{
			ans.push_back(process_alternative[0]);
		}
    	for(int i=1;i<no_of_stations;i++){
    		if(ans[i-1]==process_alternative[i]){
    			int random = 1 + rand()%3;
    			while(random==ans[i-1]){
    				random = 1 + rand()%3;
				}
				ans.push_back(random);
			}
			else if(process_alternative[i]<=0 || process_alternative[i]>3){
				int random = 1 + rand()%3;
				ans.push_back(random);
			}
			else{
				ans.push_back(process_alternative[i]);
			}
		}
		return  ans;
	}
    
    void print_solution(){
        int ct = g_best_value;
        vector<int> tasks = g_best;
        vector<int> process_alternative = g_best_process_alternative;
        cout<<endl;
        //assigning the start task for the robots
        
        cout<<endl;
        cout<<"BEST SOLUTION FOUND"<<endl;
        for(int i=0;i<no_of_tasks;i++){
            cout<<tasks[i]<<" ";
        }
        cout<<"= "<<ct<<" = "<<energy_calculation(tasks, process_alternative, ct)<<endl;
        for(int i=0;i<no_of_stations;i++){
        	cout<<process_alternative[i]<<" ";
		}
		cout<<endl;
        //assigning the start task for the robots
        int start = 0;
        int si;
        //iterating through each station for given cycle time
        for(int s=0;s<no_of_stations;s++){
            si = start;  //si = start index
        
            //if all tasks assigned, the while loop ends
            if(si>=no_of_tasks) break;
            int robo_index;
            int n = 0; //most no of tasks assigned to a robot in that station
            
            if(process_alternative[s]==1){
            for(int  r = 0; r<no_of_robots; r++){
                int t = 0; //respective time taken by that robot in that station
                si = start;
                while(t<=ct){
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
        	}
        	
            else if(process_alternative[s]==2){
            for(int  r = no_of_robots; r<2*no_of_robots; r++){
                int t = 0; //respective time taken by that robot in that station
                si = start;
                while(t<=ct){
                    if(si>=no_of_tasks) break;
                    t+=input_data[r][tasks[si]-1];  
                    //adding the sequence dependent times and setup times of the robot
                    t+=setup_time[r-no_of_robots][tasks[si]-1];
                    if(si!=start){
                        t+=seq_dependent_time[r-no_of_robots][tasks[si]-1][tasks[si-1]-1];
                    }
                    if(t>ct) break;
                    si++;
                }
                if((si-start) > n) {
                    robo_index = r;
                    n = si-start;
                }
                
            }
        	}
        	
            else{
            for(int  r = 2*no_of_robots; r<(2*no_of_robots + 1); r++){
                int t = 0; //respective time taken by that robot in that station
                si = start;
                while(t<=ct){
                    if(si>=no_of_tasks) break;
                    t+=input_data[r][tasks[si]-1];  

                    if(t>ct) break;
                    si++;
                }
                if((si-start) > n) {
                    robo_index = r;
                    n = si-start;
                }
                
            }
            }
            
            cout<<"\nstation number "<<s+1<<"'s allocation: "<<endl;
            if(process_alternative[s]==1){
            cout<<"robot assigned : "<<robo_index+1<<endl;
            }
            else if(process_alternative[s]==2){
            int cobot = robo_index - no_of_robots;
            cout<<"cobot assigned : "<<cobot+1<<endl;
            }
            else{
            cout<<"human assigned"<<endl;
            }
            cout<<"tasks assigned : ";
            int st = 0;
            for(int i=start;i<(start+n);i++){
                cout<<tasks[i]<<" ";
                st+=input_data[robo_index][tasks[i]-1];
                //adding the sequence dependent times and setup times of the robot
                if(process_alternative[s]==2){
                	st+=setup_time[robo_index-no_of_robots][tasks[i]-1];
				}
				if(process_alternative[s]==1){
                	st+=setup_time[robo_index][tasks[i]-1];
            	}
                if(i!=start){
                	int r_index = robo_index;
                	if(process_alternative[s]==2) r_index = r_index - no_of_robots;
                    if(process_alternative[s]==2 || process_alternative[s]==1)st+=seq_dependent_time[r_index][tasks[i]-1][tasks[i-1]-1];
                }
            }
            cout<<endl;
            cout<<"its cycle time : "<<st;
            cout<<endl;
            start+=n;
        }
    }
    
    //calculates energy consumption 
    int energy_calculation(vector<int> tasks, vector<int> process_alternative, int ct){
    	int si;
    	int start = 0;
    	double energy = 0; //total energy consumption in all the stations
    
    	for(int s=0;s<no_of_stations;s++){
        	si = start;  //si = start index
        
            //if all tasks assigned, the while loop ends
        	if(si>=no_of_tasks) break;
        	int robo_index;
        	int n = 0; //most no of tasks assigned to a robot in that station
            
    
            
        	if(process_alternative[s]==1){
        		for(int  r = 0; r<no_of_robots; r++){
            		int t = 0; //respective time taken by that robot in that station
            		si = start;
            		while(t<=ct){
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
        	}
        	
        	else if(process_alternative[s]==2){
        		for(int  r = no_of_robots; r<2*no_of_robots; r++){
            		int t = 0; //respective time taken by that robot in that station
            		si = start;
            		while(t<=ct){
                		if(si>=no_of_tasks) break;
                		t+=input_data[r][tasks[si]-1];  
                    //adding the sequence dependent times and setup times of the robot
                		t+=setup_time[r-no_of_robots][tasks[si]-1];
                		if(si!=start){
                    		t+=seq_dependent_time[r-no_of_robots][tasks[si]-1][tasks[si-1]-1];
                		}
                		if(t>ct) break;
                		si++;
            		}
            		if((si-start) > n) {
                		robo_index = r - no_of_robots;
                		n = si-start;
            		}
                
        		}
        	}
        	
        	else{
            	int r = 2*no_of_robots;
            	int t = 0; //respective time taken by that robot in that station
            	si = start;
            	while(t<=ct){
                	if(si>=no_of_tasks) break;
                	t+=input_data[r][tasks[si]-1];  

                	if(t>ct) break;
                	si++;
            	}
            	robo_index = no_of_robots;
            	n = si - start;      
            
        	}
            
    
        	double st = 0; //energy consumed in s'th station
        	for(int i=start;i<(start+n);i++){
            	if(process_alternative[s]==2){
                	st = st + energy_consumption[robo_index]*(double(input_data[2*no_of_robots][tasks[i]-1]));
                	st = st + energy_consumption[robo_index]*(double(input_data[robo_index+no_of_robots][tasks[i]-1]));
            	}
            	else if(process_alternative[s]==3){
                	st = st + energy_consumption[robo_index]*(double(input_data[2*no_of_robots][tasks[i]-1]));
            	}	
            	else{
                	st = st + energy_consumption[robo_index]*(double(input_data[robo_index][tasks[i]-1]));
                
            	}
                
        	}
        	energy+=st;
        	start+=n;
    	}
    	int return_value = ceil(energy);
    	return return_value;
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
   object.print_iteration(1);
   for(int t=2;t<=T;t++){
       
       object.update_population();
       object.print_iteration(t);
   }
   object.print_solution();
 
   return 0;
}
