## regex.bah


### MISSING
- Cannot put quantifier on a group
- findAllString() method


### Functions/Structure/Types


##### compileRegex (function)
Used for compiling a string into a regex. Will return a pointer to the regex as: <code>compileRegex(cpexpr cpstring) regex&ast;</code>


##### regex (struct)s
A implementation of the regex standard.<br>*Not yet completed*<br>Its methods are:
- <code>matchString(s cpstring) int</code> matches a string to a regex, returns weither or not it succeeded
- <code>findAllSubstring(s cpstring) array</code> matches a string to a regex, returns every token submatch


#### Example
<code>
#include "iostream.bah"
#include "string.bah"
#include "regex.bah"
#include "array.bah"

main(){

        regex = compileRegex("\\w+(\\d)\\w&ast;B(.{1,3})")
        if regex == 0 {
            panic("WRONG REGEX SYNTAX")
        }

        test = "dsasd65gdfdfgBf"

        if regex.matchString(test) {
            
            println("It matches!")
            
            res = regex.findAllSubstring(test)
            i = 0;for i < res.length {
                s string&ast; = res.get(i)
                println(s)
                i++
            }

        } else {
            println("Sad little string got no match...")
        }

}
</code>