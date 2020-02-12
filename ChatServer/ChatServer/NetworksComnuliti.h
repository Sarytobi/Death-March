#pragma once
#include <string>
#pragma warning(disable: 4996)

using namespace std;

class NetworksComnuliti
{
public:
	string Coder(string std);
	string Decoder(char* s);
	string NewPlayers(char* s, int size);
	void Send(string message, SOCKET connection);
};
