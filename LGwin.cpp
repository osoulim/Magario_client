//
// Created by mamzi on 7/19/17.
//

#include "LGwin.h"

LGwin::LGwin(QWidget *parent)
{
    username = new QLineEdit("Username");
    ip = new QLineEdit("127.0.0.1");
    port = new QLineEdit("8000");
    lgbut = new QPushButton("Login");
    color = new QComboBox();
    QStringList colors;
    colors<<"Red"<<"Blue"<<"Cyan"<<"Magenta"<<"Yellow"<<"Gray";
    color->addItems(colors);
    user = new QRadioButton("Im a player");
    user->setChecked(true);
    bot = new QRadioButton("Im a bot");
    observer = new QRadioButton("Im an observer");

    QVBoxLayout *lay = new QVBoxLayout();
    lay->addWidget(username);
    lay->addWidget(ip);
    lay->addWidget(port);
    lay->addWidget(color);
    lay->addWidget(user);
    lay->addWidget(bot);
    lay->addWidget(observer);
    lay->addWidget(lgbut);

    this->setWindowTitle("Magario");
    this->setLayout(lay);
    show();
    connect(lgbut, SIGNAL(clicked()), this, SLOT(login()));
    connect(username, SIGNAL(returnPressed()), this, SLOT(login()));
    connect(ip, SIGNAL(returnPressed()), this, SLOT(login()));
    connect(port, SIGNAL(returnPressed()), this, SLOT(login()));

}

void LGwin::login()
{
    QHostAddress *address = new QHostAddress(this->ip->text());
    quint16 *port = new quint16(this->port->text().toInt());
    QString type;
    if(user->isChecked()) type = "user";
    else if(bot->isChecked()) type = "bot";
    else type = "observer";
    emit mk_connection(address, *port, this->username->text(), this->color->currentIndex(), type);
}