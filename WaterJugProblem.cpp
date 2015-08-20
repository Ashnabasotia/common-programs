#include <bits/stdc++.h>

using namespace std;

// solution to water jug problem, 
// There are 2 jugs A and B where 
// A has a capacity of 3 units and B has the capacity of 2 units
// Aim is to put 2 units in jug B

vector <pair<int,int> > newStatesSet(pair<int,int> state){
  //generating all possible states from a given initial state
  std::vector<pair<int,int> > newStates;
  if(state.first==0 && state.second==0){
    newStates.push_back(make_pair(3,0));
    newStates.push_back(make_pair(0,4));
    newStates.push_back(make_pair(3,4));
  }
  if(state.first!=0 && state.second==0){
    newStates.push_back(make_pair(state.first,4));
    newStates.push_back(make_pair(0,state.first));
    if(state.first<3){
      newStates.push_back(make_pair(3,0));
      newStates.push_back(make_pair(3,4));
    }
  }
  if(state.first==0 && state.second!=0){
    int transferQuantity;
    if(state.second>3)
      transferQuantity=3;
    else
      transferQuantity=state.second;
    newStates.push_back(make_pair(transferQuantity,state.second-transferQuantity));
    newStates.push_back(make_pair(3,state.second));
  }
  if(state.first!=0 && state.second!=0){
    newStates.push_back(make_pair(0,state.second));
    newStates.push_back(make_pair(state.first,0));
    if(state.second<4){
      int transferQuantity1=state.second+state.first;
      int transferQuantity2;
      if(transferQuantity1>4){
        transferQuantity2=transferQuantity1-4;
        transferQuantity1=4;
      }
      else
        transferQuantity2=0;
      newStates.push_back(make_pair(transferQuantity2,transferQuantity1));
    }
    if(state.first<3){
      int transferQuantity1=state.second+state.first;
      int transferQuantity2;
      if(transferQuantity1>3){
        transferQuantity2=transferQuantity1-3;
        transferQuantity1=3;
      }
      else
        transferQuantity2=0;
      newStates.push_back(make_pair(transferQuantity1,transferQuantity2));
    }
  }
  return newStates;
}

bool checkGoal(pair<int,int> x,int V){
  if(x.second==V)// our aim is to get V units in jug second 
    return true;
  return false;
}

void reverseTraversal(map <pair<int,int>,pair<int,int> > parent,pair<int,int> initialState,pair<int,int> goalState){
    if(initialState != goalState){
        reverseTraversal(parent,parent[initialState],goalState);
    }
    cout<<"("<<initialState.first<<","<<initialState.second<<")"<<endl;
}

int main()
{
    //capacity (A,B)::(3,4)  
    //open list for a BFS search
    queue <pair<int,int> > Q;
    pair <int,int> parNode;

    //contains all the states to stop repetetions of states 
    map < pair<int,int> ,int > occured;

    //contains parent of every new state to backtrack for solution
    map < pair<int,int>,pair<int,int> > parent;
    Q.push(make_pair(0,0));//initial state
    while(Q.empty()!=true){
        parNode=Q.front();
        Q.pop();
        if(checkGoal(parNode,2))
          break;
        occured[parNode]++;//update the new state just poped and traversed  
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