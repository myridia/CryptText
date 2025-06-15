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
    if (sodium_init() < 0) {
      puts("Sodium library couldn't be initialized, it is not safe to use.");
      exit(1);
    }
    char *password = "1234";
    char *msg = "hello";    
    const int msg_len = strlen(msg);


#define ADDITIONAL_DATA (const unsigned char *) "123456"
#define ADDITIONAL_DATA_LEN 6

unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES];
unsigned char key[crypto_aead_aes256gcm_KEYBYTES];
unsigned char ciphertext[msg_len + crypto_aead_aes256gcm_ABYTES];
unsigned long long ciphertext_len;

sodium_init();
if (crypto_aead_aes256gcm_is_available() == 0) {
    abort(); /* Not available on this CPU */
}

/***********************************************************/

#define KEY_LEN crypto_box_SEEDBYTES
 
if (crypto_pwhash
    (key, sizeof key, password, strlen(password), key,
     crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,
     crypto_pwhash_ALG_DEFAULT) != 0) {
    /* out of memory */
}

/***********************************************************/


/* 
crypto_aead_aes256gcm_keygen(key);
*/
 

randombytes_buf(nonce, sizeof nonce);


crypto_aead_aes256gcm_encrypt(ciphertext, &ciphertext_len,
                              msg, msg_len,
                              ADDITIONAL_DATA, ADDITIONAL_DATA_LEN,
                              NULL, nonce, key);

unsigned char decrypted[msg_len];
unsigned long long decrypted_len;
if (ciphertext_len < crypto_aead_aes256gcm_ABYTES ||
    crypto_aead_aes256gcm_decrypt(decrypted, &decrypted_len,
                                  NULL,
                                  ciphertext, ciphertext_len,
                                  ADDITIONAL_DATA,
                                  ADDITIONAL_DATA_LEN,
                                  nonce, key) != 0) {
    /* message forged! */
}
 
    printf("...sodium library successfully found\n");
    puts("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        printf("key:");
        dump_hex_buff(key, crypto_secretbox_KEYBYTES);
	
        printf("decrypted data (hex):");
        dump_hex_buff(decrypted, msg_len);
        printf("decrpyted data (ascii):%s\n", decrypted);	
    puts("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");        
     
    return 0;
}

