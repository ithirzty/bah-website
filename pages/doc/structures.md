<section>
# Structures
A structure has a **name**, some **members** and some optional **methods**.

- [Definition](#definition),
- [Declaration](#declaration),
- [Methods](#methods).

<span id="definition"></span>
## Definition
A structure is defined by the keyword **struct** followed by a list of members and methods.

```bah
<kw>struct</kw> <type>myStruct</type> {
    <var>str</var>: <type>cpstring</type>
    <var>length</var>: <type>int</type>

    <func>set</func>(<var>s</var> <type>cpstring</type>) { <comment>//<a id="get_declaration" href="#methods">What is this?</a></comment>
        <var>this.str</var> = <var>s</var>
        <var>this.length</var> = <func>strlen</func>(<var>s</var>)
    }
}
```

A structure can also inherit members and methods from another struct by using the keyword **extend**:
```bah
<kw>struct</kw> <type>myOtherStruct</type> <kw>extend</kw> <type>myStruct</type> {
    <var>isValid</var>: <type>bool</type>
}
```

A member can have a default value:
```bah
<comment>//...</comment>
<var>str</var>: <type>cpstring</type> = <str>"I'm the default value, please use .set() to replace me!"</str>
<comment>//...</comment>
```

<span id="declaration"></span>
## Declaration
A variable can be declared as a structure multiple ways.

Declaring a variable as a structure **WIHTOUT initiating it** (usefull for C bindings that do not have methods or default values):
```bah
<var>myVar</var> <type>myStruct</type> <comment>//This will not contain the default values and should not have callable methods
```

A struct can also be declared on the stack:
```bah
<var>myVar</var> = <type>myStruct</type>{} <comment>//The braces are required</comment>
```
Or with specific values:
```bah
<var>myVar</var> = <type>myStruct</type>{
    <var>length</var>: <val>4</val>
    <var>str</var>: <str>"test"</str>
}
```
Or with ordered values separated by comas:
```bah
<var>myVar</var> = <type>myStruct</type>{
    <str>"test"</str>,
    <val>4</val>
}
```

If your structure needs to be accessed no matter the scope, with the same values everywhere, you can declare it on the heap with the **new** keyword:
```bah
<var>myVar</var> = <kw>new</kw> <type>myStruct</type> <comment>//There are no braces if there are no values to set</comment>
```
**Note:** The type of *myVar* is no longer *myStruct* but *myStruct&ast;*.

Structures declared on the heap can be declared with values as structures declared on the stack:
With specific values:
```bah
<var>myVar</var> = <kw>new</kw> <type>myStruct</type>{
    <var>length</var>: <val>4</val>
    <var>str</var>: <str>"test"</str>
}
```
Or with ordered values separated by comas:
```bah
<var>myVar</var> = <kw>new</kw> <type>myStruct</type>{
    <str>"test"</str>,
    <val>4</val>
}
```

<span id="methods"></span>
## Methods
A method can be defined as seen above. You can also set methods as a function pointer (usefull for building APIs):
```bah
<comment>//...</comment>
<var>customGet</var>: <kw>function</kw>(<type>myStruct*</type>)<type>cpstring</type>
<comment>//...</comment>
```

Methods access the structure by using the special variable **this**.
the method [.set()](#get_declaration) seen above is not of type *function(cpstring)* but of type *function(myStruct&ast;,cpstring)*.
```bah
<comment>//...</comment>
<func>get</func>() <type>cpstring</type> {
    <kw>return</kw> <var>this.str</var>
}
<comment>//...</comment>
```

They are called as follow:
```bah
<var>myVar</var>.<func>set</func>(<str>"no longer a default value!"</str>)
```

### Example
```bah
<button class="btn coder run">Run</button>

<hash>#import</hash> "iostream.bah"

<kw>struct</kw> <type>myStruct</type> {
    <var>str</var>: <type>cpstring</type> = <str>"I'm the default value, please use .set() to replace me!"</str>
    <var>length</var>: <type>int</type>

    <func>set</func>(<var>s</var> <type>cpstring</type>) {
        <var>this.str</var> = <var>s</var>
        <var>this.length</var> = <func>strlen</func>(<var>s</var>)
    }

    <func>get</func>() <type>cpstring</type> {
        <kw>return</kw> <var>this.str</var>
    }
}

<func>main</func>(<var>args</var> <type>[]cpstring</type>) <type>int</type> {
    <var>myVar</var> = <type>myStruct</type>{}
    <func>println</func>(<var>myVar.str</var>) <comment>//Will print the default value</comment>

    <var>myVar</var>.<func>set</func>(<str>"no longer a default value!"</str>)
    <func>println</func>(<var>myVar.str</var>) <comment>//Will print "no longer a default value!"</comment>

    <var>myOtherVar</var> = <kw>new</kw> <type>myStruct</type>{
        <var>str</var>: <str>"yo"</str>
        <var>length</var>: <val>2</val>
    }
    <func>println</func>(<var>myOtherVar</var>.<func>get</func>()) <comment>//Will print "yo"</comment>
    <kw>return</kw> <val>0</val>
}
```

</section>