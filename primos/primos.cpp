#include<iostream>
using namespace std;
bool testprime(int a,int x=2){
	if(a<=1) return false;
	if(x==a) return true;
	if(a%x==0) return false;
	return testprime(a,++x);
}
int main(){
	int a;
	cin>>a;
	if(testprime(a)) cout<<"es primo"<<endl;
	else cout<<"no es primo"<<endl;
	return 0;
}
