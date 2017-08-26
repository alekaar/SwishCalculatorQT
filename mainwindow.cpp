#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

#include <QSpacerItem>
#include <QList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //leftmost layout parent
    leftLay = new QBoxLayout(QBoxLayout::BottomToTop);
    leftLay->addStretch(1);

    ui->setupUi(this);

    //fixing mainwindow layout
    ui->mainw->setDirection(QBoxLayout::RightToLeft);
    ui->mainw->addLayout(leftLay);

    //values layout
    values = new QBoxLayout(QBoxLayout::BottomToTop);
    leftLay->addLayout(values);
    leftLay->setAlignment(values, Qt::AlignLeft);

    //headers
    QLabel *lName = new QLabel("Name");
    QLabel *lMon = new QLabel("Money");
    QBoxLayout *header = new QBoxLayout(QBoxLayout::LeftToRight);
    lName->setFixedWidth(100);
    lMon->setFixedWidth(40);
    leftLay->addLayout(header);
    leftLay->setAlignment(header, Qt::AlignLeft);
    header->addWidget(lName);
    header->addWidget(lMon);
    pers = new QList<QPair<QLineEdit *, QLineEdit *>>();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPerson_clicked()
{
    //create neew layout for lines
    QBoxLayout *v = new QBoxLayout(QBoxLayout::LeftToRight);

    //create line for name
    QLineEdit *name = new QLineEdit();
    name->setFixedWidth(100);
    name->setObjectName("name");

    //create line for money
    QLineEdit *money = new QLineEdit();
    money->setFixedWidth(40);
    money->setObjectName("money");


    //add them to layout
    v->addWidget(name);
    v->addWidget(money);

    //save them to list
    pers->prepend(qMakePair(name, money));

    //add layout to values layout
    values->addLayout(v);
    values->setAlignment(v, Qt::AlignLeft);
}

void MainWindow::on_computeMon_clicked()
{

    //calculate total amount
    float total = 0;

    for(int i = 0; i < pers->size(); i++){
        total += pers->at(i).second->text().toInt();
    }
    ui->total->setText("Total: " + QString::number(total));

    //PER PERSON
    QList<QPair <QLineEdit *, float> > *owing = new QList<QPair<QLineEdit *, float>>();
    QList<QPair <QLineEdit *, float> > *payedMore = new QList<QPair<QLineEdit *, float>>();

    float perPerson = total/pers->size();
    qDebug() << perPerson;
    //categorize
    for(int i = 0; i < pers->size(); i++){
        //not payed enough, add to owing
        if(pers->at(i).second->text().toFloat() < perPerson){
            owing->append(qMakePair(pers->at(i).first, pers->at(i).second->text().toFloat()));
        }
        //payed too much, add to payedMore
        else if(pers->at(i).second->text().toFloat() > perPerson){
            payedMore->append(qMakePair(pers->at(i).first, pers->at(i).second->text().toFloat()));
        }
    }

    QString output;
    //start planning swishing
    for(int i = 0; i < owing->size(); i++){
        float leftToPay = perPerson - owing->at(i).second;
        qDebug() << leftToPay;
        //check who to swish
        //TODO remove from payedMore when
        for(int j = 0; j < payedMore->size() && leftToPay > 0; j++){
            if(payedMore->at(j).second - leftToPay >= perPerson){

                float newBalance = payedMore->at(j).second - leftToPay;
                payedMore->replace(j, qMakePair(payedMore->at(j).first, newBalance));

                output.append("@" + owing->at(i).first->text() + " -> " + QString::number(leftToPay)
                              + "@" + payedMore->at(j).first->text() + " \n");
                leftToPay = perPerson;
            }
            else{
                float tooMuch = (perPerson - payedMore->at(j).second);
                leftToPay += tooMuch;

                float newBalance = payedMore->at(j).second - tooMuch;
                payedMore->replace(j, qMakePair(payedMore->at(j).first, newBalance));

                output.append("@" + owing->at(i).first->text() + " -> " + QString::number(tooMuch)
                              + " @" + payedMore->at(j).first->text() + " \n");
            }
        }

    }
    qDebug() << output;




}
