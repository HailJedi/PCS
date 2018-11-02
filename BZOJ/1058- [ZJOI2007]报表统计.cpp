#include<bits/stdc++.h>
#define inf 1000000000
using namespace std;
int n,m;
int st[500005],ed[500005];
multiset<int> a,b;
map<int,int> mp;
int q = inf;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void insert(int x)
{
    mp[x]++;
    if(mp[x]==1)a.insert(x);
}

multiset<int>::iterator it;
void push(int x)
{
	it = b.lower_bound(x);
	int r = *it, l = *--it;
    q = min(q, min(x-l,r-x));
    b.insert(x);
}
int main()
{
    n=read();m=read();
    b.insert(inf);b.insert(-inf);
    for(int i=1;i<=n;i++)
    {
        int x=read();
        ed[i]=st[i]=x;
        push(x);
    }
    for(int i=2;i<=n;i++)insert(abs(st[i]-st[i-1]));
    char ch[12];int p,x,t;
    for(int i=1;i<=m;i++)
    {
        scanf("%s",ch);
        if(ch[0]=='I')
        {
            p=read();x=read();
            if(p!=n)
			{
				t=abs(ed[p]-st[p+1]);
				mp[t]--;
				if(!mp[t])a.erase(t);
			}
            insert(abs(ed[p]-x));
            insert(abs(x-st[p+1]));
            ed[p]=x;push(x);
        }
        else if(ch[4]=='S')printf("%d\n",q);
        else printf("%d\n",*a.begin());
    }
    return 0;
}