

int foo(int y, int x){
	return x+y;
}

int main(){
	struct ddd{
		int a;
		int b;
	};
	struct ddd c;
	c.a=1;
	c.b=20;
	
	write(foo(c.a, c.b));
	return 0;
}