# Todo

* Implement tests for permute().
* Input validation for is_permuted(), etc.
* Test validate.h
* Finish tests for random_ints(), etc.
* Refactor validation code to use validate.h


## Components

* Create a README


## Improvements

* Make the distribution of random numbers truely uniform.
* Give random seed in random sampling functions?
  * Not sure if this is a good idea...
* Makefile
  * Auto detection of dependencies
  * Show info messages by default
* Testing
  * Give option for running the dummy Criterion tests.
* Consolidate error codes
* Implement array comparison as quicksort


## Refactoring

* Move array utility functions to another file?


## Features

* Testing and debugging
  * Logging in debug mode
  * Traces of random number selection
* Make project into a shared library
* Make project into a command
  * Sample size, sample range, random seed, outfile as arguments
  * Output one integer per line


## Tests

* Check the randomness of the samplings
* permute.c
  * Write tests for permute_()
  * Test permute() input conditions
  * Test that permute() does indeed permute an array
* utils.c
  * Write tests for array functions
* Write tests for sample_replace().

## Other functions

* Hash table implementation of gen_samples()
* Permute an array
* Sample from a population