#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 100000
#define SEG (1<<18)
#define INF 1000000000000000LL

int N,Q;
long long x[MAXN], y[MAXN], t[MAXN];
int cx[MAXN],cy[MAXN];
int cid[MAXN];

long long qx[MAXN],qy[MAXN],qt[MAXN];
int qcx[MAXN],qcy[MAXN];
int qid[MAXN];

class SegTree
{
public:
	long long seg[2*SEG];
	int l[2*SEG],r[2*SEG];
	int low,high;

	void init()
	{
		for(int i=SEG;i<2*SEG;i++)
		{
			seg[i] = -INF;
			l[i] = r[i] = i-SEG;
		}
		for(int i=SEG-1;i>0;i--)
		{
			seg[i] = -INF;
			l[i] = l[2*i], r[i] = r[2*i+1];
		}
	}
	void update(int i,long long v)
	{
		i += SEG;
		for(;i>0;i/=2)
			seg[i] = max(seg[i],v);
	}
	long long getMax(int i)
	{
		if((l[i]>high)||(r[i]<low)) return -INF;
		if((l[i]>=low)&&(r[i]<=high)) return seg[i];
		return max(getMax(2*i),getMax(2*i+1));
	}
};

bool cmp(int a,int b)
{
	return x[a]<x[b];
}

bool qcmp(int a,int b)
{
	return qx[a]<qx[b];
}

long long ansLeft[MAXN];
long long ansRight[MAXN];

int main()
{
	freopen("slingshot.in", "r", stdin);
	freopen("slingshot.out", "w", stdout);
	cin >> N >> Q;
	vector<long long> vx,vy;
	for(int i=0;i<N;i++)
	{
		cin >> x[i] >> y[i] >> t[i];
		vx.push_back(x[i]);
		vy.push_back(y[i]);
		cid[i] = i;
	}
	sort(cid,cid+N,cmp);
	for(int i=0;i<Q;i++)
	{
		cin >> qx[i] >> qy[i];
		vx.push_back(qx[i]);
		vy.push_back(qy[i]);
		qid[i] = i;
	}
	sort(qid,qid+Q,qcmp);

	sort(vx.begin(),vx.end());
	sort(vy.begin(),vy.end());
	vx.resize(distance(vx.begin(),unique(vx.begin(),vx.end())));
	vy.resize(distance(vy.begin(),unique(vy.begin(),vy.end())));
	for(int i=0;i<N;i++)
	{
		cx[i] = lower_bound(vx.begin(),vx.end(),x[i]) - vx.begin();
		cy[i] = lower_bound(vy.begin(),vy.end(),y[i]) - vy.begin();
	}
	for(int i=0;i<Q;i++)
	{
		qcx[i] = lower_bound(vx.begin(),vx.end(),qx[i]) - vx.begin();
		qcy[i] = lower_bound(vy.begin(),vy.end(),qy[i]) - vy.begin();
	}

	SegTree up, down;
	up.init();
	down.init();
	int j = 0;
	for(int i=0;i<Q;i++)
	{
		int cur = qid[i];
		while(j < N && x[cid[j]] <= qx[cur])
		{
			down.update(cy[cid[j]], x[cid[j]]+y[cid[j]]-t[cid[j]]);
			up.update(cy[cid[j]], x[cid[j]]-y[cid[j]]-t[cid[j]]);
			j++;
		}
		down.low = 0, down.high = qcy[cur];
		up.low = qcy[cur], up.high = vy.size()-1;
		ansLeft[cur] = min(qx[cur] + qy[cur] - down.getMax(1), qx[cur] - qy[cur] - up.getMax(1));
	}
	up.init();
	down.init();
	j = N-1;
	for(int i=Q-1;i>=0;i--)
	{
		int cur = qid[i];
		while(j>=0 && x[cid[j]] >= qx[cur])
		{
			down.update(cy[cid[j]], -x[cid[j]]+y[cid[j]]-t[cid[j]]);
			up.update(cy[cid[j]], -x[cid[j]]-y[cid[j]]-t[cid[j]]);
			j--;
		}
		down.low = 0, down.high = qcy[cur];
		up.low = qcy[cur], up.high = vy.size()-1;
		ansRight[cur] = min(-qx[cur] + qy[cur] - down.getMax(1), -qx[cur] - qy[cur] - up.getMax(1));
	}
	for(int i=0;i<Q;i++)
		cout << min(min(ansLeft[i],ansRight[i]),(long long)abs(qx[i]-qy[i])) << '\n';
}
