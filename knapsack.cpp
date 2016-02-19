#include <bits/stdc++.h>
#define ll long long
using namespace std;

//Solution to http://www.spoj.com/problems/KNPSACK/
// A 0/1 knapsack problem with infinite times using DP 

std::vector<pair<int, int>> vec;   

ll int M[25000];

int parse(string strs){
    int x=strs[0]-'0';
	x = x*10 + strs[2]-'0';
	x = x*10 + strs[3]-'0';
	return x;
}

void init(int N){
	for(int i=0;i<N;i++){
		int Wi;
		string Pi;
		cin>>Wi>>Pi;
		int PiInt = parse(Pi);
		vec.push_back(make_pair(PiInt,Wi));
	}
}

ll int query(int x){
	if(x<=0)
		return 0;
	return M[x];
}

int generate(int x,int N){
    M[0] = 0;
    for(int i=1;i<20000;i++){
    	ll int maxF = 0;

        for(int j=0;j<N;j++){
        	if(i>=vec[j].first){
                if(query(i-vec[j].first)+vec[j].second > maxF){
                	maxF = query(i-vec[j].first)+vec[j].second;
                }
        	}
        }
        
        M[i] = maxF;
        if(maxF>=x)
        	return i;
    }
    return 20000;
}


int main(){

	int X, M;
	cin>>X>>M;

    init(M);
    int ans = generate(X,M);
    printf("%.2f\n",(ans/100.0));
}
