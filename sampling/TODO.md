# Todo

* Implement tests for permute().
* Add tests to test-utils.c
  * Test a large array (using a regular pattern)


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

* Set up mechanism for testing internal (static) functions
* Check the randomness of the samplings
* permute()
  * Test the input conditions
  * Test that permute() does indeed permute an array
  * Verify that permute() does work with duplicates (unlike permutation())


## Other functions

* Hash table implementation of gen_samples()
* Permute an array
* Sample from a population