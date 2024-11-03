CC := clang
CFLAGS := -std=c99 -Wall -Wextra -pedantic -pedantic-errors -march=native -fstack-clash-protection -fstack-protector-all -fcf-protection=full -flto=full -fvisibility=hidden -fsanitize=cfi -fsanitize=address -D_FORTIFY_SOURCE=3 -O3 -s
LDFLAGS := -lc -lm -fuse-ld=lld -rtlib=compiler-rt -Wl,-pic-executable -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack

rsa: bin/rsa-keygen bin/rsa-encrypt bin/rsa-decrypt bin/rsa-sign bin/rsa-verify
bin/rsa-keygen: src/rsa-keygen.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
bin/rsa-encrypt: src/rsa-encrypt.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
bin/rsa-decrypt: src/rsa-decrypt.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
bin/rsa-sign: src/rsa-sign.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
bin/rsa-verify: src/rsa-verify.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY clean:
	rm -vf bin/*
	rm -vf data/*
