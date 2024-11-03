# RSA Stuff

## TODO

- Replace `stdint.h` with `gmp.h`
- Implement `rsa-encrypt`, `rsa-decrypt`, `rsa-sign` & `rsa-verify`
- Modify `rsa-keygen` to take bitsize, and to export the keypair properly

## Building

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