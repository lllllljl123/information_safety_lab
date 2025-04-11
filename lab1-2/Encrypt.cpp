#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereEncrypt(const char *plaintext, const char *key, char *ciphertext) {
    int len = strlen(plaintext);
    int keyLen = strlen(key);
    for (int i = 0; i < len; i++) {
        char p = plaintext[i] - 'A';
        char k = key[i % keyLen] - 'A';
        ciphertext[i] = ((p + k) % 26) + 'A';
    }
    ciphertext[len] = '\0';
}

int main() {
    char inputLine[200];
    char plaintext[100], key[100], ciphertext[100];

    fgets(inputLine, sizeof(inputLine), stdin);
    sscanf(inputLine, "%s %s", plaintext, key);
    vigenereEncrypt(plaintext, key, ciphertext);
    printf("%s\n", ciphertext);

    return 0;
}

