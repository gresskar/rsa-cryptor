#include "rsa.h"

bool is_prime(mpz_t number) {
    return mpz_probab_prime_p(number, 50) > 0;
}

void generate_prime(mpz_t number, uint16_t bitsize) {
    uint32_t seed;
    if (getrandom(&seed, sizeof(seed), GRND_RANDOM) == -1) {
        (void) fprintf(stderr, "warning: getrandom() failed! falling back to less secure time()...\n");
        seed = (uint32_t) time(NULL);
    }
    (void) srand(seed);

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, rand());

    mpz_set_ui(number, 0);

    do {
        // Generate a random odd number
        mpz_urandomb(number, state, bitsize);
        mpz_setbit(number, 0);
    } while (!is_prime(number));

    // Find the next prime candidate, if needed
    while (!is_prime(number)) {
        mpz_nextprime(number, number);
    }

    gmp_randclear(state);
}

int main(int argc, char **argv) {
    uint16_t keysize = 4096;
    if (argc >= 2) {
        keysize = strtoul(argv[1], NULL, 10);
    }
    if (keysize < 8) {
        (void) fprintf(stderr, "keysize should not be less than 8!\n");
        return EXIT_FAILURE;
    }
    printf("keysize: %u\n\n", keysize);

    // Generate P
    mpz_t p;
    mpz_init(p);
    (void) generate_prime(p, keysize);
    gmp_printf("p: %Zd\n\n", p);
    
    // Generate Q
    mpz_t q;
    mpz_init(q);
    (void) generate_prime(q, keysize);
    gmp_printf("q: %Zd\n\n", q);

    // Make sure Q is not equal to P
    while (mpz_cmp(p, q) == 0) {
        (void) generate_prime(q, keysize);
    }

    // Calculate N
    mpz_t n;
    mpz_init(n);
    mpz_mul(n, p, q); // n = p * q
    gmp_printf("n: %Zd\n\n", n);

    // Calculate λ(N)
    mpz_t lambda_n, gcd;
    mpz_init(lambda_n);
    mpz_init(gcd);
    mpz_sub_ui(p, p, 1); // p = p - 1
    mpz_sub_ui(q, q, 1); // q = q - 1
    mpz_gcd(gcd, p, q); // gcd(p - 1, q - 1)
    mpz_mul(lambda_n, p, q); // lcm(p, q) = p * q
    mpz_div(lambda_n, lambda_n, gcd); // lcm(p, q) = (p * q) / gcd(p, q)
    gmp_printf("λ(n): %Zd\n\n", lambda_n);

    // Calculate E
    mpz_t e;
    mpz_init(e);
    mpz_ui_pow_ui(e, 2, 16); // e = (2 ^ 16)
    mpz_add_ui(e, e, 1); // e = (2 ^ 16) + 1

    // Ensure 1 < e < λ(n)
    if (mpz_cmp_ui(e, 1) < 0 || mpz_cmp(lambda_n, e) < 0) {
        (void) fprintf(stderr, "error: `1 < e < λ(n)` is false!\n");
        mpz_clear(e); mpz_clear(gcd); mpz_clear(lambda_n); mpz_clear(n); mpz_clear(q); mpz_clear(p);
        return EXIT_FAILURE;
    }

    // Ensure gcd(e, λ(n)) = 1
    mpz_gcd(gcd, e, lambda_n);
    if (mpz_cmp_ui(gcd, 1) != 0) {
        (void) fprintf(stderr, "`error: gcd(e, λ(n))` is not 1!\n");
        mpz_clear(e); mpz_clear(gcd); mpz_clear(lambda_n); mpz_clear(n); mpz_clear(q); mpz_clear(p);
        return EXIT_FAILURE;
    }
    gmp_printf("e: %Zd\n\n", e);

    // Calculate D
    mpz_t d;
    mpz_init(d);
    if (mpz_invert(d, e, lambda_n) == 0) {
        (void) fprintf(stderr, "`error: `(e ^ -1) * (mod λ(n))` is not an inverse!\n");
        mpz_clear(d); mpz_clear(e); mpz_clear(gcd); mpz_clear(lambda_n); mpz_clear(n); mpz_clear(q); mpz_clear(p);
        return EXIT_FAILURE;
    }
    gmp_printf("d: %Zd\n\n", d);

    // Clean up & quit
    mpz_clear(d);
    mpz_clear(e);
    mpz_clear(gcd);
    mpz_clear(lambda_n);
    mpz_clear(n);
    mpz_clear(q);
    mpz_clear(p);

    return EXIT_SUCCESS;
}
