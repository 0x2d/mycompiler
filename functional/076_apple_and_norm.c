//sample function of apple and norm
int main() {
	int n, x, y;
    n = 10;
    x = 4;
    y = 9;
	int bad;
    bad = (y + x - 1) / x;
	n = n - bad;
	return n;
}