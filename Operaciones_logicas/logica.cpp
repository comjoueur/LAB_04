#include<iostream>
using namespace std;
char ANDN(char a,char p){//operacion AND entre caracteres
	if((a=='1') and (p=='1')) a='1';
	else a='0';
	return a;
}
char ORN(char a,char p){//operacion OR entre caracteres
        if((a=='1') or (p=='1')) a='1';
        else a='0';
	return a;
}
char XORN(char a,char p){//operacion XOR entre caracteres
        if(a!=p) a='1';
        else a='0';
	return a;
}
char NOTN(char a){//operacion NOT entre caracteres
	if(a=='1') a='0';
        else a='1';
	return a;
}
string reemplazar(string a,string b){//reemplaza a la primera palabra con los Valores de la segunda 
	int k=0;
	for(int i=0;i<a.size();i++) if((a[i]>='A' and a[i]<='Z') or (a[i]>='a' and a[i]<='z')) a[i]=b[k++];
	return a;
}
char resolver(string p){//resuelve una expresion
	if(p.size()==1)return p[0];//si solo hay un caracter es porque es un valor
	for(int i=0;i<p.size();i++){
		//hallamos operaciones entre parentesis para reducir el problema y resolver el subproblema
		if(p[i]=='('){
			bool e=false;
			int f;
			for(int j=i+1;j<p.size();j++){
				if(p[j]=='(') break;
				else if(p[j]==')'){e=true;f=j;break;}
			}
			if(e){
				string h="";
				for(int j=0;j<i;j++)h+=p[j];
				string d="";
				for(int j=i+1;j<f;j++){d+=p[j];}
				char r=resolver(d);//subproblema
				h+=r;
				for(int j=f+1;j<p.size();j++)h+=p[j];
				return resolver(h);//reducido
			}
		}
	}
	for(int i=0;i<p.size();i++){
		//las negaciones son las primeras que se deben resolver
		if(p[i]=='~' and (p[i+1]=='0' or p[i+1]=='1')){
			string h;
			for(int j=0;j<i;j++)h+=p[j];
			h+=NOTN(p[i+1]);
			for(int j=i+2;j<p.size();j++)h+=p[j];
			return resolver(h);//reducido
		}
	}
	for(int i=0;i<p.size();i++){
		//las conjunciones son las segunas que se deben resolver
		if(p[i]=='&'){
			string h="";
			for(int j=0;j<i-1;j++) h+=p[j];
			h+=ANDN(p[i-1],p[i+1]);
			for(int j=i+2;j<p.size();j++) h+=p[j];
			return resolver(h);//reducido
		}
	}
	for(int i=0;i<p.size();i++){
		//la disyunciones son las terceras que se deben resolver
		if(p[i]=='|'){
			string h="";
			for(int j=0;j<i-1;j++) h+=p[j];
			h+=ORN(p[i-1],p[i+1]);
			for(int j=i+2;j<p.size();j++) h+=p[j];
			return resolver(h);//reducido
		}
	}
	for(int i=0;i<p.size();i++){
		//las disyunciones fuertes son las  cuartas que se deben resolver
		if(p[i]=='+'){
			string h="";
			for(int j=0;j<i-1;j++) h+=p[j];
			h+=XORN(p[i-1],p[i+1]);
			for(int j=i+2;j<p.size();j++) h+=p[j];
			return resolver(h);//reducido
		}
	}
}
int operador(char a){//reconoce el tipo de caracter
	if(a=='~') return 1;//si es negacion
	if(a=='&' or a=='+' or a=='|') return 2;//si necesita dos variables
	return 0;
}
bool correcto(string p){//revisa si la expresion es correcta
	for(int i=0;i<p.size();i++){
		if(p[i]!='~' and p[i]!='(' and p[i]!=')' and p[i]!='+' and p[i]!='&' and p[i]!='|' and (p[i]<'a' or p[i]>'z') and (p[i]<'A' or p[i]>'Z')){//que este dentro de los caracteres permitidos
			return false;
		}
	}
	//revision de los parentesis
	int y=p.size();
	bool pila[y];
	for(int i=0;i<y;i++)pila[i]=false;
	int prendidos=0;
	for(int i=0;i<p.size();i++){
		if(p[i]=='(')pila[prendidos++]=true;
		else if(p[i]==')'){
			if(prendidos==0){return false;}
			pila[--prendidos]=false;}
	}
	if(prendidos!=0){return false;}//si no sobro algun parentesis
	for(int i=0;i<p.size()-1;i++) if(p[i]=='(' and p[i+1]==')') return false;//si no hay parentesis vacios
	if(operador(p[0])==2  or operador(p[p.size()-1])!=0){return false;}//especificaciones
	for(int i=1;i<p.size()-1;i++){
		if(operador(p[i])==2){
			if(operador(p[i-1])==2){return false;}
			if(operador(p[i+1])==2){return false;}
			//no pueden haber dos operaciones binarias juntas
		}
	}
	for(int i=0;i<p.size();i++){
		if(operador(p[i])==1){
			if(i!=p.size()-1 and operador(p[i+1])==2){return false;}
			if(i!=0 and operador(p[i-1])==0){
				if(p[i-1]!='('){return false;}
			}
			//especificaciones de la negacion
		}

	}
	for(int i=0;i<p.size();i++){
		if(operador(p[i])==0){
			if(i!=p.size()-1 and operador(p[i+1])==0){
				if((p[i]>='a' and p[i]<='z') or (p[i]>='A' and p[i]<='Z')){
					if((p[i+1]=='(') or ((p[i+1]>='a' and p[i+1]<='z') or (p[i+1]>='A' and p[i+1]<='Z'))){return false;}
				}
				else{
					if(p[i]=='('){
						if(operador(p[i+1])==2){return false;}
					}
					if(p[i]==')'){
						if((p[i+1]>='a' and p[i+1]<='z') or (p[i+1]>='A' and p[i+1]<='Z') or operador(p[i+1])==1){return false;}
					}
				}
			}
			if(i!=0 and operador(p[i-1])==0){
				if((p[i]>='a' and p[i]<='z') or (p[i]>='A' and p[i]<='Z')){
					if((p[i-1]==')') or ((p[i-1]>='a' and p[i-1]<='z') or (p[i-1]>='A' and p[i-1]<='Z'))){return false;}
				}
				else{
					if(p[i]=='('){
						if((p[i-1]>='a' and p[i-1]<='z') or (p[i-1]>='A' and p[i-1]<='Z')){return false;}
					}
					if(p[i]==')'){
						if(operador(p[i-1])==2 or operador(p[i-1])==1){return false;}
					}
				}
			}
		}//especificaciones de letras y parentesis
	}
	return true;
}

int potencia(int a,int b){//Calcula la potencia de un entero
    int k=1;
    for(int i=0;i<b;i++){k*=a;}
    return k;
}
string limpiar(string p){//limpia la palabra para la impresion
	for(int i=0;i<p.size();i++)if(p[i]!='0' and p[i]!='1')p[i]=' ';
	return p;
}
int main(){
    string x;
    cout<<"conjuncion: &     disyuncion: |     negacion:~     disyuncion fuerte:+"<<endl;
    cout<<endl;
    cin>>x;
    //COMIENZO DE VALIDACION DE LA EXPRESION
    if(not correcto(x)){//para saber si la expresion es correcta
    	cout<<"La expresion introducida no es valida"<<endl;
	return 0;
    }
    //FIN DE VALIDACION DE LA EXPRESION
    //COMIENZO DE ALGORITMO PARA HALLAR COMBINACIONES
    int n=0;//numero de variables
    for(int i=0;i<x.size();i++){
            if((x[i]>='A' and x[i]<='Z') or (x[i]>='a' and x[i]<='z')){n++;}//rellenamos el numero de variables
    }
    int g=potencia(2,n);//numero de combinaciones
    string arr[g];//un string por cada combinacion
    for(int i=0;i<g;i++){arr[i]="";}//inicializamos los string
    for(int i=0;i<n;i++){arr[0]+='0';}//llenamos la primera combinacion
    for(int i=1;i<g;i++){//crecimiento de la combinacion en binario
        arr[i]=arr[i-1];
        int u=n-1;
        while(arr[i][u]=='1'){arr[i][u]='0';u--;}
        arr[i][u]+=1;
    }
    for(int i=0;i<g;i++) arr[i]=reemplazar(x,arr[i]);//completamos las combinaciones con las operaciones
    //FIN DE ALGORITMO PARA HALLAR COMBINACIONEs
    //COMIENZO DE ALGORITMO PARA HALLAR RESPUESTAS
    char rsp[g];//aqui ira la respuesta de cada combinacion
    for(int i=0;i<g;i++)rsp[i]=resolver(arr[i]);//se halla cada respuesta
    //FIN DE ALGORITMO PARA HALLAR RESPUESTA
    //COMIENZO DE IMPRESION
    for(int i=0;i<g;i++)arr[i]=limpiar(arr[i]);//se limpia la primera combinacion,preparandola para la impresion
    cout<<endl<<endl;
    cout<<x<<" |"<<endl;
    for(int i=0;i<g;i++)cout<<arr[i]<<" |"<<rsp[i]<<endl;
    //FIN DE IMPRESION
}
