#include<bits/stdc++.h>
#include "METAHEURISTICS.H"
using namespace std;


int main(){
	srand(time(0));	
    vector<string> arr;
    
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

	for(int i=0;i<24;i++){
		cout<<"\n\n===========READING FILE NUMBER "<<i+1<<"==========="<<endl;
		string s = arr[i];
	    AOA_ABC object1;
	    int t = 1;
	    object1.get_input(s);
	    object1.T = 30;
	    object1.p = 30;
	    cout<<"ITERATION PROGESS : 1 ";
	    object1.generate_population();
	    for(int t=2;t<=object1.T;t++){
	        cout<<t<<" ";
	        object1.update_population(t);
	        object1.escape_local_minima();
	        //object.print_iteration(t);
	    }
	    object1.update_EA();
	    //object1.print_all_solution();
	    
    	string file_name = "";
    	file_name = file_name + "output_" + to_string(object1.no_of_tasks) + "_" + to_string(object1.no_of_robots) + ".txt";
    	ofstream file(file_name);
    	int len = object1.EA_seq.size();
    	for(int j=0;j<object1.EA_seq.size();j++){
    		for(int k=0;k<object1.EA_seq[j].size();k++){
    			file<<object1.EA_seq[j][k];
    			file<<" ";
			}
			file<<endl;
			for(int k=0;k<object1.EA_pa[j].size();k++){
    			file<<object1.EA_pa[j][k];
    			file<<" ";
			}
			file<<endl;
		}
		file.close();
	}
	return 0;
}
