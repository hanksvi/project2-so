uint64_t msync(uint64_t addr);
uint64_t* foo;

uint64_t main() {
    uint64_t fd;
    uint64_t ptr;

    fd = open("prueba.c", 0, 0);

    ptr = mmap(0, 2, 4096, fd, 0);

    foo = ptr;
    *foo = 8385478439673424245;

    msync(ptr);

    return 0;
}