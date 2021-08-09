# markdown


### appendCharArr (func)
<code>appendCharArr(a []char, b []char) </code>
An internal function used to append the array of chars b to the array a.


### markdownLine (struct)
An internal structure to define a single line of markdown by its type.


### markdown (struct)
A wrapper for the markdown parser.
__Its methods are:__
- <code>**str**() cpstring </code> To retreive the document as lines without transpilling it to any other language.
This is mainly for debugging/verbose purposes.
- <code>**html**() cpstring </code> To transpille your markdown document as a html document.
This will return a cpstring containning your markdown document as html code.


### parseMarkdownInline (func)
<code>parseMarkdownInline(l string) string </code>
An internal function to parse every inline element of a line.
Inline elements are syntax features that do not impact the entire line.
For instance, the bold delimiter is an inline feature, the hastag at the biginning of a line is not.


### parseMarkdown (func)
<code>parseMarkdown(a cpstring) markdown </code>
To parse a markdown document.
This will return a markdown structure that can be then transpilled into html.


### escapeMarkdownHTML (func)
<code>escapeMarkdownHTML(s string&ast;) </code>
This escapes every character that the markdown parser could take as markdown code.
It is not meant to be ran on your main markdown document but rather on some parts that you dont want to be taken as markdown.


## Example
```bah
 &#35;include "iostream.bah"
 &#35;include "markdown.bah"
 main() {
 article = "&#35; How to write Bah code?

 &gt; It's not that hard

 Simply &ast;&ast;smash&ast;&ast; your keyboard
 "
 md = parseMarkdown(article)
 htmlCode = md.html()
 println(htmlCode)
 }
```