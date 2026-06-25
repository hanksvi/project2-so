uint64_t* foo;
uint64_t main() {
    uint64_t fd;
    uint64_t* ptr;

    fd = open("hello.txt", 0, 0);
    ptr = mmap(0, 0,4096, fd, 0);  // prot=0, solo lectura

    while (*ptr != 0) {
        write(1, ptr, 8);
        ptr = ptr + 1;
    }
    return 0;
}