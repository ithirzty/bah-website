## Macros
A macro is like a shortcut that you define for the compiler.
A macro is defined using the **#macro** keyword as such: <code>#macro from => to</code>
Inside a macro, you can use arguments. If your argument takes multiple tokens, you will need to add a **&ast;** after the argument.


<code>
#macro a++ => a=a+1
#macro a += b* => a = a + b

main() {
    i = 0
    i++
    if i == 1 {
        ...
    }
    i += 4 + 4
}

</code>