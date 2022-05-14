## Structures
A structure is a type that has fields (members) and methods (functions).


### Declaration

You can declare a structure as such:
```bah
struct myStructType {
    myNumber: int
    
    myMethod(x int) {
        this.myNumber = x
    }
}
```


### Fields

Fields are declared as such <code>name: type</code>.


#### Default values

A filed can have a default value. You can declare it as such <code>name: type = defaultValue</code> inside the structure declaration.


### Methods

A method can take and return arguments as a normal function. The only difference is the **this** variable that refers to its parent structure. *To be able to call the methods and use default values, you need to initialize the structure on a variable (using myStructType{} or new myStructType)*.


### Example
```bah
struct myStructType {
    myNumber: int
    
    myMethod(x int) {
        this.myNumber = x
    }
}

main() {
    myStruct = myStructType{}
    myStruct.myNumber = 3
    myStruct.myMethod(6)
}
```

### Structure pointers


You can initialize a struct pointer using the **new** keyword as such:
```bah
main() {
    myStruct = new myStructType
}
```