#include<iostream>
using namespace std;
int forn(int a,int x=0){
	if(x==a) return 0;//caso base
	cout<<x<<" ";
	forn(a,x+1);//parte recursiva
}
int main(){
	int a;
	cin>>a;
	forn(a);
	cout<<endl;
	return 0;
}
