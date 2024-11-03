#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

uint64_t gcd(uint64_t n1, uint64_t n2);
uint64_t lcm(uint64_t n1, uint64_t n2);
uint64_t mod_inverse(uint64_t n1, uint64_t n2);
uint64_t generate_random_prime(void);
