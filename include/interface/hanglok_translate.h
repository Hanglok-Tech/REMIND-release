#pragma once
#include <QObject>
#include <QMap>
#include <memory>

using namespace std;

#if defined(TRANSLATEDLL_LIBRARY)
#  define TRANSLATEEXPORTDLL Q_DECL_EXPORT
#else
#  define TRANSLATEEXPORTDLL Q_DECL_IMPORT
#endif

#define Trans(__VA_ARGS__)  HanglokTranslate::Inst()->Translate(__VA_ARGS__)

struct InfoTranslate;
class TRANSLATEEXPORTDLL HanglokTranslate : public QObject {
    Q_OBJECT
public:
    static HanglokTranslate *Inst() {
        static HanglokTranslate t;
        return &t;
    }
    bool Init();
    void SetLanguage(const QString &lang);
    QString Translate(const QString &content);
    QString GetCurrentLanguage();
private:
    HanglokTranslate() {}
    ~HanglokTranslate() {}
private:
    bool m_init = false;
    shared_ptr<InfoTranslate> m_info = nullptr;
};
