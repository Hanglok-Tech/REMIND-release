#pragma once

#include <QtCore/qglobal.h>

#if defined(REMIND_LIBRARY)
#  define REMIND_EXPORT Q_DECL_EXPORT
#else
#  define REMIND_EXPORT Q_DECL_IMPORT
#endif
