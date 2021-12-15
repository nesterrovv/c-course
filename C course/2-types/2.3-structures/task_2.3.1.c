// упакованное число 42 выводится как "Some 42"
// Ошибка выводится как None
void maybe_int64_print( struct maybe_int64 i ) {
    if (i.valid) printf("Some %" PRId64, i.value);
    else printf("None");
}

// Если обе упаковки содержат ошибку, то результат ошибка
// Если ровно одна упаковка содержит ошибку, то результат -- вторая
// Если обе упаковки содержат число, то результат это минимум из двух чисел.
struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    // block for returning one value if only one value is correct
    if (!a.valid) { 
        return b;
    } else if (!b.valid) {
        return a;    
    }
    else {
        // find minimal value if BOTH ELEMENTS ARE INCORRECT
        int64_t minimum;
        if (a.value < b.value) {
            minimum = a.value;    
        } else {
            minimum = b.value;
        }
        struct maybe_int64 result = {.value = minimum, .valid = true};
        return result;
    }
}