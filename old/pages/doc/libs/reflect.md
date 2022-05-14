# reflect


### reflectElement (struct)
The reflection of an element (a var).
A reflection is a wrapper for informations on the data-type of the element.
This is used for getting compile-time informations at runtime.
**Usage: **
Simply put reflectElement as the type of a function argument.
The argument will then be reflected inside the function.


## Example
```bah
 &num;include "iostream.bah"
 &num;include "reflect.bah"
 reflectedPrint(e reflectElement) {
     if e.type == "int" {
         ip int&ast; = e.value
         println(intToStr(&ast;ip))
     } else if e.type == "cpstring" {
         //WARNING: if the str is the member of a struct, it will return a pointer to the cpstring.
         sp cpstring = e.value
         println(sp)
     }
 }
 main(args []cpstring) int {
     a = 54
     b = "test"
     reflectedPrint(a)
     reflectedPrint(b)
     return 0
 }
```