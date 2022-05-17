<section>
# Variables
A variable has a **name**, a **type** and a **value**.

- [Declaration](#declaration),
- [types](#types),
- [lifetime](#lifetime).


<span id="declaration"></span>
## Delcaration
To declare a variable, you must provide a name and an optional type that can be implicit with a value.

To declare **a** as a number, you can do:
```bah
<var>a</var> <type>int</type>
```
or:
```bah
<var>a</var> = <val>0</val>
```

If the declared variable is not the same type as the value, you can force its type:
```bah
<var>a</var> <type>int</type> = <val>0.0</val>
```

If the variable is already declared but the value is not the same as the variable's type, yo can cast the value:
```bah
<var>a</var> = &lt;<type>int</type>&gt;<val>0.0</val>
```

A variable can also be defined (not declared) as a constant value. Note that a const has no scope and cannot be redefined.
```bah
<kw>const</kw> <var>myConst</var> = <val>43</val>
```

<span id="types"></span>
## Types
A type can be defined as a [structure](./structures) or as a primitive.
Here is a list of all the primitive types:

- **int**, **int32** (64 and 32 bits integers)
- **uint**, **uint32** (64 and 32 bits unsigned integers)
- **float**, **float32** (64 and 32 bits floatting point numbers)
- **ufloat**, **ufloat32** (64 and 32 bits unsigned floatting point numbers)
- **char**, **byte**, **ushort** (char represents a character [-128, 128], byte [0, 255], ushort 16 bit unsigned integer)
- **cpstring**, **buffer:&lt;length&gt;** (string terminated by a null character, buffer is a cpstring allocated on the stack, faster but unaccessible at the end of declaration scope)
- **bool** (true or false)
- **ptr** (a generic pointer with no type safety)
- **[]&lt;type&gt;** (an array)
- **chan:&lt;type&gt;** (a thread safe channel)
- **map:&lt;type&gt;** (a map, basically an array with cpstring instead of int as index)

<span id="lifetime">
## Lifetime
A variable can be either declared on the stack or on the heap.
A pointer to a value declared on the stack will be invalid once the scope of the pointed variable ends.
A pointer to a value declared on the heap will always be valid only up to the point that there is no pointer in memory that may point to the allocated memory block.

**Exception:** when the scope of a buffer ends, its value will no longer be accessible. You may need to duplicate it using something like: 
```bah
<var>myStr</var> = <func>&#95;&#95;STR</func>(<var>myBuffer</var>)
```

</section>