# Server-client-c
Here you can see client-server application for Linux with error-logging.  
<b>Advantages</b>: 
* several clients can connect to the server and send files at once
* a wrapper function for error handling was made for each server-client interaction function
* the server places on disk all files received from clients with unique names that are a function of the client port  

<b>Usage:</b>  

In the project directory, run the following commands to get the executable files  

* `gcc -W -Wall -Wextra -Werror -Wunused -I include/ -o server src/server.c src/errproc.c`
* `gcc -W -Wall -Wextra -Werror -Wunused -I include/ -o client src/client.c src/errproc.c`

To run applications, enter:

* `./server <server port> <folder to put files in>`
* `./client <server ip> <server port> <file to send>`

For convenience, examples of client files to send (`source.txt` and `source2.txt`) and the server directory for client files are provided (`client_dir`)