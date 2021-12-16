int main()
{
    int i,j,k;
    i=1;
    while(i<=9)
    {
    	j=1;
        while(j<=i)
    	{
    		int tmp=i*j;
    		putint(i);
    		putch(42);
    		putint(j);
			putch(61);
			putint(tmp);
			putch(10);
            j=j+1;
        }
        i=i+1;
    }
    return 0;
}
