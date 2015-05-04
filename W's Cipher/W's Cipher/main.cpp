//poj 1107
#include <iostream>
#include <string.h>
using namespace std;
#define maxn 90

int k1,k2,k3;
char str[maxn];
char str1[maxn],str2[maxn],str3[maxn];
char str11[maxn],str22[maxn],str33[maxn];
int pos1[maxn],pos2[maxn],pos3[maxn];  //对应每个节点的位置
int main(int argc,char **argv)
{
	while(cin>>k1>>k2>>k3)
	{
		if(k1==0&&k2==0&&k3==0) break;
	    cin>>str;

		int len=strlen(str);
		int len1,len2,len3;
		len1=len2=len3=0;
		for(int i=0;i<len;i++){
			//str1 for group 1,str2 for group 2 ,str3 for group 3
			if(str[i]>='a'&&str[i]<='i')
				str1[len1]=str[i],pos1[len1++]=i;
			else if(str[i]>='j'&&str[i]<='r')
				str2[len2]=str[i],pos2[len2++]=i;
			else
				str3[len3]=str[i],pos3[len3++]=i;
		}

		//对每一个组进行右移操作
		for(int i=0;i<len1;i++){
			str11[i]=str1[i];
		}

		for(int i=0;i<len1;i++)
			str11[(i+k1)%len1]=str1[i];

		//for group 2
		for(int i=0;i<len2;i++)
			str22[i]=str2[i];

		for(int i=0;i<len2;i++)
			str22[(i+k2)%len2]=str2[i];

		//for group 3
		for(int i=0;i<len3;i++)
			str33[i]=str3[i];

		for(int i=0;i<len3;i++)
			str33[(i+k3)%len3]=str3[i]; 



		int inx1,inx2,inx3;
		inx1=0,inx2=0,inx3=0;

		for(int i=0;i<len;i++){
			if(inx1<len1&&pos1[inx1]==i)
				cout<<str11[inx1++];
			else if(inx2<len2&&pos2[inx2]==i)
				cout<<str22[inx2++];
			else if(inx3<len3&&pos3[inx3]==i)
				cout<<str33[inx3++];
		}
		cout<<endl;
	}
	return 0;
}