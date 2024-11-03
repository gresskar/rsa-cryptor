#include "rsa.h"

uint64_t extended_gcd(uint64_t n1, uint64_t n2, uint64_t *x, uint64_t *y)
{
    if (n1 == 0)
    {
        *x = 0;
        *y = 1;
        return n2;
    }
    uint64_t x1, y1;
    uint64_t gcd = extended_gcd(n2 % n1, n1, &x1, &y1);
    *x = y1 - (n2 / n1) * x1;
    *y = x1;
    return gcd;
}

uint64_t gcd(uint64_t n1, uint64_t n2)
{
    uint64_t gcd = 0;
    
    /* this segfaults 
    for (uint64_t i = 0; i <= n1 && i <= n2; ++i)
    {
        if (n1 % i == 0 && n2 % i == 0)
            gcd_value = i;
    }
    */
   while (n1 != n2)
   {
    if (n1 > n2)
        gcd -= n2;
    else
        gcd -= n1;
   }
    
    return gcd;
}

uint64_t lcm(uint64_t n1, uint64_t n2)
{
    uint64_t lcm = 0;

    uint64_t max = (n1 > n2) ? n1 : n2;
    lcm = max;
    while (lcm % n1 != 0 || lcm % n2 != 0)
    {
        lcm += max;
    }

    return lcm;
}

uint64_t mod_inverse(uint64_t n1, uint64_t n2)
{
    uint64_t x = 0, y = 0;
    uint64_t gcd = extended_gcd(n1, n2, &x, &y);
    if (gcd != 1) {
        // Inverse doesn't exist
        return -1;
    } else {
        // Make x positive
        return (x % n2 + n2) % n2;
    }
}

uint64_t generate_random_prime(void)
{
    uint64_t number = 0;

    FILE *fp = fopen("/dev/urandom", "rt");
    if (fp == NULL)
    {
        (void) fprintf(stderr, "fopen(\"/dev/urandom\") failed\n");
        return 0;
    }

    bool is_prime = false;

    while (!is_prime)
    {
        // Generate random number
        if (fread(&number, sizeof(uint32_t), 1, fp) <= 0)
        {
            (void) fprintf(stderr, "fread() failed\n");
            (void) fclose(fp);
            return 0;
        }

        // Don't bother with miniscule numbers
        if (number <= 2)
            is_prime = false;

        // Is our number a prime number?
        bool found = true;
        for (uint64_t i = 2; i <= sqrt(number); ++i)
        {
            if (number % i == 0)
            {
                found = false;
                is_prime = false;
            }
        }
        is_prime = (found ? true : false);
    }

    (void) fclose(fp);
 
    return number;
}

int main(void)
{
    (void) fprintf(stdout, "Generating RSA keypair...\n");

    FILE *fp_pubkey = fopen("data/pubkey.asc", "wt");
    if (fp_pubkey == NULL)
    {
        (void) fprintf(stderr, "fopen(\"data/pubkey.asc\") failed\n");
        return EXIT_FAILURE;
    }

    FILE *fp_privkey = fopen("data/privkey.asc", "wt");
    if (fp_privkey == NULL)
    {
        (void) fprintf(stderr, "fopen(\"data/privkey.asc\") failed\n");
        return EXIT_FAILURE;
    }

    // Generate P and Q
    uint64_t p = generate_random_prime();
    uint64_t q = generate_random_prime();
    
    // Calculate N
    uint64_t n = p * q;

    // Calculate λ(N)
    uint64_t ln = lcm(p - 1, q - 1);

    // Choose an integer E
    uint64_t e = (uint64_t) pow(2, 16) + 1; // 65537
    if (1 > e > ln) return EXIT_FAILURE;
    //if (gcd(e, ln) != 1) return EXIT_FAILURE;

    // Determine an integer D (is this correct?)
    uint64_t d = mod_inverse(e, ln);

    // Write pub/privkey
    (void) fprintf(fp_pubkey, "e: %" PRIu64 ", n: %" PRIu64 "\n", e, n);
    (void) fclose(fp_pubkey);

    (void) fprintf(fp_privkey, "d: %" PRIu64 ", n: %" PRIu64 "\n", d, n);
    (void) fclose(fp_privkey);

    // TODO: base64 encode the keys and stuff

    return EXIT_SUCCESS;
}
