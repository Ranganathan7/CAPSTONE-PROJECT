#include<bits/stdc++.h>
using namespace std;

class HRCvsOR{
public:
	int no_of_tasks;
	int no_of_robots;
	int no_of_stations;
	vector<vector<int> > input_data;
	vector<vector<vector<int> > > seq_dependent_time;
	vector<vector<int> > setup_time;
	vector<vector<int> > pre_matrix;
	vector<double> energy_consumption;
	int CT;
	vector<vector<int> > task_seq;
	vector<vector<int> > hrc_pa;
	vector<vector<int> > or_pa;
	vector<int>  cycle_time_hrc;
	vector<int> cycle_time_or;
	vector<int> energy_hrc;
	vector<int> energy_or;	
		
	void get_input(string s){
	   ifstream file(s);
	   file.seekg(0);
       file>>no_of_tasks;
       file>>no_of_robots;
       no_of_stations = no_of_robots;
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
       //file<<endl<<"OPERATION TIMES FOR HRC\n";
        for(int i=0;i<(no_of_robots*2 + 1); i++){
            for(int j=0;j<no_of_tasks;j++){
                file>>input_data[i][j];
            }
        }
       //file<<endl<<"SETUP TIMES FOR ROBOTS\n";
        for(int i=0;i<no_of_robots; i++){
            for(int j=0;j<no_of_tasks;j++){
                file>>setup_time[i][j];
            }
        }
        for(int i=0;i<no_of_robots;i++){
           //file<<endl<<"SEQUENCE DEPENDENT TIME FOR ROBOT "<<i+1<<endl;
           for(int j=0;j<no_of_tasks;j++){
               for(int k=0;k<no_of_tasks;k++){
                   file>>seq_dependent_time[i][j][k];
               }
           }
           //file<<endl;
       }
       //file<<endl<<"PRECEDENCE MATRIX"<<endl;
       for(int i=0;i<no_of_tasks;i++){
           for(int j=0;j<no_of_tasks;j++){
            	file>>pre_matrix[i][j];
    		}
       }
       //file<<endl<<"ENERGY CONSUMPTION"<<endl;
       for(int i=0;i<(no_of_robots+1);i++){
           file>>energy_consumption[i];
       }
       file.close();
       calculate_initial_cycle_time();
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
    int cycle_time_calculation(vector<int> tasks, vector<int> process_alternative){
    
    	int cycle_time = CT;
        int no_robots = no_of_robots; //no of rows in the input_data matrix 
        int no_tasks = no_of_tasks;  //no of cols in the input_data matrix
        //file<<endl<<"INITIAL CYCLE TIME : "<<cycle_time<<endl;
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
                        //task constraint
                        if(input_data[r][tasks[si]-1]<=0){
                        	si = start;
                        	break;
						}
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
                		//task constraint
                        if(input_data[r][tasks[si]-1]<=0){
                        	si = start;
                        	break;
						}
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
	
	//decoding and printing the solution from obtained best solution
    void print_solution(int ct, int energy, vector<int> tasks, vector<int> process_alternative, bool flag, int q, ofstream& file){
    	if(flag){
        	file<<"FOR THE TASK SEQUENCE : ";
	        for(int i=0;i<no_of_tasks;i++){
	            file<<task_seq[q][i]<<" ";
	        }
	        file<<endl<<endl;
	        file<<"USING HUMAN ROBOT ALLOCATION : ";
	        for(int i=0;i<no_of_stations;i++){
	        	file<<hrc_pa[q][i]<<" ";
			}
			file<<endl<<endl;
			file<<"CYCLE TIME : "<<cycle_time_hrc[q]<<endl<<endl;
			file<<"ENERGY CONSUMPTION : "<<energy_hrc[q]<<endl<<endl;
			file<<"THE ALLOCATION FOR EACH STATION IS AS FOLLOWS"<<endl;
		}
		else{	
			file<<"FOR THE TASK SEQUENCE : ";
	        for(int i=0;i<no_of_tasks;i++){
	            file<<task_seq[q][i]<<" ";
	        }
	        file<<endl<<endl;
	        file<<"USING ONLY ROBOT ALLOCATION : ";
	        for(int i=0;i<no_of_stations;i++){
	        	file<<or_pa[q][i]<<" ";
			}
			file<<endl<<endl;
			file<<"CYCLE TIME : "<<cycle_time_or[q]<<endl<<endl;
			file<<"ENERGY CONSUMPTION : "<<energy_or[q]<<endl<<endl;
			file<<"THE ALLOCATION FOR EACH STATION IS AS FOLLOWS"<<endl;
		}
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
                    //task constraint
                    if(input_data[r][tasks[si]-1]<=0){
                        si = start;
                        break;
					}
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
            
            file<<"\n#station number "<<s+1<<"'s allocation: "<<endl;
            if(process_alternative[s]==1){
            file<<"robot assigned : "<<robo_index+1<<endl;
            }
            else if(process_alternative[s]==2){
            int cobot = robo_index - no_of_robots;
            file<<"cobot assigned : "<<cobot+1<<endl;
            }
            else{
            file<<"human assigned"<<endl;
            }
            file<<"tasks assigned : ";
            int st = 0;
            for(int i=start;i<(start+n);i++){
                file<<tasks[i]<<" ";
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
            file<<endl;
            start+=n;
        }
        file<<endl<<endl;
    }
    
    
    void initialise(vector<vector<int> > sequence, vector<vector<int> > hrc, vector<vector<int> > only_robot){
    	task_seq = sequence;
    	hrc_pa = hrc;
    	or_pa = only_robot;
	}
	
	
    void allocate(){
    	for(int i=0;i<task_seq.size();i++){
    		cycle_time_hrc.push_back(cycle_time_calculation(task_seq[i], hrc_pa[i]));
    		cycle_time_or.push_back(cycle_time_calculation(task_seq[i], or_pa[i]));
    		energy_hrc.push_back(energy_calculation(task_seq[i], hrc_pa[i], cycle_time_hrc[i]));
    		energy_or.push_back(energy_calculation(task_seq[i], hrc_pa[i], cycle_time_or[i]));
		}
	}
	
	void write_output(){
		string file_name = "";
    	file_name = file_name + "output_allocation_" + to_string(no_of_tasks) + "_" + to_string(no_of_robots) + ".txt";
    	ofstream file(file_name);
    	for(int q=0;q<10;q++){
	        print_solution(cycle_time_hrc[q], energy_hrc[q], task_seq[q], hrc_pa[q], true, q, file);
	        print_solution(cycle_time_or[q], energy_or[q], task_seq[q], or_pa[q], false, q, file);
		}
		file.close();
	}
	
	double evaluate_percentage(int i){
		double ans = 0;
		double size = 0;
		for(int j=0;j<no_of_stations;j++){
			if(hrc_pa[i][j]==2){
				ans = ans + 0.5;
			}
			if(hrc_pa[i][j]==3){
				ans = ans + 1;
			}
			size = size + 1;
		}
		ans = ans / size;
		ans = ans * 100;
		return ans;
	}
};

int main(){
	srand(time(0));	
    vector<string> arr;
    vector<int> arr2;
    vector<int> arr3;
    
    arr.push_back("output_25_3.txt"); arr2.push_back(25); arr3.push_back(3);
    arr.push_back("output_25_4.txt"); arr2.push_back(25); arr3.push_back(4);
    arr.push_back("output_25_6.txt"); arr2.push_back(25); arr3.push_back(6);
    arr.push_back("output_25_9.txt"); arr2.push_back(25); arr3.push_back(9);
    
    arr.push_back("output_35_4.txt"); arr2.push_back(35); arr3.push_back(4);
    arr.push_back("output_35_5.txt"); arr2.push_back(35); arr3.push_back(5);
    arr.push_back("output_35_7.txt"); arr2.push_back(35); arr3.push_back(7);
    arr.push_back("output_35_12.txt"); arr2.push_back(35); arr3.push_back(12);
    
    arr.push_back("output_53_5.txt"); arr2.push_back(53); arr3.push_back(5);
    arr.push_back("output_53_7.txt"); arr2.push_back(53); arr3.push_back(7);
    arr.push_back("output_53_10.txt"); arr2.push_back(53); arr3.push_back(10);
    arr.push_back("output_53_14.txt"); arr2.push_back(53); arr3.push_back(14);
    
    arr.push_back("output_70_7.txt"); arr2.push_back(70); arr3.push_back(7);
    arr.push_back("output_70_10.txt"); arr2.push_back(70); arr3.push_back(10);
    arr.push_back("output_70_14.txt"); arr2.push_back(70); arr3.push_back(14);
    arr.push_back("output_70_19.txt"); arr2.push_back(70); arr3.push_back(19);
    
    arr.push_back("output_89_8.txt"); arr2.push_back(89); arr3.push_back(8);
    arr.push_back("output_89_12.txt"); arr2.push_back(89); arr3.push_back(12);
    arr.push_back("output_89_16.txt"); arr2.push_back(89); arr3.push_back(16);
    arr.push_back("output_89_21.txt"); arr2.push_back(89); arr3.push_back(21);
    
    arr.push_back("output_111_9.txt"); arr2.push_back(111); arr3.push_back(9);
    arr.push_back("output_111_13.txt"); arr2.push_back(111); arr3.push_back(13);
    arr.push_back("output_111_17.txt"); arr2.push_back(111); arr3.push_back(17);
    arr.push_back("output_111_22.txt"); arr2.push_back(111); arr3.push_back(22);
    
    string file_name = "";
    file_name = file_name + "plot_data_1.txt";
    ofstream file2(file_name);
    
    string file_name3 = "";
    file_name3 = file_name3 + "plot_data_2.txt";
    ofstream file3(file_name3);
    file3<<"CT WITH HRC\t"<<"ENERGY WITH HRC\t"<<"CT WITH OR\t"<<"ENERGY WITH OR"<<endl;
    
    string file_name4 = "";
    file_name4 = file_name4 + "plot_data_3.txt";
    ofstream file4(file_name4);
    file4<<"CYCLE TIME\t"<<"ENERGY\t"<<"HUMAN %"<<endl;
    
    for(int i=0;i<24;i++){
		cout<<"\n\n===========READING FILE NUMBER "<<i+1<<"==========="<<endl;
		string s = arr[i];
		ifstream file(s);
		file.seekg(0);
		vector<vector<int> > sequence(10, vector<int>(arr2[i]));
		vector<vector<int> > hrc(10, vector<int>(arr3[i]));
		vector<vector<int> > only_robot(10, vector<int>(arr3[i]));
		for(int j=0;j<10;j++){
			for(int k=0;k<sequence[j].size();k++){
				file>>sequence[j][k];
				//cout<<sequence[j][k]<<" ";
			}
			//cout<<endl;
			for(int k=0;k<hrc[j].size();k++){
				file>>hrc[j][k];
				//cout<<hrc[j][k]<<" ";
				only_robot[j][k] = 1;
			}
			//cout<<endl;
		}
		file.close();
		string temp = "C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_";
		temp = temp + to_string(arr2[i]);
		temp = temp + "_" + to_string(arr3[i]);
		temp = temp + ".txt";
		
		HRCvsOR object1;
		object1.get_input(temp);
		object1.initialise(sequence, hrc, only_robot);
		object1.allocate();
		object1.write_output();
		int avg_ct_hrc = 0;
		int avg_ct_or = 0;
		int avg_energy_hrc = 0;
		int avg_energy_or = 0;
		
		
    	file2<<"FOR TASKS NUMBER "<<object1.no_of_tasks<<" & NO OF STATIONS "<<object1.no_of_stations<<endl<<endl;
    	file2<<"CYCLE TIME VALUES WITH HRC";
    	for(int j=0;j<10;j++){
    		file2<<"\t";
    		file2<<object1.cycle_time_hrc[j];
    		avg_ct_hrc+=object1.cycle_time_hrc[j];
	    }
	    file2<<endl;
    	file2<<"ENERGY VALUES WITH HRC";
    	for(int j=0;j<10;j++){
    		file2<<"\t";
    		file2<<object1.energy_hrc[j];
    		avg_energy_hrc+=object1.energy_hrc[j];
	    }
	    file2<<endl<<endl;
	    file2<<"CYCLE TIME VALUES WITH ONLY ROBOTS";
    	for(int j=0;j<10;j++){
    		file2<<"\t";
    		file2<<object1.cycle_time_or[j];
    		avg_ct_or+=object1.cycle_time_or[j];
	    }
	    file2<<endl;
    	file2<<"ENERGY VALUES WITH ONLY ROBOTS";
    	for(int j=0;j<10;j++){
    		file2<<"\t";
    		file2<<object1.energy_or[j];
    		avg_energy_or+=object1.energy_or[j];
	    }
	    file2<<endl<<endl<<endl<<endl;
	    
	    avg_ct_hrc = avg_ct_hrc / 10;
	    avg_ct_or = avg_ct_or / 10;
	    avg_energy_hrc = avg_energy_hrc / 10;
	    avg_energy_or = avg_energy_or / 10;
	    file3<<avg_ct_hrc<<"\t";
	    file3<<avg_energy_hrc<<"\t";
	    file3<<avg_ct_or<<"\t";
	    file3<<avg_energy_or;
	    file3<<endl;
	    
	    
	    double avg_human_percentage = 0;
	    for(int j=0;j<10;j++){
	    	avg_human_percentage = avg_human_percentage + object1.evaluate_percentage(j);
		}
	    avg_human_percentage = avg_human_percentage / 10;
	    file4<<avg_ct_hrc<<"\t";
	    file4<<avg_energy_hrc<<"\t";
	    file4<<avg_human_percentage;
	    file4<<endl;
	}
	file2.close();
	file3.close();
	file4.close();
	return 0;
}
