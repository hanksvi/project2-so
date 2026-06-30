// Prototipos
uint64_t mmap(uint64_t addr, uint64_t length, uint64_t prot, uint64_t fd, uint64_t offset);
uint64_t msync(uint64_t addr);
uint64_t open(char* name, uint64_t flags, uint64_t mode);
uint64_t write(uint64_t fd, char* buf, uint64_t len);

int main() {
uint64_t fd;
char* ptr;
uint64_t res;

write(1, "TEST 3: Prueba de Dirty/Modified Bits\n", 38);
write(1, "Nota: Revisa los logs de Selfie para comprobar si hubo escritura a disco\n", 73);

fd = open("test_3_dirty.txt", 0, 0);
ptr = (char*) mmap(0, 4096, 2, fd, 0);

if ((uint64_t)ptr == (uint64_t)-1) { return -1; }
if ((uint64_t)ptr == 0)            { return -1; }

// NO MODIFICAMOS NADA.
// Simplemente llamamos a msync. 
// Si la logica dirty_bit esta implementada en selfie.c, NO debe haber I/O de disco.
write(1, "-> Ejecutando msync sobre frame limpio...\n", 42);
res = msync((uint64_t) ptr);

if (res == 0) {
    write(1, "-> OK: msync finalizo\n", 22);
} else {
    write(1, "-> ERROR: msync fallo\n", 22);
}

// Ahora ensuciamos la pagina
*ptr = 68; // 'D'
write(1, "-> Ensuciando pagina en memoria...\n", 35);

// Llamamos a msync de nuevo. AHORA SI debe haber I/O de disco.
write(1, "-> Ejecutando msync sobre frame sucio...\n", 41);
res = msync((uint64_t) ptr);

if (res == 0) {
    write(1, "-> OK: msync finalizo (debio guardar a disco)\n", 46);
}

return 0;


}