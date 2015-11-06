#include <bits/stdc++.h>

/*
A NAIVE TETRIS SOLVER WITH BASIC HEURISTICS
WAS WRITTEN INITIALLY AS A SOLUTION TO THIS CHALLENGE PROBLEM ON CODECHEF.COM
https://www.codechef.com/problems/CHTTRS
*/

using namespace std;

//Data type for representing pieces 
struct tetro{
	int width, height; //width and height of tetrominos 
	int repr[4];       //binary representation of tetrominos
};

vector <tetro> piece[7];//meta data about tetrominos
vector <int> board(20,0); // actually used uptil 15

void print(vector<int> vec) {

    for (int i = 14; i >= 0; i--) {
    	string str="";
        for (int j = 0; j < 15; j++) {
            str+=(vec[i] & (1<<j) ? '#' : '.');
        }
        reverse(str.begin(),str.end());
        cout<<str;
        cout<<"   "<<vec[i]<<" \n";
    }
}

void init(){
    //initializing meta data of tetrominos 
    piece[0].resize(2);
    piece[0][0].width = 4;
    piece[0][0].height = 1;
    piece[0][0].repr[0] = 15;
    
    piece[0][1].width = 1;
    piece[0][1].height = 4;
    piece[0][1].repr[0] = 1;
    piece[0][1].repr[1] = 1;
    piece[0][1].repr[2] = 1;
    piece[0][1].repr[3] = 1;

    piece[1].resize(4);
    piece[1][0].width = 3;
    piece[1][0].height = 7;
    piece[1][0].repr[0] = 4;
    piece[1][0].repr[1] = 2;

    piece[1][1].width = 2;
    piece[1][1].height = 3;
    piece[1][1].repr[0] = 3;
    piece[1][1].repr[1] = 1;
    piece[1][1].repr[2] = 1;

    piece[1][2].width = 2;
    piece[1][2].height = 3;
    piece[1][2].repr[0] = 2;
    piece[1][2].repr[1] = 2;
    piece[1][2].repr[2] = 3;
    
    piece[1][3].width = 3;
    piece[1][3].height = 2;
    piece[1][3].repr[0] = 1;
    piece[1][3].repr[1] = 7;

    piece[2].resize(4);
    piece[2][0].width = 3;
    piece[2][0].height = 2;
    piece[2][0].repr[0] = 7;
    piece[2][0].repr[1] = 1;

    piece[2][1].width = 2;
    piece[2][1].height = 3;
    piece[2][1].repr[0] = 3;
    piece[2][1].repr[1] = 2;
    piece[2][1].repr[2] = 2;

    piece[2][2].width = 3;
    piece[2][2].height = 2;
    piece[2][2].repr[0] = 4;
    piece[2][2].repr[1] = 7;

    piece[2][3].width = 2;
    piece[2][3].height = 3;
    piece[2][3].repr[0] = 1;
    piece[2][3].repr[1] = 1;
    piece[2][3].repr[2] = 3;

    piece[3].resize(1);
    piece[3][0].width = 2;
    piece[3][0].height = 2;
    piece[3][0].repr[0] = 3;
    piece[3][0].repr[1] = 3;

    piece[4].resize(2);
    piece[4][0].width = 3;
    piece[4][0].height = 2;
    piece[4][0].repr[0] = 6;
    piece[4][0].repr[1] = 3;

    piece[4][1].width = 2;
    piece[4][1].height = 3;
    piece[4][1].repr[0] = 1;
    piece[4][1].repr[1] = 3;
    piece[4][1].repr[2] = 2;

    piece[5].resize(4);
    piece[5][0].width = 3;
    piece[5][0].height = 2;
    piece[5][0].repr[0] = 7;
    piece[5][0].repr[1] = 2;

    piece[5][1].width = 2;
    piece[5][1].height = 3;
    piece[5][1].repr[0] = 2;
    piece[5][1].repr[1] = 3;
    piece[5][1].repr[2] = 2;

    piece[5][2].width = 3;
    piece[5][2].height = 2;
    piece[5][2].repr[0] = 2;
    piece[5][2].repr[1] = 7;

    piece[5][3].width = 2;
    piece[5][3].height = 3;
    piece[5][3].repr[0] = 1;
    piece[5][3].repr[1] = 3;
    piece[5][3].repr[2] = 1;

    piece[6].resize(2);
    piece[6][0].width = 3;
    piece[6][0].height = 2;
    piece[6][0].repr[0] = 3;
    piece[6][0].repr[1] = 6;

    piece[6][1].width = 2;
    piece[6][1].height = 3;
    piece[6][1].repr[0] = 2;
    piece[6][1].repr[1] = 3;
    piece[6][1].repr[2] = 1;
}

struct playInfo {
    bool over;
    int R,C,fig,orien;
};


struct tetrisMove{//final selected move are saved here 
public:
	int R, C, O;
	double eval;
	bool over;
};

string binary(int x){
	return(bitset<15>(x).to_string());	
}

//given a coordinate(row,coloum) on board it returns the corrected 15 bit integer 
//according to the tetromino orien data 
//it basically shifts the orien data req number of bits <<    line is the scan line on which we are on piece
int fourMatCorr(int coloum, int orientation,  int figure, int line){ // line is 0 indexed

    int req = 15 - coloum - piece[figure][orientation].width;
    int ans = piece[figure][orientation].repr[line];
    ans=ans<<req;
    return ans;

}

// Board | figure -> 0 indexed | coloum | orientation. 
// Returns Row in 0 enumerated format BUT IN SAME order that is to be printed.
int getRow(vector<int> &v, int figure, int coloum, int orientation){
	int row = 0;
    for(int i = 15 - 1; i>=0; i--){//row
    	int cntr=i;
        for(int j = 0;  j < piece[figure][orientation].height ; j++){//row
        	int compare = fourMatCorr(coloum, orientation, figure, j); // stores the piece info in bin form
            //if(coloum>12)cout<<coloum<<"   "<<figure<<"  "<<i<<"  vec == "<<v[i]<<" orig pattern "<<piece[figure][orientation].repr[j]<<" BIN == "<<compare<<"  == "<<(compare&v[i])<<" orien = "<<orientation<<endl; 
        	if(compare & v[cntr++])
        		return i+1;
        }
        //cout<<"\n";
    }
    //cout<<"\n\n";
    return 0;
}

// board | figure -> 0 indexed | coloum | orientation 
playInfo makeMove(vector<int> &v, int figure, int coloum, int orientation){
    playInfo info;
    info.over = false;
    info.R=-1;
    info.C=-1;

    int row   = getRow(v,figure,coloum,orientation);
    //cout<<"Row >> "<<row<<endl;
    if(row+piece[figure][orientation].height>15)
    	info.over=true;
    info.R = row;
    info.C = coloum;
    info.fig = figure;
    info.orien = orientation;
    return info;
}

void refreshBoard(vector<int> &v,  playInfo info){

    for(int i = 0; i< piece[info.fig][info.orien].height; i++){
        int pieceLine = fourMatCorr(info.C, info.orien, info.fig, i);
        v[info.R+i] |= pieceLine; 
        //cout<<info.R+i<<endl;
    }

}

//HERUSTIC FUNCTIONS

//counts 1 - 4 holes in proximity bound by 3 sides accept from top
double holes(vector<int> board){

    int i, j, holes = 0, row_holes = 0, pre_row = board[14];
    for (i = 13; i >= 0; --i)
    {
        row_holes = ~board[i] & (pre_row | row_holes);
        for(j = 0; j < 15; ++j)
        {
            holes += ((row_holes >> j) & 1);
        }
        pre_row = board[i];
    }
    return holes;
}

double height(vector<int> v, std::vector<int> &height,int debug){
    int mask = 1;
    double ans = 0;

    for(int col = 0; col<15; col++){
    	int col_height = 0;
        for(int i=14; i>=0; i--){
            if(v[i]&mask){
            	col_height = i+1;
            	break;
            }
        }
        height[14-col]=col_height;
        ans+=col_height;
        mask=mask<<1;
    }
    for(int i=0;i<15&&debug;i++){
    	cout<<height[i]<<" ";
    }
    if(debug)
    	cout<<"\n";
    return ans/15;
}

int completeLines(std::vector<int> v){
    int ans = 0;
	for(int i=0; i<15 ;i++){
		if(v[i]==32767)
			ans++;
	}
	return ans;
}
//debug = 1 when debug stat on
double Bumps(std::vector<int> v,int debug){
	//sum of absolute difference bet all two coloums 
	double ans = 0;
	for(int i=1; i<15; i++){
        int x = v[i]<v[i-1]?(v[i-1]-v[i]):(v[i]-v[i-1]);
        if(debug)
			cout<<x<<" ";
        ans+=x;
	}
	if(debug)
		cout<<"\n";
	return ans;
}

//not used
int valleys(std::vector<int> vec){
    return 1;
}

// the actual generation of evaluation function value takes place here
double analyze(vector<int> v){
	std::vector<int> hgh(15);

	double hole_      = holes(v)*-0.35663; //Holes   Count : SELF
	double avgHeight  = height(v,hgh,0)*-0.510066; //Average Height  
  double completeL  = completeLines(v)*0.760666; //Complete Lines
  double Valleys    = 1; //Valleys Count : counts of creeks that are deeper than 3 cells 
	double bumps      = Bumps(hgh,0)*-0.184483;//Bumps : sudden changes on the top layer of board more than one is taken as bump
	double randomness = (rand()%500)/500.0-0.2;
	return hole_+avgHeight+completeL+bumps+randomness;
	//Distribution : how much pieces are distributed across the board
}

tetrisMove play(int fig, int rot){
    tetrisMove bestMove;
    bestMove.O=rot;
    bestMove.eval = -999999;
    bestMove.over = true;

    int i = 0;
    bool stop = false;
    
    if(rot!=-1){
    	i     = rot;
    	stop  = true;
    }

    //best move and final move are the same thing in different format 
    playInfo finalMove;//stores the selected move
    bool set = false;

    for (; i < piece[fig-1].size(); i++){
        
        for (int j = 0; j < 16 - piece[fig-1][i].width; j++){
            vector<int> tempBoard = board;
            //if(i==2)
            //cout<<fig<<" width "<<piece[fig-1][i].width<<" col = "<<j<<" orien = "<<i<<"\n";
            playInfo info = makeMove(tempBoard, fig-1 , j, i);//temporary board | figure | coloum | orientation 
            
            if(info.over)
            	continue;
            //cout<<" ===> "<<info.R<<endl;
            refreshBoard(tempBoard, info);
            double val = analyze(tempBoard);//val evaluation function value more the better 
            
            if(bestMove.eval<val){
                
                bestMove.O   =i;
                bestMove.R   =info.R;
                bestMove.C   =info.C;
                bestMove.eval=val;

                finalMove    =info;
                bestMove.over=false;
                set = true;
            }
            
        }
        
        if(stop)
        	break;
    }

    if(set)
        refreshBoard(board, finalMove);
    
    //print(board);
    //cout<<"Real Selected move "<<finalMove.R<<"  "<<finalMove.C<<"  "<<finalMove.fig<<" "<<finalMove.orien<<endl;
    //cout<<"Selected Move "<<bestMove.R<<"  "<<bestMove.C<<"  "<<bestMove.O<<"  "<<set<<endl; 
    return bestMove;

}

void cleanRows(vector<int> &vec){
    for(int i=0; i<15; i++ ){

    	if(vec[i] == 32767){
    		for(int j=i; j<15; j++ ){
    			if(j==14)
    				vec[j] = 0;
    			else
    				vec[j] = vec[j+1];
    		}
    		i--;
    	}

    }
    //print(vec);
}

//debug only function to fill board as required
void debug_fillBoard(vector<int> &b){
    for(int i=0;i<14;i++)
        b[i]=32766;
   b[14] = 0;
   b[13] = 0;
   /* b[14]=32760;
    b[13]=32766;
    b[12]=32766;
    b[11]=32766;
    b[10]=32640;
    b[9]=32640;
    b[8]=32640;
    b[7]=32640;
    b[6]=32640;
    b[5]=32640;
    b[4]=32640;
    b[3]=32640;
    b[2]=32256;
    b[1]=31488;
    b[0]=32640;
    */

}

int main(){
    int type=1;
    init();
    int debug=0;// to give debug information and random input 

    //debug_fillBoard(board);
    while(type){
    	int fig;

    	cin>>type;
    	if(debug==0)
    	    cin>>fig;
        else{ 
        	fig = rand()%7+1;
        	cout<<fig<<" ";
        }
        
        int rot=-1, fixed=0;
        
        if(type==2){
        	char x;
        	cin>>x;
        	rot=x-(int)'a';//0 corrected rotation value
        }
        if(type==0)
            return 0;
        
        //move -> rotation 0,1,2... |  R  | C 
        tetrisMove Move = play(fig, rot);
        if(Move.over)
        	return 0;
        
        cleanRows(board);
        cout<<(char)(Move.O+(int)'a')<<" "<<15-Move.R<<" "<<Move.C+1<<endl;
        if(debug==0)
        	continue;
        	
      /* DEBUG CODE
        print(board);
        std::vector<int> hgh(15);
        double hg =height(board,hgh,0);
        cout<<"Hole "<<holes(board)<<" height= "<<hg<<" comple "<<completeLines(board)<<" bmps= "<<Bumps(hgh,1)<<endl; 
      */
    }
  
}
