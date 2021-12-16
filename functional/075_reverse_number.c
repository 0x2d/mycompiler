int main()
{
	int x,digit,rev;
	rev=0;
	x=12345;
	while(x>0)
	{
	   digit=x%10;  
	   putint(digit);
	   x=x/10;	
	} 
	return 0;
}
