#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;



int main()
{
    WSADATA wsadata;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 
    int res = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (res != NO_ERROR)
    {
        cout << "WSAStartup failked with error " << res << endl;
        return 1;
    }

    SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket == INVALID_SOCKET)
    {
        cout << "socket failed with error " << WSAGetLastError() << endl;
        return 2;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;    
    addr.sin_port = htons(23000);   
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    if (bind(udpSocket, (SOCKADDR*)&addr, sizeof(addr)) != NO_ERROR)
    {
        cout << "bind failed with error " << WSAGetLastError() << endl;
        return 3;
    }

    const size_t receiveBufSize = 1024;
    char receiveBuf[receiveBufSize];
 
    sockaddr_in senderAddr;
    int senderAddrSize = sizeof(senderAddr);

    cout << "Receiving data...." << endl;
    int bytesReceived = recvfrom(udpSocket, receiveBuf, receiveBufSize, 0, (SOCKADDR*)&senderAddr, &senderAddrSize);

    if (bytesReceived == SOCKET_ERROR)
    {
        cout << "recvfrom failed with error " << WSAGetLastError() << endl;
        return 4;
    }

    receiveBuf[bytesReceived] = '\0';   

    char firstWord[receiveBufSize], secondWord[receiveBufSize], restOfText[receiveBufSize]; 

    size_t i;   
    for (i = 0; receiveBuf[i] != ' ' && receiveBuf[i] != '\0'; ++i) {   
        firstWord[i] = receiveBuf[i];   
    }
    firstWord[i] = '\0';    

    if (receiveBuf[i] == ' ')   
        ++i;

    size_t j;   
    for (j = 0; receiveBuf[i] != ' ' && receiveBuf[i] != '\0'; ++i, ++j) {  
        secondWord[j] = receiveBuf[i];  
    }
    secondWord[j] = '\0'; 

    strcpy_s(restOfText, &receiveBuf[i]);   
    int number = atoi(secondWord); 
    const char* arrayWords[] = { "end", "start", "error", "hello" };   

    const size_t maxWords = 100; 
    const size_t maxWordLength = 50;    
    const char* newText[maxWords]; 
    size_t wordCount = 0; 

    size_t bufIndex = 0;
    while (restOfText[bufIndex] != '\0' && wordCount < maxWords) {
        while (restOfText[bufIndex] == ' ') {
            ++bufIndex; 
        }

        char* wordBuffer = new char[maxWordLength]; 
        size_t wordIndex = 0;       
        while (restOfText[bufIndex] != ' ' && restOfText[bufIndex] != '\0' && wordIndex < maxWordLength - 1) {
            wordBuffer[wordIndex] = restOfText[bufIndex];   
            ++bufIndex; 
            ++wordIndex;    
        }
        wordBuffer[wordIndex] = '\0';
        newText[wordCount] = wordBuffer;
        ++wordCount;  
    }
   
    char newWords[maxWords][maxWordLength]; 
    size_t newWordCount = 0;

    for (int i = 0; i < wordCount; i++) {
        bool found = false;
        for (int j = 0; j < 4; j++) {
            if (strcmp(newText[i], arrayWords[j]) == 0) {
                found = true;
                break;
            }
        }
        if (found) {
            strcpy_s(newWords[newWordCount], "*****");  
            newWordCount++; 
        }
        else {
            strcpy_s(newWords[newWordCount], newText[i]); 
            newWordCount++;
        }   
    }

    cout << "Received from " << senderAddr.sin_addr.s_host << endl;          
    SetConsoleTextAttribute(h, number); 
    cout << firstWord << ": ";
    for (size_t i = 0; i < newWordCount; i++) {        
        cout << newWords[i] << " "; 
    }

    SetConsoleTextAttribute(h, 7); 
    closesocket(udpSocket);
    WSACleanup();
}

