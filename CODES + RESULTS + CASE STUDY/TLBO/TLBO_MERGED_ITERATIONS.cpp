#include<bits/stdc++.h>
#include "METAHEURISTICS.H"
using namespace std;

bool sort_obj_values( const vector<int>& v1, const vector<int>& v2 ) {
    	if(v1[0]==v2[0]) return (v1[1]<v2[1]);
    	else return v1[0]>v2[0];
	}

int main(){
	srand(time(0));	
    //string s = "C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_35_5.txt";
    string s = "C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_70_7.txt";
    //string s = "C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_111_9.txt";

{//RUNNING ALL META HEURISTICS
   TLBO_ABC object1;
   TLBO_ABC object2;
   TLBO_ABC object3;
   TLBO_ABC object4;
   TLBO_ABC object5;
   TLBO_ABC object6;
    
	cout<<"\n\n\n====STARTING TYPE 1====\n";
{//TLBO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object1.get_input(s);
   object1.T = 5;
   object1.p = 5;
   object1.generate_population();
   object1.calculate_mean();
   for(int t=2;t<=object1.T;t++){
       cout<<t<<" ";
       object1.update_population();
       //object.print_iteration(t);
   }
   object1.update_EA();
   //object1.print_all_solution();
}
	cout<<"\n====COMPLETED TYPE 1====\n";
	cout<<"\n\n\n====STARTING TYPE 2====\n";
{//TLBO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object2.get_input(s);
   object2.T = 10;
   object2.p = 10;
   object2.generate_population();
   object2.calculate_mean();
   for(int t=2;t<=object2.T;t++){
       cout<<t<<" ";
       object2.update_population();
       //object.print_iteration(t);
   }
   object2.update_EA();
   //object2.print_all_solution();
}
	cout<<"\n====COMPLETED TYPE 2====\n";
		cout<<"\n\n\n====STARTING TYPE 3====\n";
{//TLBO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object3.get_input(s);
   object3.T = 15;
   object3.p = 15;
   object3.generate_population();
   object3.calculate_mean();
   for(int t=2;t<=object3.T;t++){
       cout<<t<<" ";
       object3.update_population();
       //object.print_iteration(t);
   }
   object3.update_EA();
   //object3.print_all_solution();
}
	cout<<"\n====COMPLETED TYPE 3====\n";
		cout<<"\n\n\n====STARTING TYPE 4====\n";
{//TLBO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object4.get_input(s);
   object4.T = 20;
   object4.p = 20;
   object4.generate_population();
   object4.calculate_mean();
   for(int t=2;t<=object4.T;t++){
       cout<<t<<" ";
       object4.update_population();
       //object.print_iteration(t);
   }
   object4.update_EA();
   //object3.print_all_solution();
}
	cout<<"\n====COMPLETED TYPE 4====\n";
		cout<<"\n\n\n====STARTING TYPE 5====\n";
{//TLBO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object5.get_input(s);
   object5.T = 25;
   object5.p = 25;
   object5.generate_population();
   object5.calculate_mean();
   for(int t=2;t<=object5.T;t++){
       cout<<t<<" ";
       object5.update_population();
       //object.print_iteration(t);
   }
   object5.update_EA();
   //object5.print_all_solution();
}
	cout<<"\n====COMPLETED TYPE 5====\n";
		cout<<"\n\n\n====STARTING TYPE 6====\n";
{//TLBO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object6.get_input(s);
   object6.T = 30;
   object6.p = 30;
   object6.generate_population();
   object6.calculate_mean();
   for(int t=2;t<=object6.T;t++){
       cout<<t<<" ";
       object6.update_population();
       //object.print_iteration(t);
   }
   object6.update_EA();
   //object6.print_all_solution();
}
	cout<<"\n====COMPLETED TYPE 6====\n";
	
	//writing the final results of all algo into a txt file
	   string file_name = "";
       file_name = file_name + "iterations_output_" + to_string(object1.no_of_tasks) + "_" + to_string(object1.no_of_robots) + ".txt";
       ofstream file(file_name);
		int len1 = object1.EA_seq.size();
		int len2 = object2.EA_seq.size();
		int len3 = object3.EA_seq.size();
		int len4 = object4.EA_seq.size();
		int len5 = object5.EA_seq.size();
		int len6 = object6.EA_seq.size();
		int len = max(len1, len2);
		len = max(len, len3);
		len = max(len, len4);
		len = max(len, len5);
		len = max(len, len6);
		sort(object1.EA_obj_values.begin(), object1.EA_obj_values.end(),sort_obj_values);
		sort(object2.EA_obj_values.begin(), object2.EA_obj_values.end(),sort_obj_values);
		sort(object3.EA_obj_values.begin(), object3.EA_obj_values.end(),sort_obj_values);
		sort(object4.EA_obj_values.begin(), object4.EA_obj_values.end(),sort_obj_values);
		sort(object5.EA_obj_values.begin(), object5.EA_obj_values.end(),sort_obj_values);
		sort(object6.EA_obj_values.begin(), object6.EA_obj_values.end(),sort_obj_values);
        for(int i=0;i<len; i++){
        	
        	if(i<len1){
				file<<object1.EA_obj_values[i][0];
				file<<"\t";
				file<<object1.EA_obj_values[i][1];
				file<<"\t";
			}
			if(i>=len1){
				file<<"\t";
				file<<"\t";
			}
			
			if(i<len2){
				file<<object2.EA_obj_values[i][0];
				file<<"\t";
				file<<object2.EA_obj_values[i][1];
				file<<"\t";
			}
			if(i>=len2){
				file<<"\t";
				file<<"\t";
			}
			
			if(i<len3){
				file<<object3.EA_obj_values[i][0];
				file<<"\t";
				file<<object3.EA_obj_values[i][1];
				file<<"\t";
			}
			if(i>=len3){
				file<<"\t";
				file<<"\t";
			}
			
			if(i<len4){
				file<<object4.EA_obj_values[i][0];
				file<<"\t";
				file<<object4.EA_obj_values[i][1];
				file<<"\t";
			}
			if(i>=len4){
				file<<"\t";
				file<<"\t";
			}
			
			if(i<len5){
				file<<object5.EA_obj_values[i][0];
				file<<"\t";
				file<<object5.EA_obj_values[i][1];
				file<<"\t";
			}
			if(i>=len5){
				file<<"\t";
				file<<"\t";
			}
			
			if(i<len6){
				file<<object6.EA_obj_values[i][0];
				file<<"\t";
				file<<object6.EA_obj_values[i][1];
				file<<"\t";
			}
			if(i>=len6){
				file<<"\t";
				file<<"\t";
			}
			
			file<<endl;
        }
       
       file.close();
	
	cout<<"\n\n\t\t==========FINAL RESULTS==========\n\n";  
    cout<<"SOLUTIONS FOUND USING TYPE 1 = "<<len1<<endl;
    cout<<"SOLUTIONS FOUND USING TYPE 2 = "<<len2<<endl;
    cout<<"SOLUTIONS FOUND USING TYPE 3 = "<<len3<<endl;
    cout<<"SOLUTIONS FOUND USING TYPE 4 = "<<len4<<endl;
    cout<<"SOLUTIONS FOUND USING TYPE 5 = "<<len5<<endl;
    cout<<"SOLUTIONS FOUND USING TYPE 6 = "<<len6<<endl;
}
   
    return 0;
}
