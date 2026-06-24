uint64_t* foo;

uint64_t main() {
    uint64_t fd;
    uint64_t* ptr;

    // abrir archivo para lectura
    fd = open("hello.txt", 0, 0);

    // mapear el archivo en memoria
    ptr = mmap(0, 4096, fd, 0);

    // imprimir lo que hay en memoria mapeada
    // imprime 8 caracteres a la vez como hello-world.c
    while (*ptr != 0) {
        write(1, ptr, 8);
        ptr = ptr + 1;
    }

    return 0;
}