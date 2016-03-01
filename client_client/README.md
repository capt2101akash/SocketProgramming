It is basically a client to client communication module.
To avail this feature of communication, both the server and client code should be run on individual client.

Like:


client 1 :-

Server is running on 2021 port no.

client 2 :-

Server is running on 2022 port no.

client 3 :-

Server is running on 2023 port no.


So if client1->client2 comuunication need to be happened then client1's client should connect to client2's server using port 2022 or client2's client should connect to client1's server using port 2021.

In this way one can do communication using three different clients.
 
