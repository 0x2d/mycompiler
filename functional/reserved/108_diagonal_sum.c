int main()
{
	int array[3][3]={{1,2,3},{4,5, 6},{7,7,8}};  
	int i=0;
	int sum=0;
	while(i<3)
	{
		sum=array[i][i]+sum;
		i=i+1;
	}

	return sum;

}
