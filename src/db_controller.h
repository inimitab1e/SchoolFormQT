#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#include <QString>
#include <QtSql>
#include <QSqlField>

class DbController : public QObject
{
    Q_OBJECT
public:
    explicit DbController(QObject*);
    ~DbController();
    bool checkIfTableExists(QString);
    bool checkIfConnected();

public slots:
    void connectToServerRequested(QString, QString, QString, int, QString, QString, QString, bool);
    void disconnectFromServerRequested();
    void selectTableRequested(QString, QString, QString);
    void selectTableDeleteRowRequested(QString, int);
    void insertInfoToRowRequested(QString, QStringList, QStringList);
    void getTablesNamesRequested();

signals:
    void serverConnected();
    void serverErrorWithConnection(QString);
    void serverDisconnected();
    void tableSelected(QSqlQueryModel*);
    void gotTablesNames(QStringList);

private:
    bool connectToServerMSSQL(QString, QString, int, QString, QString, QString);
    bool connectToServerMSSQL(QString, QString, int, QString);
    bool connectToServerMySQL(QString, int, QString, QString, QString);
    void disconnectFromServer();
    QSqlQueryModel* selectTable(QString, QString, QString);
    QSqlQueryModel* insertRowToTable(QString, QStringList, QStringList);
    QSqlQueryModel* selectDeleteRowTable(QString, int);
    QSqlError       getLastError();

    QSqlDatabase db;
    static const QString connection_string_sqlauth;
    static const QString connection_string_winauth;
};

#endif // DB_CONTROLLER_H
