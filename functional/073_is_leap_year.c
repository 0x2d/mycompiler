int year;
int flag;
int main()
{
	year=getint();
	if (year % 4 == 0 && year % 100 != 0)
		flag=1;
	else if (year % 400 == 0)
		flag=1;
	else
		flag=0;
	return flag;
}
