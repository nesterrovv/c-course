void normalize(int* ax) {
    while (*ax % 2 == 0) {
        *ax = *ax / 2;
        if (*ax <= 0) {
            break;
        }
    }
}