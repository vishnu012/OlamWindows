#ifndef OLAMDBHANDLER_H
#define OLAMDBHANDLER_H

#include <QString>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QMap>

class OlamDBHandler{
    public:
        OlamDBHandler(QString);
        bool connectionStatus();
        QMap<QString, QString> return_result(QString);
        QSqlDatabase db;
};

#endif // OLAMDBHANDLER_H
