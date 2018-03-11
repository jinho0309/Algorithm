#include <iostream>

using namespace std;
int n;
bool areFriend[10][10];//친구관계 배열에 저장 (true, false) 
// (0,0) (0,1) (0,2) (0,3)
void init_areFriends(){
    for(size_t i = 0; i < 10; i++)
    {
        for(size_t j = 0; j < 10; j++)
        {
            areFriend[i][j] = false;
        }
    }
}



//명단에서 아직 짝을 못지은 사람을 짝짓자... 
int countPairings(bool taken[10]){
	int ret=0;
	int min = -1;//초기값 
	for(int i=0; i<n;i++){
		if(!taken[i]){
			min=i;
			break;
		}
	}
	if(min == -1) return 1; //min이 -1이라는 것은 taken이 모두 true라는 것, 즉 탐색끝 
	
	for(int j=min+1;j<n;j++){
		if(areFriend[min][j] && !taken[j]){ 
			//친구관계이고, 아직 탐색하지 않은 i와 min이라면...
			taken[j]=true;//탐색
			taken[min]=true;
			
			ret += countPairings(taken);
			//다음 숫자의 친구관계 찾기위해 재귀함수 호출
			//호출 시 taken이 flase인 제일 작은 값을 다시 찾으므로
			//나머지 숫자 중 제일 작은 값의 친구관계를 따지게 된다....
			//ex(0,1)->(2,3)->(4,5)
			 
			taken[j] = false;
			taken[min] = false;
			//재귀가 끝나면 현재 진행중인 숫자의 관계를 false로 하고
			//다음관계를 찾아봄
			//ex : (0,1)->(0,2)->(0,3)
		}
	}
	return ret;
	
	
}


int main(void){
	int C;
	int m;
	
	int a,b;
	int* result;
	bool taken[10]={false};
	
	cin>>C;
	result = new int[C];
	
	for(int i=0;i<C;i++){
		init_areFriends();
		cin>>n>>m;
		for(int j=0;j<m;j++){
			cin>>a>>b;
			areFriend[a][b]=true;
			areFriend[b][a]=true;
			//중복된 값을 피하기위해 (3,0)을 입력받아도 (0,3)을 검색하기위함
			//낮은 숫자부터 차례대로 검색해서 중복을 피하자! 
	}
		result[i]=countPairings(taken);
	}
	
	for(int i=0;i<C;i++){
		cout<<result[i]<<endl;
	}

	

	return 0;
}
