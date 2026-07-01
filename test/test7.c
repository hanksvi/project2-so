uint64_t msync(uint64_t addr);
uint64_t* foo;

uint64_t main() {
    uint64_t fd;
    uint64_t ptr;

    fd = open("dirty.txt", 0, 0);

    // prot = 2 => read + write
    ptr = mmap(0, 2, 8192, fd, 0);

    // modificar solo la primera página
    foo = ptr;
    *foo = 4846791580151137097;

    msync(ptr);

    return 0;
}