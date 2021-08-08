# reflect


### reflectedPointer (struct)
A reflected pointer is a pointer that implements the principle of reflection.
The structure contains the pointer (.ptr field) and its type as a string (.type field).
__Its methods are:__
- <code>**isPointer**() int </code> This checks if the type of the reflected pointer is actually a pointer or not.


### newReflectPointer (func)
<code>newReflectPointer(val ptr, type cpstring) reflectedPointer </code>
THIS IS AN INTERNAL FUNCTION, do not use it. **Use the <code>#reflect(ptr)</code> macro instead**.
This makes a reflected pointer from a value and a type as a string.
If the variable passed to the #reflect() macro is of type ptr, the macro will not guess its type.


## Example
<code> #include "iostream.bah"
 #include "reflect.bah"
 #include "string.bah"
 printReflected(p reflectedPointer) {
     if p.type.compare("int") {
         i int = <int>p.ptr
         s = intToString(i)
         println(s)
     } else if p.type.compare("cpstring") {
         s cpstring = p.ptr
         print(s)
     } else {
         panic("This type isn't supported by the prinReflected function.")
     }
 }
 main() {
     i = 54
     printReflected(#reflect(i))
 }
</code>