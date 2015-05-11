/*hihocoder 第四十四周问题*/
#include <iostream>
using namespace std;

int n;
int main(void)
{
	cin>>n;
	int result=0;
	for(int i=0;i<n;i++){
		int temp;
		cin>>temp;
		result=result^temp;
	}
	if(result)
		cout<<"Alice"<<endl;
	else
		cout<<"Bob"<<endl;
	return 0;
}