#include <bits/stdc++.h>

using namespace std;

vector <pair<int,int> > newStatesSet(pair<int,int> state){
  //generating all possible states from a given initial state
  vector<pair<int,int> > newStates;

  if (state.first < 3) {
    newStates.push_back(make_pair(3, state.second));
  }
  if (state.second < 4) {
    newStates.push_back(make_pair(state.first, 4));
  }
  if (state.first > 0) {
    newStates.push_back(make_pair(0, state.second));
  }
  if (state.second > 0) {
    newStates.push_back(make_pair(state.first, 0));
  }
  if (state.second > 0 && state.first < 3) {
    newStates.push_back(make_pair(
                        std::min(3, state.first + state.second),
                        std::max(state.second - (3 - state.first), 0))
                       );
  }
  if (state.first > 0 && state.second < 4) {
    newStates.push_back(make_pair(
                        std::max(state.first - (4 - state.second), 0),
                        std::min(4, state.second + state.first))
                       );
  }
  return newStates;
}

//source node , goal node , depth , answer if found is stored here
bool  depthLimitedSearch(pair<int, int> source, pair<int, int> goal, int depth, vector<pair<int,int> > &ans){

  if(source.first==goal.first && source.second==goal.second){
    return true;
  }

  if(depth<=0)
    return false;

  vector <pair<int,int> > leafs = newStatesSet(source);
  for(int i=0; i<leafs.size(); i++)
    if(depthLimitedSearch(leafs[i], goal, depth-1, ans)){
      ans.push_back(leafs[i]);
      return true;
    }
}

void iterativeDeepeningSearch(){
  
  vector<pair<int, int> > ans;
  for(int i=1 ; i <= 8 ;i++){
    vector<pair<int, int> > vec;
    depthLimitedSearch(make_pair(0,0),make_pair(0,2),i,vec);
    if(vec.size()>0){
      ans=vec;
      break;
    }
  }
   
  for(int i=ans.size()-1; i>=0; i--){
    cout<<"("<<ans[i].first<<","<<ans[i].second<<")\n";
  }
}

int main()
{ 
  iterativeDeepeningSearch();
}