int a;
int b;
int c;
int d;
int main()
{
	a=getint();
	b=getint();
	c=getint();
	d=getint();
	int flag=0;
	if(b-a==c-b)
	{
		if(c-b==d-c)
		{
			flag=1;
		}
	}
	return flag;
}
