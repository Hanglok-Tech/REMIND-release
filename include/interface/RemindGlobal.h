#pragma once
#include <QObject>

#if defined(NO_EXPORT_IMPORT)
    #define REMINDEXPORTDLL
#else
    #if defined(REMINDDLL_LIBRARY) || defined(REMINDDATADLL_LIBRARY)
        #define REMINDEXPORTDLL Q_DECL_EXPORT
    #else
        #define REMINDEXPORTDLL Q_DECL_IMPORT
    #endif
#endif

