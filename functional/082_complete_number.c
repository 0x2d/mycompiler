int main()
{
    int i, j, s, n;  
    n = getint();
    i=2;
    while(i<=n)
    {
        s=0;  
        j=1;
        while(j<i)
        {
            if(i%j == 0)  
            {
            	s=s+j;
			}
                
            j=j+1;
        }
        if(s == i)  
        {
        	putint(i);
        	putch(10);
		}
            
        i=i+1;
    }
    return 0;
}
