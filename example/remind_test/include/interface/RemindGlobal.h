#ifndef REMIND_GLOBAL_H
#define REMIND_GLOBAL_H

#if defined(NO_EXPORT_IMPORT)
    #define REMINDEXPORTDLL
#else
    #if defined(REMINDDLL_LIBRARY) || defined(REMINDDATADLL_LIBRARY)
        #define REMINDEXPORTDLL Q_DECL_EXPORT
    #else
        #define REMINDEXPORTDLL Q_DECL_IMPORT
    #endif
#endif


#endif // REMIND_GLOBAL_H
