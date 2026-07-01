// Prototipos de syscalls
uint64_t mmap(uint64_t addr, uint64_t length, uint64_t prot, uint64_t fd, uint64_t offset);
uint64_t fork();
uint64_t open(char* name, uint64_t flags, uint64_t mode);
uint64_t write(uint64_t fd, char* buf, uint64_t len);

int main() {
uint64_t fd;
uint64_t pid;
char* ptr;
uint64_t i; // <-- Declaracion movida al inicio de la funcion

write(1, "TEST 2: Creacion de mappings compartidos\n", 41);

fd = open("test_2_shared.txt", 0, 0);
ptr = (char*) mmap(0, 2, 4096, fd, 0);

*ptr = 65; // 'A'

pid = fork();

if (pid == 0) {
    // --- PROCESO HIJO ---
    if (*ptr == 65) {
        write(1, "-> HIJO: Ve valor del padre (Cache Shared OK)\n", 46);
        *ptr = 66; // 'B'
    } else {
        write(1, "-> HIJO ERROR: Memoria no compartida\n", 37);
    }
} else {
    // --- PROCESO PADRE ---
    i = 0;
    // Loop para darle tiempo al hijo de escribir
    while(i < 10000) { i = i + 1; }

    if (*ptr == 66) {
        write(1, "-> PADRE: Ve el cambio del hijo. Exito!\n", 40);
    } else {
        write(1, "-> PADRE ERROR: No veo cambio del hijo\n", 39);
    }
}

return 0;


}