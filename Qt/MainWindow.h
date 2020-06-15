#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QGroupBox>
#include <QPainter>
#include <QScrollArea>
#include <QBackingStore>
#include "Controller.h"
#include "Graph.h"
#include "ColorBar.h"



class MainWindow: public QMainWindow
{
  Q_OBJECT
private:
    //
public:
    MainWindow(){
      //
    }
  ~ MainWindow(){}

  void Execute(){

      QGroupBox *groupBox = new QGroupBox();

      ColorBar *color_bar = new ColorBar;
      color_bar->setMaximumWidth(50);
      QHBoxLayout *vbox = new QHBoxLayout;
      Controller *controller = new Controller();



      vbox->addWidget( color_bar );
      vbox->addWidget( controller );
      groupBox->setLayout(vbox);
      groupBox->setMinimumHeight(600);
      groupBox->setMinimumWidth(950);
      groupBox->setMaximumHeight(600);
      groupBox->setMaximumWidth(950);
      groupBox->setTitle("Contatore delle interazioni");
      groupBox->show();


  }

public slots:

  void ExecutSlot(){
      //qDebug() << "executeSlot";
      Execute();
  }

};




#endif // MAINWINDOW_H
