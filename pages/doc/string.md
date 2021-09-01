## Strings
Strings are handled differently by many languages because they are an odd data type.


### Built-in strings

The built-in data type for strings in bah is **cpstring** but because a string is much more than a list of characters, the standard library **string.bah** allows you to use the **string** structure. It makes string manipulation much more easy. You can use it as such:
```bah
#include "iostream.bah"
#include "string.bah"
main() {
    a = string("I'm a string.") //declaring 'a' as a string
    
    length = intToString(a.length) //converting length of 'a' into a string
    length.prepend("String length is ")
    
    println(a) //printing a
    
    println(length) //printing it's length

    a.append(" And much more.") //concatenating text to a

    println(a) //printing a
}
```

### High-performance operations
For faster operations, you can use the [rope](./libs/rope) structure that allows you to do really
fast string concatenation (addition). It can be between 1.5x to >20x faster than concatenating
cpstrings.

##### Multi-line strings

A string can be declared over multiple lines a such:
```bah
myString = "
I'm
a
test
"
```