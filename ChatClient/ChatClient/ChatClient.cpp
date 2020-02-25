#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include "conio.h"
#include <string>
#include "NetworksComnuliti.h"
#pragma warning(disable: 4996)

SOCKET Connection;
using namespace std;
bool flagMenu = false;
string answers[10];
int answerCounter;
string upperMessage;

void ClientHandler();

string menu(string upperMessage, string* answers, int answerCounter);
void Preview();

int main(int argc, char* argv[]) {

	Preview();

	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";
	system("pause");
	system("cls");

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	std::string msg1;
	std::string temp;
	std::cout << "Enter Name Players - ";
	msg1 += "NamePlayers";
	std::getline(std::cin, temp);
	msg1 += temp;
	int msg_size = msg1.size();
	send(Connection, (char*)&msg_size, sizeof(int), NULL);
	send(Connection, msg1.c_str(), msg_size, NULL);
	while (true) {
		if (flagMenu)
		{
			msg1 = menu(upperMessage, answers, answerCounter);
		}
		else
		{
			std::getline(std::cin, msg1);
		}
		if (msg1 == "")
		{
			continue;
		}
		int msg_size = msg1.size();
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, msg1.c_str(), msg_size, NULL);

		Sleep(10);
	}

	system("pause");
	return 0;
}

void ClientHandler() {
	int msg_size;
	string message, messageToOut;
	int foundSymbol;

	while (true) {
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		message.clear();
		message = msg;

		if (message.find('#') != string::npos)
		{
			foundSymbol = message.find('#');
			upperMessage = message.substr(0, foundSymbol);
			for (int i = 0; i < 10; i++)
			{
				answers[i].clear();
			}
			message = message.substr(foundSymbol, message.length());
			answerCounter = 0;
			while (message.find('#') != string::npos)
			{
				message = message.substr(1, message.length());
				if (message.find('#') == string::npos)
				{
					messageToOut = message;
					answers[answerCounter] = messageToOut; //form array with variants of answer
					answerCounter++;
				}
				else
				{
					foundSymbol = message.find('#');
					messageToOut = message.substr(0, foundSymbol);
					answers[answerCounter] = messageToOut;
					answerCounter++;
					message = message.substr(foundSymbol, message.length());
				}
			}
			flagMenu = true; //switching to menu input model
		}
		else if (message.find('%') != string::npos)
		{
			message = message.substr(1, message.length());
			cout << message;
			Sleep(1000);
			continue;
		}
		else
		{
			std::cout << message << endl;
			std::cout << "Press Enter to continue";
		}
		delete[] msg;
	}
}

void Preview()
{
	string preview[20];
	preview[0] = "                                                      ";
	preview[1] = "   ***        ********      **      ********   **   **";
	preview[2] = "   ** **      ********     ****     ********   **   **";
	preview[3] = "   **  **     **          **  **       **      **   **";
	preview[4] = "   **   **    ********    **  **       **      *******";
	preview[5] = "   **    **   ********    ******       **      *******";
	preview[6] = "   **   **    **         ********      **      **   **";
	preview[7] = "   **  **     **         **    **      **      **   **";
	preview[8] = "   ** **      ********   **    **      **      **   **";
	preview[9] = "   **         ********   **    **      **      **   **";
	preview[10] = "                                                      ";
	preview[11] = "                                                      ";
	preview[12] = "   **    **      **      ********      **      **   **";
	preview[13] = "   ***  ***     ****     ********     ****     **   **";
	preview[14] = "   ***  ***    **  **       **       **  **    **   **";
	preview[15] = "   ** ** **    **  **       **      **         *******";
	preview[16] = "   ** ** **    ******       **      **         *******";
	preview[17] = "   **    **   ********      **       **  **    **   **";
	preview[18] = "   **    **   **    **      **        ****     **   **";
	preview[19] = "   **    **   **    **      **         **      **   **";

	for (int i = 0; i < 20; i++)
	{
		Sleep(100);
		system("cls");
		for (int j = 19 - i; j < 20; j++)
		{
			cout << preview[j] << endl;
		}
	}
}

string menu(string upperMessage, string* answers, int answerCounter)
{
	int pushButton;
	int highlightedVariant = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //color console
	while (true)
	{
		system("cls");
		cout << upperMessage << endl << endl << endl;
		for (int i = 0; i < answerCounter; i++)
		{
			if (i == highlightedVariant)
			{
				SetConsoleTextAttribute(hConsole, 240); //white console
				cout << answers[i] << endl;
				SetConsoleTextAttribute(hConsole, 15); //black console back
			}
			else
			{
				cout << answers[i] << endl;
			}
		}
		pushButton = _getch();
		if (pushButton == 224) //push
		{
			pushButton = _getch();
		}

		if (pushButton == 72) //up
		{
			if (highlightedVariant == 0)
			{
				highlightedVariant = answerCounter - 1;
			}
			else
			{
				highlightedVariant--;
			}
		}
		else if (pushButton == 80) //down
		{
			if (highlightedVariant == answerCounter - 1)
			{
				highlightedVariant = 0;
			}
			else
			{
				highlightedVariant++;
			}
		}
		else if (pushButton == 13) //enter
		{
			flagMenu = false;
			system("cls");
			return answers[highlightedVariant];
		}
	}

}