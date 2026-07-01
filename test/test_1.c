// Prototipos de syscalls
uint64_t mmap(uint64_t addr, uint64_t length, uint64_t prot, uint64_t fd, uint64_t offset);
uint64_t munmap(uint64_t addr);
uint64_t msync(uint64_t addr);
uint64_t open(char* name, uint64_t flags, uint64_t mode);
uint64_t write(uint64_t fd, char* buf, uint64_t len);

int main() {
uint64_t fd;
char* ptr;
uint64_t res;

write(1, "TEST 1: Lectura y Escritura (mmap + msync)\n", 43);

// 1. PREPARAMOS EL ARCHIVO (Escritura inicial)
fd = open("test_1_data.txt", 0, 0);
ptr = (char*) mmap(0, 2, 4096, fd, 0);

*ptr = 72; // Escribimos 'H'
msync((uint64_t) ptr); // Persistimos a disco
munmap((uint64_t) ptr); // Liberamos el mapeo

// 2. AHORA EVALUAMOS LA LECTURA
fd = open("test_1_data.txt", 0, 0);
ptr = (char*) mmap(0, 2, 4096, fd, 0); 

if (*ptr == 72) {
    write(1, "-> OK: Lectura correcta desde mmap\n", 35);
} else {
    write(1, "-> ERROR: Lectura incorrecta\n", 29);
    return -1;
}

// 3. EVALUAMOS LA MODIFICACIÓN Y ESCRITURA (msync)
*ptr = 87; // Cambiamos 'H' por 'W'
res = msync((uint64_t) ptr);

if (res == 0) {
    write(1, "-> OK: msync ejecutado\n", 23);
} else {
    write(1, "-> ERROR: msync fallo\n", 22);
    return -1;
}

munmap((uint64_t) ptr);

// 4. VERIFICAMOS PERSISTENCIA
fd = open("test_1_data.txt", 0, 0);
ptr = (char*) mmap(0, 2, 4096, fd, 0); 

if (*ptr == 87) {
    write(1, "-> OK: Cambios persistieron en disco!\n", 38);
} else {
    write(1, "-> ERROR: Cambios no persistieron\n", 34);
}

return 0;


}