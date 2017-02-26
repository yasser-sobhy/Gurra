#include "configi.h"

Configi::Configi()
{

}

void Configi::read(QString file)
{
    QFile filetoread(file);
    m_error.file = file;

    if (filetoread.open(QFile::ReadWrite)) {

        QTextStream stream(&filetoread);

        while(!stream.atEnd()){

            currentLine++;

            parseLine(stream.readLine().trimmed());
        }
    }
    else qDebug() << "Configi: couldn't open ini file";

    filetoread.close();
}

void Configi::parseLine(QString line)
{
    if(line.isEmpty()) return;

    // skiip comments lines, ; and # comments are supported
    if(line.startsWith(";") || line.startsWith("#")) return;

    // is it a section?
    if(line.startsWith("["))
    {
        if(line.endsWith("]"))
        {

            // create a new secton
            QString sectionName = line.remove("[").remove("]");
            ongoingSection = new ConfigiSection(sectionName);
            m_sections.insert(sectionName, ongoingSection);

            return;
        }
        else // invalid section name
        {
            m_error.error = InvalidSection;
            m_error.line = currentLine;
            return;
        }
    }

    // remove inline comments
    line = line.left(line.indexOf(";"));
    line = line.left(line.indexOf("#"));

    // if not comment or sesction, it must be a key-value
    QStringList keyValue = line.split("=");

    if(keyValue.size() == 2)
    {
        ongoingSection->values.insert(keyValue.at(0).trimmed(), keyValue.at(1).trimmed());
    }
    else //InvalidKey
    {
        m_error.error = InvalidKeyOrValue;
        m_error.line = currentLine;
    }
}

QVariant Configi::get(QString section, QString key, QString defaultValue){

    ConfigiSection *sction = m_sections.value(section);

    if(sction)
    {
        // if value found, return it
        if(sction->values.contains(key))
            return sction->values.value(key);

        // else, return inheretd value, if any
        else if(parent) return parent->get(section, key, defaultValue);

        // else, return an empty value
        else return defaultValue;
    }

    // else, return inheretd value, if any
    else if(parent) return parent->get(section, key, defaultValue);

    // else, return an empty value
    else return defaultValue;
}

void Configi::set(QString section, QString key, QString value){

    if(m_sections.contains(section))
        m_sections[section]->values[key] = value;
    else {
        m_sections.insert(section, new ConfigiSection(section));
        m_sections[section]->values[key] = value;
    }
}

void Configi::set(QString section, QString key, QStringList value){

    if(m_sections.contains(section))
        m_sections[section]->values[key] = value.join(",");
    else {
        m_sections.insert(section, new ConfigiSection(section));
        m_sections[section]->values[key] = value.join(",");
    }
}

void Configi::set(QString section, QString key, int value){

    m_sections[section]->values[key] = value;
}
void Configi::set(QString section, QString key, long value){

    //m_sections[section]->values[key] = value;
}
void Configi::set(QString section, QString key, double value){

    m_sections[section]->values[key] = value;
}
void Configi::set(QString section, QString key, QDate value){

    m_sections[section]->values[key] = value;
}
void Configi::set(QString section, QString key, QTime value){

    m_sections[section]->values[key] = value;
}
void Configi::set(QString section, QString key, QDateTime value){

    m_sections[section]->values[key] = value;
}

ConfigiError Configi::error(){

    return m_error;
}

ConfigiSection *Configi::section(QString name){

    return m_sections.value(name);
}
QList<ConfigiSection*> Configi::sections(){

    return m_sections.values();
}

QStringList Configi::sectionsNames(){

    return m_sections.keys();
}

void Configi::save()
{
    qDebug() << "Configi: saving";

    // not to be confusing, file name is just added to m_error at read() function
    QFile filetosave(m_error.file);

    if (filetosave.open(QFile::WriteOnly | QFile::Truncate)) {

        QTextStream stream(&filetosave);

        for(ConfigiSection *sction : m_sections)
        {
            stream << "[" << sction->name << "]" << "\n";

            for (QString key: sction->values.keys())
            {
                stream << key << " = " << sction->values.value(key).toString() << "\n";
            }

            stream << "\n\n"; // separate section with an empty line
        }
    }
    else qDebug() << "Configi: couldn't open ini file for saving";

    filetosave.close();

}
