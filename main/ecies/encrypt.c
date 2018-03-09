
#include "encrypt.h"

#define TIMER_KEY_GENERATION 	500000                   //interval between each symetric key generation (in ms)
#define TIMER_MESURE     		3000					 //interval between each sample (in ms)
#define BUFF_SIZE_MAX			8	//240				 //size max in bit of the buffer to send. in bytes daw ana tita sally
#define MSG_SIZE				24						 //size of one message to put in the buffer
#define TEMP_SIZE				8
#define PRESS_SIZE				8

//Allow to generate the first symetric key before starting sampling
int FIRST_KEY=0;

//global variable shared between the different task
uint8_t key[32];
uint8_t extern_pubkey[64];
uint8_t wraped_key[132];


/*
 * \brief							Fullfill global variable wrapped_buffer with iv || tag || encrypted_buffer
 *
 * \param	encrypted_buffer		The encrypted buffer to wrap before sending it
 * 			iv						Iv used for encryption
 * 			tag						Tag computed by the encryption
 * 			wrapped_buffer			The buffer to fullfill
 * 			wrap_size
 */
void wrap_buffer(uint8_t * encrypted_buffer, unsigned buffer_size,uint8_t * iv, uint8_t * tag,uint8_t * wrapped_buffer){
	printf("\nwrap buffer\n"); //<--kd
	memcpy(wrapped_buffer,iv,IV_SIZE);
	memcpy(wrapped_buffer+IV_SIZE,tag,TAG_SIZE);
	memcpy(wrapped_buffer+IV_SIZE+TAG_SIZE,encrypted_buffer,buffer_size);
	printf("\nend wrap buffer\n"); //<--kd
}


/*
 * \brief							Fullfill global variable key with a AESGCM symetric key
 *
 */
void symetric_generation(){	//generates public key
	printf("\nsymetric generation\n"); //<
	uint8_t ephemeral_pubkey[PUB_KEY_SIZE];
	printf("\nend symetric generation\n");
	return;
}

/*
 * \brief							Encrypt the global variable key with ECIES cipher before sending it to the receiver
 * 									Send a wrapped key of the form id_curve(3) || length(public_key) || ephemeral pubkey || tag || iv || ciphertext
 *
 * \param 		param				Must be a pointer of the socket to send wrapped key
 *
 */
void ecc_key_task(void){
//	for(;;){
	printf("\n ecc_key_task\n"); //<
	memset(key,0,32);
	memset(wraped_key,0,32+4+PUB_KEY_SIZE+TAG_SIZE+IV_SIZE);
	symetric_generation();
//	printf("\nend symetric generation in ecc key task\n");
	ECIES_encrypt_key(key,32,extern_pubkey,wraped_key);
	//send(*sock,wraped_key,32+4+PUB_KEY_SIZE+TAG_SIZE+IV_SIZE,0);
	FIRST_KEY=1;
	memset(wraped_key,0,32+4+PUB_KEY_SIZE+TAG_SIZE+IV_SIZE);
	vTaskDelay(1000/portTICK_RATE_MS);
	printf("\nend ecc_key_task\n"); //<
//	}
}

void encrypt(uint8_t data_param[static BUFF_SIZE_MAX]){
//void encrypt(uint8_t data_param){
	while(FIRST_KEY!=1){

		//wait for the first symetric key to be computed and sent
	}
	int i = 0;
	uint8_t buffer[BUFF_SIZE_MAX];
//	uint8_t random[MSG_SIZE];
	uint8_t iv[IV_SIZE];
	uint8_t tag[TAG_SIZE];
	uint8_t encrypted_buffer[BUFF_SIZE_MAX];
	uint8_t decrypted_buffer[BUFF_SIZE_MAX];
	uint8_t wraped_buffer[BUFF_SIZE_MAX+IV_SIZE+TAG_SIZE];
	uint8_t local_key[32];

	memcpy(local_key,key,32);
	printf("\nencrypt\n");

	memcpy(buffer, data_param, BUFF_SIZE_MAX); //<-- i need to clarify this
	AESGCM(buffer,BUFF_SIZE_MAX,MBEDTLS_ENCRYPT,key,iv,tag,encrypted_buffer);
		printf("\nprint message\n");
		for(i=0;i<BUFF_SIZE_MAX;i++){	//print plain message
			printf("%x", (unsigned int)buffer[i]);
		}
		printf("\nencrypted message\n");
		for(i=0;i<BUFF_SIZE_MAX;i++){
			printf("%x", (unsigned int)encrypted_buffer[i]);
		}
		wrap_buffer(encrypted_buffer,BUFF_SIZE_MAX,iv,tag,wraped_buffer);
		//send(*sock,wraped_buffer,BUFF_SIZE_MAX+IV_SIZE+TAG_SIZyE,0);

	AESGCM(encrypted_buffer,BUFF_SIZE_MAX,MBEDTLS_DECRYPT,key,iv,tag,decrypted_buffer);
		printf("\nmessage decrypted\n");
		for(i=0;i<BUFF_SIZE_MAX;i++){
			printf("%x", (unsigned int)decrypted_buffer[i]);
		}
		printf("\nwrap buffer\n");


	memset(buffer,0,BUFF_SIZE_MAX);
	memset(encrypted_buffer,0,BUFF_SIZE_MAX);
	memset(decrypted_buffer,0, BUFF_SIZE_MAX);
	memset(iv,0,IV_SIZE);
	memset(tag,0,TAG_SIZE);
	memset(wraped_buffer,0,BUFF_SIZE_MAX+IV_SIZE+TAG_SIZE);
	vTaskDelay(TIMER_MESURE/portTICK_RATE_MS);
}

void data_encrypt(uint8_t data)//[static BUFF_SIZE_MAX])
{
	uECC_set_rng(&random32);

	// generate key and send
	printf("\n \n");
	ecc_key_task();
	//encrypt data and send
	printf("\nencrypting-->\n");
	encrypt(&data);
	printf("\n<--finished\n");
}


