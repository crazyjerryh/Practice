#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;

#define maxn 1000010
int tcase,n;
struct _node{
	struct _node *next[26];
	struct _node *fail;
	int end;
	_node(){
		for(int i=0;i<26;i++){
			next[i]=0;
		}
		fail=0;
		end=0;
	}
}*pRoot;
typedef struct _node node;
char src[maxn];

void insert(char tmp[])
{
	int len=strlen(tmp);
	node *cur=pRoot;
	for(int i=0;i<len;i++){
		int inx=tmp[i]-'a';
		if(!cur->next[inx])  cur->next[inx]=new node;
		cur=cur->next[inx];
	}
	cur->end++;
}

void build(){
	 queue<node *> Q;
	 pRoot->fail=pRoot;
	 for(int i=0;i<26;i++){
		  if(pRoot->next[i]){
			   pRoot->next[i]->fail=pRoot;
			   Q.push(pRoot->next[i]);
		  }
		  else
			  pRoot->next[i]=pRoot;
	 }
	 
	 while(!Q.empty()){
		node *front=Q.front();
		Q.pop();
		for(int i=0;i<26;i++){
			if(front->next[i]){
				front->next[i]->fail=front->fail->next[i];
				Q.push(front->next[i]);
			}
			else
				front->next[i]=front->fail->next[i];
		}
	 }
}

int query(){
	int len=strlen(src);
	node *cur=pRoot;
	int ans=0;
	for(int i=0;i<len;i++){
		int inx=src[i]-'a';
		cur=cur->next[inx];
		node *tmp=cur;
		while(tmp!=pRoot){
			 ans+=tmp->end;
			 tmp->end=0;
			 tmp=tmp->fail;
		}
	}
	return ans;
}


int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		node root;
		pRoot=&root;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			char tmp[60];
			scanf("%s",tmp);
			insert(tmp);
		}
		build();
		scanf("%s",src);
		int ans=query();
		printf("%d\n",ans);
	}
	return 0;
}
