## Conditions
A condition is a way of branching the current thread only if the condition is respected.
You can use the **if** and **else** keyword to build your program logic's.
The logic operators available are:
- **==** is equal
- **!=** is not equal
- **>** is greater than
- **<** is less than
- **<=** is less than or equal to
- **>=** is greater than or equal to

<code>
#include "iostream.bah"

main() {
    a = 0
    if a == 4 {
        println("a is equal to 4")
    } else if a == 3 {
        println("a is equal to 3")
    } else {
        println("a is neither equal to 4 or 3")
    }
}
</code>