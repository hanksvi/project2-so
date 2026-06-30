uint64_t* foo;
uint64_t main() {
    uint64_t fd;
    uint64_t* ptr;
    uint64_t pid;

    // abrir archivo
    fd = open("hello.txt", 0, 0);

    // mapear antes del fork para que ambos compartan el frame
    ptr = mmap(0, 2, 4096, fd, 0);  // prot=2, lectura y escritura

    pid = fork();

    if (pid == 0) {
        // proceso hijo: escribe en memoria mapeada
        *ptr = 435510276688;
        // hijo termina
        exit(0);
    } else {
        wait(0);
        // leer lo que escribio el hijo
        write(1, ptr, 8);
    }

    return 0;
}