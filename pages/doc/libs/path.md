## path.bah


### Functions/Structure/Types


##### absPath (function)
Used for getting the absolute path of a file/folder as: <code>absPath(path cpstring) cpstring</code>


##### getCurrentPath (function)
Used for getting the current working directory as: <code>getCurrentPath() cpstring</code>


#### Example
<code>
#include "iostream.bah"
#include "path.bah"

main() {

    currentPath = getCurrentPath()
    println(currentPath)

    filePath = absPath("./file.txt")
    println(filePath)

}
</code>