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
        OlamDBHandler();
        bool createConnection(QString);
        QMap<QString, QString> return_result(QString);
};

#endif // OLAMDBHANDLER_H
