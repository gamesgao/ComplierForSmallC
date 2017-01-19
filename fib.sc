

int foo(int y, int x){
	if(y>1){
		return y * foo(y-1 , 2);
	}
	return 1;
}

int main(){
	int x;
	read(x);
	write(foo(x, 2));
	return 0;
}