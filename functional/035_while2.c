//test while-while
int main(){
    int a, b;
    a = 5;
    b = 10;
    while(a < 10){
        while(b < 15){
            b = b + 1;
        }
        a = a + 1;
    }
    return b;
}