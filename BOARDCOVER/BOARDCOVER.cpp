#include <iostream>
#include <vector>

using namespace std;
int c;
int h;
int w;
void printBoard(vector<vector<int> > &board){
	for(int i=0 ; i<h;i++){
		for(int j=0 ; j<w;j++){
			if(board[i][j]==1)
				cout<<'#';
			else
				cout<<'.';
			
		}
		cout<<endl;
	}
	cout<<endl<<endl;
}
/*bool set(vector<vector<int> > &board,int x,int y,int type, int d){
	bool flag=false;
	//cout<<"X : "<<x<<" Y : "<<y<<endl;
	
	switch(type){
		case 0 :
			if( board[y][x+1] == 0 && board[y+1][x] ==0){
			flag = true;
			board[y][x+1] = board[y+1][x] = 1;
			}
			if(d==-1)
			board[y][x+1] = board[y+1][x] = 0;
			break;
		case 1 :
			if( board[y][x+1] == 0 && board[y+1][x+1] ==0){
			flag = true;
			board[y][x+1] = board[y+1][x+1] = 1;
			}
			if(d==-1)
			board[y][x+1] = board[y+1][x+1] = 0;
			break;
		case 2 :
			if( board[y+1][x] == 0 && board[y+1][x+1] ==0){
			flag = true;
			board[y+1][x] = board[y+1][x+1] = 1;
			}
			if(d==-1)
			board[y+1][x] = board[y+1][x+1] = 0;
			break;
		case 3 :
			if( board[y+1][x] == 0 && board[y+1][x-1] ==0){
			flag = true;
			board[y+1][x] = board[y+1][x-1] = 1;
			}
			if(d==-1)
			board[y+1][x] = board[y+1][x-1] = 0;
			break;
			
		}
	

	
	
	if(flag)
		board[y][x]=1;
	if(d==-1)
		board[y][x]=0;
		
	return flag;
}
int cover(vector<vector<int> > &board){
	int x=-1,y=-1;
	int ret = 0;
	for(int i=0;i<h;i++){
		bool flag = false;
		for(int j=0;j<w;j++){
			if(board[i][j]==0){
				x=j;
				y=i;
				flag = true;
				break;
			}
		}
		if(flag)
			break;
	}
	
	//printBoard(board);
	if(y==-1) return 1;//다 채워졌으면 return 1 
	
	for(int i=0;i<4;i++){
	//cover함수의 type값을 넘겨주면서 4가지 경우 다해봄.... 
	//채워지는거 있으면 채우고 cover함수 재귀
	//재귀가 return 되면서 덮었던 블록 치우며 다음 type탐색
	 
	 
		if(set(board,x,y,i,1)){
			ret += cover(board);
			set(board,x,y,i,-1);
		}
		
	}

	
	return ret;
	
}*/
//주어진 칸을 덮을 수 있는 네 가지 방법
//블록을 구성하는 세 칸의 상대적 위치(dy,dx) *dy가 앞임!! 
const int coverType[4][3][2] ={
{{0,0},{1,0},{0,1}},
{{0,0},{0,1},{1,1}},
{{0,0},{1,0},{1,1}},
{{0,0},{1,0},{1,-1}}
};

//board의 (y,x)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다.
// delta= 1이면 덮고, -1이면 덮었던 블록 제거.
// 블록이 제대로 덮이지 않은 경우(게임판 밖으로 나가거나, 겹치거나, 검은 칸을 덮을 때)flase 반환
bool set(vector<vector<int> > &board, int y, int x, int type, int delta){
	bool ok = true;
	for(int i=0;i<3;i++){
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if(ny < 0 || ny >=board.size() || nx< 0 || nx>=board[0].size())
			ok=false;
		else if((board[ny][nx]+=delta) > 1)
			ok=false; 
			//2가 됫다는건 이미 1인 곳에 겹쳐졌다는거...
			//2가 되도록 놔두는 이유는 delta가 -1일때 블록을 들면2-1=1이 되므로
			// 따로 방금 덮었던 블록을 구분할 필요가 없음. 
	}
	return ok; 
}
//board의 모든 빈 칸을 덮을 수 있는 방법의 수 반환
//board[i][j] = 1 이미 덮인 칸 혹은 검은 칸
//board[i][j] = 0 아직 덮이지 않은 칸
int cover(vector<vector<int> >& board){
	//아직 채우지 못한 칸 중 가장 윗줄 왼쪽 찾기
	int y = -1, x= -1;
	for(int i=0;i<board.size();i++){
		for(int j=0;j<board[i].size();j++){
			if(board[i][j]==0){
				y = i;
				x = j;
				break;
			}
		}
		if(y!=-1)
			break;
	}
	
	
	//기저 사례 : 모든 칸을 채웠으면 1 반환 
	if(y == -1) return 1; 
	int ret = 0;
	for(int type=0 ; type<4;type++){
		//board[y][x]를 type형태로 덮을 수 있으면 재귀 호출하여 다음 블록 덮기
		if(set(board,y,x,type,1))
			ret += cover(board);
		//덮었던 블록 치우기.
		set(board,y,x,type,-1); 
	}
	return ret;
} 
int main(void){

	char temp;
	vector<vector<int> > input;
	cin>>c;
	for(int i=0;i <c;i++){
		input.clear();
		cin>>h>>w;
		
		for(int j=0;j<h;j++){
			vector<int> vec;
			for(int k=0;k<w;k++){
				cin>>temp;
				if(temp == '#')
					vec.push_back(1);
				else
					vec.push_back(0);
			}
			input.push_back(vec);
			
		}
		cout<<cover(input);
		
	}
}
