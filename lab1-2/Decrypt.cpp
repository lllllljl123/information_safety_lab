#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LEN 5000

// 解密函数，参数分别是密文、密钥和要生成的原文
void vigenereDecrypt(const char *ciphertext, const char *key, char *plaintext) {
    // 计算密文和密钥的长度
    int len = strlen(ciphertext);
    int keyLen = strlen(key);
    // 循环次数是密文长度，若密钥较短需要将密钥补齐
    for (int i = 0; i < len; i++) {
        // 根据模运算解密
        char c = ciphertext[i] - 'A';
        char k = key[i % keyLen] - 'A';
        plaintext[i] = ((c - k + 26) % 26) + 'A';
    }
    plaintext[len] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT_LEN];
    char key[1000];
    char plaintext[MAX_TEXT_LEN];

    scanf("%s %s", ciphertext, key);
    vigenereDecrypt(ciphertext, key, plaintext); // 调用函数
    printf("%s\n", plaintext);

    return 0;
}
