#include "base64.h"
#include <sodium.h>
#include <stdio.h>
#include <string.h>
#define MAX_PAINTEXT_LEN 100
#define MAX_CIPHERTEXT_LEN crypto_secretbox_MACBYTES + MAX_PAINTEXT_LEN
#define MAX_B64ENCODED_LEN 156

char *encrypt(char plaintext[MAX_PAINTEXT_LEN],
              unsigned char key[crypto_secretbox_KEYBYTES],
              unsigned char nonce[crypto_secretbox_NONCEBYTES]);

int decrypt(char b64encoded_cipher[MAX_B64ENCODED_LEN],
            char decrypted_text[MAX_PAINTEXT_LEN], size_t message_len,
            unsigned char key[crypto_secretbox_KEYBYTES],
            unsigned char nonce[crypto_secretbox_NONCEBYTES]);
