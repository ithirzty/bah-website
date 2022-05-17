<section>
# Bindings
Bindings are used to include librairies wrote in other languages.
The most common use case of bindings is for using a library written in C. 

- [Heder file](#header_file),
- [types](#types),
- [functions](#functions),
- [structures](#structures).

<span id="header_file"></span>
## Header file
To include a C header file (header.h), you can use **#include**.
**Note:** this will not be parsed by the Bah parser, only by the C compiler.

```bah
<hash>#include</hash> <str>"&lt;myHeader.h&gt;"</str>
```

You may need to bind types/functions/structures that you want to use in Bah.

<span id="types"></span>
## Types
To bind a type, simply use **#define** with &#33;.
**The exclamation mark is mandatory to indicate that this is a binding and not a redefinition of whatever is in the .h file.**
```bah
<hash>#define</hash>! <type>myBindingType</type> <type>myBahType</type>
```

<span id="functions"></span>
## Function
To bind a function, once again use **#define** with &#33;.
**The exclamation mark is mandatory to indicate that this is a binding and not a redefinition of whatever is in the .h file.**
```bah
<hash>#define</hash>! <func>myBindingFunc</func>(<var>arg1</var> <type>int</type>) <type>int</type>
```

<span id="structures"></span>
## Structures
To bind a structure, use **structure** with &#33;.
**The exclamation mark is mandatory to indicate that this is a binding and not a redefinition of whatever is in the .h file.**
```bah
<kw>struct</kw>! <type>myStruct</type> {
    <var>memb1</var>: <type>int</type>
} 
```
</section>