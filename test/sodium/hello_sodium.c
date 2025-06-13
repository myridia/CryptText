#include <stdio.h>
#include <sodium.h>
/*
  https://doc.libsodium.org/secret-key_cryptography/aead/aes-256-gcm#example-combined-mode
 */
int main(void)
{
    printf("Hello Sodium\n");

    if (sodium_init() < 0) {
      puts("Sodium library couldn't be initialized, it is not safe to use.");
      exit(1);
    }

    puts("Sodium library successfully found");
    char *passwd = "password123";


#define MESSAGE (const unsigned char *) "test"
#define MESSAGE_LEN 4
#define ADDITIONAL_DATA (const unsigned char *) "123456"
#define ADDITIONAL_DATA_LEN 6

unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES];
unsigned char key[crypto_aead_aes256gcm_KEYBYTES];
unsigned char ciphertext[MESSAGE_LEN + crypto_aead_aes256gcm_ABYTES];
unsigned long long ciphertext_len;


if (crypto_aead_aes256gcm_is_available() == 0) {
    abort(); /* Not available on this CPU */
}
 

crypto_aead_aes256gcm_keygen(key);
randombytes_buf(nonce, sizeof nonce);
 
crypto_aead_aes256gcm_encrypt(ciphertext, &ciphertext_len,
                              MESSAGE, MESSAGE_LEN,
                              ADDITIONAL_DATA, ADDITIONAL_DATA_LEN,
                              NULL, nonce, key);



unsigned char decrypted[MESSAGE_LEN];
unsigned long long decrypted_len;


 if (ciphertext_len < crypto_aead_aes256gcm_ABYTES ||
    crypto_aead_aes256gcm_decrypt(decrypted, &decrypted_len,
                                  NULL,
                                  ciphertext, ciphertext_len,
                                  ADDITIONAL_DATA,
                                  ADDITIONAL_DATA_LEN,
                                  nonce, key) != 0) {


   char *dm = (unsigned char *)malloc(ciphertext_len - crypto_aead_aes256gcm_ABYTES);
   printf("%s",dm);
   
    /* message forged! */
}
 



 
    return 0;
    
}
