#include "olam.h"

Olam::Olam(QWidget *parent) : QMainWindow(parent) , ui(new Ui::Olam){
    ui->setupUi(this);

}

Olam::~Olam()
{
    delete ui;
}



void Olam::on_searchButton_clicked(){

    ui->ResulttextBrowser->setText(""); //reset UI every time

    OlamDBHandler database;
    database.createConnection("D:\\Projects\\OlamWindows\\OlamWindows\\db\\olamdict.db");

    QString outputText = "Meaning     :    Part of speech\n _________________________________\n\n";

    QString searchText = ui->searchlineEdit -> text();
    qDebug() << "Text searched: " << searchText;

    if(searchText == ""){
        QMessageBox::information(this, "Warning", "Enter a text");
    }
    else{

        QMap<QString, QString>::const_iterator it;
        QMap<QString, QString> returnedResult = database.return_result(searchText);

        if(returnedResult.empty()){
          QMessageBox::information(this, "Warning", "Word not found");
        }
        else{
            for (it = returnedResult.constBegin(); it != returnedResult.constEnd(); ++it) {
                QString key = it.key();
                QString value = it.value();
                outputText += QString("%1    :    %2\n").arg(key).arg(value);
            }
            ui->ResulttextBrowser->setText(outputText);
        }
    }
}


void Olam::on_actionExit_triggered()
{
    qDebug() <<"exit button triggered ";
    QCoreApplication::quit();

}


void Olam::on_actionAbout_triggered()
{
    //trigger the about window
    qDebug() <<"about window triggered ";
    About *aboutWindow = new About();
    aboutWindow->show();
}

