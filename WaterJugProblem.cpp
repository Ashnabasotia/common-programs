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

bool checkGoal(pair<int,int> x,int sum){
  return(x.second==sum);
}

void reverseTraversal(map <pair<int,int>,pair<int,int> > parent,pair<int,int> initialState,pair<int,int> goalState){
  if(initialState != goalState){
    reverseTraversal(parent,parent[initialState],goalState);
  }
  cout<<"("<<initialState.first<<","<<initialState.second<<")"<<endl;
}

int main()
{
  //capacity (3,4)  
  //open list
  queue <pair<int,int> > Q;
  pair <int,int> parNode;
  //contains all the states
  map < pair<int,int> ,int > occured;
  //contains parent
  map < pair<int,int>,pair<int,int> > parent;
    
  Q.push(make_pair(0,0));
  while(Q.empty()!=true){
    parNode=Q.front();
    Q.pop();
    if(checkGoal(parNode,2))
      break;
    occured[parNode]++;
    vector <pair<int,int> > leafs = newStatesSet(parNode);
    for(int i=0;i<leafs.size();i++){
      if(occured[leafs[i]]==0){
        Q.push(leafs[i]);
        parent[leafs[i]]=parNode;
      }
    }
  }
  reverseTraversal(parent,parNode,make_pair(0,0));
    
}