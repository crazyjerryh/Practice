#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>

#define maxm 26
#define maxn 1000003
using namespace std;

typedef struct trr{
	struct trr *next[maxm];
	int cnt;
	struct trr * _fail;
	trr(){
	   cnt=0,_fail=0;
	   for(int i=0;i<maxm;i++)
		   next[i]=0;
	}
}trie;

trie root;
int n;
char str[maxn],temp[maxn];

void insert()
{
	trie *cur=&root;
	int len=strlen(temp);

	int i=0;
	while(len--){
	    int index=temp[i++]-'a';
		if(!cur->next[index])
			cur->next[index]=new trie;
		cur=cur->next[index];
	}
	
	cur->cnt++;
}

void build_ac()
{
	std::queue<trie *> Q;
	root._fail=0;
	for(int i=0;i<maxm;i++){
		if(root.next[i]!=0)
		{
			root.next[i]->_fail=&root;
			Q.push(root.next[i]);   
		}
	}

	while(!Q.empty()){
		trie *front=Q.front();
	    Q.pop();  
		
		for(int i=0;i<maxm;i++){
			if(front->next[i]!=0){
				trie *p=front->_fail; 
				while(p!=0){
					if(p->next[i]!=0){
						front->next[i]->_fail=p->next[i];
						break;
					}
					p=p->_fail;
				}
				if(p==0)  front->next[i]->_fail=&root;
				Q.push(front->next[i]);
			}
		}
	}
}

bool query()
{
	int len=strlen(str);
	trie *cur=&root;
	for(int i=0;i<len;i++){
	    int index=str[i]-'a';
		while(cur->next[index]==0&&cur!=&root)
			cur=cur->_fail;
		
		if(cur->next[index]==0) cur=&root;
		else
			cur=cur->next[index];

		//cout<<str[i]<<cur->cnt;
		if(cur!=(&root)&&cur->cnt>0)
			 return true;
	}

	return false;
}

int main(void)
{
    scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",&temp);
		insert();
	}

	build_ac();
	scanf("%s",&str);
	if(query())
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}