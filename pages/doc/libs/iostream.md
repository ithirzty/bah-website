# iostream


### stdinput (func)
<code>stdinput(len int) cpstring </code>
Returns the text inputted by the user inside the terminal.
The returned cpstring will have the specified length.


### print (func)
<code>print(s cpstring) </code>
Prints text to the terminal.


### println (func)
<code>println(s cpstring) </code>
Prints text to the terminal and adds a line return at the end.


### panic (func)
<code>panic(e cpstring) </code>
Print an error to the terminal and exits the program.


### fileStream (struct)
A wrapper that makes file manipulation easier.
*Note: after openning a file, you will need to close it.*
**Warning:** fileStream can be many, many times slower than fileMap.
So it is recommended to **use fileMap as much as possible**.
__Its methods are:__
- <code>**isValid**() int </code> Checks if the current opened file is valid or not.
- <code>**open**(path cpstring, mode cpstring) </code> Opens a file by its name.
The differents modes can be found [here](https://koor.fr/C/cstdio/fopen.wp).
- <code>**close**() </code> Closes an opennend connection to a file.
- <code>**getSize**() int </code> Returns the size of a file in bytes.
- <code>**readContent**() cpstring </code> Returns the content of the opened file.
- <code>**rewind**() </code> Sets the reading cursor to the beginning of the file.
- <code>**getChar**() char </code> Returns a char at the current reading cursor in the file and moves the reading cursor to the next char.
- <code>**createFile**(path cpstring) </code> Creates a file by name.
- <code>**writeFile**(content cpstring) int </code> Writes the opened file with the specified content.


### fileMap (struct)
A wrapper to make file direct operation, wihtout needing to write file on changes.
**This is way faster than the fileStream** but every modification made to the returned string will be directly made to the file.
__Its methods are:__
- <code>**open**(fileName cpstring) cpstring </code> To open a file inside the fileMap.
It returns the content of the file as cpstring.
- <code>**isValid**() int </code> Check if file is valid or not.
- <code>**close**() </code> To close a file after you are done working on it.


### listFiles (func)
<code>listFiles(dir cpstring) []cpstring </code>
Returns a list of all files found inside the specified directory.


### fileExists (func)
<code>fileExists(path cpstring) int </code>
Checks if a file exists.


## Example
```bah
 &num;include "iostream.bah"
 main() {
 fs = fileStream{}
 fs.open("./myFile.txt", "r")
 fileContent = fs.readContent()
 println(fileContent)
 fs.close()
 }
```