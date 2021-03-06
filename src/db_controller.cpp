#include "db_controller.h"
#include "dbtables.h"

DbController::DbController(QObject* parent) :
    QObject(parent)
{

}

DbController::~DbController()
{
    if (db.isOpen())
        db.close();
}

void DbController::connectToServerRequested(QString engine, QString driver, QString server, int port, QString database,
                                            QString login, QString password, bool is_sql_authentication)
{
    db = QSqlDatabase();
    db.removeDatabase("example-connection"); // remove old connection if exists

    if (engine == "mysql")
    {
        db = QSqlDatabase::addDatabase("QMYSQL", "example-connection");
    }
    else if (engine == "mssql")
    {
        db = QSqlDatabase::addDatabase("QODBC", "example-connection");
    }
    else
    {
        emit serverErrorWithConnection("Unknown database engine");
        return;
    }

    bool connection_succesfull;

    if (engine == "mysql")
    {
        connection_succesfull = connectToServerMySQL(server, port, database, login, password);
    }
    else if (engine == "mssql")
    {
        connection_succesfull =
                (is_sql_authentication ? connectToServerMSSQL(driver, server, port, database, login, password) :
                                         connectToServerMSSQL(driver, server, port, database));
    }
    else
    {
        emit serverErrorWithConnection("Unknown database engine");
        return;
    }

    if (connection_succesfull)
        emit serverConnected();
    else
        emit serverErrorWithConnection(getLastError().driverText());
}

void DbController::disconnectFromServerRequested()
{
    disconnectFromServer();

    emit serverDisconnected();
}

bool DbController::checkIfTableExists(QString table)
{
    return db.tables().contains(table);
}

bool DbController::checkIfConnected()
{
    return db.isOpen();
}

void DbController::selectTableRequested(QString table, QString field, QString value)
{
    QSqlQueryModel* model = selectTable(table, field, value);

    emit tableSelected(model);
}

void DbController::selectTableDeleteRowRequested(QString table, int ID)
{
    QSqlQueryModel* model = selectDeleteRowTable(table, ID);

    emit tableSelected(model);
}

void DbController::insertInfoToRowRequested(QString table_name, QStringList fields, QStringList values)
{
    QSqlQueryModel* model = insertRowToTable(table_name, fields, values);

    emit tableSelected(model);
}

void DbController::getTablesNamesRequested()
{
    emit gotTablesNames(db.tables());
}

bool DbController::connectToServerMSSQL(QString driver, QString server, int port, QString database,
                                   QString login, QString password)
{
    db.setDatabaseName(connection_string_sqlauth.arg(driver).arg(server).arg(port).arg(database)
                       .arg(login).arg(password));

    return db.open();
}

bool DbController::connectToServerMSSQL(QString driver, QString server, int port, QString database)
{
    db.setDatabaseName(connection_string_winauth.arg(driver).arg(server).arg(port).arg(database));

    return db.open();
}

bool DbController::connectToServerMySQL(QString server, int port, QString database,
                                        QString login, QString password)
{
    db.setHostName(server);
    db.setPort(port);
    db.setDatabaseName(database);
    db.setUserName(login);
    db.setPassword(password);

    return db.open();
}

void DbController::disconnectFromServer()
{
    db.close();
}

QSqlQueryModel* DbController::selectTable(QString name, QString Field, QString Value)
{
    QSqlQueryModel* model = new QSqlQueryModel;
    DbTable dbtable;
    QString query = "";

    if (name == "Школы")
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Название")
            {
                Field = "SchoolName";
            }
            else if (Field == "Адрес")
            {
                Field = "Adress";
            }
            else
            {
                Field = "FoundingDate";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.School;
        model->setQuery("Select " + dbtable.School + ".SchoolName as 'Название', adress as 'Адрес', "
                        + "FoundingDate as 'Дата основания', " + dbtable.School + ".SchoolID from " + name + query, db);

    }
    else if (name == "Ученики")
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Имя ученика")
            {
                Field = "StudentName";
            }
            else if (Field == "Пол")
            {
                Field = "Gender";
            }
            else if (Field == "Дата рождения")
            {
                Field = "Birthday";
            }
            else if (Field == "Номер телефона")
            {
                Field = "PhoneNumber";
            }
            else if (Field == "Средний балл")
            {
                Field = "AverageScore";
            }
            else if (Field == "Школа")
            {
                Field = "SchoolName";
            }
            else
            {
                Field = "ClassNameNumber";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.Student;
        model->setQuery("Select " + dbtable.Student + ".StudentName as 'Имя ученика', " + dbtable.Student + ".Gender as 'Пол', "
                       + dbtable.Student + ".Birthday as 'Дата рождения', " + dbtable.Student + ".PhoneNumber as 'Номер телефона', "
                       + dbtable.Student + ".AverageScore as 'Средний балл', " + dbtable.School + ".SchoolName as 'Школа', "
                       + dbtable.ClassNames + ".ClassNameNumber as 'Класс', StudentID " + "from " + name + " left join " + dbtable.School + " on "
                       + dbtable.Student + ".SchoolID = " + dbtable.School + ".SchoolID " + " left join " + dbtable.ClassNames + " on "
                       + dbtable.Student + ".ClassNameID = " + dbtable.ClassNames + ".ClassNameID " + query, db);
    }
    else if (name == "Учителя")
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Имя учителя")
            {
                Field = "TeacherName";
            }
            else if (Field == "Пол")
            {
                Field = "Gender";
            }
            else if (Field == "Дата рождения")
            {
                Field = "Birthday";
            }
            else if (Field == "Номер телефона")
            {
                Field = "PhoneNumber";
            }
            else if (Field == "Опыт работы")
            {
                Field = "WorkExperience";
            }
            else
            {
                Field = "Education";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.Teacher;
        model->setQuery("Select TeacherName as 'Имя учителя', " + dbtable.Teacher + ".Gender as 'Пол', "
                        + dbtable.Teacher + ".Birthday as 'Дата рождения', " + dbtable.Teacher
                        + ".PhoneNumber as 'Номер телефона', WorkExperience as 'Опыт работы', Education as 'Образование', "
                        + dbtable.Teacher + ".TeacherID from " + name + query, db);
    }
    else if (name == "Расписание")
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Школа")
            {
                Field = "SchoolName";
            }
            else if (Field == "День недели")
            {
                Field = "Weekday";
            }
            else if (Field == "Класс")
            {
                Field = "ClassNameNumber";
            }
            else if (Field == "Предмет")
            {
                Field = "SubjectName";
            }
            else if (Field == "Учитель")
            {
                Field = "TeacherName";
            }
            else
            {
                Field = "ClassRoomName";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.Timetable;
        model->setQuery("Select " + dbtable.School + ".SchoolName as 'Школа', Weekday as 'День недели', "
                        + dbtable.ClassNames + ".ClassNameNumber as 'Класс', " + dbtable.Subjects + ".SubjectName as 'Предмет', "
                        + dbtable.Teacher + ".TeacherName as 'Учитель', " + dbtable.ClassRooms + ".ClassRoomName as 'Номер кабинета', TimeTableID from " + name
                        + " left join " + dbtable.School + " on " + dbtable.Timetable + ".SchoolID = " + dbtable.School + ".SchoolID "
                        + " left join " + dbtable.ClassNames + " on " + dbtable.Timetable + ".ClassNameID = " + dbtable.ClassNames + ".ClassNameID "
                        + " left join " + dbtable.Subjects + " on " + dbtable.Timetable + ".SubjectID = " + dbtable.Subjects + ".SubjectID "
                        + " left join " + dbtable.Teacher + " on " + dbtable.Timetable + ".TeacherID = " + dbtable.Teacher + ".TeacherID "
                        + " left join " + dbtable.ClassRooms + " on " + dbtable.Timetable + ".ClassRoomID = " + dbtable.ClassRooms + ".ClassRoomID " + query, db);
    }
    else if (name == "Классы")
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Класс")
            {
                Field = "ClassNameNumber";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.ClassNames;
        model->setQuery("Select " + dbtable.ClassNames + ".ClassNameNumber as 'Класс', " + dbtable.ClassNames
                        + ".ClassNameID from " + name + query, db);
    }
    else if (name == "Предметы")
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Предмет")
            {
                Field = "SubjectName";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.Subjects;
        model->setQuery("Select " + dbtable.Subjects + ".SubjectName as 'Предмет', " + dbtable.Subjects
                        + ".SubjectID from " + name + query, db);
    }
    else if (name == "Кабинеты")
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Кабинет")
            {
                Field = "ClassRoomName";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.ClassRooms;
        model->setQuery("Select " + dbtable.ClassRooms + ".ClassRoomName as 'Кабинет', " + dbtable.ClassRooms
                        + ".ClassRoomID from " + name + query, db);
    }
    else if (name == "Учитель и школа")
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Школа")
            {
                Field = "Schoolname";
            }
            else
            {
                Field = "TeacherName";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.TeacherAndSchool;
        model->setQuery("Select " + dbtable.School + ".Schoolname as 'Школа', " + dbtable.Teacher + ".TeacherName as 'Учитель', TeacherAndSchoolID from " + name
                        + " left join " + dbtable.School + " on " + dbtable.TeacherAndSchool + ".SchoolID = " + dbtable.School + ".SchoolID "
                        + " left join " + dbtable.Teacher + " on " + dbtable.TeacherAndSchool + ".TeacherID = " + dbtable.Teacher + ".TeacherID " + query, db);
    }
    else
    {
        if (!(Field.isEmpty()) || !(Value.isEmpty()))
        {

            if (Field == "Учитель")
            {
                Field = "TeacherName";
            }
            else
            {
                Field = "SubjectName";
            }
            query = " where " + Field + " = " + "'" + Value + "'";
        }
        name = dbtable.TeacherAndSubjects;
        model->setQuery("Select " + dbtable.Teacher + ".TeacherName as 'Учитель', " + dbtable.Subjects + ".SubjectName as 'Предмет', TeacherAndSubjectsID from " + name
                        + " left join " + dbtable.Teacher + " on " + dbtable.TeacherAndSubjects + ".TeacherID = " + dbtable.Teacher + ".TeacherID "
                        + " left join " + dbtable.Subjects + " on " + dbtable.TeacherAndSubjects + ".SubjectID = " + dbtable.Subjects + ".SubjectID " + query, db);
    }
    return model;
}

QSqlQueryModel* DbController::insertRowToTable(QString table_name, QStringList fields, QStringList values)
{
    QSqlQueryModel* model = new QSqlQueryModel;

    DbTable dbtable;
    int i = 0;
    QString query = "insert into " + table_name + " (";
    if (table_name == "School")
    {
        for(i = 0; i < fields.length() - 1; i++)
        {
            query += (fields[i] + ", ");
        }
        query += (fields[i] + ") values (");

        for(i = 0; i < values.length() - 1; i++)
        {
            query += ("'" + values[i] + "', ");
        }
        query += ("'" + values[i] + "')");

        model->setQuery(query, db);
    }
    else if (table_name == "Student")
    {
        for(i = 0; i < fields.length() - 3; i++)
            {
                query += (fields[i] + ", ");
            }
            query += ("SchoolID, ClassNameID, " + fields[6] + ") values (");

            for(i = 0; i < values.length() - 3; i++)
            {
                query += ("'" + values[i] + "', ");
            }
            query += ("(select SchoolID from " + dbtable.School + " where " + fields[4] + " = '" + values[4] + "')");
            query += (", (select ClassNameID from " + dbtable.ClassNames + " where " + fields[5] + " = '" + values[5] + "')");
            query += (", '" + values[6] + "')");

            model->setQuery(query, db);
    }
    else if (table_name == "Teacher")
    {
            for(i = 0; i < fields.length() - 1; i++)
            {
                query += (fields[i] + ", ");
            }
            query += (fields[i] + ") values (");

            for(i = 0; i < values.length() - 1; i++)
            {
                query += ("'" + values[i] + "', ");
            }
            query += ("'" + values[i] + "')");

            model->setQuery(query, db);
    }
    else if (table_name == "Timetable")
    {
        query += ("SchoolID, " + fields[1] + ", ClassNameID, SubjectID, TeacherID, ClassRoomID) values (");

        query += ("(select SchoolID from " + dbtable.School + " where " + fields[0] + " = '" + values[0] + "'), '" + values[1] + "', ");
        query += ("(select ClassNameID from " + dbtable.ClassNames + " where " + fields[2] + " = '" + values[2] + "'), ");
        query += ("(select SubjectID from " + dbtable.Subjects + " where " + fields[3] + " = '" + values[3] + "'), ");
        query += ("(select TeacherID from " + dbtable.Teacher + " where " + fields[4] + " = '" + values[4] + "'), ");
        query += ("(select ClassRoomID from " + dbtable.ClassRooms + " where " + fields[5] + " = '" + values[5] + "'))");

        model->setQuery(query, db);
    }
    else if (table_name == "ClassNames")
    {
        query += (fields[0] + ") values ('" + values[0] + "')");
        model->setQuery(query, db);
    }
    else if (table_name == "ClassRooms")
    {
        query += (fields[0] + ") values ('" + values[0] + "')");
        model->setQuery(query, db);
    }
    else if (table_name == "Subjects")
    {
        query += (fields[0] + ") values ('" + values[0] + "')");
        model->setQuery(query, db);
    }
    else if (table_name == "TeacherAndSchool")
    {
        query += ("TeacherID, SchoolID) values (");
        query += ("(select TeacherID from " + dbtable.Teacher + " where " + fields[0] + " = '" + values[0] + "'), ");
        query += ("(select SchoolID from " + dbtable.School + " where " + fields[1] + " = '" + values[1] + "'))");
        model->setQuery(query, db);
    }
    else
    {
        query += ("TeacherID, SubjectID) values (");
        query += ("(select TeacherID from " + dbtable.Teacher + " where " + fields[0] + " = '" + values[0] + "'), ");
        query += ("(select SubjectID from " + dbtable.Subjects + " where " + fields[1] + " = '" + values[1] + "'))");
        model->setQuery(query, db);
    }
    return model;
}

QSqlQueryModel* DbController::selectDeleteRowTable(QString table, int ID)
{
    QSqlQueryModel* model = new QSqlQueryModel;

    DbTable dbtable;
    QString query = "";
    QString id = QString::number(ID);

    if (table == "Школы")
    {
        table = dbtable.School;
        query = "Delete from " + table + " where " + dbtable.School + ".SchoolID = " + id;
    }
    else if (table == "Ученики")
    {
        table = dbtable.Student;
        query = "Delete from " + table + " where " + dbtable.Student + ".StudentID = " + id;
    }
    else if (table == "Учителя")
    {
        table = dbtable.Teacher;
        query = "Delete from " + table + " where " + dbtable.Teacher + ".TeacherID = " + id;
    }
    else if (table == "Расписание")
    {
        table = dbtable.Timetable;
        query = "Delete from " + table + " where " + dbtable.Timetable + ".TimetableID = " + id;
    }
    else if (table == "Классы")
    {
        table = dbtable.ClassNames;
        query = "Delete from " + table + " where " + dbtable.ClassNames + ".ClassNameID = " + id;
    }
    else if (table == "Предметы")
    {
        table = dbtable.Subjects;
        query = "Delete from " + table + " where " + dbtable.Subjects + ".SubjectID = " + id;
    }
    else if (table == "Кабинеты")
    {
        table = dbtable.ClassRooms;
        query = "Delete from " + table + " where " + dbtable.ClassRooms + ".ClassRoomID = " + id;
    }
    else if (table == "Учитель и школа")
    {
        table = dbtable.TeacherAndSchool;
        query = "Delete from " + table + " where " + dbtable.TeacherAndSchool + ".TeacherAndSchoolID = " + id;
    }
    else
    {
        table = dbtable.TeacherAndSubjects;
        query = "Delete from " + table + " where " + dbtable.TeacherAndSubjects + ".TeacherAndSubjectsID = " + id;
    }

    model->setQuery(query, db);
    return model;
}

QSqlError DbController::getLastError()
{
    return db.lastError();
}

const QString DbController::connection_string_sqlauth =
        QString("DRIVER={%1};SERVER=%2;PORT=%3;DATABASE=%4;UID=%5;PWD=%6");

const QString DbController::connection_string_winauth =
        QString("DRIVER={%1};SERVER=%2;PORT=%3;DATABASE=%4");
