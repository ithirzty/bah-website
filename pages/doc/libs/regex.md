# regex


### REGEX_TYPE_WORD (const)


### REGEX_TYPE_DIGIT (const)


### REGEX_TYPE_BOUNDARY (const)


### REGEX_TYPE_START (const)


### REGEX_TYPE_END (const)


### REGEX_TYPE_TEXT (const)


### REGEX_TYPE_GROUP_START (const)


### REGEX_TYPE_GROUP_END (const)


### REGEX_TYPE_SPACE (const)


### REGEX_TYPE_ALL (const)


### REGEX_TYPE_RANGE (const)


### regexRange (struct)
An internal structure implementing a range quantifier.


### regexToken (struct)
An internal structure implementing a single regex token.


### matchToken (func)
<code>matchToken(tp ptr, c char) int </code>
An internal function that tries to match a character to a token.


### regex (struct)
A wrapper for a regex parser.
This is the ouput of compileRegex().
This structure should not be used by multiple functions at the same time.
__Its methods are:__
- <code>**procesString**(cps cpstring, si int) int </code> An internal function to process a string.
This should not be used if you are not trying to extend the implementation of regexes. 
- <code>**matchString**(s cpstring) int </code> This tries to match a string to a regex. If the regex matches the string, this will return 1.
- <code>**findAllSubstring**(s cpstring) []cpstring </code> This tries to match every group of the regex to a substring and returns an array of cpstring.


### compileRegex (func)
<code>compileRegex(cpexpr cpstring) regex* </code>
This is used to parse a regex expression and returns a pointer to its instance.


## Example
<code> #include "iostream.bah"
 #include "string.bah"
 #include "regex.bah"
 #include "array.bah"
 main(){
 regex = compileRegex("\\w+(\\d)\\w*B(.{1,3})")
 if regex == 0 {
 panic("WRONG REGEX SYNTAX")
 }
 test = "dsasd65gdfdfgBf"
 if regex.matchString(test) {
 println("It matches")
 res = regex.findAllSubstring(test)
 i = 0;for i < len(res) {
 s = res[i]
 println(s)
 i++
 }
 } else {
 println("Sad little string got no match...")
 }
 }

</code>