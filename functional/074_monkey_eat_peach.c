//sample function of monkey eat peach
int main(){
    int day, x1, x2;
    day = 9;
    x2 = 1;
    while(day > 0){
        x1 = (x2 + 1) * 2;
        x2 = x1;
        day = day -1;
    }
    return x1;
}