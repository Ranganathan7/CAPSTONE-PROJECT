#include<bits/stdc++.h>

using namespace std;

bool sort_obj_values( const vector<int>& v1, const vector<int>& v2 ) {
    	if(v1[0]==v2[0]) return (v1[1]<v2[1]);
    	else return v1[0]>v2[0];
	}

class evaluate_winner{
public:
	 
	vector<vector<double> > data;

	
	void split(string &s, char delim, vector<string> &elems) {
    	stringstream ss;
    	ss.str(s);
    	string item;
    	while (getline(ss, item, delim)) {
        	elems.push_back(item);
    	}
	}
	

	
	vector<int> evaluate_winner1(string file_name){
		data.clear();
		vector<int> ans;
		ifstream file(file_name);
		file.seekg(0);
		double x;
		string line;
        while (getline(file, line)){
        	vector<string> row_values;
        	split(line, '\t', row_values);
        	vector<double> temp;
        	for (auto v: row_values){
        		x = stod(v);
        		temp.push_back(x);
            }
            data.push_back(temp);
        }
        for(int i=0;i<32;i++){
        	int winner = 1;
        	double value = data[i][0];
        	for(int j=1;j<8;j++){
        		if(data[i][j]>=value){
        			value = data[i][j];
        			winner = j+1;
				}
			}
        	ans.push_back(winner);
		}
        
    return ans;  
	}
	
	vector<int> evaluate_winner2(string file_name){
		data.clear();
		vector<int> ans;
		ifstream file(file_name);
		file.seekg(0);
		double x;
		string line;
        while (getline(file, line)){
        	vector<string> row_values;
        	split(line, '\t', row_values);
        	vector<double> temp;
        	for (auto v: row_values){
        		x = stod(v);
        		temp.push_back(x);
            }
            data.push_back(temp);
        }
        for(int i=0;i<32;i++){
        	int winner = 1;
        	double value = data[i][0];
        	for(int j=1;j<8;j++){
        		if(data[i][j]<=value){
        			value = data[i][j];
        			winner = j+1;
				}
			}
        	ans.push_back(winner);
		}
        
    return ans;  
	}
	
	vector<int> evaluate_winner3(string file_name){
		data.clear();
		vector<int> ans;
		ifstream file(file_name);
		file.seekg(0);
		double x;
		string line;
        while (getline(file, line)){
        	vector<string> row_values;
        	split(line, '\t', row_values);
        	vector<double> temp;
        	for (auto v: row_values){
        		x = stod(v);
        		temp.push_back(x);
            }
            data.push_back(temp);
        }
        for(int i=0;i<32;i++){
        	int winner = 1;
        	double value = data[i][0];
        	for(int j=1;j<8;j++){
        		if(data[i][j]<=value){
        			value = data[i][j];
        			winner = j+1;
				}
			}
        	ans.push_back(winner);
		}
        
    return ans;  
	}
	
	vector<int> evaluate_winner4(string file_name){
		data.clear();
		vector<int> ans;
		ifstream file(file_name);
		file.seekg(0);
		double x;
		string line;
        while (getline(file, line)){
        	vector<string> row_values;
        	split(line, '\t', row_values);
        	vector<double> temp;
        	for (auto v: row_values){
        		x = stod(v);
        		temp.push_back(x);
            }
            data.push_back(temp);
        }
        for(int i=0;i<32;i++){
        	int winner = 1;
        	double value = data[i][0];
        	for(int j=1;j<8;j++){
        		if(data[i][j]<=value){
        			value = data[i][j];
        			winner = j+1;
				}
			}
        	ans.push_back(winner);
		}
        
    return ans;  
	}
	
	vector<int> evaluate_winner5(string file_name){
		data.clear();
		vector<int> ans;
		ifstream file(file_name);
		file.seekg(0);
		double x;
		string line;
        while (getline(file, line)){
        	vector<string> row_values;
        	split(line, '\t', row_values);
        	vector<double> temp;
        	for (auto v: row_values){
        		x = stod(v);
        		temp.push_back(x);
            }
            data.push_back(temp);
        }
        for(int i=0;i<32;i++){
        	int winner = 1;
        	double value = data[i][0];
        	for(int j=1;j<8;j++){
        		if(data[i][j]>=value){
        			value = data[i][j];
        			winner = j+1;
				}
			}
        	ans.push_back(winner);
		}
        
    return ans;  
	}
};
	


int main(){
	srand(time(0));	
	vector<string> arr;
	string file_name;
	vector<int> winner1;
	vector<int> winner2;
	vector<int> winner3;
	vector<int> winner4;
	vector<int> winner5;
	vector<int> total_winner;
    arr.push_back("performance indicator 1.txt");
    arr.push_back("performance indicator 2.txt");
    arr.push_back("performance indicator 3.txt");
    arr.push_back("performance indicator 4.txt");
    arr.push_back("performance indicator 5.txt");
    evaluate_winner object;
		
	file_name = arr[0];
	winner1 = object.evaluate_winner1(file_name);
	
	file_name = arr[1];
	winner2 = object.evaluate_winner2(file_name);
	
	file_name = arr[2];
	winner3 = object.evaluate_winner3(file_name);
	
	file_name = arr[3];
	winner4 = object.evaluate_winner4(file_name);
	
	file_name = arr[4];
	winner5 = object.evaluate_winner5(file_name);
	
	
	for(int i=0;i<32;i++){
		map<int, int> m;
		m[winner1[i]]++;
		m[winner2[i]]++;
		m[winner3[i]]++;
		m[winner4[i]]++;
		m[winner5[i]]++;
		int ans = 0;
		for(auto x: m){
			if(x.second>=ans){
				ans = x.first;
			}
		}
		total_winner.push_back(ans);
	}
	string file_name1 = "";
	file_name1 = file_name1 + "conclusion" + ".txt";
	ofstream file1(file_name1);
	for(int i=0;i<32;i++){
		file1<<winner1[i];
		file1<<"\t";
		file1<<winner2[i];
		file1<<"\t";
		file1<<winner3[i];
		file1<<"\t";
		file1<<winner4[i];
		file1<<"\t";
		file1<<winner5[i];
		file1<<"\t";
		file1<<total_winner[i];
		file1<<endl;
	}
	file1.close();
    return 0;
}
