#ifndef COLORBAR_H
#define COLORBAR_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QStaticText>

class ColorBar : public QWidget {
    Q_OBJECT

  public:

    void paintEvent(QPaintEvent *) override {

            QPainter painter(this);
            painter.setOpacity(0.9);
            painter.setRenderHint(QPainter::HighQualityAntialiasing);
            QLinearGradient gradient(0, 0, 0, height());
            QGradientStops stops;
            stops << QGradientStop(0, colorize(0));
            stops << QGradientStop(1.0/3, colorize((int)(100/3)));
            stops << QGradientStop(2.0/3, colorize((int)(200/3)));
            stops << QGradientStop(1, colorize(100));

            gradient.setStops(stops);

            painter.fillRect(rect(), gradient);
            int h = this->height();

            painter.drawStaticText(QPoint(15, h-20), QStaticText("10"));
            painter.drawStaticText(QPoint(20, (h/2) ), QStaticText("5"));
            painter.drawStaticText(QPoint(20, 10), QStaticText("0"));

        }


  private:
    QColor colorize(int v, int d = 100) {
      qreal rv = qreal(v) / d;
      QColor c = QColor::fromHsl(205 - (205 - 42) * rv, 200, 135);
      return c;
    }
};



#endif // COLORBAR_H
