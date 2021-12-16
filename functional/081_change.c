int m[4]={20,10,5,1};
int k;

void greedMoney(int n){
	int i;
	i=0;
	while(i<k)
	{
		while(n>=m[i]){
			putint(m[i]);
			putch(10);
			n=n-m[i];
		}
		i=i+1;
	}

}

int main(){
	k=4;
	greedMoney(40);
	return 0;
}
