# wrestd
**NOTE: This is out of date and I need to update this, but do not have time to at the moment.**

My standard C++ library. This basically is just a collection of my most-used classes/methods. Some classes may have better documentation in comments than the others do. This is simply because I don't plan on other people using this, and I already know what the things all do.

## Usage
In order to use this, you just have to include [`wrestd.h`](Code/wrestd.h).

After that, you can use things like this:

```c++
#include "wrestd.h"

using namespace wrestd;
using namespace wrestd::iofuncs;
using wrestd::iofuncs::clear();
```

Of course, you can always just use the fully qualified names, which does still require the inclusion of `wrestd.h`, obviously.

```c++
#include "wrestd.h"

int main() {
	wrestd::iofuncs::clear();
	std::cout << "'ha' is in 'hahaha' " << wrestd::substr_count("hahaha", "ha") << " times." << std::endl;
	
	return 0;
}
```

## Namespaces:
| Namespace | Definitions | Function |
| --- | --- | --- |
| [`wrestd::iofuncs`](Code/wrestd.h#L49) | [`iofuncs.cpp`](Code/iofuncs.cpp) | Handles various IO-related things, both console and file IO. Adapts to multiple platforms. Supports colored console output on windows. |

## Methods
| Method | Function |
| --- | --- |
| `wrestd::substr_count()` | Counts the number of times a substring occurs in a string. Overlap by default. |
| `wrestd::substr_replace()` | Replaces all occurrences of a substring with another string. No overlap by default. |

## Cross-platform
This should be cross-platform, at least as much as possible. For example, in `wrestd::iofuncs::setcolor()`, it will only do that if on Windows, and if you aren't, it will simply print it in normal colors.

**Note:** I have not tested cross-platform compatibility much. If something does not work, feel free to make a pull request with a fix and (obviously) create an issue - I'll get there when I can.