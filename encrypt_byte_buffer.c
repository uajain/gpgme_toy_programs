#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <gpgme.h>
#define PGM "run-keylist"
#include "run-support.h"

#define DATA_TO_ENCRYPT "This is the line to be encrypted"
#define MAX 4096

int main (int argc, char **argv)

{
	gpgme_error_t err;
	gpgme_ctx_t ctx;
	gpgme_keylist_mode_t mode = 0;
	gpgme_key_t key[2] = {NULL, NULL}; /* gpgme_op_encrypt needs NULL terminated key array */
	gpgme_encrypt_result_t result;
	gpgme_protocol_t protocol = GPGME_PROTOCOL_OpenPGP;
	gpgme_user_id_t uid;
	gpgme_data_t clear_text, encrypted_text;
	ssize_t nbytes;
	char *buffer;

	/*Initialize the local env*/
	init_gpgme (protocol);
	err = gpgme_new (&ctx);
	if (err) 			/* or use fail_if_err */
	{
		printf("Could not create new Context. Exiting...\n");
		return -1;
	}

	/*Set the cryptographic protocol*/
	gpgme_set_protocol (ctx, protocol);
	gpgme_set_keylist_mode (ctx, mode);
	gpgme_set_offline (ctx, 0);	/* Disable additional checks by DirMngr */
	gpgme_set_armor (ctx, 1);

	err = gpgme_op_keylist_start (ctx, "chingu", 0);
	if (err)
	{
		printf ("Error occured. Exiting...");
		return -1;
	}

	/* get the key */
	err = gpgme_op_keylist_next (ctx, &key[0]);
	uid = key[0]->uids;
	printf("\nEncrypting data for %s <%s>\n\n", uid->name, uid->email);

	/* Prepare the data buffer */
	err = gpgme_data_new_from_mem (&clear_text, DATA_TO_ENCRYPT, strlen(DATA_TO_ENCRYPT), 1);
	if (err)
	{
		printf("Error preparing data buffers. Exiting...\n");
		return -1;
	}

	err = gpgme_data_new (&encrypted_text);
	/* Encrypt */
	err = gpgme_op_encrypt(ctx, key,
                           GPGME_ENCRYPT_ALWAYS_TRUST, clear_text, encrypted_text);

	result = gpgme_op_encrypt_result (ctx);
	nbytes = gpgme_data_seek (encrypted_text, 0, SEEK_SET);

	buffer = malloc(MAX);
	nbytes = gpgme_data_read (encrypted_text, buffer, MAX);
	if (nbytes == -1)
	{
		printf("Could not get the bytes. Exiting...\n");
		return -1;
	}

	buffer[nbytes] = '\0';
	/* Print the ASCII-armored encrypted text to stdoout */
	printf("Encrypted text (%i bytes):\n%s\n", (int)nbytes, buffer);

	gpgme_key_unref (key[0]);
	gpgme_release (ctx);
	free (buffer);
	return 0;
}

