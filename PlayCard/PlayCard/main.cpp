/*编程之美第二场第一题*/
#include <iostream>
#include <vector>
using namespace std;

int tcase,n;
std::vector<int> cards;
unsigned long long dp[60][60];  //60 为扑克牌种类的分类

int _hash(char a,char b)
{
    int type=0;
	switch(b){
	case 'S':
		type=0;
		break;
	case 'H':
		type=1;
		break;
	case 'D':
		type=2;
		break;
	case 'C':
		type=3;
		break;
	}

	int num=0;
	if(a>='2'&&a<='9')
		num=a-'2';  //每一类所在的下标
	if(a=='T')
		num=8;
	else if(a=='J')
		num=9;
	else if(a=='Q')
		num=10;
	else if(a=='K')
		num=11;
	else if(a=='A')
		num=12;
		
    return type*13+num;
}

unsigned long long getmod()
{
	unsigned long long result=1;
	for(int i=0;i<64;i++)
		result=result*2;
	
	return result;
}

int main(void)
{
	cin>>tcase;
	for(int t=0;t<tcase;t++){
		cin>>n;
		getchar();
		cards.clear();
		unsigned long long tmod=getmod();

		for(int i=0;i<n;i++){
			char c1,c2;
			c1=getchar();
			c2=getchar();

			int inx=_hash(c1,c2);
			cards.push_back(inx);
			getchar();
		}
		

		memset(dp,0,sizeof(dp));
		//初始化dp的值
		int size=cards.size();
		for(int i=0;i<size;i++)
			cout<<cards[i]<<" ";
		cout<<endl;

		for(int i=0;i<size;i++){
			dp[0][cards[i]]=1;   //对长度为1扑克牌进行初始化
		}

		//递推计算出dp的值
		for(int i=1;i<size;i++){  //i+1为长度
			//对每一种扑克牌进行计算
			for(int j=0;j<52;j++){
				for(int k=0;k<size;k++){
					if(cards[k]%13!=j%13)
						dp[i][cards[k]]=(dp[i][cards[k]]+dp[i-1][j])%tmod;
				}
			}
		}

		//将所有长度为size-1的结果相加
// 		unsigned long long result=0;
// 		for(int i=0;i<52;i++)
// 			result=(result+dp[size-1][i])%tmod;
// 
/*// 		cout<<"Case #"<<t+1<<": "<<result<<endl;*/

	}
	return 0;
}