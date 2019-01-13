#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 120

// globals
const int width = 120;
int offset = 10;
HANDLE wHnd;
HANDLE rHnd;

struct pos
{
	int x;
	int y;	
};
struct pos Pos;

//Prototypes
void setPos(int x, int y, HANDLE hConsole);
void cls( HANDLE hConsole );
unsigned int pseudoRandom(unsigned int start_range, unsigned int end_range);
void printChar(int offsets);

int main(int argc, char* argv[])
{
	// Set up the handles for reading/wrinting
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle("asteroid !!");

	SMALL_RECT windowSize = {0, 0, width, 30};
	SetConsoleWindowInfo(wHnd, 1, &windowSize);

	COORD bufferSize = {20, 20};
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	HANDLE hStdout;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hStdout);



	// qu'est-ce que je fais ? game loop ??
	Pos.x = 30;
	Pos.y = 30;
	//game loop
	while(1)
	{
		setPos(Pos.x++,Pos.y++, hStdout);
		printChar(offset);
	}

	// Exit 
	return(0);
}

void setPos(int x, int y, HANDLE hConsole)
{
	COORD coordScreen = { x, y };
	SetConsoleCursorPosition( hConsole, coordScreen );
}

void cls( HANDLE hConsole )
{
   COORD coordScreen = { 0, 0 };    // home for the cursor 
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi; 
   DWORD dwConSize;

	// Get the number of character cells in the current buffer. 
   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
   {
      return;
   }

   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   // Fill the entire screen with blanks.
   if( !FillConsoleOutputCharacter( hConsole,        // Handle to console screen buffer 
                                    (TCHAR) ' ',     // Character to write to the buffer
                                    dwConSize,       // Number of cells to write 
                                    coordScreen,     // Coordinates of first cell 
                                    &cCharsWritten ))// Receive number of characters written
   {
      return;
   }

   // Get the current text attribute.
   if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
   {
      return;
   }

   // Set the buffer's attributes accordingly.
   if( !FillConsoleOutputAttribute( hConsole,         // Handle to console screen buffer 
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute 
                                    coordScreen,      // Coordinates of first cell 
                                    &cCharsWritten )) // Receive number of characters written
   {
      return;
   }

   // Put the cursor at its home coordinates.
   SetConsoleCursorPosition( hConsole, coordScreen );
}

void printChar(int offsets)
{
		//fair en sorte que tant que l'usager n'appuie pas sur une lettre on continue le program
	int nbBuffer = 0; 

	//while(1)
	{
		char buffer[120];
		int i = 0;
		while(i < width - offsets)
		{
			if(i == width - offsets)
				buffer[width - offsets] = '\0';
			else if(i < offsets)
				buffer[i] = ' ';
			else 
				buffer[i] = pseudoRandom(33, 255);

			i++;
		}

		printf("%s \n", buffer);

		nbBuffer++;
		_sleep(60);
	}
}

unsigned int pseudoRandom(unsigned int start_range, unsigned int end_range)
{
	static unsigned int rand = 44257;

	if(start_range == end_range){
		return start_range;
	}

	rand += 941;
	rand %= end_range;

	while(rand < start_range){
		rand = rand + end_range - start_range;
	}
	return rand;
}