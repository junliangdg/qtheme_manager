#pragma once

#include <QtCore/qglobal.h>

/**
 * @file qthemelib_global.h
 * @brief DLL export/import macro for QThemeLib.
 *
 * When building the shared library, define QTHEMELIB_LIBRARY so that
 * symbols are exported.  Consumers of the DLL get the import decoration
 * automatically.
 *
 * Static-library builds (QTHEMELIB_STATIC) skip the decoration entirely.
 */

#if defined(QTHEMELIB_STATIC)
#  define QTHEMELIB_EXPORT
#elif defined(QTHEMELIB_LIBRARY)
#  define QTHEMELIB_EXPORT Q_DECL_EXPORT
#else
#  define QTHEMELIB_EXPORT Q_DECL_IMPORT
#endif
