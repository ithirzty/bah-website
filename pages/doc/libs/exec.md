# exec


### command (struct)
A wrapper for executting command.
This is will return the output of the command.
__Its methods are:__
- <code>**run**() cpstring </code> To run the command.
This returns a cpstring containning the output of the command.


### command (func)
<code>command(s cpstring) command </code>
To initiate a command.
You must specify the command as a cpstring.


### exec (func)
<code>exec(s cpstring, args []cpstring) int </code>
Exec will execute a binary/command with the specified arguments passed to it.
Note that this will take the current proccess.


## Example
<code></code>