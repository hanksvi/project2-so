uint64_t munmap(uint64_t addr);
uint64_t* foo;

uint64_t main() {
    uint64_t fd1;
    uint64_t fd2;
    uint64_t fd3;
    uint64_t p1;
    uint64_t p2;
    uint64_t p3;
    uint64_t pid;

    fd1 = open("file1.txt", 0, 0);
    fd2 = open("file2.txt", 0, 0);
    fd3 = open("file3.txt", 0, 0);

    p1 = mmap(0, 0, 4096, fd1, 0);
    p2 = mmap(0, 0, 4096, fd2, 0);
    p3 = mmap(0, 0, 4096, fd3, 0);

    pid = fork();

    if (pid == 0) {
        munmap(p2);
        exit(0);
    } else {
        wait(0);

        write(1, p1, 8);
        write(1, p2, 8);
        write(1, p3, 8);
    }

    return 0;
}