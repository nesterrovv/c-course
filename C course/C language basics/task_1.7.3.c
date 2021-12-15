void factorize( int n, int* a, int* b ) {
    if (n == 1) {
        *a = 1;
        *b = 1;
    } else {
        int check = 0;
        for (int i = 2; i <= n/2; i++) {
            if (n % i == 0) {
                if (i > n/i) {
                    *a = n/i;
                    *b = i;
                    check = 1;
                } else {
                    *a = i;
                    *b = n/i;
                    check = 1;
                }
            } else {
                if (check == 0) {
                    *a = 1;
                    *b = n;
                }
            }
        }
    }
}