int main()
{
	int a[4][2]={1,2,3,4,5,6,7,8};
	int i=0;
	int j=0;
	int cnt=0;
	while(i<4)
	{
		while(j<2)
		{
			cnt=cnt+a[i][j];
			j=j+1;
		}
		i=i+1;
		j=0;
	}
	
	return cnt;
}
