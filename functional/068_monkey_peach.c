int func(int n)
{
	if (n >= 10)
	{
		return 1;
	}
	else
	{
		return (func(n + 1) + 1) * 2;
	}
}
 
int main()
{
	int i;
	int cnt;
	i=1;
	cnt=0;
	
	cnt=func(i);
	
	return cnt;
}

