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
	if(y==-1) return 1;//�� ä�������� return 1 
	
	for(int i=0;i<4;i++){
	//cover�Լ��� type���� �Ѱ��ָ鼭 4���� ��� ���غ�.... 
	//ä�����°� ������ ä��� cover�Լ� ���
	//��Ͱ� return �Ǹ鼭 ������ ��� ġ��� ���� typeŽ��
	 
	 
		if(set(board,x,y,i,1)){
			ret += cover(board);
			set(board,x,y,i,-1);
		}
		
	}

	
	return ret;
	
}*/
//�־��� ĭ�� ���� �� �ִ� �� ���� ���
//����� �����ϴ� �� ĭ�� ����� ��ġ(dy,dx) *dy�� ����!! 
const int coverType[4][3][2] ={
{{0,0},{1,0},{0,1}},
{{0,0},{0,1},{1,1}},
{{0,0},{1,0},{1,1}},
{{0,0},{1,0},{1,-1}}
};

//board�� (y,x)�� type�� ������� ���ų�, ������ ����� ���ش�.
// delta= 1�̸� ����, -1�̸� ������ ��� ����.
// ����� ����� ������ ���� ���(������ ������ �����ų�, ��ġ�ų�, ���� ĭ�� ���� ��)flase ��ȯ
bool set(vector<vector<int> > &board, int y, int x, int type, int delta){
	bool ok = true;
	for(int i=0;i<3;i++){
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if(ny < 0 || ny >=board.size() || nx< 0 || nx>=board[0].size())
			ok=false;
		else if((board[ny][nx]+=delta) > 1)
			ok=false; 
			//2�� �̴ٴ°� �̹� 1�� ���� �������ٴ°�...
			//2�� �ǵ��� ���δ� ������ delta�� -1�϶� ����� ���2-1=1�� �ǹǷ�
			// ���� ��� ������ ����� ������ �ʿ䰡 ����. 
	}
	return ok; 
}
//board�� ��� �� ĭ�� ���� �� �ִ� ����� �� ��ȯ
//board[i][j] = 1 �̹� ���� ĭ Ȥ�� ���� ĭ
//board[i][j] = 0 ���� ������ ���� ĭ
int cover(vector<vector<int> >& board){
	//���� ä���� ���� ĭ �� ���� ���� ���� ã��
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
	
	
	//���� ��� : ��� ĭ�� ä������ 1 ��ȯ 
	if(y == -1) return 1; 
	int ret = 0;
	for(int type=0 ; type<4;type++){
		//board[y][x]�� type���·� ���� �� ������ ��� ȣ���Ͽ� ���� ��� ����
		if(set(board,y,x,type,1))
			ret += cover(board);
		//������ ��� ġ���.
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
