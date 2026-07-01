uint64_X factorial(uint64_t n) {
    if (n <= 1)
        return 1;

    return n * factorial(n - 1);
}

uint64_t main() {
    uint64_t x;

    x = factorial(5);

    return x;
}