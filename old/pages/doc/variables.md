## Variables
In bah, variables are strictcly typed at compile time.


### Declaration

When declaring a variable, you can
- declare it without a value but with a type
```bah
a int
```
- declare it without a type but with a value
```bah
a = 0
```
- or you can do both
```bah
a int = 0
```

> Can I change the type of a variable ?
You can [cast](./casts) a variable or use a function to convert it.


### Pointers

You can declare a variable as pointer by adding asterisc at the end of its type: <code>a int&ast;</code>
You can also pass a variable pointers by using an ampersand: <code>&a</code>
You can set the value of a pointer by using a unary (&ast;): <code>&ast;a</code>


### Const
You can declare a const, *a variable that cannot change and is staticly compiled into the program*.
```bah
const MyConstant = 1
```