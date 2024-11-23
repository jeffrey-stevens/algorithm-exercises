/*
 * Make a random sampling of integers such that no two integers are equal.
 * 
*/

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>


#define ERR_SUCCESS             0
#define ERR_MIN_GT_MAX          1
#define ERR_RANGE_TOO_LARGE     2


typedef struct NumNode Node;

struct NumNode {
    int num;
    Node * left;
    Node * right;
};

typedef Node * Tree;


void fatal_error(char * message) {
    perror(message);
    exit(EXIT_FAILURE);
}


// Returns true if the number was not in the tree.
static bool insert_num(Tree * tree, int num) {
    
    bool found = false;

    if (*tree == NULL) {
        *tree = new_node(num, NULL, NULL);
        found = false;

    } else {
        Node * curr_node = *tree;
        while (curr_node != NULL && found == false) {

            if (num < curr_node->num) {
                if (curr_node->left == NULL) {
                    curr_node->left = new_node(num, NULL, NULL);
                    curr_node = NULL;
                    found = false;
                } else {
                    curr_node = curr_node->left;
                }

            } else if (num > curr_node->num) {
                if (curr_node->right == NULL) {
                    curr_node->right = new_node(num, NULL, NULL);
                    curr_node = NULL;
                    found = false;
                } else {
                    curr_node = curr_node->right;
                }

            } else {
                found = true;
            }
        }
    }

    return found;
}


static Node * new_node(int num, Node * left, Node * right) {

    Node * node = (Node *) malloc(sizeof(Node));
    if (node == NULL) {
        fatal_error("Unable to allocate memory for the binary tree.");
    }

    node->num = num;
    node->left = left;
    node->right = right;

    return node;
}


/*
 * gen_sample()
 * 
 * Generates a random sampling of integers between min_int and max_int such that
 * no two integers are equal.
 * 
 * sample:  The array to store the random sample in.  Must be at least as large
 * as sample_size.
 * 
 * Returns 0 if the sampling was generated successfully; otherwise the error
 * code is returned.
 * 
 * An error code will be generated if min_int > max_int, or if
 * max_int - min_int > RAND_MAX.
 * 
 * Assumes that the caller has already set the random seed.
*/
int gen_sample(int sample_size, int min_int, int max_int, int * sample) {

    if (min_int > max_int) {
        return ERR_MIN_GT_MAX;
    }

    // Want max_int - min_int + 1 <= RAND_MAX.
    // Must rewrite this to avoid overflow...
    if (min_int < 0 && max_int > RAND_MAX + min_int - 1) {
        return ERR_RANGE_TOO_LARGE;
    }

    int range = max_int - min_int + 1;

    Tree tree = NULL;

    int i = 0;
    int num;
    bool found;
    Node * curr_node;

    while (i < sample_size) {
        // FIXME:  This isn't a true random sampling since "range" may not evenly
        // divide RAND_MAX...
        num = min_int + rand() % range;

        found = insert_num(&tree, num);
        if (!found) {
            // Add num to the sample
            sample[i] = num;
            ++i;
        }
    }

    return ERR_SUCCESS;
}