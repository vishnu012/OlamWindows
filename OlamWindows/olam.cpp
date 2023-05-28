#include "olam.h"

Olam::Olam(QWidget *parent) : QMainWindow(parent) , ui(new Ui::Olam){
    ui->setupUi(this);

}

Olam::~Olam()
{
    delete ui;
}



void Olam::on_searchButton_clicked(){

    bool connection_status = false;

    ui->ResulttextBrowser->setText(""); //reset UI every time

    OlamDBHandler database("D:\\Projects\\OlamWindows\\OlamWindows\\db\\olamdict.db");
    connection_status = database.connectionStatus();

    QString outputText = "Meaning     :    Part of speech\n _________________________________\n\n";

    QString searchText = ui->searchlineEdit -> text();
    qDebug() << "Text searched: " << searchText;

    if(connection_status){
        QMessageBox::information(this, "Error", "DB connection failed");
    }
    else{
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

