int main()
{
    int i,j,k;
    i=1;
    while(i<5)
    {
    	j=1;
        while(j<5)
    	{
    		k=1;
    		while(k<5)
    		{
                if (i!=k&&i!=j&&j!=k) {
                    int tmp=100*i+10*j+k;
                    putint(tmp);
                    putch(10);
                }
                k=k+1;
            }
            j=j+1;
        }
        i=i+1;
    }
    return 0;
}
