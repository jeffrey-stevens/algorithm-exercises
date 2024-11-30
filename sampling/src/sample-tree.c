/*
 * Make a random sampling of integers such that no two integers are equal.
 * 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sample.h"
#include "utils.h"
#include "error.h"
#include "testing.h"


typedef struct NumNode Node;

struct NumNode {
    int num;
    Node * left;
    Node * right;
};

typedef Node * Tree;


STATIC Node * new_node(int num, Node * left, Node * right) {

    Node * node = (Node *) malloc(sizeof(Node));
    if (node == NULL) {
        fatal_error("Unable to allocate memory for the binary tree.");
    }

    node->num = num;
    node->left = left;
    node->right = right;

    return node;
}

// Returns true if the number was not in the tree.
STATIC bool insert_num(Tree * tree, int num) {
    
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


STATIC void free_node(Node * node) {

    if (node != NULL) {
        free_node(node->left);
        free_node(node->right);

        free(node);
    }

    return;
}


STATIC void free_tree(Tree * tree) {

    Node * root = *tree;
    free_node(root);

    *tree = NULL;

    return;
}


/*
 * gen_sample_tree()
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
int gen_sample_tree(int sample_size, int min_int, int max_int, int * sample) {

    int err_code = validate_inputs(sample_size, min_int, max_int, sample);

    if (err_code != ERR_SUCCESS) {
        return err_code;
    }

    Tree tree = NULL;

    int range = max_int - min_int + 1;
    int i = 0;
    int num;

    while (i < sample_size) {
        // FIXME:  This isn't a true random sampling since "range" may not evenly
        // divide RAND_MAX...
        num = min_int + rand() % range;

        // The following keeps probing until there's no collision...
        // This will work well if sample_size << range, but may be slow if
        // sample_size ~ range.  In either case it's faster than calling rand()
        // repeatedly.
        bool found;
        while ( (found = insert_num(&tree, num)) ) {
            // Try the next number
            // Not sure if this is a valid approach.  The thinking is that if the original
            // number is random, then incrementing the number would essentially be random.
            // This shouldn't result in positional clustering, but it may cause numerical
            // clustering...Choosing another random number would be problematic when
            // The sample size is near the size of the numerical range...
            num = min_int + (num + 1) % range;
        }

        // Add num to the sample
        sample[i] = num;
        ++i;
    }

    free_tree(&tree);

    return ERR_SUCCESS;
}