//test water flower num
int main(){
    int i, j, k;
    int n, cnt;
    n = 100;
    cnt = 0;
    while(n < 1000){
        i = n/100;
        j = n / 10 % 10;
        k = n % 10;
        if(i*i*i + j*j*j + k*k*k == n){
            cnt = cnt + 1;
        }
        n = n + 1;
    }
    return cnt;
}
