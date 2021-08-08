# http


### http_url (struct)


### parseUrl (func)
<code>parseUrl(cps cpstring) http_url {   </code>
Used for parsing an URL.


### http_server (struct)
A wrapper for a http web server.
__Its methods are:__
- <code>**handle**(connfd int) int </code> The handle to pass when receiving connections.
- <code>**listenAndServe**() </code> To start the server.
- <code>**stop**() </code> To stop the server.


### http_request (struct)
A wrapper for requests.
When receiving a connection, you will be able to retreive the passed headers, path... from the client.
__Its methods are:__
- <code>**getHeader**(name cpstring) cpstring </code> Get a header by name.


### http_response (struct)
A wrapper for HTTP responses. You will be able to set/retreive the headers sent/receive.
You will encounter this when doing a request or sending a response to the client.
__Its methods are:__
- <code>**send**() </code> Send the response.
*Use it only when sending response to the client from a http_server*.
- <code>**setHeader**(name cpstring, value cpstring) </code> To set a header by name.
- <code>**getHeader**(name cpstring) cpstring </code> To get the value of a header by name.
- <code>**write**(content cpstring) </code> To append to the body of the response.


### makeRawHttpsRequest (func)
<code>makeRawHttpsRequest(host cpstring, message cpstring) cpstring </code>
Used for making TLS requests.
*This is an internal function, you should know what you're doing if you decide to use it.*


### makeRawRequest (func)
<code>makeRawRequest(method cpstring, u http_url, args []cpstring) http_response </code>
Used for making any request.
Method is either http or https. The arguments (args) are the variables to pass (can be post or get variable) formatted as: name=value.


### get (func)
<code>get(url cpstring) http_response </code>
Used for making simple get request.


### post (func)
<code>post(url cpstring, args string) http_response </code>
Used for making simple post request with variables (args) formatted as name=value.


## Example
<code> #include "http.bah"


 server(serv http_server*, connfd int) int {

     request = http_request(connfd)
     response = http_response(connfd)

     response.setHeader("Content-Type", "text/html")

     response.write("Current path:")
     response.write(request.path)

     response.write("\nIt works!")
     response.send()

     return 0
 }

 main() {
  
     s = http_server{}
     s.port = 8080
     s.handle = &server
     s.listenAndServe()

 }
</code>