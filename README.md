# gpgme_toy_programs
To compile, get corresponding devel packages installed.

```bash
$ gcc `gpgme-config --cflags --libs` <file_name>.c -o hello
```

Run the binary:
```bash
$ ./hello
```

### Sample output for encrypted_byte_buffer.c

```bash
Encrypting data for chingujain <chingujain@gmail.com>

Encrypted text (571 bytes):
-----BEGIN PGP MESSAGE-----
Version: GnuPG v2

hQEMA419F+5NVItfAQf/RmS07MhEr6jQ24pxv7yN1FLQZmma5Cl7KCp51VBDeWI+
ACBfy9qvaFHfmRkspwp88CGTwUzM7BICSVT8Yxxxrp5ULFqf2sFj/+iDrdkChiCW
eVOnqElnljxy7GwGPSCrX/WUnwTNafJoJ/raQQRezaIQEaG3JLRFru/UAmV3nSEt
jWxxZDiH/km90ujiQgnkd1KwLXxrb84aIcaQDSqoSlKfgunch1LafWPD8LwZfKaZ
F+AQNV/+elSAsy7QiRjcfahOD44AlECmzcuDSadzBbxqbwEXL+cVTG90E/pSlR50
rhDx5XKXilLXGHoZv/+cmIFfRboFezp2nZ/pFtWWUdJaAa8JsP88FJQe5AnwZ5Q9
bH9IUf/BUl0YQLtrLAioLMS91ac5s1FJI52hzwAJvfiwlhSyLV9db/XF5Rm6vsQL
r47oZhzYhljnUAl/DbdvM56q9LH3cUvZkCuV
=i6LP
-----END PGP MESSAGE-----
```
