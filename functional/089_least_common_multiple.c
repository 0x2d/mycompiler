int main()
{
    int m, n, temp, i;
    m=getint();
    n=getint();
    if(m<n)  
    {
        temp = m;
        m = n;
        n = temp;
    }
    i=m;
    while(i>0)
	{
        if(i%m==0 && i%n==0)
        {
            putint(i);
            break;
        }
		i=i+1;
	}
    return 0;
}
