# path


### absPath (func)
<code>absPath(path cpstring) cpstring </code>
Used for getting the absolute path of a file/directory.
An absolute path is a path that goes all the way to the root.


### getCurrentPath (func)
<code>getCurrentPath() cpstring </code>
To get the working path.
The working path is the path to the directory that is defined as **./**.


## Example
<code> #include "iostream.bah"
 #include "path.bah"
 main() {
 currentPath = getCurrentPath()
 println(currentPath)
 filePath = absPath("./file.txt")
 println(filePath)
 }
</code>