## Bah's Syntax
**Bah's syntax is a mix of [Go](https://golang.org/) and [C](https://fr.wikipedia.org/wiki/C_%28langage%29) syntax with it's own touch.**
Here is a hello world in bah:
```bah
#include "iostream.bah"
main() {
    println("Hello world")
}
```
> The standard in Bah is **camel case** where there should be a space.

### It supports :
- [variables](./variables)
- [types](./types)
- [strings](./string)
- [structures](./structs) (that can act as objects)
- [functions](./functions)
- [conditions](./conditions)
- [loops](./loops)
- [casts](./casts)
- [macros](./macros)
- [comments](./comments)
- [arrays](./arrays)

### Additional Features
- You can put multiple lines in one by using a <code>**;**</code> as such: <code>println("hello");println("world")</code>

### Librairies
*If you had to do everything from scratch, it would not be easy.*
That is why the [bah compiler](./compiler) comes with [standard librairies](./std_libs)

### C Librairies
If you want to import a C library, you can use the **#include** keyword as such: <code>#include "&lt;stdlib.h&gt;"</code>.
If you need to link the program with a C library, use the **#cLib** keyword followed by the argument that needs to be passed to the compiler/linker as such: <code>#clib "lm"</code> for the maths library.