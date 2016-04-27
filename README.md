# wrestd
My standard C++ classes. This basically is just a collection of my most-used classes. Some classes may have better documentation in comments than the others do. This is simply because I don't plan on other people using this, and I already know what the things all do.

## Usage
In order to use this, you just have to include [`wrestd.h`](Code/wrestd.h). If you don't want certain classes, comment out the `#define` corresponding to it in the top of `wrestd.h`. This will make it easier to add the file back later on if you want to - just uncomment the line.

## Classes:
| Class | Header | Function |
| --- | --- | --- |
| IOManager | [`IOManager.h`](Code/IOManager.h) | Handles various IO-related things, both console and file IO. Adapts to multiple platforms. Supports colored console output on windows. |

## Methods
| Method | Function |
| --- | --- |
| `wrestd::substr_count()` | Counts the number of times a substring occurs in a string. Overlap by default. |
| `wrestd::substr_replace()` | Replaces all occurrences of a substring with another string. No overlap by default. |

## Cross-platform
This should be cross-platform. The IOManager class, for instance, will support printing in all kinds of colors on Windows, but should not do so on other platforms without raising errors. If I add any classes in the future that are only going to work on one platform, I will make sure that if you just use this code as-is on another platform, it will still work.

**Note:** I have not tested cross-platform compatibility much. If something does not work, feel free to make a pull request with a fix and (obviously) create and issue - I'll get there when I can.