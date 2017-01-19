

int foo(int y, int x){
	return x+y;
}

int main(){
	int x;
	int i = 1;
	int j =2;
	int ans[2] = {1,2};
	read(x);
	write(foo(ans[i-1], ans[j-1]));
	return 0;
}