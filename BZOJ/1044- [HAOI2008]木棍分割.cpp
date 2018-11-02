#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<deque>
#define mod 10007
#define inf 2000000000
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,ans1,ans2;
int a[50005],sum[50005];
int f[2][50005],q[50005];
bool jud(int x)
{
    int tmp=0,sum=0;
    for(int i=1;i<=n;i++)
    {
        sum+=a[i];
        if(sum>x){tmp++;sum=a[i];}
        if(tmp>m)return 0;
        if(a[i]>x)return 0;
    }
    return 1;
}
void solve1()
{
	int l=1,r=sum[n];
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(jud(mid)){ans1=mid;r=mid-1;}
		else l=mid+1;
	}
}
void solve2()
{
    f[0][0]=1;
	int pre,cur,tot;
	for(int i=1;i<=m;i++)
	{
		pre=i&1;cur=pre^1;
		int l=1,r=1;
		q[1]=0;tot=f[cur][0];
		for(int j=1;j<=n;j++)
		{
			while(l<=r&&sum[j]-sum[q[l]]>ans1)
				tot=(tot-f[cur][q[l++]]+mod)%mod;
			f[pre][j]=tot;q[++r]=j;
			tot=(tot+f[cur][j]+mod)%mod;
		}
		for(int j=n-1;j;j--)
		{
			if(sum[n]-sum[j]>ans1)break;
			ans2=(ans2+f[pre][j]+mod)%mod;
		}
		memset(f[cur],0,sizeof(f[cur]));
	}
	printf("%d\n",ans2);
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	solve1();
	printf("%d ",ans1);
	solve2();
	return 0;
}