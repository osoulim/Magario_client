//
// Created by mamzi on 7/19/17.
//

#include "Gamewin.h"
#define vsize(x, y) sqrt(x * x + y * y)

QString next(QStringList *input)
{
    static int i = 0;
    if(i == input->size() - 1)
    {
        i = 0;
        return input->at(input->size() - 1);
    }
    return input->at(i++);
}

QPair<double, double> vec(double myx, double my, double x, double y, double r)
{
    double dx = myx - x, dy = my - y;
    double sz = dx * dx + dy * dy;
    return qMakePair(-dx / sz * r, -dy / sz * r);
}

double get_rand(int st, int en)
{
    int res = st + qrand() % (en - st);
    return (double)res;
}

Gamewin::Gamewin(QString type)
{
    dX = dY = 0;
    bot = 0;
    scene = new QGraphicsScene();
    scene->addText("fuck");
    this->setScene(scene);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    if(type == "bot")
        bot = 1;

    showMaximized();
    show();
}

void Gamewin::draw(QString info)
{
    //qDebug()<<info;
    static QVector<QGraphicsEllipseItem*> items;

    //scene clear
    for(int i = 0; i < items.size(); i++)
        delete items[i];
    items.clear();
    scene->clear();

    //area view
    QStringList input = info.split(' ');
    QStringList *arr = &input;
    int extra = 100;
    int minx = (int)next(arr).toDouble() + extra, miny = (int)next(arr).toDouble() + extra, maxx = (int)next(arr).toDouble() - extra, maxy = (int)next(arr).toDouble() - extra;
    QRect vrect(minx, miny, maxx - minx, maxy - miny);
    this->fitInView(vrect,Qt::KeepAspectRatioByExpanding);
    //this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatioByExpanding);



    //drawing player balls
    QString username = next(arr);
    int color = next(arr).toInt();
    int n = next(arr).toInt();
    for(int i = 0; i < n; i++)
    {
        int x = (int)next(arr).toDouble(), y = (int)next(arr).toDouble(), r = (int)next(arr).toDouble();
        items.push_back(new QGraphicsEllipseItem(x-r, y-r, 2*r, 2*r));
        items.back()->setBrush(QBrush(colors[color]));
        if(i == 0)
        {
            this->centerOn(x, y);
        }
        scene->addItem(items.back());
    }


    //drawing other balls
    n = next(arr).toInt();
    for(int i = 0; i < n; i++)
    {
        username = next(arr);
        color = next(arr).toInt();
        int N = (int)next(arr).toDouble();
        for(int j = 0; j < N; j++)
        {
            int x = (int)next(arr).toDouble(), y = (int)next(arr).toDouble(), r = (int)next(arr).toDouble();
            items.push_back(new QGraphicsEllipseItem(x-r, y-r, 2*r, 2*r));
            items.back()->setBrush(QBrush(colors[color]));
            scene->addItem(items.back());

        }

    }

    //drawing viruses
    n = next(arr).toInt();
    for(int i = 0; i < n; i++)
    {
        int x = (int)next(arr).toDouble(), y = (int)next(arr).toDouble();
        items.push_back(new QGraphicsEllipseItem(x-50, y-50, 100, 100));
        items.back()->setBrush(QBrush(Qt::green));
        items.back()->setPen(QPen(Qt::darkGreen));
        items.back()->setZValue(1);
        scene->addItem(items.back());
    }

    //drawing points
    n = next(arr).toInt();
    for(int i = 0; i < n; i++)
    {
        int x = (int)next(arr).toDouble(), y = (int)next(arr).toDouble();
        items.push_back(new QGraphicsEllipseItem(x-4, y-4, 8, 8));
        items.back()->setBrush(QBrush(colors[(x + y) % 6]));
        scene->addItem(items.back());
    }

    if(bot)
        decide(info);
    check_input();
}


void Gamewin::mouseMoveEvent(QMouseEvent *event)
{
    if(bot)
        return;
    if(event->buttons())
    {
        double delX = event->x() - this->width() / 2, delY = event->y() - this->height() / 2;
        double sz = sqrt(delX * delX + delY * delY);
        delX /= (sz ? sz : 1);
        delY /= (sz ? sz : 1);
        dX = delX;
        dY = delY;
    }

}

void Gamewin::check_input()
{
    QString move = "w " + QString::number(dX) + " " + QString::number(dY) + "\n";
    emit send_move(move);
    //qDebug()<<move;
}

void Gamewin::mouseReleaseEvent(QMouseEvent *event)
{
    if(bot)
        return;
    dX = dY = 0;
}

void Gamewin::keyPressEvent(QKeyEvent *event)
{
    if(bot)
        return;
    if(event->key() == Qt::Key_Plus)
        emit send_move("p 5\n");
    if(event->key() == Qt::Key_Space)
        emit send_move("t 5\n");
    if(event->key() == Qt::Key_Enter)
        emit send_move("n 10\n");
    if(event->key() == Qt::Key_W)
        dY = -1;
    if(event->key() == Qt::Key_S)
        dY = 1;
    if(event->key() == Qt::Key_A)
        dX = -1;
    if(event->key() == Qt::Key_D)
        dX = 1;
    if(dX == dY)
    {
        dX /= 1.41;
        dY /= 1.41;
    }

}

void Gamewin::keyReleaseEvent(QKeyEvent *)
{
    if(bot)
        return;
    dX = dY = 0;
}

void Gamewin::decide(QString info)
{
    QStringList input = info.split(' ');
    QStringList *arr = &input;
    double Xway = 0, Yway = 0;
    next(arr); next(arr); next(arr); next(arr);
    next(arr); next(arr);
    double myx = 0, myy = 0, myr = 0;
    int n = next(arr).toInt();
    for(int i = 0; i < n; i++)
    {
        myx += next(arr).toDouble();
        myy += next(arr).toDouble();
        myr += next(arr).toDouble();
    }
    myx /= n; myy /= n; myr /= n;

    n = next(arr).toInt();
    for(int i = 0; i < n; i++)
    {
        next(arr); next(arr);
        int b = next(arr).toInt();
        for(int j = 0; j < b; j++)
        {
            double x = next(arr).toDouble(), y = next(arr).toDouble(), r = next(arr).toDouble();
            auto v = vec(myx, myy, x, y, r / 3);

            if(r > myr)
                v.first *= -1, v.second *= -1;
            Xway += v.first, Yway += v.second;
        }
    }


    n = next(arr).toInt();
    for(int i = 0; i < n; i++)
    {
        double x = next(arr).toDouble(), y = next(arr).toDouble(), r = 30;
        auto v = vec(myx, myy, x, y, r);
        if(r < myr)
            Xway -= v.first, Yway -= v.second;

    }

    n = next(arr).toInt();
    for(int i = 0; i < n; i++)
    {
        double x = next(arr).toDouble(), y = next(arr).toDouble(), r = 1;
        auto v = vec(myx, myy, x, y, r);
        Xway += v.first, Yway += v.second;
    }

    double size = vsize(Xway, Yway);
    //qDebug()<<size;
    if(size == 0)
        Xway = 1, Yway = 0;
    else
        Xway /= size, Yway /= size;

    dX = Xway, dY = Yway;

}




