int time = 0;
int x;
int a1=0;
int a2=1;
int a3=1;

int solve(int x){
	int i;
	int temp;
	if(x == 0) return a1;
	else if(x == 1) return a2;
	else{
		for(i=0;i<x-2;++i){
			temp = a3;
			a3 = a1+a2;
			a1 = a2;
			a2 = temp;
		}
		return a3;
	}
}

int main(){
	read(x);
	write(solve(x));
	return 0;
}