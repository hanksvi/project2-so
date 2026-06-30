uint64_t* foo;
uint64_t main() {
    uint64_t fd;
    uint64_t fd2;
    uint64_t* ptr;

    // abrir archivo
    fd = open("hello.txt", 0, 0);

    // mapear con prot=0 (solo lectura)
    ptr = mmap(0, 0, 4096, fd, 0);

    // abrir otro archivo para leer hacia el buffer mapeado
    fd2 = open("hello.txt", 0, 0);

    
    read(fd2, ptr, 8);

    return 0;
}