#pragma once
#include <QObject>
#include <QDate>
#include <vector>
#include "xpack.h"
using std::vector;

struct InfoPatient {
    enum enum_sex { male, female, unknown };
    QString     id;
    QString     cardId;
    QString     name;
    QString     birthdate;
    enum_sex    sex;
    QString     phone;
    QString     addr;
    QString     diseaseHitory;
    QString     familyDiseaseHitory;
    QString     surgeryHitory;
    int age;
    //list_sessionBaseInfo m_sessions;
//    int age() const {
//        if (! birthdate.isValid()) { return -1; }
//        return (QDate::currentDate().year() - birthdate.year());
//    }
//    QString getBirthdate() const {
//        if (!birthdate.isValid()) { return ""; }
//        return birthdate.toString("yyyy/MM/dd");
//    }
    XPACK(O(id, cardId, name, sex, phone, addr, diseaseHitory, familyDiseaseHitory, surgeryHitory, age, birthdate));
};

