int is_whitespace(char c) {
    if (c == ' ' || c == '\t' || c == '\n') {
        return 1;
    } else return 0;
}

int string_count(char *str) {
    int counter = 0;
    for (int index = 0; str[index] != 0; index++) {
        counter++; // length of word
    }
    return counter;
}

int string_words(char *str) {
    int tmp = 0;
    int counterOfWords = 0;
    for (int index = 0; str[index]; index++) {
        if (is_whitespace(str[index])) {
            continue; // if is whitespace - not count
        }
        tmp = index;
        counterOfWords++;
        break;
    }
    for (int index = tmp; str[index] != 0; index++) {
        if (is_whitespace(str[index]) && !is_whitespace(str[index + 1]) && str[index+1] != 0) {
            counterOfWords++; // if this part of string between whitespaces and is no zero-term
        }
    }
    return counterOfWords;
}