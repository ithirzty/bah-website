## Loops
Loops are a form of recursion and are a building block of computer sciences.
There is only one way of doing loops in Bah, using the **for** keyword.
As long as the expression is true, the code inside of the for loop will be executed.

```bah
#include "iostream.bah"
#include "string.bah"

main() {
    i = 0; for i < 10 {
        println("i: "+intToStr(i))

        i = i + 1
    }
}
```