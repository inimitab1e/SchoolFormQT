#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "db_controller.h"

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent, DbController* dbc, QThread* dbt);
    ~MainWindow();

public slots:
    void connectToServerRequested();
    void disconnectFromServerRequested();
    void engineChanged();
    void authenticationMethodChanged();
    void showTableRequested();
    void deleteRowRequested();
    void serverConnected();
    void serverErrorWithConnection(QString);
    void serverDisconnected();
    void displayTable(QSqlQueryModel*);
    void fillTablesNames(QStringList);

signals:
    void connectToServer(QString, QString, QString, int, QString, QString, QString, bool);
    void disconnectFromServer();
    void selectTable(QString, QString, QString);
    void selectTableDeleteRow(QString, int);
    void getTablesNames();
    
private:
    DbController*   db_controller;
    QThread*        db_thread;
    Ui::MainWindow* ui;
protected:
    virtual void keyPressEvent(QKeyEvent*);
private slots:
};

#endif // MAINWINDOW_H
