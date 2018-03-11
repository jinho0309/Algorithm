#include <iostream>

using namespace std;
int n;
bool areFriend[10][10];//ģ������ �迭�� ���� (true, false) 
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



//��ܿ��� ���� ¦�� ������ ����� ¦����... 
int countPairings(bool taken[10]){
	int ret=0;
	int min = -1;//�ʱⰪ 
	for(int i=0; i<n;i++){
		if(!taken[i]){
			min=i;
			break;
		}
	}
	if(min == -1) return 1; //min�� -1�̶�� ���� taken�� ��� true��� ��, �� Ž���� 
	
	for(int j=min+1;j<n;j++){
		if(areFriend[min][j] && !taken[j]){ 
			//ģ�������̰�, ���� Ž������ ���� i�� min�̶��...
			taken[j]=true;//Ž��
			taken[min]=true;
			
			ret += countPairings(taken);
			//���� ������ ģ������ ã������ ����Լ� ȣ��
			//ȣ�� �� taken�� flase�� ���� ���� ���� �ٽ� ã���Ƿ�
			//������ ���� �� ���� ���� ���� ģ�����踦 ������ �ȴ�....
			//ex(0,1)->(2,3)->(4,5)
			 
			taken[j] = false;
			taken[min] = false;
			//��Ͱ� ������ ���� �������� ������ ���踦 false�� �ϰ�
			//�������踦 ã�ƺ�
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
			//�ߺ��� ���� ���ϱ����� (3,0)�� �Է¹޾Ƶ� (0,3)�� �˻��ϱ�����
			//���� ���ں��� ���ʴ�� �˻��ؼ� �ߺ��� ������! 
	}
		result[i]=countPairings(taken);
	}
	
	for(int i=0;i<C;i++){
		cout<<result[i]<<endl;
	}

	

	return 0;
}
