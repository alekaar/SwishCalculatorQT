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

/*void MainWindow::on_pushButton_clicked()
{
    QLabel *t1 = new QLabel(ui->lineEdit->text());
    QString s = ui->lineEdit_1->text();

    bool ok;
    s.toInt(&ok, 10);

    if(ok){
        QLabel *t2 = new QLabel(s);

        QBoxLayout *l = new QBoxLayout(QBoxLayout::LeftToRight);

        l->addWidget(t1);
        l->addWidget(t2);
        ui->verticalLayout_2->addLayout(l);
    }
}
*/
void MainWindow::on_addPerson_clicked()
{
    QBoxLayout *v = new QBoxLayout(QBoxLayout::LeftToRight);

    QLineEdit *name = new QLineEdit();
    name->setFixedWidth(100);
    name->setObjectName("name");

    QLineEdit *money = new QLineEdit();
    money->setFixedWidth(40);
    money->setObjectName("money");


    v->addWidget(name);
    v->addWidget(money);

    pers->prepend(qMakePair(name, money));

    values->addLayout(v);
    values->setAlignment(v, Qt::AlignLeft);
}

void MainWindow::on_computeMon_clicked()
{

    //calculate total amount
    int total = 0;

    for(int i = 0; i < pers->size(); i++){
        total += pers->at(i).second->text().toInt();
    }
    ui->total->setText("Total: " + QString::number(total));
    //PER PERSON
    int perPerson = total/pers->size();
    qDebug() << perPerson;


}
