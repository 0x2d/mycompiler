//sample function of Serpentine filling
int t = 1;
int a[15][15];

int main() {
	int n, i, j;
	n = 4;
	i = 1;
    j = 1;//初始位置
	while (t <= n * n) {//没有遍历完继续
		while (1) {//向右上走
			if (i<1 || j>n) {//不出界
                i = i + 1;
                j = j - 1;
                break;
			}
			else {
				a[i][j] = t;
                t = t + 1;
                i = i - 1;
                j = j + 1;
			}
		}
		if (j == n) {
            i = i + 1;
        }
		else{
            if (i == 1){
                j = j + 1;
            }
        }
		while (1) {//向左下走
			if (i > n || j < 1) {//不出界
				j = j + 1;
                i = i - 1;
                break;
			}
			else {
				a[i][j] = t;
                t = t + 1;
                i = i + 1;
                j = j - 1;
			}
		}
		if (i == n){
            j = j + 1;
        }
		else{
            if (j == 1){
                i = i + 1;
            }
        }
	}
    i = 1;
    while(i <= n){
        j = 1;
        while(j <= n){
            putint(a[i][j]);
            j = j + 1;
        }
        i  = i + 1;
    }
    return 0;
}