# wrestd

My standard C++ library. This basically is just a collection of my most-used classes/methods. Some classes may have better documentation in comments than the others do. This is simply because I don't plan on other people using this, and I already know what the things all do. In any case, most or all methods have short comments above their definitions that will tell you what they do.

## Usage
In order to use this, you just have to compile it with the included Makefiles:

```bash
make
# if you want to compile the test in the testing/ dir, you can do that from the root directory:
make test
```

After compilation, the things you will need are the library (`.so`) from `output/lib/` and the headers, basically the whole directory of `output/headers/wrestd`. To compile with the library:

```bash
g++ -Loutput/lib -lwrestd -Ioutput/headers/wrestd/ yourfile.cpp -std=c++14
```

Replace the paths with the locations you put the library at and the headers. Inside `yourfile.cpp`:

```c++
#include <wrestd/io.h> // if you get an error, remove wrestd/

using namespace wrestd::io;

...
```