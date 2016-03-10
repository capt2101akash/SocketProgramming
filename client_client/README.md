It is basically a client to client communication module.
To avail this feature of communication, both the server and client code should be run on individual client.
Server program of every client will broadcast it's IP and the other clients will then send a request to connect to it.
Server will then receive the list of requests made by other IPs and the server will connect to one of the client.
After connecting to this client they will communicate with each other.And the other client will get disconnected from the network after some time of inactivity.
All will use the same port like ssh use 22, this protocol will also use only a single port.
Like:


client 1 :-

Server is running on 2022 port no.

client 2 :-

Server is running on 2022 port no.

client 3 :-

Server is running on 2022 port no.

So in the above example if client1 wants to communicate with client2 or client3, then he will first broadcast it's ip and name but at present I did with only IP. So client2 and client3 will then send request to connect and client1 will get the requested IP, then from the list client1 chooses the IP it wants to communivate with and start communication.

In this way one can do communication using three different clients.
 
