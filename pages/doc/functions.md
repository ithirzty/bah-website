<section>
# Functions
A function has a **name**, some optional **arguments**, an optional **return value** and a **code**.

- [Declaration](#declaration),
- [call](#call),
- [function pointers](#function_pointers),
- [reflection](#reflection).


<span id="declaration"></span>
## Declaration
To define a function, you need to be in the upper (global) scope.
A definition goes as: *function name* followed by the *list of arguments* inside parentheses, the optional *return type* and finally a *code block* inside braces.

Declaring a function with arguments and a return type:
```bah
<func>myAdd</func>(<var>a</var> <type>int</type>, <var>b</var> <type>int</type>) <type>int</type> {
    <kw>return</kw> <var>a</var> + <var>b</var>
}
```
Declaring a function without arguments:
```bah
<func>myFunc</func>() <type>int</type> {
    <kw>return</kw> <val>0</val>
}
```

Declaring a function without return type
```bah
<func>myAdd</func>(<var>a</var> <type>int*</type>, <var>b</var> <type>int</type>) {
    <var>*a</var> = <var>*a</var> + <var>b</var>
}
```

You can define a function to be able to call it before declaring it:
```bah
<hash>#define</hash> <func>myOtherFunc</func>(<var>a</var> <type>int</type>) <type>int</type>

<func>myFunc</func>() <type>int</type> {
    <kw>return</kw> <func>myOtherFunc</func>(<val>43</val>)
}

<comment>//defining myOtherFunc later</comment>
```

<span id="call"></span>
## Calling a function
When calling a function, you must provide all of its arguments in the right order with the right types.
If a function has no return value, it is not considered a value.

Calling a function with multiple arguments
```bah
<comment>//myAdd is defined as myAdd(a int, b int) int</comment>
<var>myInt</var> = <func>myAdd</func>(<val>43</val>, <val>-1</val>)
```

**Note:** You can also call a function at runtime by evaluating its call:
```bah
<button class="btn coder run">Run</button>

<hash>#import</hash> <str>"iostream.bah"</str>
<hash>#import</hash> <str>"eval.bah"</str>

<hash>#eval</hash> println

<func>myAdd</func>(<var>a</var> <type>int</type>, <var>b</var> <type>int</type>) <type>int</type> {
    <kw>return</kw> <var>a</var> + <var>b</var>
}

<hash>#eval</hash> myAdd
<comment>//If you want every function to be evaluable, you can use #evalAll</comment>

<func>main</func>(<var>args</var> <type>[]cpstring</type>) <type>int</type> {

    <comment>//println is defined as println(s cpstring)</comment>
    <var>fnArgs</var> = <type>[]ptr</type>{
        <str>"Hello world!"</str>
    }
    <func>evalCall</func>(<str>"println"</str>, <var>fnArgs</var>) <comment>//will print Hello world!</comment>

    <comment>//myAdd is defined as myAdd(a int, b int) int</comment>
    <var>myInt</var> <type>int</type>
    <func>eval</func>(<str>"myAdd(43, -1)"</str>, <var>&myInt</var>) <comment>//will save the result of myAdd in myInt</comment>

    <func>println</func>(<func>intToStr</func>(<var>myInt</var>)) <comment>//will print 42 </comment>

    <kw>return</kw> <val>0</val>
}
```

<span id="function_pointers"></span>
## Function pointers
A function pointer is a variable that contains a pointer to a function.
It will because of it act as a function.

A function pointer can be either declared and point to no function (usefull for APIs):
```bah
<var>myFuncPtr</var> <kw>function</kw>(<type>int</type>,<type>int</type>)<type>int</type>
```

Or by using a function's name as value:
```bah
<var>myFuncPtr</var> = <func>myAdd</func> <comment>//Note that there are not parentheses because we are not calling the function</comment>
```

Note that a function can be redefined by a const, only one time.
Every call to the targetted function will be redirected to the specified function.
```bah
<comment>//myAdd adds two numbers together while mySub substracts two numbers.</comment>
<kw>const</kw> <var>myAdd</var> = <func>mySub</func> <comment>//Please do not use this 💀 (because of its trolling abilities)</comment>
```

<span id="reflection"></span>
## Reflection
A reflection is a data-structure that enables you to get infos about a variable at runtime.
It can be seem as a variable having reflected consciousness.

```bah
<button class="btn coder run">Run</button>

<hash>#import</hash> <str>"iostream.bah"</str>
<hash>#import</hash> <str>"reflect.bah"</str>

<func>printType</func>(<var>e</var> <type>reflectElement</type>) {
    <func>println</func>(<var>e.name</var> + <str>": "</str> + <var>e.type</var>)
}

<func>main</func>(<var>args</var> <type>[]cpstring</type>) <type>int</type> {
    <var>a</var> = <val>43</val>
    <func>printType</func>(<var>a</var>)
    <func>printType</func>(<str>"I'm a cpstring!"</str>)
    <kw>return</kw> <val>0</val>
}
```

</section>