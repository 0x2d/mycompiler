//sample function of apple and norm
int main() {
	int n, x, y;
    n = 10;
    x = 4;
    y = 9;
	int left;
    left = n - (y + x - 1) / x;
	if (left < 0)
		left = 0;
	return left;
}