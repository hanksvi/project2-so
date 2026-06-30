uint64_t* foo;
uint64_t main() {
    uint64_t fd;
    uint64_t* ptr;
    uint64_t pid;

    pid = fork();

    if(pid ==0){
        fd = open("hello.txt", 0, 0);
        ptr = mmap(0, 2, 4096, fd, 0);

        *ptr = 435510276688;
        exit(0);
    }else{
        wait(0);
        fd = open("hello.txt", 0, 0);
        ptr = mmap(0, 2, 4096, fd, 0);

        write(1, ptr, 8);
    }

    

    return 0;
}