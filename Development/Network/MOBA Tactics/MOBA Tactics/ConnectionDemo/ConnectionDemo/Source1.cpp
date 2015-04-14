#include "Server.h"
#include "Thread.h"
#include <thread>

Server *s;
string message;
bool shutDown;
int activeClient;

void thread_1()
{
	do{
		s->connectionThread();
		//cout << "Loop 1" << endl;
	} while (shutDown != true);
}

int main(int argc, char *argv[])
{
	s = new Server(1234, 512, 4); //Port, BufferSize, ClientNumber 
	message = "I CAUSE ERRORS";
	shutDown = false;
	thread t1(thread_1);
	//thread
	
	do{
		activeClient = -1;
		do{
			activeClient = s->checkForActivity(); // ActiveClient is the client number
			//cout << "Loop 2" << endl;
			if (activeClient != -1)
			{
				message = s->storeActivity(activeClient);

				//*Server code that deals with activity stuff
				cout << message << endl;

				string dataToSend = message;

				s->sendData(dataToSend); // will send data from above to all clients.
			}

		} while (activeClient != -1);

	} while (shutDown != true);
	
	getchar();
	return 0;
}

