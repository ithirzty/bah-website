# string


### charToString (func)
<code>charToString(c char) cpstring </code>
Used for converting a char into a cpstring of length 1.


### isUpper (func)
<code>isUpper(c char) int </code>
Used to know if a char is upper-cased, will return 1 if true.


### isLower (func)
<code>isLower(c char) int </code>
Used to know if a char is lower-cased, will return 1 if true.


### isLetter (func)
<code>isLetter(s char) int </code>
Used to know if a char is a letter, will return 1 if true.


### isNumber (func)
<code>isNumber(c char) int </code>
Used to know if a char is a number, will return 1 if true.


### isAlphaNumeric (func)
<code>isAlphaNumeric(s char) int </code>
Used to know if a char is alphanumeric, will return 1 if true.
Alphanumeric means letter or number.


### isSpace (func)
<code>isSpace(c char) int </code>
Used to know if a char is a space / new line character, will return 1 if true.


### string (struct)
A string wrapper to make string manipulation easier.
__Its methods are:__
- <code>**set**(s cpstring) </code> Sets the string value to the specified cpstring.
- <code>**append**(s cpstring) </code> Appends the specified cpstring to the string.
- <code>**prepend**(s cpstring) </code> Prepends the specified cpstring to the string.
- <code>**charAt**(i int) char </code> Returns the char at the specified position of the string.
- <code>**compare**(s cpstring) int </code> Used to know if the content of the string is the same as the specified cpstring, returns 1 if true.
- <code>**str**() cpstring </code> Used for getting the content of the string as a cpstring.
- <code>**replace**(nd cpstring, rl cpstring) </code> Used to replace a substring by another.
- <code>**count**(need cpstring) int </code> Used to count the number of substring(s).
- <code>**hasPrefix**(need cpstring) int </code> Used to know if the string as a specified prefix, returns 1 if true.
- <code>**hasSuffix**(need cpstring) int </code> Used to know if the string as a specified suffix, returns 1 if true.
- <code>**trim**() </code> Used for trimming spaces at the beginning of the string.
- <code>**trimLeft**(s int) </code> Used to trim a specified number of charcaters from the beginning of the string.
- <code>**trimRight**(s int) </code> Used to trim a specified number of charcaters from the end of the string.


### string (func)
<code>string(s cpstring) string </code>
Used to make a string wrapper from a specified cpstring.


### arrToStr (func)
<code>arrToStr(arr []char) cpstring </code>
Used to convert an array of characters to a cpstring.


### strToArr (func)
<code>strToArr(str cpstring) []char </code>
Used to convert a cpstring into an array of characters.


### intToString (func)
<code>intToString(i int) string </code>
Used to convert an integer into a string.
*It returns a string, not a cpstring*


### stringToInt (func)
<code>stringToInt(s string) int </code>
Used to convert a string into an integer.
*It takes a string, not a cpstring*


### splitString (func)
<code>splitString(s string, sp cpstring) []string </code>
Used for splitting a string into multiple substrings delimited by the specified delimiter.


### joinString (func)
<code>joinString(a []string, sep cpstring) string </code>
Used for joinning an array of strings with a specified separator into a string.


### splitStringBefore (func)
<code>splitStringBefore(s string, sp cpstring) cpstring </code>
Used to get the content of a string before a certain delimiter.


### toLower (func)
<code>toLower(s string) string </code>
Used to lowe-case a string.


## Example
<code>#include "iostream.bah"
#include "string.bah"

 main() {
     a = string("I code in ")
     a.append("Bah")

     println(a)

     age = 16
     b = intToString(age)
     b.prepend("I'm ")
     b.append(" years old")
     println(b)
 }
</code>