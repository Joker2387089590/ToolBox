#ifndef PICS_GLOBAL_H
#define PICS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PICS_LIBRARY)
#  define PICS_EXPORT Q_DECL_EXPORT
#else
#  define PICS_EXPORT Q_DECL_IMPORT
#endif

#endif // PICS_GLOBAL_H
