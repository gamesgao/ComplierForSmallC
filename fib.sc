int x = 5;
int main(){
	for(;x>1;--x){
		if(x % 2 == 0) break;
		write(x);
	}
	return 0;
}