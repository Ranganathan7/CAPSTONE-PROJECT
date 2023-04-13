#include<bits/stdc++.h>

using namespace std;

bool sort_obj_values( const vector<int>& v1, const vector<int>& v2 ) {
    	if(v1[0]==v2[0]) return (v1[1]<v2[1]);
    	else return v1[0]>v2[0];
	}

class performance_indicators{
public:
	 
	vector<vector<int> > combined_EA;
	vector<vector<vector<int> > > EA;
	vector<vector<double> > d;
	vector<double> average_d;
	vector<vector<double> > dist;
	vector<double> average_dist;
	
	void split(string &s, char delim, vector<string> &elems) {
    	stringstream ss;
    	ss.str(s);
    	string item;
    	while (getline(ss, item, delim)) {
        	elems.push_back(item);
    	}
	}
	
	void print_EA(vector<vector<int> > front){
		for(int i=0;i<front.size();i++){
			cout<<front[i][0]<<" "<<front[i][1]<<endl;
		}
	}
	
	void create_combined_front(string file_name){
		vector<vector<int> > EA_1;
		vector<vector<int> > EA_2;
		vector<vector<int> > EA_3;
		vector<vector<int> > EA_4;
		vector<vector<int> > EA_5;
		vector<vector<int> > EA_6;
		
		ifstream file(file_name);
		file.seekg(0);
		int x;
		string line;
        while (getline(file, line)){
        	vector<string> row_values;
        	split(line, '\t', row_values);
        	int index = 0;
        	int counter=0;
        	vector<int> temp;
        	for (auto v: row_values){
        		
                if(v!=""){
                	x = stoi(v);
                	temp.push_back(x);
				}
				counter++;
				if(counter==2){
        			if(temp.size()==0){
        				
					}
        			else if(index==0){
                		EA_1.push_back(temp);
					}
					else if(index==1){
						EA_2.push_back(temp);
					}
					else if(index==2){
						EA_3.push_back(temp);
					}
					else if(index==3){
						EA_4.push_back(temp);
					}
					else if(index==4){
						EA_5.push_back(temp);
					}
					else{
						EA_6.push_back(temp);
					}
        			counter = 0;
        			index++;
        			temp.clear();
				}
            }
        }
    
        sort(EA_1.begin(), EA_1.end());
		EA_1.erase(unique(EA_1.begin(), EA_1.end()), EA_1.end());
		
		sort(EA_2.begin(), EA_2.end());
		EA_2.erase(unique(EA_2.begin(), EA_2.end()), EA_2.end());
		
		sort(EA_3.begin(), EA_3.end());
		EA_3.erase(unique(EA_3.begin(), EA_3.end()), EA_3.end());
		
		sort(EA_4.begin(), EA_4.end());
		EA_4.erase(unique(EA_4.begin(), EA_4.end()), EA_4.end());
		
		sort(EA_5.begin(), EA_5.end());
		EA_5.erase(unique(EA_5.begin(), EA_5.end()), EA_5.end());
		
		sort(EA_6.begin(), EA_6.end());
		EA_6.erase(unique(EA_6.begin(), EA_6.end()), EA_6.end());
		

		
		EA.push_back(EA_1);
		EA.push_back(EA_2);
		EA.push_back(EA_3);
		EA.push_back(EA_4);
		EA.push_back(EA_5);
		EA.push_back(EA_6);

		EA_1.clear();
		EA_2.clear();
		EA_3.clear();
		EA_4.clear();
		EA_5.clear();
		EA_6.clear();

		file.close();
        update_combined_front();
        calculate_d();
        calculate_distance();
	}
	
	double distance(int x1, int y1, int x2, int y2)
	{
    	// Calculating distance
    	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
	}
	
	double min_distance(int x1, int y1){
		double ans = INT_MAX;
		for(int i=0; i<combined_EA.size();i++){
			ans = min(ans, distance(x1, y1, combined_EA[i][0], combined_EA[i][1]));
		}
		return ans;
	}
	
	vector<double> calculate_d_for_one_algo(vector<vector<int> > front){
		vector<double> ans;
		for(int i=0;i<front.size();i++){
			ans.push_back(min_distance(front[i][0], front[i][1]));
		}
		return ans;
	}
	
	void calculate_d(){
		for(int i=0;i<6;i++){
			d.push_back(calculate_d_for_one_algo(EA[i]));
		}
		for(int i=0;i<6;i++){
			double average = 0;
			for(int j=0;j<d[i].size();j++){
				average+=d[i][j];
			}
			average = average/d[i].size();
			average_d.push_back(average);
		}
	}
	
	
	vector<double> calculate_distance_for_one_algo(vector<vector<int> > front){
		vector<double> ans;
		for(int i=0;i<front.size();i++){
			double temp = INT_MAX;
			for(int j=0;j<front.size();j++){
				if(i!=j) temp = min(temp, distance(front[i][0], front[i][1], front[j][0], front[j][1]));
			}
		    ans.push_back(temp);	
		}
		return ans;
	}
	
	
	void calculate_distance(){
		for(int i=0;i<6;i++){
			dist.push_back(calculate_distance_for_one_algo(EA[i]));
		}
		for(int i=0;i<6;i++){
			double average = 0;
			for(int j=0;j<dist[i].size();j++){
				average+=dist[i][j];
			}
			average = average/dist[i].size();
			average_dist.push_back(average);
		}
	}
	
	void update_combined_front(){
		vector<vector<int> > combined_front;
		
		for(int i=0;i<6;i++){
			for(int j=0;j<EA[i].size();j++){
				combined_front.push_back(EA[i][j]);
			}
		}
		sort(combined_front.begin(), combined_front.end());
		combined_front.erase(unique(combined_front.begin(), combined_front.end()), combined_front.end());
	    int temp_index = combined_front.size();
	    
	    for(int i=0;i<temp_index;i++){
	        int n = 0;
	        for(int j=0;j<temp_index;j++){
	            if(i==j) continue;
	            
	            if(is_dominating(combined_front[j], combined_front[i])){
	                n = n + 1;
	            }
	        }
	        if(n==0){
	            combined_EA.push_back(combined_front[i]);
	        }
	    }
	}
	
	bool is_dominating(vector<int> x, vector<int> y){
	    bool flag = false;
	    if(x[0]<y[0] && x[1]<y[1]){
	        flag = true;
	        return flag;
	    }
	    else return flag;
	}
	
	double calculate_indicator1_for_one_algo(vector<vector<int> > front){
		double ans;
		ans = front.size();
		return ans;
	}
	
	double calculate_indicator2_for_one_algo(vector<vector<int> > front){
		double ans = 0;
		for(int i=0;i<front.size();i++){
			bool flag = true;
			for(int j=0;j<combined_EA.size();j++){
				if(front[i][0]==combined_EA[j][0] && front[i][1]==combined_EA[j][1]){
					flag = false;
					 break;
				}
			}
			if(flag){
				ans++;
			}
		}
		ans = ans/front.size();
		return ans;
	}
	
	double calculate_indicator3_for_one_algo(int index){
		double ans;
		ans = average_d[index];
		return ans;
	}
	
	double calculate_indicator4_for_one_algo(int index){
		double ans = 0;
		for(int i=0;i<EA[index].size();i++){
			ans+=(pow((dist[index][i] - average_dist[index]), 2));
		}
		ans = ans / EA[index].size();
		ans = sqrt(ans);
		return ans;
	}
	
	double calculate_indicator5_for_one_algo(vector<vector<int> > front){
		double ans = 0;
		double min_ct, max_ct, min_energy, max_energy;
		min_ct = -1;
		max_ct = -1;
		min_energy = -1;
		max_energy = -1;
		for(int i=0;i<front.size();i++){
			if(min_ct==-1){
				min_ct = (double)front[i][0];
				max_ct = (double)front[i][0];
				min_energy = (double)front[i][1];
				max_energy = (double)front[i][1];
			}
			else{
				min_ct = min(min_ct, (double)front[i][0]);
				max_ct = max(max_ct, (double)front[i][0]);
				min_energy = min(min_energy, (double)front[i][1]);
				max_energy = max(max_energy, (double)front[i][1]);
			}
		}
		ans = ans + pow((min_ct - max_ct), 2);
		ans = ans + pow((min_energy - max_energy), 2);
		ans = sqrt(ans);
		return ans;
	}
	
	vector<double> evaluate_indicator1(){
		vector<double> ans;
		for(int i=0;i<6;i++){
			ans.push_back(calculate_indicator1_for_one_algo(EA[i]));
		}
		return ans;
	}
	
	vector<double> evaluate_indicator2(){
		vector<double> ans;
		for(int i=0;i<6;i++){
			ans.push_back(calculate_indicator2_for_one_algo(EA[i]));
		}
		return ans;
	}
	
	vector<double> evaluate_indicator3(){
		vector<double> ans;
		for(int i=0;i<6;i++){
			ans.push_back(calculate_indicator3_for_one_algo(i));
		}
		return ans;
	}
	
	vector<double> evaluate_indicator4(){
		vector<double> ans;
		for(int i=0;i<6;i++){
			ans.push_back(calculate_indicator4_for_one_algo(i));
		}
		return ans;
	}
	
	vector<double> evaluate_indicator5(){
		vector<double> ans;
		for(int i=0;i<6;i++){
			ans.push_back(calculate_indicator5_for_one_algo(EA[i]));
		}
		return ans;
	}
	
};
	


int main(){
	srand(time(0));	
	vector<string> arr;
	string file_name;
	vector<vector<double> > indicator1;
	vector<vector<double> > indicator2;
	vector<vector<double> > indicator3;
	vector<vector<double> > indicator4;
	vector<vector<double> > indicator5;

    arr.push_back("iterations_output_35_5.txt");
    arr.push_back("iterations_output_70_7.txt");
    arr.push_back("iterations_output_111_9.txt");
    
    
	for(int file_number=0; file_number<3; file_number++){	
		file_name = arr[file_number];
		performance_indicators object;
		cout<<"evaluating indicator for file number "<<file_number+1<<endl;
		object.create_combined_front(file_name);
		indicator1.push_back(object.evaluate_indicator1());
		indicator2.push_back(object.evaluate_indicator2());
		indicator3.push_back(object.evaluate_indicator3());
		indicator4.push_back(object.evaluate_indicator4());
		indicator5.push_back(object.evaluate_indicator5());
	}

	string file_name1 = "";
	string file_name2 = "";
	string file_name3 = "";
	string file_name4 = "";
	string file_name5 = "";
	file_name1 = file_name1 + "iterations performance indicator 1" + ".txt";
	file_name2 = file_name2 + "iterations performance indicator 2" + ".txt";
	file_name3 = file_name3 + "iterations performance indicator 3" + ".txt";
	file_name4 = file_name4 + "iterations performance indicator 4" + ".txt";
	file_name5 = file_name5 + "iterations performance indicator 5" + ".txt";
	ofstream file1(file_name1);
	ofstream file2(file_name2);
	ofstream file3(file_name3);
	ofstream file4(file_name4);
	ofstream file5(file_name5);
	for(int i=0;i<3;i++){
		for(int j=0;j<6;j++){
			file1<<indicator1[i][j];
			file1<<"\t";
			file2<<indicator2[i][j];
			file2<<"\t";
			file3<<indicator3[i][j];
			file3<<"\t";
			file4<<indicator4[i][j];
			file4<<"\t";
			file5<<indicator5[i][j];
			file5<<"\t";
		}
		file1<<endl;
		file2<<endl;
		file3<<endl;
		file4<<endl;
		file5<<endl;
	}
	file1.close();
	file2.close();
	file3.close();
	file4.close();
	file5.close();
    return 0;
}
