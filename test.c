int arr1[10][2][3][4][5][6][2];
int arr2[10][2][3][2][4][8][7];

void loop1(int x, int y) {
  int a, b, c, d, e, f, g;
  a = 0;
  while (a < x && a < y) {
    b = 0;
    while (b < 2) {
      c = 0;
      while (c < 3) {
        d = 0;
        while (d < 4) {
          e = 0;
          while (e < 5) {
            f = 0;
            while (f < 6) {
              g = 0;
              while (g < 2) {
                arr1[a][b][c][d][e][f][g] = a + b + c + d + e + f + g + x + y;
                g = g + 1;
              }
              f = f + 1;
            }
            e = e + 1;
          }
          d = d + 1;
        }
        c = c + 1;
      }
      b = b + 1;
    }
    a = a + 1;
  }
}

void loop2() {
  int a, b, c, d, e, f, g;
  a = 0;
  while (a < 10) {
    b = 0;
    while (b < 2) {
      c = 0;
      while (c < 3) {
        d = 0;
        while (d < 2) {
          e = 0;
          while (e < 4) {
            f = 0;
            while (f < 8) {
              g = 0;
              while (g < 7) {
                arr2[a][b][c][d][e][f][g] = a + b + d + g;
                g = g + 1;
              }
              f = f + 1;
            }
            e = e + 1;
          }
          d = d + 1;
        }
        c = c + 1;
      }
      b = b + 1;
    }
    a = a + 1;
  }
}

int loop3(int h, int i, int j, int k, int l, int m, int n) {
  int a, b, c, d, e, f, g;
  int ans = 0;
  a = 0;
  while (a < 10) {
    b = 0;
    while (b < 100) {
      c = 0;
      while (c < 1000) {
        d = 0;
        while (d < 10000) {
          e = 0;
          while (e < 100000) {
            f = 0;
            while (f < 1000000) {
              g = 0;
              while (g < 10000000) {
                ans = ans % 817 + arr1[a][b][c][d][e][f][g] + arr2[a][b][c][d][e][f][g];
                g = g + 1;
                if (g >= n) break;
              }
              f = f + 1;
              if (f >= m) break;
            }
            e = e + 1;
            if (e >= l) break;
          }
          d = d + 1;
          if (d >= k) break;
        }
        c = c + 1;
        if (c >= j) break;
      }
      b = b + 1;
      if (b >= i) break;
    }
    a = a + 1;
    if (a >= h) break;
  }
  return ans;
}

int main() {
  int x = getint();
  int y = getint();
  int h = getint();
  int i = getint(), j = getint();
  int k = getint();
  int l = getint();
  int m = getint();
  int n = getint();
  loop1(x, y);
  loop2();
  return loop3(h, i, j, k, l, m, n);
}

/*
int n;
int Merge(int array[], int low, int middle, int high)
{
    int n1;
    n1 = middle - low + 1;
    int n2;
    n2 = high - middle;
    int L[10];
    int R[10];
    int i;
    i = 0;
    int j;
    j = 0;
 
    while(i < n1){
        L[i] = array[i + low];
        i = i + 1;        
    }
    while(j < n2){
        R[j] = array[j + middle  +1];
        j = j + 1;        
    }
    i = 0;
    j = 0;
    int k;
    k = low;
    while(i!=n1 && j!= n2)
    {   
        if(L[i] < R[j] + 1){
            array[k] = L[i];
            k = k + 1;
            i = i + 1;
        }
        else{
            array[k] = R[j];
            k = k + 1;
            j = j + 1;
        }
    }
    while(i < n1){
        array[k] = L[i];
        k = k + 1;
        i = i + 1;
        
    }
    while(j < n2){
        array[k] = R[j];
        k = k + 1;
        j = j + 1;
    }
    return 0;
}
 
int MergeSort(int array[], int p, int q)
{
    if(p < q)
    {
        int mid;
        mid = (p+q)/2;
        int tmp;
        tmp = MergeSort(array, p, mid);
        tmp = mid + 1;
        tmp = MergeSort(array, tmp, q);
        tmp = Merge(array,p, mid, q);
    }
    return 0;
}

int main(){
    n = 10;
    int a[10];
    a[0]=4;a[1]=3;a[2]=9;a[3]=2;a[4]=0;
    a[5]=1;a[6]=6;a[7]=5;a[8]=7;a[9]=8;
    int i;
    i = 0;
    int tmp;
    tmp = n - 1;
    i = MergeSort(a, i, tmp);
    while (i < n) {
        tmp = a[i];
        putint(tmp);
        tmp = 10;
        putch(tmp);
        i = i + 1;
    }
    return 0;
}
*/