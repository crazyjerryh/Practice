#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

typedef struct _trie
{
	struct _trie *next[26];
	struct _trie *fail;
	int cnt;

	_trie():cnt(0),fail(0){
		for(int i=0;i<26;i++){
			next[i]=0;
		}
	}
}trie,node;

int tcase;
int n;
char temp[50];
char str[1000003];
trie root;

void insert()
{
    trie *cur=&root;
	int len=strlen(temp);

	for(int i=0;i<len;i++){
		int index=temp[i]-'a';
		if(!cur->next[index])
			  cur->next[index]=new node;
		cur=cur->next[index];
	}
	cur->cnt++;
}

void build_ac()
{
    std::queue<trie *>Q;
	root.fail=0;
	for(int i=0;i<26;i++)
	   if(root.next[i])
	   {
		   root.next[i]->fail=&root;
		   Q.push(root.next[i]);
	   }

	while(!Q.empty())
	{
		trie *front=Q.front();
		Q.pop();

		for(int i=0;i<26;i++){
			if(front->next[i]){
				trie *p=front->fail;
				while(p){
					if(p->next[i])
					{
						front->next[i]->fail=p->next[i];
						break;
					}
					p=p->fail;
				}

				if(!p) front->next[i]->fail=&root;
				Q.push(front->next[i]);
			}
		}
	}
}

int query()
{
	trie *cur=&root;
	int len=strlen(str);
	int cnt=0;
	for(int i=0;i<len;i++){
		int index=str[i]-'a';
		while(cur->next[index]==0&&cur!=&root)
			cur=cur->fail;
		
		if(cur->next[index]!=0)
			 cur=cur->next[index];
		else
			cur=&root;

		trie *p=cur;
		while(p!=&root&&p->cnt!=-1){
			cnt+=p->cnt;
			p->cnt=-1;
			p=p->fail;
		}
	}

	return cnt;
}

int main(void)
{
	cin>>tcase;
	while(tcase--){
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>temp;
			insert();
		}

		build_ac();
		cin>>str;
		cout<<query()<<endl;
	}
	return 0;
}