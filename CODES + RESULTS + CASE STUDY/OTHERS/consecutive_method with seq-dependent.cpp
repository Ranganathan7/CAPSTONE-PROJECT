#include <bits/stdc++.h>

using namespace std;


int consecutive_method(vector<int> &tasks, vector<vector<int> > &input_data, int no_of_stations, vector<vector<int> > &setup_time, vector<vector<vector<int> > > &seq_dependent_time){
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
    
    cout<<endl<<"INITIAL CYCLE TIME : "<<cycle_time<<endl;
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
                    if(si!=0){
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



int main()
{
    //taking no of activites = 11 and no of robots = 4

    //INPUT DATA (taking robots in rows and activites in columns)
    
    vector<vector<int> > v
    {
        {81, 109, 65, 51, 92, 77, 51, 50, 43, 45, 76}, //Robot 1's time taken for ith activity
        {37, 101, 80, 41, 36, 65, 51, 42, 76, 46, 38},
        {51, 90, 38, 91, 33, 83, 40, 34, 41, 41, 83},
        {49, 42, 52, 40, 25, 71, 49, 44, 33, 77, 87}
    };
    
    int n = 4; //assuming no of station = 4
    
    //assuming a random order of tasks from optimization algorithm
    vector<int> t {1, 3, 2, 4, 5, 6, 7, 9, 8, 10, 11};
    
    //CALLING THE CONSECUTIVE METHOD FUNCTION (fitness evaluation)
    int optimal_cycle_time = consecutive_method(t, v, n);
    cout<<endl<<"OPTIMAL CYCLE TIME (C0) = "<<optimal_cycle_time; 
   return 0;
}
