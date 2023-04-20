
#ifndef OLAM_H
#define OLAM_H

#include <QMainWindow>



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

private:
    Ui::Olam *ui;
};

#endif // OLAM_H
