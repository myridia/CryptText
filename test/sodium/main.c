#include <stdio.h>
#include <sodium.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



char str2byte(void)
{
const char* hexstring = "1DE7142993816A6A81A7D4A2089A11F5C0A150FBC8E7DC0978D58825CE550000";
size_t length = strlen(hexstring);
unsigned char bytearray[length / 2];

for (size_t i = 0, j = 0; i < (length / 2); i++, j += 2)
	bytearray[i] = (hexstring[j] % 32 + 9) % 25 * 16 + (hexstring[j+1] % 32 + 9) % 25;


 dump_hex_buff(bytearray, length/2); 
 
 return bytearray;
}


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
    char *msg = "hello_sodium";
    char *add_data = "crypttext";
    const int add_data_len = 6;
    const int msg_len = strlen(msg);

 

  unsigned char key[crypto_aead_aes256gcm_KEYBYTES];
  unsigned char ciphertext[msg_len + crypto_aead_aes256gcm_ABYTES];
  char encrypted[msg_len + crypto_aead_aes256gcm_ABYTES];  
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


 
crypto_aead_aes256gcm_encrypt(ciphertext, &ciphertext_len,
                              msg, msg_len,
                              add_data, add_data_len,
                              NULL, key, key);

unsigned char decrypted[msg_len];
unsigned long long decrypted_len;
 if (ciphertext_len < crypto_aead_aes256gcm_ABYTES ||
    crypto_aead_aes256gcm_decrypt(decrypted, &decrypted_len,
                                  NULL,
                                  ciphertext, ciphertext_len,
                                  add_data,
                                  add_data_len,
                                  key, key) != 0) {
    /* message forged! */
}


 
    printf("...sodium library successfully found\n");
    puts("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        printf("key:");
        dump_hex_buff(key, crypto_secretbox_KEYBYTES);

        printf("encrypted:");
        dump_hex_buff(ciphertext, crypto_secretbox_KEYBYTES);
	
        printf("decrypted data (hex):");
        dump_hex_buff(decrypted, msg_len);
        printf("decrpyted data (ascii):%s\n", decrypted);
        puts("...string to bytes:");
	*encrypted = str2byte();
        dump_hex_buff(str2byte(), crypto_secretbox_KEYBYTES);

	
    puts("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");        
     
    return 0;
}

