#include "Sha256.cpp"
#include "Sha384.cpp"
#include "Sha512.cpp"

int main() {
    char * data = "abc";
    Sha256 sha256;
    unsigned* hash256 = sha256.encode(data);
    printf("%x%x%x%x%x%x%x%x\n" , hash256[0], hash256[1], hash256[2], hash256[3], hash256[4], hash256[5], hash256[6], hash256[7]);
    Sha512 sha512;
    uint64_t* hash512 = sha512.encode(data);
    printf("%llx%llx%llx%llx%llx%llx%llx%llx\n" , hash512[0], hash512[1], hash512[2], hash512[3], hash512[4], hash512[5], hash512[6], hash512[7]);

    Sha384 sha384;
    uint64_t* hash384 = sha384.encode(data);
    printf("%llx%llx%llx%llx%llx%llx\n" , hash384[0], hash384[1], hash384[2], hash384[3], hash384[4], hash384[5]);

}
