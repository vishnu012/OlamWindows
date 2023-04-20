
#include "olamdbhandler.h"

OlamDBHandler::OlamDBHandler(){

}


void OlamDBHandler::createConnection(QString file_location)
{
    QSqlDatabase olamdict = QSqlDatabase::addDatabase("QSQLITE");
    olamdict.setDatabaseName(file_location);

    if (!olamdict.open()) {
        qDebug() << "Failed to connect to database!";
    }
    else{
        qDebug() << "Connection sucessfull";
    }

}

QMap<QString, QString> OlamDBHandler::return_result(QString searchWord){

    QMap<QString, QString> searchResult;

    QSqlQuery searchQuery;
    searchQuery.prepare("SELECT malayalam_definition, part_of_speech FROM data WHERE english_word = ?");
    searchQuery.addBindValue(searchWord);

    if (!searchQuery.exec()) {
        qDebug() << "Failed to execute query!";
    }

    // iterate over the results and store it in a map
    while (searchQuery.next()) {
        QString malayalam_definition = searchQuery.value("malayalam_definition").toString();
        QString part_of_speech = searchQuery.value("part_of_speech").toString();
        searchResult.insert(malayalam_definition, part_of_speech);
        qDebug() << "malayalam_definition" << malayalam_definition << ", part_of_speech:" << part_of_speech ;

    }

    return searchResult;
}
