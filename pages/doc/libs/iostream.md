## iostream.bah


### Functions/Structure/Types


##### stdinput (function)
Used for getting line inputed in the console by the user as: <code>stdinput(len int) cpstring</code>


##### print/println (function)
Used for printing to the console (the ln variation adds a newline character to the end) as: <code>print(s cpstring)</code>


##### panic (function)
Used for printing a message then exiting as an error as: <code>panic(e cpstring)</code>


##### listFiles (function)
Used for listting every files of a directory as: <code>listFiles(dir cpstring) []cpstring</code>


##### fileStream (struct)
An interface with the file system.<br>Its methods are:
- <code>open(path cpstring, mode cpstring)</code> to open a file. The openning mode are the same as in C (r, w, a, r+, a+, w+). **When oppening a file, you will need to close it.**
- <code>getSize() int</code> to get the size of the current openned file in bytes
- <code>readContent() cpstring</code> to get the content of the current openned file
- <code>rewind()</code> to rewind the current openned file
- <code>getChar() char</code> to get the content of the current openned file
- <code>createFile(path cpstring)</code> to create a file
- <code>writeFile(content cpstring)</code> to set the content of the current openned file
- <code>close()</code> to close the handle to the file.


#### Example
<code>
#include "iostream.bah"

main() {
    
    fs = fileStream{}
    fs.open("./myFile.txt", "r")
    fileContent = fs.readContent()
    println(fileContent)
    fs.close()

}
</code>