//reverse the order of array
int main(){
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i,t;
    i = 0;
    while(i < 5){
        t = a[i];
        a[i] = a[9 - i];
        a[9 - i] = t;
        i = i + 1;
    }
    return a[3];
}