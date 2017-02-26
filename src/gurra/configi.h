#ifndef CONFIGI_H
#define CONFIGI_H

#include <QList>
#include <QVariant>
#include <QVariantList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

struct ConfigiError
{
    int error;
    QString file;
    int line;
};

enum ConfigiErrors
{
    InvalidSection,
    InvalidKeyOrValue
};

struct ConfigiSection
{
    ConfigiSection(QString sectionName): name {sectionName}{}

    QString name;
    QHash<QString, QVariant> values;
};

class Configi
{
public:
    Configi();

    QVariant get(QString section, QString key, QString defaultValue = "");

    void set(QString section, QString key, QString value);
    void set(QString section, QString key, QStringList value);
    void set(QString section, QString key, int value);
    void set(QString section, QString key, long value);
    void set(QString section, QString key, double value);
    void set(QString section, QString key, QDate value);
    void set(QString section, QString key, QTime value);
    void set(QString section, QString key, QDateTime value);

    void read(QString file);
    void save();

    ConfigiError error();

    ConfigiSection *section(QString name);
    QList<ConfigiSection*> sections();
    QStringList sectionsNames();

private:
    void parseLine(QString line);

    Configi *parent = nullptr;
    QHash<QString, ConfigiSection *> m_sections;
    ConfigiSection *ongoingSection = nullptr;
    ConfigiError m_error;
    int currentLine = 0;
};

#endif // CONFIGI_H
