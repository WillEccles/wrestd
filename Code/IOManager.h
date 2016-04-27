#include <string>

#ifdef _WIN32
#define ISWINDOWS 1
#else
#define ISWINDOWS 0
#endif

#define BLACK 0
#define DARKBLUE 1
#define DARKGREEN 2
#define DARKTEAL 3
#define DARKRED 4
#define DARKMAGENTA 5
#define DARKYELLOW 6
#define DARKWHITE 7
#define DARKGREY 8
#define BLUE 9
#define GREEN 10
#define TEAL 11
#define RED 12
#define MAGENTA 13
#define YELLOW 14
#define WHITE 15

using namespace std;

/* This class handles IO functions. */
class IOManager
{
public:
	IOManager();
	IOManager(int);
	void printc(string, int);
	void printlc(string, int);
	void clear();
	void wait();
	void wait(string);
	void setColor(int);
	int DEFAULT;
	bool fileExists(char[]);
};

