/*----------COPYRIGHT-------------------------
(c) Copyright Will Eccles, 2016
----------------------------------------------*/

/*----------LICENSE---------------------------
This software is licensed under the Apache license. See LICENSE file to learn more.
----------------------------------------------*/

/*----------DESCRIPTION-----------------------
This is a collection of my frequently used classes and methods. They can be selected below.
----------------------------------------------*/

/*----------INSTRUCTIONS----------------------
Comment out the classes you don't want - I recommend this instead of removing the #include for the file.
It's easier to drop the file back in if you want to later on.
----------------------------------------------*/

#define IOMANAGER

// since I often want to have this in my projects, I just went ahead and added it here.
#include <stdio.h>

// include classes, as selected above
#ifdef IOMANAGER
#include "IOManager.h"
#endif

#include <string>

// My namespace, which contains helpful methods and such.
namespace wrestd {
	int substr_count(std::string, std::string, bool);
	std::string substr_replace(std::string&, std::string, std::string, bool, bool);
}