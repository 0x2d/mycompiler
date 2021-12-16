//get 1*2*3*4*5
int factorial(int n)
{
	if(n <= 1)
		return 1;
	else 
		return n * factorial(n-1);
}

int main(){
    return factorial(5);
}