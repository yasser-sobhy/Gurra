#ifndef MIMETYPES_H
#define MIMETYPES_H

#include "configi.h"

class MimeTypes
{
public:
    MimeTypes(){

        configi.read("mime-types.ini");
        typesToExtentions();
    }

    QByteArray type(QByteArray extention){
        return types[extention];
    }

    QByteArray type(QString extention){
        return types[QByteArray().append(extention)];
    }

    QByteArray extention(QByteArray type){

        // list all type's extentions
        QByteArrayList list = configi.get("MIME-TYPES", type.trimmed()).toByteArray().split(',');

        // return first extention, considered as default
        if(!list.empty()) return list.at(0);

        return QByteArray();
    }

private:

    Configi configi;

    // in mime-types.ini, key is type name not extention
    // so reverse it here to map extention to type
    QHash<QByteArray, QByteArray> types;

    void typesToExtentions(){

        ConfigiSection *mime_section = configi.section("MIME-TYPES");

        if(mime_section)
        {
            for(QString type : mime_section->values.keys())
            {
                // list all extentions for every key
                QByteArrayList extentions = mime_section->values[type].toByteArray().split(',');

                // map extention for it's type
                for (QByteArray ext : extentions)
                {
                    types.insert(ext, QByteArray().append(type));
                }
            }
        }
    }

};

#endif // MIMETYPES_H
