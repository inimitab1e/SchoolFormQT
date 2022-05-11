#ifndef DBTABLES_H
#define DBTABLES_H
class DbTable
{
private:
    QString DbName = "SchoolDB.";
public:
    DbTable() {}
    QString School = DbName + "School";
    QString Student = DbName + "Student";
    QString Teacher = DbName + "Teacher";
    QString Timetable = DbName + "Timetable";
    QString Subjects = DbName + "Subjects";
    QString ClassNames = DbName + "ClassNames";
    QString ClassRooms = DbName + "ClassRooms";
    QString TeacherAndSchool = DbName + "TeacherAndSchool";
    QString TeacherAndSubjects = DbName + "TeacherAndSubjects";
};
#endif // DBTABLES_H
