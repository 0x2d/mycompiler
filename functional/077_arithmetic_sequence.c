//sample function of Arithmetic sequence
int main() {
	int a1, a2, n;
	int delta;
    a1 = 1;
    a2 = 4;
    n = 100;
	delta = a2 - a1;
	int an;
    an = a1 + delta * (n - 1);
	return an;
}