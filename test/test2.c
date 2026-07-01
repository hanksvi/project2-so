uint64_t msync(uint64_t addr);
uint64_t* foo;

uint64_t main() {
    uint64_t fd;
    uint64_t* ptr;

    fd = open("hello.txt", 0, 0);
    ptr = mmap(0, 2, 4096, fd, 0);

    *ptr = 435510276688;

    msync((uint64_t) ptr);

    fd = open("hello.txt", 0, 0);
    read(fd, ptr, 8);
    write(1, ptr, 8);

    return 0;
}