#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QSettings>
#include <QFrame>

MainWindow::MainWindow(QWidget* parent, DbController* dbc, QThread* dbt) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db_controller = dbc;
    db_thread = dbt;

    // connect signals with slots

    // ui => ui

    connect(ui->button_connect, SIGNAL(clicked()), this, SLOT(connectToServerRequested()));
    connect(ui->radio_mssql, SIGNAL(clicked()), this, SLOT(engineChanged()));
    connect(ui->radio_mysql, SIGNAL(clicked()), this, SLOT(engineChanged()));
    connect(ui->radio_sql_authentication, SIGNAL(clicked()), this, SLOT(authenticationMethodChanged()));
    connect(ui->radio_windows_authentication, SIGNAL(clicked()), this, SLOT(authenticationMethodChanged()));
    connect(ui->button_show_table, SIGNAL(clicked()), this, SLOT(showTableRequested()));
    connect(ui->button_deleteRow, SIGNAL(clicked()), this, SLOT(deleteRowRequested()));

    // ui => db_controller

    connect(this, SIGNAL(connectToServer(QString,QString,QString,int,QString,QString,QString,bool)),
            db_controller, SLOT(connectToServerRequested(QString,QString,QString,int,QString,QString,QString,bool)));
    connect(this, SIGNAL(disconnectFromServer()), db_controller, SLOT(disconnectFromServerRequested()));
    connect(this, SIGNAL(selectTable(QString,QString,QString)), db_controller, SLOT(selectTableRequested(QString, QString, QString)));
    connect(this, SIGNAL(selectTableDeleteRow(QString,int)), db_controller, SLOT(selectTableDeleteRowRequested(QString, int)));
    connect(this, SIGNAL(getTablesNames()), db_controller, SLOT(getTablesNamesRequested()));

     // db_controller => ui

    connect(db_controller, SIGNAL(serverConnected()), this, SLOT(serverConnected()));
    connect(db_controller, SIGNAL(serverErrorWithConnection(QString)),
            this, SLOT(serverErrorWithConnection(QString)));
    connect(db_controller, SIGNAL(serverDisconnected()), this, SLOT(serverDisconnected()));
    connect(db_controller, SIGNAL(tableSelected(QSqlQueryModel*)), this, SLOT(displayTable(QSqlQueryModel*)));
    connect(db_controller, SIGNAL(tableDeleteRowSelected(QSqlQueryModel*)), this, SLOT(displayTable(QSqlQueryModel*)));
    connect(db_controller, SIGNAL(gotTablesNames(QStringList)), this, SLOT(fillTablesNames(QStringList)));

}

MainWindow::~MainWindow()
{
    db_thread->exit();
    db_thread->wait();
    delete ui;
}

void MainWindow::connectToServerRequested()
{
    QString engine;
    if (ui->radio_mysql->isChecked())
        engine = "mysql";
    else if (ui->radio_mssql->isChecked())
        engine = "mssql";
    else
    {
        QMessageBox::information(this,
                                 "Не выбран способ подключения",
                                 "Выберите предложенный способ подключения",
                                 QMessageBox::Ok);
        return;
    }

    QString driver   = ui->lineEdit_driver->text(),
            server   = ui->lineEdit_server_address->text(),
            database = ui->lineEdit_database_name->text(),
            login    = ui->lineEdit_login->text(),
            password = ui->lineEdit_password->text();
    int port = ui->spinBox_server_port->value();

    if (server == "")
    {
        QMessageBox::information(this,
                                 "Не указан адрес сервера",
                                 "Введите адрес сервера для подключения",
                                 QMessageBox::Ok);
        return;
    }

    bool is_sql_authentication = ui->radio_sql_authentication->isChecked();

    if (is_sql_authentication && login == "")
    {
        QMessageBox::information(this,
                                 "Не указаны логин или пароль",
                                 "Введите логин и пароль для подключения",
                                 QMessageBox::Ok);
        return;
    }

    if (database == "")
    {
        QMessageBox::information(this,
                                 "Не указано имя базы данных",
                                 "Введите имя базы данных для подключения",
                                 QMessageBox::Ok);
        return;
    }

    ui->button_connect->setEnabled(false);
    ui->statusBar->showMessage("Соединение...");

    emit connectToServer(engine, driver, server, port, database, login, password, is_sql_authentication);
}

void MainWindow::disconnectFromServerRequested()
{
    ui->button_connect->setEnabled(false);

    delete ui->tableView_database_table->model();

    emit disconnectFromServer();
}

void MainWindow::authenticationMethodChanged()
{
    bool is_sql_authentication = ui->radio_sql_authentication->isChecked();

    ui->lineEdit_login->setEnabled(is_sql_authentication);
    ui->lineEdit_password->setEnabled(is_sql_authentication);
}

void MainWindow::engineChanged()
{
    bool is_mssql_engine = ui->radio_mssql->isChecked();

    ui->lineEdit_driver->setEnabled(is_mssql_engine);
    ui->radio_windows_authentication->setEnabled(is_mssql_engine);

    ui->spinBox_server_port->setValue(is_mssql_engine ? 1433 : 3306);

    if (!is_mssql_engine)
    {
        ui->radio_sql_authentication->setChecked(true);
        emit authenticationMethodChanged();
    }
}

void MainWindow::showTableRequested()
{
    ui->button_show_table->setEnabled(false);

    delete ui->tableView_database_table->model(); // remove old model

    QString table_name = ui->comboBox_table_name->currentText();

    if (ui->checkBox_filter->checkState() == 0)
    {
        emit selectTable(table_name, "", "");
    }
    else
    {
        QString Field = ui->comboBox_table_filter->currentText();
        QString Value = ui->lineEdit_filter->text();
        emit selectTable(table_name, Field, Value);
    }
}

void MainWindow::deleteRowRequested()
{
    int ID = -1;
    QString Table = ui->comboBox_table_name->currentText();
    ID = ui->spinBox_deleteRow->value();
    if(ID == -1)
    {
        QMessageBox::information(this,
                                 "Значение ID пустое",
                                 "Введите значение поля ID",
                                 QMessageBox::Ok);
        return;
    }
    emit selectTableDeleteRow(Table, ID);
}

void MainWindow::addInfoIntoRowRequested()
{
    QStringList fields;
    QStringList values;
    values << ui->
    values << "asd" << "" << "dawd";
    //emit selectTableDeleteRow(Table, ID);
}

void MainWindow::serverConnected()
{
    ui->button_connect->setEnabled(true);

    disconnect(ui->button_connect, SIGNAL(clicked()), this, SLOT(connectToServerRequested()));
    connect(ui->button_connect, SIGNAL(clicked()), this, SLOT(disconnectFromServerRequested()));

    ui->button_connect->setText("Отключиться");
    ui->groupBox_database_browser->setEnabled(true);
    ui->groupBox_table_tools->setEnabled(true);

    ui->statusBar->showMessage("Соединено", 3000);
    emit getTablesNames();
}

void MainWindow::fillTablesNames(QStringList tables_names)
{
    QStringList RusName = {"Классы", "Кабинеты", "Квалификации", "Школы", "Ученики", "Предметы",
                            "Учителя", "Учитель и школа", "Учитель и предмет", "Расписание"};

    if (tables_names.length() == 0)
        QMessageBox::warning(this,
                             "Таблицы",
                             "В этой базе данных нет таблиц",
                             QMessageBox::Ok);
    else
    {
        for(int i = 0; i < 10; ++i)
        {
            tables_names[i] = RusName[i];
        }

        ui->comboBox_table_name->addItems(tables_names);

        ui->comboBox_table_name->setEnabled(true);
        ui->comboBox_table_name->setFocus();
    }
}

void MainWindow::serverErrorWithConnection(QString message)
{
    QMessageBox::critical(this,
                          "Соединение не удалось",
                          message,
                          QMessageBox::Ok);

    ui->button_connect->setEnabled(true);

    ui->statusBar->showMessage("Соединение не удалось", 3000);
}

void MainWindow::serverDisconnected()
{
    disconnect(ui->button_connect, SIGNAL(clicked()), this, SLOT(disconnectFromServerRequested()));
    connect(ui->button_connect, SIGNAL(clicked()), this, SLOT(connectToServerRequested()));

    ui->tableView_database_table->setModel(NULL);

    ui->button_connect->setEnabled(true);
    ui->button_connect->setText("Подключиться");

    ui->comboBox_table_name->clear();
    ui->comboBox_table_name->setEnabled(false);

    ui->groupBox_database_browser->setEnabled(false);
    ui->groupBox_table_tools->setEnabled(false);
    ui->button_connect->setFocus();
}

void MainWindow::displayTable(QSqlQueryModel* model)
{
    if (!model->lastError().isValid())
        ui->tableView_database_table->setModel(model);
    else
        QMessageBox::critical(this,
                              "Не удалось получить информацию о таблицах",
                              model->lastError().databaseText(),
                              QMessageBox::Ok);

    ui->button_show_table->setEnabled(true);
    ui->comboBox_table_name->setFocus();

    ui->comboBox_table_filter->clear();

    int column = 0;
    while(model->record(0).fieldName(column) != "")
    {
        QString columnName = model->record(0).fieldName(column);
        ui->comboBox_table_filter->addItem(columnName);
        column++;
    }
}

void MainWindow::keyPressEvent(QKeyEvent* pe)
{
    if (pe->key() == Qt::Key_Enter || pe->key() == Qt::Key_Return)
    {
        if (!db_controller->checkIfConnected())
            emit connectToServerRequested();
        else if (ui->comboBox_table_name->isEnabled() && ui->comboBox_table_name->hasFocus())
            emit showTableRequested();
    }
}
