CC := clang
CFLAGS := -std=c99 -Wall -Wextra -pedantic -pedantic-errors -march=native -fPIC -fstack-clash-protection -fstack-protector-all -fcf-protection=full -flto=full -fvisibility=hidden -fsanitize=cfi -fsanitize=address -D_FORTIFY_SOURCE=3 -O2 -s
LDFLAGS := -lc -lgmp -fuse-ld=lld -rtlib=compiler-rt -Wl,-pic-executable -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack

BINS = rsa-decrypt rsa-encrypt rsa-keygen rsa-sign rsa-verify
SRC = $(patsubst %, src/%.c, $(BINS))
BIN = $(patsubst %, bin/%, $(BINS))

all: $(BIN)
bin/%: src/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

.PHONY clean:
	rm -vf bin/*
	rm -vf data/*
