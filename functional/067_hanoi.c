int cnt;
void action(int num,int p,int q)
{
	
	putint(num);
	putch(58);
	putint(p);
	putch(45);
	putch(62);
	putint(q);
	putch(10);
	
	cnt=cnt+1;
}

void hanoi(int num,int p, int q,int r)
{
	if(num==1) action(num,p,r);
	else 
	{
		hanoi(num-1,p,r,q);
		action(num,p,r);
		hanoi(num-1,q,p,r);
	}
}
int main()
{
	int num,a,b,c;
	cnt=0; 
	num=3;
	a=1;
	b=2;
	c=3;
	hanoi(num,a,b,c);
	return cnt;
	 
}
