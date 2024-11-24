# General notes

## gen_sample() test coverage

* Relationship between min_int and max_int
  * Fails when min_int > max_int.
  * Succeeds when min_int = max_int and generates a single number (min_int).

* Relationship between the number range and numerical limits
  * Fails when the range is greater than RAND_MAX. 
  * Succeeds when the range is equal to RAND_MAX.

* Relationship between the number range and the sample size
  * Fails when the sample size is larger than the range.
  * Succeeds when then sample size is the same size of the range, and produces all numbers in the range.

* Number generation
  * Succeeds in generating sequences such that each number is unique.
  * Succeeds to generate numbers in the correct range.
    * For range = 1.
    * For other small ranges.
    * For various values of min_int/max_int.
      * min_int = INT_MIN
      * max_int = INT_MAX
  * The generated sequence is indeed random.
  * That different sequences are generated with different seeds.

* The samples array
  * Succeeds in generating the correct number of samples for various sample sizes.
    * Will work with a sample size of 0.  Does not modify the array.
    * Fails when given a negative sample size.
    * Succeeds to generate an array of size RAND_MAX.
    * Fails to generate an array of size RAND_MAX + 1.
      * (This would also violate the range > RAND_MAX condition).
  * Works if the array size is larger than the sample size.
    * Writes to the first n entries.
    * Doesn't write to the other entries.
  * Handles being given a NULL pointer.