#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
class Sha512 {
public:
    uint64_t* encode(char* data) {
        uint64_t h0 = 0x6a09e667f3bcc908ULL;
        uint64_t h1 = 0xbb67ae8584caa73bULL;
        uint64_t h2 = 0x3c6ef372fe94f82bULL;
        uint64_t h3 = 0xa54ff53a5f1d36f1ULL;
        uint64_t h4 = 0x510e527fade682d1ULL;
        uint64_t h5 = 0x9b05688c2b3e6c1fULL;
        uint64_t h6 = 0x1f83d9abfb41bd6bULL;
        uint64_t h7 = 0x5be0cd19137e2179ULL;
        
        uint64_t k[] = {0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL, 
                0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 
                0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL, 0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 
                0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL, 
                0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL, 0x983e5152ee66dfabULL, 
                0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 
                0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 
                0x53380d139d95b3dfULL, 0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL, 
                0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL, 
                0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL, 0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 
                0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 
                0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL, 
                0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 0xca273eceea26619cULL, 
                0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 
                0x113f9804bef90daeULL, 0x1b710b35131c471bULL, 0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 
                0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817};
        uint64_t origLen = strlen(data);
        uint64_t origLenBits = origLen * 8;

        char* withOne = (char*) (malloc(origLen + 1));
        withOne[origLen] = 0x80;

        for (int i = 0; i < origLen; i++) {
            withOne[i] = data[i];
        }

        uint64_t newLength = (origLen + 1) * 8;

        while(newLength % 1024 != 896) {
            newLength += 8;
        }

        char* output = (char *)malloc((newLength/8 + 16));
        for (int i = 0; i < (newLength/8 + 16); i++) {
            output[i] = 0;
        }

        for (int i = 0; i < (origLen + 1); i++) {
            output[i] = *(withOne+i);
        }

        uint64_t outputLen = newLength/8 + 16;
        for (int i = 0; i < 8; i++) {
            output[outputLen -1 - i] = ((origLenBits >> (8 * i)) & 0xFFULL);
        }

        uint64_t numChunks = outputLen * 8 / 1024;

        for (int i = 0 ; i < numChunks; i++) {
            uint64_t* w = (uint64_t*)(malloc(sizeof(uint64_t)* 80));

            for (int j = 0; j < 80; j++) {
                w[j] = 0ULL;
            }

            for (int j = 0; j < 16; j++) {     
                w[j] = (((uint64_t)(output[i*1024/8 + 8*j]) << 56) & 0xFF00000000000000ULL) | (((uint64_t)(output[i*1024/8 + 8*j+1]) << 48) & 0x00FF000000000000ULL);
                w[j] |= (((uint64_t)(output[i*1024/8 + 8*j+2]) << 40) & 0x0000FF0000000000ULL) | (((uint64_t)(output[i*1024/8 + 8*j+3]) << 32) & 0x000000FF00000000ULL);
                w[j] |= (((uint64_t)(output[i*1024/8 + 8*j+4]) << 24) & 0xFF000000ULL) | (((uint64_t)(output[i*1024/8 + 8*j+5]) << 16) & 0xFF0000ULL);
                w[j] |= (((uint64_t)(output[i*1024/8 + 8*j+6]) << 8) & 0xFF00ULL) | (((uint64_t)(output[i*1024/8 + 8*j+7])) & 0xFFULL);
            }

            //extend first 16 into remaining
            for (int j = 16; j < 80; j++) {
                uint64_t s0 = rightRotate(w[j-15], 1) ^ rightRotate(w[j-15], 8) ^ (w[j-15] >> 7);
                uint64_t s1 = rightRotate(w[j-2], 19) ^ rightRotate(w[j-2], 61) ^ (w[j-2] >> 6);
                w[j] = w[j-16] + s0 + w[j-7] + s1;
            }

            //initialize working variables
            uint64_t a = h0;
            uint64_t b = h1;
            uint64_t c = h2;
            uint64_t d = h3;
            uint64_t e = h4;
            uint64_t f = h5;
            uint64_t g = h6;
            uint64_t h = h7;
            
            for (int j = 0; j < 80; j++) {
                uint64_t S1 = rightRotate(e, 14) ^ rightRotate(e, 18) ^ rightRotate(e, 41);
                uint64_t ch = (e & f) ^ (~e & g);
                uint64_t temp1 = h + S1 + ch + k[j] + w[j];
                uint64_t S0 = rightRotate(a, 28) ^ rightRotate(a, 34) ^ rightRotate(a, 39);
                uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
                uint64_t temp2 = S0 + maj;
                
                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }
                  
            h0 = h0 + a;
            h1 = h1 + b;
            h2 = h2 + c;
            h3 = h3 + d;
            h4 = h4 + e;
            h5 = h5 + f;
            h6 = h6 + g;
            h7 = h7 + h;          
        }

        uint64_t* hash = (uint64_t*) (malloc(sizeof(uint64_t) * 8));
        
        *hash = h0;
        *(hash + 1) = h1;
        *(hash + 2) = h2;
        *(hash + 3) = h3;
        *(hash + 4) = h4;
        *(hash + 5) = h5;
        *(hash + 6) = h6;
        *(hash + 7) = h7;
        return hash;
    }

    uint64_t rightRotate(uint64_t n, uint64_t d) {
        return (n >> d) | (n << (64-d));
    }


};