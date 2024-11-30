# Todo

* Implement range tests for permutation().

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


## Features

* Testing and debugging
  * Logging in debug mode
  * Traces of random number selection
* Make project into a shared library
* Make project into a command
  * Sample size, sample range, random seed, outfile as arguments
  * Output one integer per line


## Tests

* Set up mechanism for testing internal functions
* Check the randomness of the samplings
* permutation()
  * Test if setting seed generates same permutation
  * Fail if large n produces the trivial permutation?
  * Fail if running permutation() twice in a row generates the same permutation (for large n)


## Other functions

* Hash table implementation of gen_samples()
* Generate random permutations
* Sample from a population