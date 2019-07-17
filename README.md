# C-Chat-Application
Chat application built using C Programming language using Sockets...

# Usage

Run the Server.c file first on your terminal running the latest version of GCC Compiler with the following command line parameters:

                                            gcc Server.c -o Server
                                            ./Server 8080

This will set up the Server... Lets break this down:
  - Create a Socket and Binds it to the Port number: 8080
  - Listens for any incoming connections from clients


Now from another terminal window or another system's terminal connected to the same Network run the following:
                                            
                                            gcc Client.c -o Client
                                            ./Client (server_ip) 8080

This will set up the Client, make sure that you find the IP Address of your server and replace that with server_ip...

Note that the Server has to start chatting first and it's one way communication channel...

# Contributors

Valluri Pavan Preetham (@ppvalluri09)
