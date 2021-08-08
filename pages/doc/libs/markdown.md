## markdown.bah
Note that this whole documentation is parsed in real-time by the markdown library.


### Functions/Structure/Types


##### parseMarkdown (function)
Used for parsing markdown as: <code>parseMarkdown(text cpstring) markdown</code>


##### parseMarkdownInline (function)
Used for parsing inline markdown (bold, italic, links, images...) as: <code>parseMarkdownInline(line string&ast;) string&ast;</code>


##### markdown (struct)
Contains the parsed markdown.<br>Its methods are:
- <code>html() cpstring</code> to get the parsed markdown as html


#### Example
<code>
#include "iostream.bah"
#include "markdown.bah"

main() {
    
    article = "# How to write Bah code?


&gt; It's not that hard


Simply &ast;&ast;smash&ast;&ast; your keyboard!
"

    md = parseMarkdown(article)

    htmlCode = md.html()

    println(htmlCode)

}
</code>