int main()
{
    int a,n;
    int sn=0,tn=0,count=1;
	a=4;
	n=4;

    while(count <= n)
    {   
        tn = tn + a;
        sn = sn + tn; 
        a = a * 10; 
        count=count+1;
    }   
    return sn;
    
      
}
