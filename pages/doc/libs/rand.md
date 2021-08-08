## rand.bah


### Functions/Structure/Types


##### seedRandom (function)
Used for seeding the pseudo random generator as: <code>seedRandom(seed int)</code>


##### randomInRange (function)
Used for generating a pseudo random int inside the specified range as: <code>randomInRange(min int, max int) int</code><br> *Warning: if not seeded, the pseudo number generator is seeded with the current timestamp.*


##### cryptoRand (function)
Used for generating a random int, random enough to be used in cryptographic use as: <code>cryptoRand() int</code>


#### Example
<code>
#include "iostream.bah"
#include "rand.bah"

main() {
    i = randomInRange(0, 100)

    println(intToString(i))

}
</code>