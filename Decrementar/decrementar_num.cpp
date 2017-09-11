#include<iostream>
using namespace std;
int decrementar(int a,int x=0){//donde x es el iterador
	if(x==a){return 0;}
	decrementar(a,x+1);//incrementa el iterador
	cout<<x<<endl;
	return 0;
}
int main(){
	int a;
	cin>>a;
	decrementar(a);
	return 0;
}
