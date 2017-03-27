#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <gpgme.h>
#define PGM "run-keylist"
#include "run-support.h"
int main (int argc, char **argv)

{
	gpgme_error_t err;
	gpgme_ctx_t ctx;
	gpgme_keylist_mode_t mode = 0;
	gpgme_key_t key;
	gpgme_keylist_result_t result;
	gpgme_protocol_t protocol = GPGME_PROTOCOL_OpenPGP;
	gpgme_user_id_t uid;
	int i;

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

	err = gpgme_op_keylist_start (ctx, NULL, 0);
	if (err)
	{
		printf ("Error occured. Exiting...");
		return -1;
	}

	/* Iterate over the keys */
	while (!(err = gpgme_op_keylist_next (ctx, &key)))
	{
		printf ("Keyid : %s\n", key->subkeys?nonnull (key->subkeys->keyid):"?");
		/* Iterate over key's subkeys and print user id */
		for (i=0, uid=key->uids; uid != NULL; uid = uid->next, i++)
			printf ("userid %d: %s\n", i, nonnull(uid->uid));

		printf("=================================================\n\n");
	}

	gpgme_key_unref (key);
	gpgme_release (ctx);
	return 0;
}

