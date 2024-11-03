# RSA Stuff

## TODO

- Implement `rsa-encrypt`, `rsa-decrypt`, `rsa-sign` & `rsa-verify`
- Modify `rsa-keygen` to to export the keypair in PEM format

## Building

Make sure `clang`, `lld`, `compiler-rt` & `make` is installed

Then build the programs by running:

```Shell
make -j$(nproc)
```

## Usage

**Generate a key:**

```Shell
./bin/rsa-keygen
```

**Encrypt a message:**

```Shell
./bin/rsa-encrypt <message> <public key>
```

For example:

```Shell
./bin/rsa-encrypt "message.txt" "data/pubkey.asc"
```

**Decrypt a message:**

```Shell
./bin/rsa-decrypt <message> <private key>
```

For example:

```Shell
./bin/rsa-decrypt "message.txt.enc" "data/privkey.asc"
```

**Sign a message:**

```Shell
./bin/rsa-sign <message> <private key>
```

For example:

```Shell
./bin/rsa-sign "message.txt" "data/privkey.asc"
```

**Verify a message:**

```Shell
./bin/rsa-verify <message> <public key>
```

For example:

```Shell
./bin/rsa-verify "message.txt.asc" "data/pubkey.asc"
```
