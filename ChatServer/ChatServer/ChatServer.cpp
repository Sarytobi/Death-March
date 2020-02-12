#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include "Players.h"
#include "NetworksComnuliti.h"
#include "Forest.h"
#pragma warning(disable: 4996)

Players arr[100];
int playersCounter = 0;
SOCKET Connections[100];
int threadCounter = 0;

using namespace std;

void ClientHandler(int index) {
	int messageSize;
	NetworksComnuliti messageControllerText;
	int herues = playersCounter;
	string message;
	Forest forest;

	while (true) 
	{
		message.clear();
		if (recv(Connections[index], (char*)&messageSize, sizeof(int), NULL) < 0) //check closed client
		{			
			break; // only one work variant
		}
		char* msg = new char[messageSize + 1];
		msg[messageSize] = '\0';
		recv(Connections[index], msg, messageSize, NULL);
		std::cout << "Received: Client = " << index << " Message = " << msg << std::endl;
		// передача данных
		message = messageControllerText.Decoder(msg);
		//!arr[playersCounter].GetName().string::empty()
		if (herues == playersCounter)
		{
			string msgString;
			std::cout << "Создание персонажа" << std::endl;
			arr[playersCounter] = Players(messageControllerText.NewPlayers(msg, messageSize));
			delete[] msg;
			msgString = arr[herues].InfoPlayerString();
			//msgtest = arr[herues].InfoPlayerString().c_str();
			int sizeHeruesMsg = msgString.size();
			cout << sizeHeruesMsg << endl;
			char* msgtest = new char[sizeHeruesMsg+1];
			msgtest[messageSize] = '\0';
			strcpy(msgtest, msgString.c_str());

			std::cout << msgtest << std::endl;

			send(Connections[herues], (char*)&sizeHeruesMsg, sizeof(int), NULL);
			send(Connections[herues], msgtest, sizeHeruesMsg, NULL);
			//нужно передать стринг
			arr[herues].InfoPlayer();
			playersCounter++;
			delete[] msgtest;
		}

		//reaction on the back message
		
		if (arr[herues].location == "square")
		{
			if (message == "1. Go to the forest")
			{
				arr[herues].location = "forest";
			}
			else if (message == "2. Go to the arena")
			{
				arr[herues].location = "arena";
			}
			else if (message == "3. Go to the market")
			{
				arr[herues].location = "market";
			}
			else if (message == "4. Check character's stats")
			{
				message = arr[herues].InfoPlayerString();
				message += "#1. Back";
				arr[herues].location = "dressroom";
				messageControllerText.Send(message, Connections[herues]);
			}
		}
		else if (arr[herues].location == "dressroom")
		{
			arr[herues].location = "square";
		}
		else if (arr[herues].location == "forest")
		{
			if ((message == "1. Left") || (message == "2. Straight") || (message == "2. Right") || (message == "1. Straight") || (message == "3. Rightt"))
			{
				//do nothing??
			}
			else if (message == "1. Exit from forest")
			{
				arr[herues].location = "square";
			}
			else if (message == "1. Pick up it")
			{
				//Get item??
				arr[herues].location = "square";
			}
			else if (message == "1. Take the fight in the forest")
			{
				//Start the fight
				arr[herues].location = "square";
			}
		}
		else if (arr[herues].location == "market")
		{

		}
		
		
		//menu

		if (arr[herues].location == "square")
		{
			cout << "Character " << arr[herues].GetName() << " on the square";
			message = "Character " + arr[herues].GetName() + " on the square";
			message += "#1. Go to the forest";
			message += "#2. Go to the arena";
			message += "#3. Go to the market";
			message += "#4. Check character's stats";
			messageControllerText.Send(message, Connections[herues]);
		}
		else if (arr[herues].location == "forest")
		{
			message = forest.NextLocation();
			messageControllerText.Send(message, Connections[herues]);
		}

		/*// Chat
		for (int i = 0; i < threadCounter; i++) {
			if (i == index) {
				continue;
			}
			std::cout << "Sended: Client = " << i << " Message = " << msg << std::endl;
			send(Connections[i], (char*)&messageSize, sizeof(int), NULL);
			send(Connections[i], msg, messageSize, NULL);
		}
		delete[] msg;*/
		
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "rus");
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(1111); //socket
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	while (true)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client #" << threadCounter << " Connected!\n";
			Connections[threadCounter] = newConnection;
			threadCounter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(threadCounter - 1), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}