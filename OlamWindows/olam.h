
#ifndef OLAM_H
#define OLAM_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>

#include "./ui_olam.h"
#include "olamdbhandler.h"
#include "about.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Olam; }
QT_END_NAMESPACE

class Olam : public QMainWindow

{
    Q_OBJECT

public:
    Olam(QWidget *parent = nullptr);
    ~Olam();

private slots:

    void on_searchButton_clicked();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

private:
    Ui::Olam *ui;
};

#endif // OLAM_H
