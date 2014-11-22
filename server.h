/*
 * Written by Pascal Wichmann
 */

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>

class server: public QObject
{
Q_OBJECT
public:
    server(QObject * parent = 0);
    ~server();

public slots:
    void handleConnection();
    void readFromConnection();

private:
    QTcpServer tcpServer;
    QTcpSocket* tcpClient;
};

#endif // SERVER_H
