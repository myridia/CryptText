#include <stdio.h>
#include <sodium.h>

#define CIPHERTEXT_LEN (crypto_secretbox_MACBYTES + MESSAGE_LEN)

void dump_hex_buff(unsigned char buf[], unsigned int len)
{
    printf("\n");  
    int i;
    for (i=0; i<len; i++) {
      printf("%02X ", buf[i]);
    }
    printf("\n");
}


/*
  https://doc.libsodium.org/secret-key_cryptography/aead/aes-256-gcm#example-combined-mode
  https://franks42.gitbooks.io/libsodium-doc/content/secret-key_cryptography/aead.html
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
    char *msg = "hello";    

    unsigned char key[crypto_secretbox_KEYBYTES];
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    unsigned char ciphertext[CIPHERTEXT_LEN];
    unsigned char decrypted[MESSAGE_LEN];

    /* Generating a random key */
    crypto_secretbox_keygen(key);
    printf("secret key generated:\n");
    printf("xxxxxxxxxxxxxxxxxxxxxx\n");
    printf("msg: %s\n",msg);
    const int msg_length = strlen(msg);
    printf("msg length: %d\n",msg_length);    
    printf("zzzzzzzzzzzzzzzzzzzzzzzz\n");    
    dump_hex_buff(key, crypto_secretbox_KEYBYTES);


    

    
    /* Using random bytes for a nonce buffer (a buffer used only once) */
    randombytes_buf(nonce, sizeof nonce);
    printf("nonce:\n");
    dump_hex_buff(nonce, sizeof nonce);

    /* Encrypt MESSAGE using key and nonce
       Encrypted message is stored in ciphertext buffer */
    crypto_secretbox_easy(ciphertext, msg, msg_length, nonce, key);
    printf("ciphertext:\n");
    
    dump_hex_buff(ciphertext, CIPHERTEXT_LEN);



    /* Decrypt ciphertext buffer using key and nounce
       Decrypted message is stored in decrypted buffer */
    if (crypto_secretbox_open_easy(decrypted, ciphertext, CIPHERTEXT_LEN, nonce, key) != 0) {
        /* message forged!, meaning decryption failed */

    } else {
        /* Successful decryption */
        printf("decrypted data (hex):\n");
        dump_hex_buff(decrypted, MESSAGE_LEN);
        printf("decrpyted data (ascii):%.4s\n", decrypted);
    }
    return 0;
    
}

