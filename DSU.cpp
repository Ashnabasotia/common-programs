#include <bits/stdc++.h>

/* solution to http://www.spoj.com/problems/LOSTNSURVIVED/ 
   A simple implementation of DSU
*/

int parent[100005];
std::vector<int> rank(100005,1);
std::vector <int> count(100005,1);
std::multiset <std::pair<int,int>> elem; 

void createSet(int x){
    parent[x] = x;
    rank[x] = 1;
}

void init(int n){
    for(int i = 1;i<=n; i++)
        createSet(i);
    for(int i = 1;i<=n;i++)
        elem.insert(std::make_pair(1,i));
}

int findSet(int x){
    if(parent[x] != x) parent[x] = findSet(parent[x]);
    return parent[x];
}

int mergeSets(int x, int y, int n){
    int px = findSet(x);
    int py = findSet(y);
    
    if(px!=py){
        if(rank[py]>rank[px])
            std::swap(px,py);

        elem.erase(elem.find(std::make_pair(rank[py],py)));
        elem.erase(elem.find(std::make_pair(rank[px],px)));
        count[px] += count[py];
        rank[px] += rank[py];
        
        parent[py] = px;
        elem.insert(std::make_pair(rank[px],px));
    }
    
    int min,max;
    
    std::set <std::pair<int,int>>::iterator  ite = elem.begin();
    min = (*ite).first;
    //int temps  = ite->first;
    ite = elem.end();
    ite--;
    max = (*ite).first;
    
    return max - min;
}

void check(int n){
    for(int i=0 ;i<=n ;i++)
        std::cout<<i<<" parent = "<<parent[i]<<"  "<<rank[parent[i]]<<std::endl;
    std::cout<<"\n\n";
    for(int i=0 ;i<=n ;i++)
        std::cout<<i<<"  "<<parent[i]<<std::endl;
}

int main(int argc, char const *argv[])
{
    int n,q;
    std::cin>>n>>q;
    init(n);
    while(q--){
        int x,y;
        std::cin>>x>>y;
        std::cout<<mergeSets(x,y,n)<<std::endl;
        //check(n);
    }
    return 0;
}