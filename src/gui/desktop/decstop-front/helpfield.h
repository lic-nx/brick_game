#ifndef HELPFIELD_H
#define HELPFIELD_H

#include <QWidget>
#include <QPainter>

class HelpField : public QWidget
{
public:
    HelpField();
protected:
void paintEvent(QPaintEvent *e);
};

#endif // HELPFIELD_H
