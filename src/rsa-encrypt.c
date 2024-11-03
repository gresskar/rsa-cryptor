#include "rsa.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        (void) fprintf(stderr, "Usage: %s <message> <public key>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
