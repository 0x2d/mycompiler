int n = 10;
int s1[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int cnt = 0;
int s2[10] = {};
void merge(int L, int R, int Mid) {
  int i = L;
  int j = Mid + 1;
  int k = L;
  while (i <= Mid && j <= R) {
    if (s1[i] <= s1[j]) {
      s2[k] = s1[i];
      k = k + 1;
      i = i + 1;
    } else {
      cnt = cnt + Mid - i + 1;

      s2[k] = s1[j];
      k = k + 1;
      j = j + 1;
    }
  }
  while (i <= Mid) {
    s2[k] = s1[i];
    k = k + 1;
    i = i + 1;
  }

  while (j <= R) {
    s2[k] = s1[j];
    k = k + 1;
    j = j + 1;
  }
  i = L;
  while (i <= R) {
    s1[i] = s2[i];
    i = i + 1;
  }
}
void mergesort(int L, int R) {
  if (L < R) {
    int Mid = (L + R) / 2;
    mergesort(L, Mid);
    mergesort(Mid + 1, R);
    merge(L, R, Mid);
  }
}
int main() {
  mergesort(1, n);
  return cnt;
}
