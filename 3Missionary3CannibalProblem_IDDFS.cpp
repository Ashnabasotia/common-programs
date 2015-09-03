#include <bits/stdc++.h>

using namespace std;

//state initial state (0,3,3) Side Of the Boat 0->Right/1 /Cannibal/Missionary on right hand side 
vector < pair < int, pair<int,int> > > newStatesSet(pair< int, pair < int, int > > state){
  //generating all possible states from a given initial state
  vector < pair< int, pair< int, int> > > newStatesSet;
  int C = state.second.first, M = state.second.second;

  if(state.first==0){
    if(C>=1)
      newStatesSet.push_back(make_pair(1, make_pair( C-1 ,M  )));
    if(M>=1)
      newStatesSet.push_back(make_pair(1, make_pair( C   ,M-1)));
    if(C >= 2)
      newStatesSet.push_back(make_pair(1, make_pair( C-2, M   )));
    if(C >= 1 && M >=1 )
      newStatesSet.push_back(make_pair(1, make_pair( C-1, M-1 )));
    if(M >= 2)
      newStatesSet.push_back(make_pair(1, make_pair( C  , M-2 )));
  }
  else{
    C = 3- C;
    M = 3- M;
    
    if(C >= 1)
      newStatesSet.push_back(make_pair(0, make_pair(3- C+ 1 ,3- M  )));
    if(M >= 1)
      newStatesSet.push_back(make_pair(0, make_pair(3- C   ,3- M+ 1)));
    if(C >= 2)
      newStatesSet.push_back(make_pair(0, make_pair(3- C+ 2, 3- M   )));
    if(C >= 1 && M >=1 )
      newStatesSet.push_back(make_pair(0, make_pair(3- C+ 1, 3- M+ 1 )));
    if(M >= 2)
      newStatesSet.push_back(make_pair(0, make_pair(3- C  , 3- M+ 2)));
  }
  return newStatesSet;
}

bool validState(pair<int, pair<int, int> > state){
  int C = state.second.first, M = state.second.second;
  if(C > M && M!=0)
    return false;
  C = 3- C, M = 3- M;
  if(C > M && M!=0)
    return false;
  return true;
}

//source node , goal node , depth , answer if found is stored here
bool  depthLimitedSearch(pair<int, pair<int, int> > source, pair<int, pair<int, int> > goal, int depth, vector<pair<int, pair<int,int> > > &ans){

  if(source==goal)
    return true;

  if(depth<=0)
    return false;

  vector <pair<int, pair<int,int> > > leafs = newStatesSet(source);
  for(int i=0; i<leafs.size(); i++)
    if(validState(leafs[i])){
      if(depthLimitedSearch(leafs[i], goal, depth-1, ans)){
        ans.push_back(leafs[i]);
        return true;
      }
    }
}

string form(int stateNos,string character){
  string rep="";
  for(int i=1; i<=3; i++)
    if(stateNos>=i)
      rep.append(character);
    else
      rep.append(" ");
  return rep;
}

void displayState(pair<int, pair<int, int> > state){
  string rep = "";
  rep.append(form(state.second.first,"C"));
  rep.append(form(state.second.second,"M"));
  for(int i=1; i<=6; i++){
    if(state.first==0 && i==2)
      rep.append("B");
    else
    if(state.first==1 && i==5)
      rep.append("B");
    else
      rep.append(" ");
  }
  rep.append(form(3-state.second.first,"C"));
  rep.append(form(3-state.second.second,"M"));
  cout<<rep<<endl;
}

void iterativeDeepeningSearch(pair<int, pair<int, int> > source, pair<int, pair<int, int> > goal){
  
  vector< pair<int , pair<int, int> > > ans;
  for(int i=1 ; i <= 25 ;i++){
    vector<pair<int, pair<int, int> > >vec;
    depthLimitedSearch(source,goal,i,vec);
    if(vec.size()>0){
      ans=vec;
      break;
    }
  }
  
  displayState(source);
  for(int i=ans.size()-1; i>=0; i--){
  //  cout<<"("<<ans[i].first<<","<<ans[i].second.first<<", "<<ans[i].second.second<<")\n";
    displayState(ans[i]);
  }
}

int main()
{ 
  pair<int, pair<int, int> > source = make_pair(0,make_pair(3, 3 ));
  pair<int, pair<int, int> > goal   = make_pair(1,make_pair(0, 0 ));
  iterativeDeepeningSearch(source,goal);
  
  /*for (int j=1;j<5;j++){
    int a,b,c;
    cin>>a>>b>>c;

    vector <pair<int, pair<int,int> > > V = newStatesSet(make_pair(a,make_pair(b,c)));
    for(int i=0 ; i<V.size(); i++)
      cout<<V[i].first<<",  "<<V[i].second.first<<", "<<V[i].second.second<<endl;
  }//*/
}