#include<bits/stdc++.h>
#include "METAHEURISTICS.H"
using namespace std;

bool sort_obj_values( const vector<int>& v1, const vector<int>& v2 ) {
    	if(v1[0]==v2[0]) return (v1[1]<v2[1]);
    	else return v1[0]>v2[0];
	}

int main(){
	srand(time(0));	
	int T, p;
	// +0 = 25 task size
	// +4 = 35 task size
	// +8 = 53 task size
	// +12 = 70 task size
	// +16 = 89 task size
	// +20 = 111 task size
	// +24 = 148 task size
	// +28 = 297 task size
	int counter = 0;
	
	T = 30;
	p = 30;
	vector<string> arr;
	string s;
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_25_3.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_25_4.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_25_6.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_25_9.txt");
    
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_35_4.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_35_5.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_35_7.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_35_12.txt");
    
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_53_5.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_53_7.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_53_10.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_53_14.txt");
    
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_70_7.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_70_10.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_70_14.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_70_19.txt");
    
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_89_8.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_89_12.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_89_16.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_89_21.txt");
    
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_111_9.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_111_13.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_111_17.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_111_22.txt");
    
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_148_10.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_148_14.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_148_21.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_148_29.txt");
    
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_297_19.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_297_29.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_297_38.txt");
    arr.push_back("C:/Users/user/OneDrive/Desktop/CAPSTONE PROJECT/CODES/DATA/input_297_50.txt");
    
for(int file_number=0; file_number<4; file_number++){	
s = arr[file_number+counter];
    
{//RUNNING ALL META HEURISTICS
   PSO_ABC object1;
   PSO_ABC object2;
   TLBO_ABC object3;
   TLBO_ABC object4;
   MBO_ABC object5;
   MBO_ABC object6;
   AOA_ABC object7;
   AOA_ABC object8;
    
    cout<<"\n\n\n=====STRATING PSO====\n";
{//PSO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object1.get_input(s);
   object1.T = T;
   object1.p = p;
   object1.generate_population();
   object1.generate_velocity();
   object1.initialise_bests();
   for(int t=2;t<=T;t++){
       cout<<t<<" ";
       object1.update_population();
       //object.print_iteration(t);
   }
   object1.update_EA();
   //object1.print_all_solution();
}
	cout<<"\n====COMPLETED PSO====\n";
	cout<<"\n\n\n====STARTING PSO + ABC====\n";
{//PSO + ABC
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object2.get_input(s);
   object2.T = T;
   object2.p = p;
   object2.generate_population();
   object2.generate_velocity();
   object2.initialise_bests();
   for(int t=2;t<=T;t++){
       cout<<t<<" ";
       object2.update_population();
       object2.escape_local_minima();
       //object.print_iteration(t);
   }
   object2.update_EA();
   //object2.print_all_solution();
}
	cout<<"\n====COMPLETED PSO + ABC====\n";
	cout<<"\n\n\n====STARTING TLBO====\n";
{//TLBO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object3.get_input(s);
   object3.T = T;
   object3.p = p;
   object3.generate_population();
   object3.calculate_mean();
   for(int t=2;t<=T;t++){
       cout<<t<<" ";
       object3.update_population();
       //object.print_iteration(t);
   }
   object3.update_EA();
   //object3.print_all_solution();
}
	cout<<"\n====COMPLETED TLBO====\n";
	cout<<"\n\n\n====STARTING TLBO + ABC====\n";
{//TLBO + ABC
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object4.get_input(s);
   object4.T = T;
   object4.p = p;
   object4.generate_population();
   object4.calculate_mean();
   for(int t=2;t<=T;t++){
       cout<<t<<" ";
       object4.update_population();
       object4.escape_local_minima();
       //object.print_iteration(t);
   }
   object4.update_EA();
   //object4.print_all_solution();
}
	cout<<"\n====COMPLETED TLBO + ABC====\n";
	cout<<"\n\n\n====STARTING MBO====\n";
{//MBO
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object5.get_input(s);
   object5.T = T;
   object5.p = p;
   object5.generate_population();
   for(int t=2;t<=T;t++){
       cout<<t<<" ";
       object5.update_population();
       //object.print_iteration(t);
   }
   object5.update_EA();
   //object5.print_all_solution();
}
	cout<<"\n====COMPLETED MBO====\n";
	cout<<"\n\n\n====STARTING MBO + ABC====\n";
{//MBO + ABC
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object6.get_input(s);
   object6.T = T;
   object6.p = p;
   object6.generate_population();
   for(int t=2;t<=T;t++){
       cout<<t<<" ";
       object6.update_population();
       object6.escape_local_minima();
       //object.print_iteration(t);
   }
   object6.update_EA();
   //object6.print_all_solution();
}
	cout<<"\n====COMPLETED MBO + ABC====\n";
	cout<<"\n====STARTING AOA====\n";
{//AOA
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object7.get_input(s);
   object7.T = T;
   object7.p = p;
   object7.generate_population();
   for(int t=2;t<=T;t++){
       cout<<t<<" ";
       object7.update_population(t);
       //object.print_iteration(t);
   }
   object7.update_EA();
   //object7.print_all_solution();
}
	cout<<"\n====COMPLETED AOA====\n";
	cout<<"\n\n\n====STARTING AOA + ABC====\n";
{//AOA + ABC
   int t = 1;
   cout<<"ITERATION PROGRESS : 1 ";
   object8.get_input(s);
   object8.T = T;
   object8.p = p;
   object8.generate_population();
   for(int t=2;t<=T;t++){
       cout<<t<<" ";
       object8.update_population(t);
       object8.escape_local_minima();
       //object.print_iteration(t);
   }
   object8.update_EA();
   //object8.print_all_solution();
}
	cout<<"\n====COMPLETED AOA + ABC====\n";
	
	//writing the final results of all algo into a txt file
	   string file_name = "";
       file_name = file_name + "output_" + to_string(object1.no_of_tasks) + "_" + to_string(object1.no_of_robots) + ".txt";
       ofstream file(file_name);
		int len1 = object1.EA_seq.size();
		int len2 = object2.EA_seq.size();
		int len3 = object3.EA_seq.size();
		int len4 = object4.EA_seq.size();
		int len5 = object5.EA_seq.size();
		int len6 = object6.EA_seq.size();
		int len7 = object7.EA_seq.size();
		int len8 = object8.EA_seq.size();
		int len = max(len1, len2);
		len = max(len, len3);
		len = max(len, len4);
		len = max(len, len5);
		len = max(len, len6);
		len = max(len, len7);
		len = max(len, len8);
		sort(object1.EA_obj_values.begin(), object1.EA_obj_values.end(),sort_obj_values);
		sort(object2.EA_obj_values.begin(), object2.EA_obj_values.end(),sort_obj_values);
		sort(object3.EA_obj_values.begin(), object3.EA_obj_values.end(),sort_obj_values);
		sort(object4.EA_obj_values.begin(), object4.EA_obj_values.end(),sort_obj_values);
		sort(object5.EA_obj_values.begin(), object5.EA_obj_values.end(),sort_obj_values);
		sort(object6.EA_obj_values.begin(), object6.EA_obj_values.end(),sort_obj_values);
		sort(object7.EA_obj_values.begin(), object7.EA_obj_values.end(),sort_obj_values);
		sort(object8.EA_obj_values.begin(), object8.EA_obj_values.end(),sort_obj_values);
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
			
			if(i<len7){
				file<<object7.EA_obj_values[i][0];
				file<<"\t";
				file<<object7.EA_obj_values[i][1];
				file<<"\t";
			}
			if(i>=len7){
				file<<"\t";
				file<<"\t";
			}
			
			if(i<len8){
				file<<object8.EA_obj_values[i][0];
				file<<"\t";
				file<<object8.EA_obj_values[i][1];
				file<<"\t";
			}
			if(i>=len8){
				file<<"\t";
				file<<"\t";
			}
			
			file<<endl;
        }
       
       file.close();
	
	cout<<"\n\n\t\t==========FINAL RESULTS==========\n\n";  
    cout<<"SOLUTIONS FOUND USING PSO = "<<len1<<endl;
    cout<<"SOLUTIONS FOUND USING HYBRID PSO AND ABC = "<<len2<<endl;
    cout<<"SOLUTIONS FOUND USING TLBO = "<<len3<<endl;
    cout<<"SOLUTIONS FOUND USING HYBRID TLBO AND ABC = "<<len4<<endl;
    cout<<"SOLUTIONS FOUND USING MBO = "<<len5<<endl;
    cout<<"SOLUTIONS FOUND USING HYBRID MBO AND ABC = "<<len6<<endl;
    cout<<"SOLUTIONS FOUND USING AOA = "<<len7<<endl;
    cout<<"SOLUTIONS FOUND USING HYBRID AOA AND ABC = "<<len8<<endl;
}

//end of for loop
}
   
    return 0;
}
