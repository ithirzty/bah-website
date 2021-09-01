## Casting
A cast is used to use a variable of a certain type as if it was of antoher's.
Casts can only be used on a variable (cannot be used on a function call).
You can cast a variable using <code>&lt;type&gt;</code> before a variable as such: 
```bah
myFunction(a float) {
    ...
}
main() {
    i int = 0
    myFunction(&lt;float&gt;i)
}
```

##### Casting a variable is not the same thing as converting a variable.