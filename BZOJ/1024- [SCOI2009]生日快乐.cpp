#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

double f(double x,double y,int k){
	if (k==1) return max(x,y)/min(x,y);
	double ans=233333.33;
	for (int i=1;i<k;i++)
		ans=min(ans,max(f(x,y*i/k,i),f(x,y*(k-i)/k,k-i)));
	for (int i=1;i<k;i++)
		ans=min(ans,max(f(x*i/k,y,i),f(x*(k-i)/k,y,k-i)));
	return ans;
}

int main(){
	int x,y,k;
	cin>>x>>y>>k;
	printf("%.6lf",f(x,y,k));
}