/*
 * Written by Pascal Wichmann
 */

#include "server.h"
#include <iostream>

server::server(QObject* parent): QObject(parent)
{
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(handleConnection()));
    tcpServer.listen(QHostAddress::Any, 12341);//listen on tcp port 12341
}

server::~server()
{
    tcpServer.close();
}

/*
 * handle incoming tcp connection
 */
void server::handleConnection()
{
    tcpClient = tcpServer.nextPendingConnection();//get tcp connection
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readFromConnection()));//read data from tcp connection
}

/*
 * read data from tcp connection
 */
void server::readFromConnection()
{
    char buffer[1024];
    tcpClient->read(buffer, tcpClient->bytesAvailable());//write message to buffer

    std::cout << "Received tcp message: " << QString(buffer).toStdString() << std::endl;//print tcp message with cout

    //send dbus signal if tcp message contains task
    if (QString(buffer).mid(0, 9) == "playPause") {
        system("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause");
    } else if (QString(buffer).mid(0, 4) == "next") {
        system("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next");
    } else if (QString(buffer).mid(0, 8) == "previous") {
        system("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous");
    }

    tcpClient->close();//close the tcp connection to client
}
