//
// Created by mamzi on 7/19/17.
//

#include "Client.h"

Client::Client()
{
    Login = new LGwin();
    connect(Login, SIGNAL(mk_connection(QHostAddress*, quint16, QString, int, QString)), this, SLOT(Make_Connection(QHostAddress*, quint16, QString, int, QString)));
}

void Client::Make_Connection(QHostAddress *address, quint16 port, QString username, int color, QString type)
{

    Username = username;
    Color = color;
    Type = type;
    Socket = new QTcpSocket();
    Socket->connectToHost(*address, port);
    Login->hide();
    Game = new Gamewin(type);
    connect(Socket, SIGNAL(readyRead()), this, SLOT(get_info()));
    connect(Game, SIGNAL(send_move(QString)), this, SLOT(Socket_send(QString)));
    connect(Socket, SIGNAL(connected()), this, SLOT(initial()));

}

void Client::get_info()
{
    QString info = Socket->readLine();
    Game->draw(info);
}

void Client::Socket_send(QString move)
{
    Socket->write(move.toLocal8Bit());
}

void Client::initial()
{
    QString init = "l " + Username + " " + QString::number(Color) + "\n";
    Socket->write(init.toLocal8Bit());
}