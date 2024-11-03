#include "helpfield.h"

HelpField::HelpField()
{
    setFixedSize(300,50);
}

void HelpField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter;
    painter.begin(this);
    painter.drawRect(0, 0, width()-1, height()-1);
    painter.setFont(QFont("Arial", 10, 700));
    painter.drawText(QRect(0,0,width(),height()), "\n how to play\n don’t hit a wall and don’t bite your own tail");
    painter.end();
}
