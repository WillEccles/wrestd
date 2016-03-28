// comment out the classes you don't want - I recommend this instead of removing the #include for the file
// it's easier to drop the file back in if you want to later on
#define IOMANAGER

#include <stdio.h>

// this is a collection of all of my frequently-used custom-made classes
// including this file is a convenient way to get at them
#ifdef IOMANAGER
#include "IOManager.h"
#endif