#ifndef VERSION_H
#define VERSION_H

#cmakedefine VERSION_MAJOR "@VERSION_MAJOR@"
#cmakedefine VERSION_MINOR "@VERSION_MINOR@"
#cmakedefine VERSION_PATCH "@VERSION_PATCH@"

#ifndef VERSION_MAJOR
#define VERSION_MAJOR "0"
#endif

#ifndef VERSION_MINOR
#define VERSION_MINOR "0"
#endif

#ifndef VERSION_PATCH
#define VERSION_PATCH "0"
#endif

#endif