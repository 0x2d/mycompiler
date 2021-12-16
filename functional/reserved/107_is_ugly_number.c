int main()         

{
 	int num=5400;
 	int flag;
    while (num % 2 == 0) {
        num = num / 2;
    }
    while (num % 3 == 0) {
        num = num / 3;
    }
    while (num % 5 == 0) {
        num = num / 5;
    }
    if (num == 1) {
        flag=1;
    } else {
        flag=0;
    }
    return flag;
}
