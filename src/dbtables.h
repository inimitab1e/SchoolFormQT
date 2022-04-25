#ifndef DBTABLES_H
#define DBTABLES_H
class DbTable
{
private:
    QString DbName = "schoolBD.";
public:
    DbTable() {}
    QString School = DbName + "School";
    QString Student = DbName + "Student";
    QString Teacher = DbName + "Teacher";
    QString Timetable = DbName + "Timetable";
    QString Subjects = DbName + "Subjects";
    QString QualificationCategories = DbName + "QualificationCategories";
    QString ClassNames = DbName + "ClassNames";
    QString Classes = DbName + "Classes";
    QString TeacherAndSchool = DbName + "TeacherAndSchool";
    QString TeacherAndSubjects = DbName + "TeacherAndSubjects";
};
#endif // DBTABLES_H
