//
// Created by mamzi on 7/19/17.
//

#ifndef AGAR_CLIENT_CLIENT_H
#define AGAR_CLIENT_CLIENT_H

#include <QTcpSocket>
#include <LGwin.h>
#include <Gamewin.h>

class Client :public QObject
{
    Q_OBJECT
public:
    Client();

private:
    LGwin *Login;
    Gamewin *Game;
    QTcpSocket *Socket;
    QString Username;
    int Color;
    QString Type;
public slots:
    void Make_Connection(QHostAddress*, quint16, QString, int, QString);
    void get_info();
    void Socket_send(QString);
    void initial();
};


#endif //AGAR_CLIENT_CLIENT_H
