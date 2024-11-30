#define PERM_ERR_SUCCESS 0;
#define PERM_ERR_NEG_SIZE 1;
#define PERM_ERR_NULL_ARRAY 2;
#define PERM_SIZE_TOO_LARGE 3;

#define PERMUTATION_MAX_SIZE \
    (RAND_MAX == INT_MAX ? INT_MAX : RAND_MAX + 1)


int permutation(int n, int * array);