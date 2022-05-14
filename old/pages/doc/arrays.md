### Arrays
An array is a data-type that can store multiple values that are indexed.


#### Declaration
An array is declared as such: <code>arr = []cpstring</code>.


#### Usage
- To set a value by index, do the following: <code>arr[0] = "I'm a value"</code>.
- To get a value by index, usse the array as such <code>arr[0]</code>.
- To get the current length of an array (not to confuse with the allocated size), use the function <code>len(myArray)</code>.
- To append to an array, use the following code: <code>arr[len(arr)] = "I'm another value"</code>.


#### Example
```bah
#include "iostream.bah"
main() {
    arr = []cpstring{
        "this",
        "is",
        "a"
    }
    arr[3] = "test"

    i=0;for i < len(arr) {
        println(arr[i])
        i++
    }

}
```