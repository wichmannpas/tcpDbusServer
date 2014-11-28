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

    //split received tcp signal at iterator ::: to be able to receive multiple information from one single string
    //data format should end with ::: to avoid incorrect parses i.e. of blank spaces
    QStringList tcpData = QString(buffer).remove("&").remove("|").split(":::");

    //check tcp signal for validity
    if (tcpData.count() >= 2 && tcpData.at(0) == "volume") {//volume alsa action - exactly two fragments needed; accepting more because of blank spaces/lines at the end of string can be counted as third
        if (tcpData.at(1) == "up") {
            //send volume up command
            system("amixer -D pulse sset Master 10%+");
        } else if (tcpData.at(1) == "down") {
            //send volume down command
            system("amixer -D pulse sset Master 10%-");
        } else {
            //restore 100%
            system("amixer -D pulse sset Master 100%");
        }
    } else if (tcpData.count() >= 2) {//dbus actions, if none of the above was found - exactly two fragments needed; accepting more because of blank spaces/lines at the end of string can be counted as third
        //generate dbus command
        char command[256];
        strcpy(command, "dbus-send --print-reply --dest=org.mpris.MediaPlayer2.");
        strcat(command, tcpData.at(1).toUtf8().constData());//target (i.e. rhythmbox, spotify, vlc)
        strcat(command, " /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.");
        strcat(command, tcpData.at(0).toUtf8().constData());//action (i.e. PlayPause)

        //send command to system
        system(command);
    }

    tcpClient->close();//close the tcp connection to client
}
