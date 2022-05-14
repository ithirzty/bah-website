## Functions
A function is a bit of code that can takes arguments (variables) and return a return value. They can be called anywhere in the program after their declaration and cannot be redeclared. 


### Declaration

You can declare a function in the outter scope (not inside a function) as such:
```bah
myFunc(x int, y int) int {
    z = x + y
    return z
}
```


### Calling

You can call a function as such: <code>result = myFunc(3,4)</code>


### Bindings

You can import a C function as a binding by usssing the **#define** keyword followed by the declaration of the function as such: <code>#define puts(line cpstring)</code>.