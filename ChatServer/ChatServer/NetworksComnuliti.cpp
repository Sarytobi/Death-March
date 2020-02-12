#include <winsock2.h>
#include "NetworksComnuliti.h"


string NetworksComnuliti::Coder(string std)
{
	return string();
}

string NetworksComnuliti::Decoder(char* s)
{
	string temp = s;
	return temp;
}

void NetworksComnuliti::Send(string message, SOCKET connection)
{
	SOCKET tempConnection = connection;
	int sizeOfMessage = 0;
	sizeOfMessage = message.length();
	char* messageChar = new char[sizeOfMessage + 1];
	strcpy(messageChar, message.c_str());
	messageChar[sizeOfMessage] = '\0';
	send(tempConnection, (char*)&sizeOfMessage, sizeof(int), NULL);
	send(tempConnection, messageChar, sizeOfMessage, NULL);
	delete[] messageChar;
}

string NetworksComnuliti::NewPlayers(char* s, int size)
{
	string temp = s;
	string t;
	if (temp.find("NamePlayers") != string::npos)
	{
		t = temp.substr(11); // возвращает сроку после "NamePlayers"
		return t;
	}
	return "Error";
}
