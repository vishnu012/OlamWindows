#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>

#include "olam.h"
#include "./ui_olam.h"
#include "olamdbhandler.h"

Olam::Olam(QWidget *parent) : QMainWindow(parent) , ui(new Ui::Olam){
    ui->setupUi(this);
}

Olam::~Olam()
{
    delete ui;
}


void Olam::on_searchButton_clicked(){

    OlamDBHandler database;
    database.createConnection("D:\\Projects\\OlamWindows\\OlamWindows\\olamdict.db");

    QString outputText = "";

    QString searchText = ui->searchlineEdit -> text();
    qDebug() << "Text entered: " << searchText;

    if(searchText == ""){
        QMessageBox::information(this, "Warning", "Enter a text");
    }
    else{

        QMap<QString, QString>::const_iterator it;
        QMap<QString, QString> returned_result = database.return_result(searchText);
        for (it = returned_result.constBegin(); it != returned_result.constEnd(); ++it) {
            QString key = it.key();
            QString value = it.value();
            outputText += QString("%1: %2\n").arg(key).arg(value);
        }
        ui->ResulttextBrowser->setText(outputText);
    }
}

