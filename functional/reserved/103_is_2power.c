int main()         

{
	int num=128, flag;

    while (num % 2 == 0) {
        num = num / 2;
    }

    if (num == 1) {
        flag=1;
    } else {
        flag=2;

    }
    return flag;

}
