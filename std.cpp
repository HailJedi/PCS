#include<bits/stdc++.h>
 
using namespace std;
 
int n,m,K,cnt;
 
char ch[20];
 
int trie[110][26],q[110],fail[110];
 
bool End[110],vis[110];
 
struct Matrix
{
	long double a[110][110];
	Matrix() { memset(a,0,sizeof(a)); }
	void init() { for(int i=0;i<=cnt;i++) a[i][i]=1; }
	Matrix operator * (const Matrix b) const
	{
		Matrix tmp;
		for(int i=0;i<=cnt;i++)
			for(int j=0;j<=cnt;j++)
				for(int k=0;k<=cnt;k++)
					tmp.a[i][j]+=a[i][k]*b.a[k][j];
		return tmp;
	}
}Mat,ans;
 
inline void insert()
{
	scanf("%s",ch+1);
	int now=0,len=strlen(ch+1);
	for(int i=1;i<=len;i++)
	{
		if(!trie[now][ch[i]-'a']) trie[now][ch[i]-'a']=++cnt;
		now=trie[now][ch[i]-'a'];
	}
	End[now]=1;
}
 
inline void buildfail()
{
	int head=0,tail=0;
	for(int i=0;i<K;i++) if(trie[0][i]) q[++tail]=trie[0][i];
	while(head<tail)
	{
		int now=q[++head];
		for(int i=0;i<K;i++)
		{
			if(!trie[now][i]) trie[now][i]=trie[fail[now]][i];
			else fail[trie[now][i]]=trie[fail[now]][i],q[++tail]=trie[now][i];
		}
	}
	cnt++;
}
 
inline void buildmatrix()
{
	int head=0,tail=0;
	long double G=(long double)1/K;
	q[++tail]=0;vis[0]=1;
	while(head<tail)
	{
		int now=q[++head];
		for(int i=0;i<K;i++)
		{
			if(!vis[trie[now][i]]) vis[trie[now][i]]=1,q[++tail]=trie[now][i];
			if(End[trie[now][i]]) Mat.a[now][cnt]+=G,Mat.a[now][0]+=G;
			else Mat.a[now][trie[now][i]]+=G;
		}
	}
	Mat.a[cnt][cnt]=1;
}
 
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;i++) insert();
	buildfail();
	buildmatrix();
	ans.init();
	while(m)
	{
		if(m&1) ans=ans*Mat;
		Mat=Mat*Mat; m>>=1;
	}
	printf("%.7Lf\n",ans.a[0][cnt]);
}
