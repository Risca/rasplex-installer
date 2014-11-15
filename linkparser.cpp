#include "linkparser.h"

#include <QByteArray>

#if QT_VERSION >= 0x050000
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStandardPaths>
#else
#include <qjson/parser.h>
#endif

LinkParser::LinkParser(const QByteArray &data)
{
    QVariantList releaseList;
    bool ok;

    #if QT_VERSION >= 0x050000
    releaseList = QJsonDocument::fromJson(data).toVariant().toList();
    #else
    QJson::Parser parser;

    releaseList = parser.parse(data, &ok).toList();
    Q_ASSERT(ok);
    #endif

    foreach (const QVariant &release, releaseList) {
        ok = release.canConvert<QVariantMap>();
        Q_ASSERT(ok);
        releaseData.append(release.toMap());
    }
}


QList<ReleaseData> LinkParser::releases() const
{
    return releaseData;
}
