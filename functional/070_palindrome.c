//test if palindrome number
int main(){
	int num;
	num = 3113;
    int flag;
	if (num % 10 == num / 1000) {
		if ((num / 10)% 10 == (num / 100) % 10) {
			flag = 1;
		}
		else {
			flag = 2;
		}
	}else {
		flag = 2;
	}
	return flag;
}