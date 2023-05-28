
#include "olamdbhandler.h"

OlamDBHandler::OlamDBHandler(QString file_location)
{
    this-> db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(file_location);

}


bool OlamDBHandler::connectionStatus()
{

    bool connection_status = false;
    if (!this->db.open()) {
        qDebug() << "Failed to connect to database!";
        connection_status = true;
    }
    else{
        qDebug() << "Connection sucessfull";
        connection_status = false;
    }

    return connection_status;
}

QMap<QString, QString> OlamDBHandler::return_result(QString searchWord){

    QMap<QString, QString> searchResult;

    searchWord = searchWord.trimmed();
    searchWord = searchWord.left(1).toUpper() + searchWord.mid(1); // Capitalise the first char

    QSqlQuery searchQuery(this->db);
    searchQuery.prepare("SELECT malayalam_definition, part_of_speech FROM data WHERE english_word = ?");
    searchQuery.addBindValue(searchWord);

    if (!searchQuery.exec()) {
        qDebug() << "Failed to execute query!";
    }

    // iterate over the results and store it in a map
    while (searchQuery.next()) {
        QString malayalam_definition = searchQuery.value("malayalam_definition").toString();
        QString part_of_speech = searchQuery.value("part_of_speech").toString();
        if (part_of_speech == "n")
            part_of_speech = "noun";
        else if (part_of_speech == "v")
            part_of_speech = "verb";
        else if (part_of_speech == "a")
            part_of_speech = "adj";
        else if (part_of_speech == "adv")
            part_of_speech = "adverb";
        else
            part_of_speech = "unknown";
        searchResult.insert(malayalam_definition, part_of_speech);
        qDebug() << "malayalam_definition" << malayalam_definition << ", part_of_speech:" << part_of_speech ;

    }

    return searchResult;
}
