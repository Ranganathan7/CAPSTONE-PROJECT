#include <bits/stdc++.h>

using namespace std;


class generate_data{
public:
    int no_of_tasks;
    int no_of_robots;
    vector<int> lb;
    vector<int> ub;
    int lb_a; //averages of all lower bounds
    int ub_a; //averages of all upper bounds
    double a1, a2, a3, a4; //parameters
    vector<vector<int> > input_data; //operation times
    vector<vector<int> > pre_matrix; 
    vector<vector<int> > setup_time;
    vector<vector<vector<int> > > seq_dependent_time;
    vector<double> energy_consumption;
    
    void get_data(){
    	
    	int x;
    	cout<<"ENTER NUMBER OF TASKS : ";
    	cin>>no_of_tasks;
    	cout<<"ENTER NUMBER OF TYPES OF ROBOTS : ";
    	cin>>no_of_robots;
    	cout<<"ENTER THE PARAMETER a1 VALUE [0.0 - 1.0] : ";
    	cin>>a1;
    	cout<<"ENTER THE PARAMETER a2 VALUE [0.0 - 1.0] : ";
    	cin>>a2;
    	cout<<"ENTER THE PARAMETER a3 VALUE [0.0 - 1.0] : ";
    	cin>>a3;
    	cout<<"ENTER THE PARAMETER a4 VALUE [0.0 - 1.0] : ";
    	cin>>a4;
        /*a1 = 0.25; //tuning lower bound for setup time
        a2 = 0.5; //tuning upper bound for setup time
        a3 = 0.1; //tuning lower bound for seq dep time
        a4 = 0.25; //tuning upper bound for seq dep time
        //cout<<endl<<"ENTER NUMBER OF TASKS : ";
        no_of_tasks = 11;
        //cout<<endl<<"ENTER NUMBER OF ROBOTS : ";
        no_of_robots = 4;
        //cout<<endl<<"ENTER LOWER BOUND FOR OPERATION TIME(minutes)(int)  : ";
        lb = 50;
        //cout<<endl<<"ENTER UPPER BOUND FOR OPERATION TIME(minutes)(int) : ";
        ub = 150;*/
        
        
        for(int i=0; i<no_of_robots; i++){
        	cout<<endl<<"LOWER BOUND FOR OPERATION TIME OF ROBOT TYPE "<<i+1<<" : ";
        	cin>>x;
        	lb.push_back(x);
        	cout<<"UPPER BOUND FOR OPERATION TIME OF ROBOT TYPE "<<i+1<<" : ";
        	cin>>x;
        	ub.push_back(x);
		}
		
		
		//printing them all
		cout<<"\n\n======================PRINTING ALL DATA======================\n\n";
		cout<<endl<<"NUMBER OF TASKS : "<<no_of_tasks;
        cout<<endl<<"NUMBER OF TYPES OF ROBOTS (NUMBER OF WORKSTATIONS) : "<<no_of_robots;
		for(int i=0;i<no_of_robots;i++){
			cout<<"\n\nDATA FOR ROBOT TYPE "<<i+1<<":";
			cout<<endl<<"LOWER BOUND FOR OPERATION TIME : "<<lb[i];
        	cout<<endl<<"UPPER BOUND FOR OPERATION TIME : "<<ub[i];
        	cout<<endl<<"LOWER BOUND FOR SETUP TIME : "<<floor(a1*lb[i]);
        	cout<<endl<<"UPPER BOUND FOR SETUP TIME : "<<floor(a1*ub[i]);
        	cout<<endl<<"LOWER BOUND FOR SEQUNCE DEPENDENT TIME : "<<floor(a2*lb[i]);
        	cout<<endl<<"UPPER BOUND FOR SEQUENCE DEPENDENT TIME : "<<floor(a2*ub[i]);
		}
		int lb_sum = 0;
		int ub_sum = 0;
		for(int i=0;i<no_of_robots;i++){
			cout<<"\n\nDATA FOR COBOT TYPE "<<i+1<<" [ROBOT TYPE "<<i+1<<" + HUMAN WORKER]:";
			int lower, upper;
			lower =  lb[i] - (a3 * (ub[i] - lb[i]));
			upper =  ub[i] - (a3 * (ub[i] - lb[i]));
			cout<<endl<<"LOWER BOUND FOR OPERATION TIME : "<<lower;
        	cout<<endl<<"UPPER BOUND FOR OPERATION TIME : "<<upper;
        	lb_sum+=lb[i];
        	ub_sum+=ub[i];
		}
		lb_a = lb_sum / no_of_robots;
		ub_a = ub_sum / no_of_robots;
		int lower, upper;
		lower =  lb_a + (a4 * (ub_a - lb_a));
		upper =  ub_a + (a4 * (ub_a - lb_a));
		cout<<"\n\nDATA FOR HUMAN WORKER:";
		cout<<endl<<"LOWER BOUND FOR OPERATION TIME : "<<lower;
        cout<<endl<<"UPPER BOUND FOR OPERATION TIME : "<<upper;
        cout<<endl<<endl;
    }
    
    void generate_operation_time(){
     //taking HRC
        //filling for robots
        int lower;
        int upper;
        for(int i=0;i<no_of_robots;i++){
            vector<int> temp;
            lower = lb[i];
            upper = ub[i];
            for(int j=0;j<no_of_tasks;j++){
                int random = lower + rand()%(upper-lower+1);
                temp.push_back(random);
            }
            input_data.push_back(temp);
        }
        //filling for cobots
        for(int i=0;i<no_of_robots;i++){
            vector<int> temp;
            lower =  lb[i] - (a3 * (ub[i] - lb[i]));
			upper =  ub[i] - (a3 * (ub[i] - lb[i]));
            for(int j=0;j<no_of_tasks;j++){
                int random = lower + rand()%(upper-lower+1);
                temp.push_back(random);
            }
            input_data.push_back(temp);
        }
        //filling for human
        lower = lb_a + (a4 * (ub_a - lb_a));
        upper = ub_a + (a4 * (ub_a - lb_a));
        vector<int> temp;
        for(int i=0;i<no_of_tasks;i++){
            int random = lower + rand()%(upper-lower+1);
            temp.push_back(random);
        }
        input_data.push_back(temp);
        //printing
        cout<<endl<<"OPERATION TIMES FOR HRC\n";
        for(int i=0;i<(no_of_robots*2 + 1); i++){
            for(int j=0;j<no_of_tasks;j++){
                cout<<input_data[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    
    void generate_setup_time(){
        int lower;
        int upper;
        for(int i=0;i<no_of_robots;i++){
            vector<int> temp;
            lower = a1 * lb[i];
            upper = a1 * ub[i];
            for(int j=0;j<no_of_tasks;j++){
                int random = lower + rand()%(upper-lower+1);
                temp.push_back(random);
            }
            setup_time.push_back(temp);
        }
        //printing
        cout<<endl<<"SETUP TIMES FOR ROBOTS\n";
        for(int i=0;i<no_of_robots; i++){
            for(int j=0;j<no_of_tasks;j++){
                cout<<setup_time[i][j]<<" ";
            }
            cout<<endl;
        }
    }
   
   vector<vector<int> > generate_seq_dependent_time_for_one_robot(int index){
       int lower = a2 * lb[index];
       int upper = a2 * ub[index];
       vector<vector<int> > ans;
       for(int i=0;i<no_of_tasks;i++){
            vector<int> temp;
            for(int j=0;j<no_of_tasks;j++){
                int random = lower + rand()%(upper-lower+1);
                temp.push_back(random);
            }
            ans.push_back(temp);
        }
        return ans;
   }
   
   void generate_seq_dependent_time(){
       for(int i=0;i<no_of_robots;i++){
           seq_dependent_time.push_back(generate_seq_dependent_time_for_one_robot(i));
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
   }
   
   void generate_pre_matrix(){
       for(int i=0;i<no_of_tasks;i++){
           vector<int> temp;
           for(int j=0;j<no_of_tasks;j++){
               if(j<i){
                   int random = rand()%int((double(no_of_tasks * no_of_tasks)/1.5));
                   if(((i+1)*(j+1))>=random) temp.push_back(1);
                   else temp.push_back(0);
               }
               else{
                   temp.push_back(0);
               }
           }
           pre_matrix.push_back(temp);
       }
       //printing
       cout<<endl<<"PRECEDENCE MATRIX"<<endl;
       for(int i=0;i<no_of_tasks;i++){
           for(int j=0;j<no_of_tasks;j++){
            cout<<pre_matrix[i][j]<<" ";
           }
           cout<<endl;
       }
   }
   
   //generates energy consumption
   void generate_energy_consumption(){
       //taken the range as (0.10 - 0.30) Wh / min for robots
       for(int i=0; i<(no_of_robots); i++){
           double random = 10 + (rand()%(30-10+1));
           random = random / 100;
           energy_consumption.push_back(random);
       }
       //taken the range as (0.05 - 0.15) Wh / min for human
       double random = 5 + (rand()%(15-5+1));
       random = random / 100;
       energy_consumption.push_back(random);
       
       //printing
       cout<<endl<<"ENERGY CONSUMPTION"<<endl;
       for(int i=0;i<(no_of_robots+1);i++){
           cout<<energy_consumption[i]<<" ";
       }
       cout<<endl;
   }
   
   void write_all(){
       //cout<<endl<<endl<<"COPY PASTE THE BELOW LINES INTO YOUR TXT FILE"<<endl<<endl;
       string file_name = "";
       file_name = file_name + "input_" + to_string(no_of_tasks) + "_" + to_string(no_of_robots) + ".txt";
       ofstream file(file_name);
       file<<no_of_tasks<<endl;
       file<<no_of_robots<<endl;
       //cout<<endl<<"OPERATION TIMES FOR HRC\n";
        for(int i=0;i<(no_of_robots*2 + 1); i++){
            for(int j=0;j<no_of_tasks;j++){
                file<<input_data[i][j]<<" ";
            }
            file<<endl;
        }
       //cout<<endl<<"SETUP TIMES FOR ROBOTS\n";
        for(int i=0;i<no_of_robots; i++){
            for(int j=0;j<no_of_tasks;j++){
                file<<setup_time[i][j]<<" ";
            }
            file<<endl;
        }
        for(int i=0;i<no_of_robots;i++){
           //cout<<endl<<"SEQUENCE DEPENDENT TIME FOR ROBOT "<<i+1<<endl;
           for(int j=0;j<no_of_tasks;j++){
               for(int k=0;k<no_of_tasks;k++){
                   file<<seq_dependent_time[i][j][k]<<" ";
               }
               file<<endl;
           }
           //cout<<endl;
       }
       //cout<<endl<<"PRECEDENCE MATRIX"<<endl;
       for(int i=0;i<no_of_tasks;i++){
           for(int j=0;j<no_of_tasks;j++){
            file<<pre_matrix[i][j]<<" ";
           }
           file<<endl;
       }
       //cout<<endl<<"ENERGY CONSUMPTION"<<endl;
       for(int i=0;i<(no_of_robots+1);i++){
           file<<energy_consumption[i]<<" ";
       }
       file.close();
   }
   
};

int main(){
    srand(time(0));
    generate_data object;
    object.get_data();
    object.generate_operation_time();
    object.generate_setup_time();
    object.generate_seq_dependent_time();
    //object.generate_pre_matrix();
    //object.generate_energy_consumption();
    //object.write_all();
    
    return 0;
}
