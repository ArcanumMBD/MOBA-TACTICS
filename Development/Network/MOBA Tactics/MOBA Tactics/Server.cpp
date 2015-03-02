#include "Server.h"

int recievedByteCount = 0;
IPaddress ip;
TCPsocket server;
TCPsocket client;

Server::Server(unsigned int portGiven, unsigned int bufferSizeGiven, unsigned int maxSocketAllowed)
{
	// Create the items nessecary for a server 
	// as well as open the servers Socket for client connections.

	port = portGiven;
	bufferSize = bufferSizeGiven;
	maxSockets = maxSocketAllowed;
	maxClients = maxSocketAllowed - 1;

	clientSocket = new TCPsocket[maxClients];
	socketIsFree = new bool[maxClients];
	buffer = new char[bufferSize];

	clientCount = 0; // on creation of server nothing is connected to it.

	// Creating the SocketSet with the Max Sockets number
	socketSet = SDLNet_AllocSocketSet(maxSockets);

	// error catching goes here

	for (int loop = 0; loop < maxClients; loop++)
	{
		clientSocket[loop] = NULL; // there are not clients yet.
		socketIsFree[loop] = true; // True means avaialable to connect to.
	}

	// For error checking place code below as an int and check for it.
	SDLNet_ResolveHost(&serverIP, NULL, port);

	serverSocket = SDLNet_TCP_Open(&serverIP);

	SDLNet_TCP_AddSocket(socketSet, serverSocket);
}

// removes and deletes the Socket set & arrays
Server::~Server()
{
	// Close all the open client sockets
	for (unsigned int loop = 0; loop < maxClients; loop++)
	{
		if (socketIsFree[loop] == false)
		{
			SDLNet_TCP_Close(clientSocket[loop]);
			socketIsFree[loop] = true;
		}
	}

	// Close our server socket
	SDLNet_TCP_Close(serverSocket);

	// Free our socket set
	SDLNet_FreeSocketSet(socketSet);

	// Release any properties on the heap
	delete clientSocket;
	delete socketIsFree;
	delete buffer;
}

void Server::connectionThread()
{
	// Check if there is activity on the server socket. 
	// If there is no activity don't do anything
	int checkActivity = SDLNet_SocketReady(serverSocket);

	if (checkActivity != 0)
	{
		// check if we have room for clients, else we don't and cannot accept any more. 
		// Send information to that client that there is no room for them.
		if (clientCount < maxClients)
		{
			int freeSlot;
			// Loop through the Client Socket Array using the Bool Array
			for (int loop = 0; loop < maxClients; loop++)
			{
				if (socketIsFree[loop] == true)
				{
					// The socket has a free spot for a client.

					socketIsFree[loop] = false; 
					freeSlot = loop; // Save the index.
					break; // Break out of the for loop
					// Slot is no longer free because we are placing a client into it.
				}
			}
			// Accept the client into the free slot.
			clientSocket[freeSlot] = SDLNet_TCP_Accept(serverSocket);
			
			// Add that client to the SocketSet.
			SDLNet_TCP_AddSocket(socketSet, clientSocket[freeSlot]);

			// Increase the clientCount by the connected client (1)
			clientCount++;

			// Send the client a message that they connected.
			buffer = "You have connected to the Server";
			int bufferLength = strlen(buffer) + 1;
			// Send the client info that we are full
			SDLNet_TCP_Send(clientSocket[freeSlot], buffer, bufferLength);

		}
		else
		{
			//Accept this socket so we can remove it from connecting.
			TCPsocket tempClient = SDLNet_TCP_Accept(serverSocket);

			buffer = "Server is Full";
			int bufferLength = strlen(buffer) + 1;
			// Send the client info that we are full
			SDLNet_TCP_Send(tempClient, buffer, bufferLength);

			//Now we close their connection
			SDLNet_TCP_Close(tempClient);
		}

	}
	

}

void Server::checkForActivity()
{

}

void Server::dealWithActivity(unsigned int clientNumber)
{

}