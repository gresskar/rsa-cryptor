#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/random.h>
#include <time.h>
#include <gmp.h>

bool is_prime(mpz_t number);
void generate_prime(mpz_t number, uint16_t bitsize);
int main(int argc, char **argv);
