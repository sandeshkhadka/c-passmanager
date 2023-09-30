#include "encrypt_decrypt.h"
char *encrypt(char plaintext[MAX_PAINTEXT_LEN],
              unsigned char key[crypto_secretbox_KEYBYTES],
              unsigned char nonce[crypto_secretbox_NONCEBYTES]) {

  size_t message_len = strlen(plaintext);
  int CIPHERTEXT_LEN = crypto_secretbox_MACBYTES + message_len;

  unsigned char ciphertext[CIPHERTEXT_LEN];

  crypto_secretbox_easy(ciphertext, (const unsigned char *)plaintext,
                        message_len, nonce, key);

  char *b64encoded_ciphertext = b64_encode(ciphertext, CIPHERTEXT_LEN);

  return b64encoded_ciphertext;
}

int decrypt(char b64encoded_cipher[MAX_B64ENCODED_LEN],
            char decrypted_text[MAX_PAINTEXT_LEN], size_t message_len,
            unsigned char key[crypto_secretbox_KEYBYTES],
            unsigned char nonce[crypto_secretbox_NONCEBYTES]) {
  /* Variable declaration */
  int CIPHERTEXT_LEN = crypto_secretbox_MACBYTES + message_len;

  unsigned char decrypted[message_len];

  char b64Input[b64_encoded_size(CIPHERTEXT_LEN)];

  sprintf(b64Input, "%s", b64encoded_cipher);
  unsigned char *ciphertext;

  ciphertext = malloc(b64_decoded_size(b64Input));
  b64_decode(b64Input, ciphertext, CIPHERTEXT_LEN);

  /* Decrypt ciphertext buffer using key and nounce
     Decrypted message is stored in decrypted buffer */
  if (crypto_secretbox_open_easy(decrypted, ciphertext, CIPHERTEXT_LEN, nonce,
                                 key) != 0) {
    return 0;
  } else {
    sprintf(decrypted_text, "%s", decrypted);
    return 1;
  }
}
