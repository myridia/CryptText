#include <stdio.h>
#include <sodium.h>

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
    const int msg_length = strlen(msg);
    int ciphertext_len = crypto_secretbox_MACBYTES + msg_length;
    
    unsigned char key[crypto_secretbox_KEYBYTES];
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    unsigned char ciphertext[ciphertext_len];
    unsigned char decrypted[msg_length];
    
    /* Generating a random key */
    crypto_secretbox_keygen(key);
    printf("secret key generated:\n");
    printf("xxxxxxxxxxxxxxxxxxxxxx\n");
    printf("msg: %s\n",msg);
    
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


    
    dump_hex_buff(ciphertext, ciphertext_len); 

    /* Decrypt ciphertext buffer using key and nounce
       Decrypted message is stored in decrypted buffer */
    if (crypto_secretbox_open_easy(decrypted, ciphertext, ciphertext_len, nonce, key) != 0) {
        /* message forged!, meaning decryption failed */

    } else {
        /* Successful decryption */
        printf("decrypted data (hex):\n");
        dump_hex_buff(decrypted, msg_length);
	
        printf("decrpyted data (ascii):%s\n", decrypted);
    }
    return 0;
    
}

