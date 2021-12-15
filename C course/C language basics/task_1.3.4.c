void fizzbuzz(int num) {
    if (num <= 0) {
        printf("no");
    } else {
        if (num % 3 == 0) {
            printf("fizz");
        } if (num % 5 == 0) {
            printf("buzz");
        }
    }
}