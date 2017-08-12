//
// Created by mamzi on 7/19/17.
//

#ifndef AGAR_CLIENT_GAMEWIN_H
#define AGAR_CLIENT_GAMEWIN_H

#include <QMouseEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QDebug>


class Gamewin : public QGraphicsView
{
    Q_OBJECT
public:
    Gamewin(QString = "user");
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void draw(QString);
    void decide(QString);
    int bot;
private:
    QGraphicsScene *scene;
    void check_input();
    double dX, dY;
    const QColor colors[6] = {Qt::red, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow, Qt::gray};

signals:
    void send_move(QString);
};


#endif //AGAR_CLIENT_GAMEWIN_H
