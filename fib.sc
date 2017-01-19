

int foo(int y){
	if(y>1){
		return y * foo(y-1);
	}
	return 1;
}

int main(){
	int x;
	read(x);
	write(foo(x));
	return 0;
}