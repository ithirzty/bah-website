# rand


### seedRandom (func)
<code>seedRandom(i int) </code>
Used for seeding the pseudo-random number generator.
If two instances of a PRNG have the same seed, they will have the same output.


### randomInRange (func)
<code>randomInRange(min int, max int) int </code>
This generates a pseudo random integer in the range of min and max.
*Note: this is not cryptographically safe. This output of this function can be predicted.*
*Note: `max` should not be equal to `0`.*


### cryptoRand (func)
<code>cryptoRand() int </code>
Used for generating a random integer.
The ouput of this function uses the os specified way of generating a random int.
This is slower than the PRNG but cannot be predicted. It does not need to be seeded.


## Example
```bah
 &num;include "iostream.bah"
 &num;include "rand.bah"
 main() {
 i = randomInRange(0, 100)
 s = intToString(i)
 println(s)
 }
```