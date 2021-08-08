## exec


### Functions/Structure/Types


##### exec() (function)
Used for executing a binary and passing it arguments as: <code>exec(s cpstring, args []cpstring) int</code>


##### command() (function)
Used for making and initiating a command as: <code>command(s cpstring) command</code>


##### command (struct)
A wrapper used to execute a command and getting back its output. *The command is not interpreted by bash or any command line interpreter.*<br>Its methods are:
- <code>run() cpstring</code> to execute the command and get back its output


Its fields:
- <code>command</code> the current command that will be executed


#### Example
<code>
#include "iostream.bah"
#include "exec.bah"

main() {
    cmd = command("ls ./")
    ouput = cmd.run()
}

</code>