//
// Created by mamzi on 7/19/17.
//

#ifndef AGAR_CLIENT_LGWIN_H
#define AGAR_CLIENT_LGWIN_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtNetwork/QHostAddress>
#include <QLayout>
#include <QtCore/QItemSelection>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QRadioButton>

class LGwin: public QWidget
{
    Q_OBJECT
public:
    explicit LGwin(QWidget *parent = 0);
private:
    QPushButton *lgbut;
    QLineEdit *username, *ip, *port;
    QComboBox *color;
    QRadioButton *user, *bot, *observer;
public slots:
    void login();
    signals:
    void mk_connection(QHostAddress*, quint16, QString, int, QString);

};


#endif //AGAR_CLIENT_LGWIN_H
