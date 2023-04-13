#include<bits/stdc++.h>

using namespace std;

class ABC{
public:
    //variables limitation
    int x, y, r, q, z , f, bp;
    
    int p;//population size
    
    int t;//number of iterations
    double w1, w2; //weights
    //setup cost (y, q)
    vector<vector<double> > SRyq{
        {6, 6, 6},
        {5, 5, 5},
        {5, 5, 5}
    };
    
    //maximum capacity
    vector<vector<double> > QRyq{
        {5000, 4000, 4500},
        {6500, 5500, 5000},
        {7000, 6000, 5500}
    };
    
    //TRR(y, r, q)
    vector<vector<vector<double> > > TRRyrq{
        {
            {0.3, 0.3, 0.3},
            {0.1, 0.3, 0.3}
        },
        {
            {0.1, 0.1, 0.1},
            {0.2, 0.3, 0.3}
        },
        {
            {0.2, 0.2, 0.2},
            {0.1, 0.3, 0.3}   
        }
    };
    
    //TRU(y, r, q)
    vector<vector<vector<double> > > TRUyqr{
        {
            {0.7, 0.7, 0.7},
            {0.5, 0.7, 0.7}
        },
        {
            {0.5, 0.5, 0.5},
            {0.6, 0.7, 0.7}
        },
        {
            {0.6, 0.6, 0.6},
            {0.5, 0.7, 0.7}
        }
    };
    
     //ETR(y, r, q)
    vector<vector<vector<double> > > ETRyrq{
        {
            {0.8, 0.8, 0.8},
            {0.6, 0.8, 0.8}
        },
        {
            {0.6, 0.6, 0.6},
            {0.7, 0.8, 0.8}
        },
        {
            {0.7, 0.7, 0.7},
            {0.6, 0.8, 0.8}
        }
    };
    
    //PR(x, z)
    vector<vector<double> > PRxz{
        {0.25, 0},
        {0, 0.1}
    };
    
    //RP(x)
    vector<double> RPx{0.35, 0.2};

    //UR(y, q)
    vector<vector<double> > URyq{
        {0.04, 0.01},
        {0.01, 0.02},
        {0.03, 0.02}
    };
    
    //demand
    vector<double> D{2000, 1800, 2300};
    
    //profit
    vector<double> PFy{400, 360, 460};
    
    //production capacity
    vector<double> QP{2200, 2000, 2300};
    
    //refund(y, q)
    vector<vector<double> > RFyq{
        {10, 8, 8},
        {8, 8, 8},
        {9, 10, 10}
    };
    
    //RR(y, q)
    vector<vector<double> > RRyq{
        {0.4, 0.1},
        {0.2, 0.1},
        {0.3, 0.15}
    };
        vector<vector<double> > PE{
    	{1500, 2050},
        {2500, 1850},
        {1450, 1300}
	};
	
	vector<vector<double> > CARBONry{
        {50, 15, 0},
        {25, 20, 10}
    };
    
    //holds the trial count
    vector<int> trial;
    
    //holds the product amout(y) to be manufactured
    vector<vector<double> > Py;
    
    //Product amount y?Y to be received at intake node q?Q from sales and distribution node r?R
    vector<vector<vector<vector<double> > > > Ryrq;
    
    //Product amount y?Y to be reused from intake node q?Q
    vector<vector<vector<double> > > Ayq;
    
    //Part amount x?X to be acquired from seller z?Z
    vector<vector<vector<double> > > Sxz;
    
    //holds z1 values of the population
    vector<double> z1;
    //holds z2 values of the population
    vector<double> z2;
    //holds Z value
    vector<double> Z;
    //holds fitness values
    vector<double> fit;
    
    double max_z1;
    double max_z2;
    vector<double> prob;
    int limit;
    
    vector<double> best_Py;
    vector<vector<vector<double> > > best_Ryrq;
    vector<vector<double> > best_Ayq;
    vector<vector<double> > best_Sxz;
    double best_z1;
    double best_z2;
    double best_Z;
    double best_fit;
    
    //inputs default values
    void get_input(){
        x = 2;
        y = 3;
        z = 2;
        r = 2;
        q = 2;
        f = 2;
        bp = 3;
        p = 15;
        t = 30;
        w1 = 0.5;
        w2 = 0.5;
        limit = 3;
        best_fit = 1000;
    }
    
    //generates population with size p
      void generate_population(){
        for(int i=0;i<p;i++){
            Py.push_back(generate_Py());
            Ryrq.push_back(generate_Ryrq());
            Ayq.push_back(generate_Ayq());
            Sxz.push_back(generate_Sxz());
        
        }
        constraint_flow_balance(Ryrq, Ayq);
        constraint_demand(Ayq, Py, D);
        
        for(int i=0;i<p;i++){
            
            z1.push_back(calculate_z1(Py[i], Ryrq[i], Ayq[i], Sxz[i]));
            z2.push_back(calculate_z2(Ryrq[i], Py[i]));
            trial.push_back(0);
            
        }
        calculate_max_values();
        for(int i=0;i<p;i++){
        	Z.push_back(calculate_Z(z1[i], z2[i]));
            fit.push_back(fitness_evaluation(Z[i]));
            prob.push_back(0);
		}
        
    }
    
    //generates one random data for Py
    vector<double> generate_Py(){
        vector<double> ans;
        for(int i=0;i<y;i++){
            double random = 500 + rand()%(5000-500+1);
            ans.push_back(random);
        }
        return ans;
    }
    
    //generates one random data for Ryrq
    vector<vector<vector<double> > > generate_Ryrq(){
        vector<vector<vector<double> > > ans;
        for(int i=0;i<y;i++){
            vector<vector<double> > temp2;
            for(int j=0;j<r;j++){
                vector<double> temp1;
                for(int k=0;k<q;k++){
                    double random = 250 + rand()%(500-250+1);
                    temp1.push_back(random);
                }
                temp2.push_back(temp1);
            }
            ans.push_back(temp2);
        }
        return ans;
    }
    
    //generates one random data for Ayq
    vector<vector<double> > generate_Ayq(){
        vector<vector<double> > ans;
        for(int i=0;i<y;i++){
            vector<double> temp;
            for(int j=0;j<q;j++){
                double random = 250 + rand()%(500-250+1);
                temp.push_back(random);
            }
            ans.push_back(temp);
        }
       
        return ans;
    }
    
    //generates one random data for Sxz
    vector<vector<double> > generate_Sxz(){
        vector<vector<double> > ans;
        for(int i=0;i<x;i++){
            vector<double> temp;
            for(int j=0;j<z;j++){
                double random = 500 + rand()%(5000-500+1);
                temp.push_back(random);
            }
            ans.push_back(temp);
        }
        return ans;
    }
    
    //prints the population
    void print_population(){
        for(int i=0;i<p;i++){
            cout<<"\n\nBEE NUMBER : "<<i+1<<endl;
            cout<<endl<<"Py:\n";
            for(int j=0;j<y;j++){
                cout<<int(Py[i][j])<<" ";
            }
            cout<<endl;
            cout<<endl<<"Ryrq:\n";
            for(int j=0;j<y;j++){
                for(int k=0;k<r;k++){
                    for(int l=0;l<q;l++){
                        cout<<int(Ryrq[i][j][k][l])<<" ";
                    }
                    cout<<endl;
                }
                cout<<endl;
            }
            cout<<endl<<"Ayq:\n";
            for(int j=0;j<y;j++){
                for(int k=0;k<q;k++){
                    cout<<int(Ayq[i][j][k])<<" ";
                }
                cout<<endl;
            }
            cout<<endl<<"Sxz\n";
            for(int j=0;j<x;j++){
                for(int k=0;k<z;k++){
                    cout<<int(Sxz[i][j][k])<<" ";
                }
                cout<<endl;
            }
            cout<<endl<<"Z1 value : "<<z1[i]<<endl;
            cout<<endl<<"Z2 value : "<<z2[i]<<endl;
            cout<<endl<<"Z value : "<<Z[i]<<endl;
            cout<<endl<<"FITNESS value : "<<fit[i]<<endl;
        }
    }
    
    //calculates Z1
    double calculate_z1(vector<double> Py, vector<vector<vector<double> > > Ryrq, vector<vector<double> > Ayq, vector<vector<double> > Sxz){
        double first=0, second=0, third=0, fourth=0, fifth=0, sixth = 0, seventh = 0, eight = 0, ninth = 0, tenth = 0;
        for(int i=0;i<y;i++){
            double temp_sum = 0;
            for(int j=0;j<q;j++){
                temp_sum+=Ayq[i][j];
            }
            first+=(PFy[i]*(Py[i]+temp_sum));
        }
        for(int i=0;i<x;i++){
            double temp_sum = 0;
            for(int j=0;j<z;j++){
                temp_sum+=Sxz[i][j];
            }
            second+=(RPx[i]*temp_sum);
        }
        for(int i=0;i<z;i++){
            for(int j=0;j<x;j++){
                third+=(PRxz[j][i] * Sxz[j][i]);
            }
        }
        for(int i=0;i<y;i++){
            for(int j=0;j<r;j++){
                for(int k=0;k<q;k++){
                    fourth+=(RRyq[i][k]*Ryrq[i][j][k]);
                }
            }
        }
        for(int i=0;i<y;i++){
            for(int j=0;j<q;j++){
                fifth+=(URyq[i][j]*Ayq[i][j]);
            }
        }
        for(int i=0;i<y;i++){
            for(int j=0;j<q;j++){
                sixth+=(SRyq[i][j]);
            }
        }
        for(int i=0;i<y;i++){
            for(int j=0;j<q;j++){
                for(int k=0;k<r;k++){
                    seventh+=(RFyq[i][j]*Ryrq[i][j][k]);
                }
            }
        }
        for(int i=0;i<y;i++){
            for(int j=0;j<r;j++){
                for(int k=0;k<q;k++){
                    eight+=(TRRyrq[i][j][k]*Ryrq[i][j][k]);
                }
            }
        }
        for(int i=0;i<y;i++){
            for(int j=0;j<q;j++){
                for(int k=0;k<r;k++){
                    ninth+=(TRUyqr[i][j][k]*Ayq[i][j]);
                }
            }
        }
                    for(int i=0;i<bp;i++){
        	for(int j=0;j<f;j++){
        		tenth+=PE[i][j];
			}
        }
        
        double z1 = first + second - (third + fourth + fifth + sixth + seventh + eight + ninth) +tenth;
        return z1;
    }
    
    //calculates Z2
    double calculate_z2(vector<vector<vector<double> > > Ryrq, vector<double> Py){
        double ans = 0;
        for(int i=0;i<y;i++){
            for(int j=0;j<r;j++){
                for(int k=0;k<q;k++){
                    ans+=(ETRyrq[i][j][k]*Ryrq[i][j][k]);
                }
            }
        }
        for(int i=0;i<r;i++){
            for(int j=0;j<y;j++){
                ans+=(CARBONry[i][j]*Py[j]*0.009);
            }
        }
        return ans;
    }
    
    //calculates Z
    double calculate_Z(double z1, double z2){
        double ans = ((w1 * (z1/max_z1)) - (w2 * (z2/max_z2)));
        return ans;
    }
    
    //fitness evaluation
    double fitness_evaluation(double Z){
        
        double temp;
        if(Z>=0){
            temp = 1 / (1+Z);
        }
        else{
            temp = 1 + abs(Z);
        }
        return temp;
    }
    
    //probability evaluation
    double probability_evaluation(double fit, double max_fit){
        double ans;
        ans = 0.9 * (fit / max_fit);
        return ans;
    }
    
    //employee bee phase
    void employee_bee_phase(){
        for(int i=0;i<p;i++){
            int partner = rand()%p;
            while(partner==i){
                partner = rand()%p;
            }
            int j = rand()%2;
            /*if(j==0){
                modify_Py(i, partner);
            }*/
            if(j==1){
                modify_Ryrq(i, partner);
                
            }
            /*else if(j==2){
                modify_Ayq(i, partner);
            }*/
            else{
                modify_Sxz(i, partner);
            }
        }
        
    }
    void modify_Py(int current, int partner){
        vector<double> new_Py;
        double phi = rand()%11;
        phi = phi/10;
        for(int i=0;i<y;i++){
            double new_value = (Py[current][i] + (phi * (Py[current][i] - Py[partner][i])));
            if(new_value>5000) new_value = 5000;
            if(new_value<500) new_value = 500;
            new_Py.push_back(new_value);
        }
        double z1_new = calculate_z1(new_Py, Ryrq[current], Ayq[current], Sxz[current]);
        double z2_new = calculate_z2(Ryrq[current], new_Py);
        double Z_new = calculate_Z(z1_new, z2_new);
        double fit_new = fitness_evaluation(Z_new);
        if(fit_new <= fit[current]){
            Py[current] = new_Py;
            z1[current] = z1_new;
            z2[current] = z2_new;
            Z[current] = Z_new;
            fit[current] = fit_new;
            trial[current] = 0;
        }
        else{
            trial[current]++;
        }
    }
    
    void modify_Ryrq(int current, int partner){
        vector<vector<vector<double> > > new_Ryrq(y, vector<vector<double>>(r, vector<double>(q)));
        double phi = rand()%11;
        phi = phi/10;
        for(int i=0;i<y;i++){
            for(int j=0;j<r;j++){
                for(int k=0;k<q;k++){
                    double new_value = (Ryrq[current][i][j][k] + (phi * (Ryrq[current][i][j][k] - Ryrq[partner][i][j][k])));
                    if(new_value<250) new_value = 250;
                    if(new_value>500) new_value = 500;
                    new_Ryrq[i][j][k] = new_value;
                }
            }
        }
        
        double z1_new = calculate_z1(Py[current], new_Ryrq, Ayq[current], Sxz[current]);
        double z2_new = calculate_z2(new_Ryrq, Py[current]);
        double Z_new = calculate_Z(z1_new, z2_new);
        double fit_new = fitness_evaluation(Z_new);
        if(fit_new <= fit[current]){
            Ryrq[current] = new_Ryrq;
            z1[current] = z1_new;
            z2[current] = z2_new;
            Z[current] = Z_new;
            fit[current] = fit_new;
            trial[current] = 0;
            constraint_flow_balance(Ryrq, Ayq);
        	constraint_demand(Ayq, Py, D);
        }
        else{
            trial[current]++;
        }
    }
    
    void modify_Ayq(int current, int partner){
        vector<vector<double> > new_Ayq(y, vector<double>(q));
        
        double phi = rand()%11;
        phi = phi/10;
        for(int i=0;i<y;i++){
            for(int j=0;j<q;j++){
                double new_value = (Ayq[current][i][j] + (phi * (Ayq[current][i][j] - Ayq[partner][i][j])));
                if(new_value>500) new_value = 500;
                if(new_value<250) new_value = 250;
                new_Ayq[i][j] = new_value;
            }
        }
        double z1_new = calculate_z1(Py[current], Ryrq[current], new_Ayq, Sxz[current]);
        double z2_new = calculate_z2(Ryrq[current], Py[current]);
        double Z_new = calculate_Z(z1_new, z2_new);
        double fit_new = fitness_evaluation(Z_new);
        if(fit_new <= fit[current]){
            Ayq[current] = new_Ayq;
            z1[current] = z1_new;
            z2[current] = z2_new;
            Z[current] = Z_new;
            fit[current] = fit_new;
            trial[current] = 0;
        }
        else{
            trial[current]++;
        }
    }
    
    void modify_Sxz(int current, int partner){
        vector<vector<double> > new_Sxz(x, vector<double>(z));
        double phi = rand()%11;
        phi = phi/10;
        for(int i=0;i<x;i++){
            for(int j=0;j<z;j++){
                double new_value = (Sxz[current][i][j] + (phi * (Sxz[current][i][j] - Sxz[partner][i][j])));
                if(new_value>5000) new_value = 5000;
                if(new_value<500) new_value = 500;
                new_Sxz[i][j] = new_value;
            }
        }
        constraint_flow_balance(Ryrq, Ayq);
        constraint_demand(Ayq, Py, D);
        double z1_new = calculate_z1(Py[current], Ryrq[current], Ayq[current], new_Sxz);
        double z2_new = calculate_z2(Ryrq[current], Py[current]);
        double Z_new = calculate_Z(z1_new, z2_new);
        double fit_new = fitness_evaluation(Z_new);
        if(fit_new <= fit[current]){
            Sxz[current] = new_Sxz;
            z1[current] = z1_new;
            z2[current] = z2_new;
            Z[current] = Z_new;
            fit[current] = fit_new;
            trial[current] = 0;
        }
        else{
            trial[current]++;
        }
    }
    
    //onlooker bee phase
    void onlooker_bee_phase(){
        int m = 0, n = 0;
        double max_fit = -1;
        for(int i=0;i<p;i++){
            if(fit[i]>max_fit) max_fit = fit[i];
        }
        for(int i=0;i<p;i++){
            prob[i] = probability_evaluation(fit[i], max_fit);
        }
        while(m<p){
            double r = rand()%11;
            r = r / 10;
            if(r<prob[n]){
                int partner = rand()%p;
                while(partner==n){
                    partner = rand()%p;
                }
                int j = rand()%2;
                /*if(j==0){
                    modify_Py(n, partner);
                }*/
                if(j==1){
                    modify_Ryrq(n, partner);

                }
                /*else if(j==2){
                    modify_Ayq(n, partner);
                }*/
                else{
                    modify_Sxz(n, partner);
                }
                m = m + 1;
            }
            n = n + 1;
            if(n>=p) n = 0;
        }
    }
    
    //scout bee phase
    void scout_bee_phase(){
        for(int i=0;i<p;i++){
            if(trial[i]>limit){
                trial[i] = 0;
                Py[i] = generate_Py();
                Ryrq[i] = generate_Ryrq();
                Ayq[i] = generate_Ayq();
                Sxz[i] = generate_Sxz();
                constraint_flow_balance(Ryrq, Ayq);
        		constraint_demand(Ayq, Py, D);
                z1[i] = calculate_z1(Py[i], Ryrq[i], Ayq[i], Sxz[i]);
                z2[i] = calculate_z2(Ryrq[i], Py[i]);
                Z[i] = calculate_Z(z1[i], z2[i]);
                fit[i] = fitness_evaluation(Z[i]);
                
            }
        }
        
        
    }
    
    //memorizing the best solution
    void memorize_best_solution(){
        for(int i=0;i<p;i++){
            if(fit[i]<best_fit){
                best_fit = fit[i];
                best_Py = Py[i];
                best_Ryrq = Ryrq[i];
                best_Ayq = Ayq[i];
                best_Sxz = Sxz[i];
                best_z1 = z1[i];
                best_z2 = z2[i];
                best_Z = Z[i];
            }
        }
    }
    
    void print_best_solution(){
        cout<<"\n============BEST SOLUTION===============\n";
        cout<<"\nPy"<<endl;
        for(int i=0;i<y;i++){
            cout<<int(best_Py[i])<<" ";
        }
        cout<<endl;
        
        cout<<"\nRyrq"<<endl;
        for(int i=0;i<y;i++){
            for(int j=0;j<r;j++){
                for(int k=0;k<q;k++){
                    cout<<int(best_Ryrq[i][j][k])<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl;
        
        cout<<"\nAyq"<<endl;
        for(int i=0;i<y;i++){
            for(int j=0;j<q;j++){
                cout<<int(best_Ayq[i][j])<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        
        cout<<"\nSxz"<<endl;
        for(int i=0;i<x;i++){
            for(int j=0;j<z;j++){
                cout<<int(best_Sxz[i][j])<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"\n Z1 value = "<<best_z1<<endl;
        cout<<"\n Z2 value = "<<best_z2<<endl;
        cout<<"\n Z value = "<<best_Z<<endl;
        cout<<"\n fitness value = "<<best_fit<<endl;
    }
    
    //Ayq = sum(Ryrq) for all r
    void constraint_flow_balance(vector<vector<vector<vector<double> > > > &Ryrq, vector<vector<vector<double> > > &Ayq){
        for(int i=0;i<p;i++){
            for(int j=0;j<y;j++){
                for(int k=0;k<q;k++){
                    double temp_sum = 0;
                    for(int l=0;l<r;l++){
                        temp_sum+=Ryrq[i][j][l][k];
                    }
                    Ayq[i][j][k] = temp_sum;
                }
            }
        }
    }
    
    void constraint_demand(vector<vector<vector<double> > > &Ayq, vector<vector<double> > &Py, vector<double> &D){
        for(int i=0;i<p;i++){
            for(int j=0;j<y;j++){
                double temp_sum = 0;
                for(int k=0;k<q;k++){
                    temp_sum+=Ayq[i][j][k];
                }
                Py[i][j] = D[j] - temp_sum;
            }
        }
        
    }
    void calculate_max_values(){
		max_z1 = INT_MIN;
		max_z2 = INT_MIN;
		for(int i=0;i<p;i++){
			max_z1 = max(z1[i], max_z1);
			max_z2 = max(z2[i], max_z2);
		}
	}
};





int main(){
    srand(time(0));
    ABC object;
    ofstream file("output.txt");
    object.get_input();
    object.generate_population();
    int T = object.t;
    for(int i=0;i<T;i++){
        cout<<"\n\n\nITERATION "<<i+1<<endl;
        file<<"\nITERATION "<<i+1<<endl;
        object.print_population();
        for(int j=0;j<object.p;j++){
        	file<<object.z1[j]<<"\t"<<object.z2[j]<<"\t"<<object.Z[j]<<endl;
		}
        object.employee_bee_phase();
        object.onlooker_bee_phase();
        object.memorize_best_solution();
        object.scout_bee_phase();
    }
    object.print_best_solution();
    file.close();
    return 0;
}

