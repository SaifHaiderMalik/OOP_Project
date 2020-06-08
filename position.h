void gotoxy(int x,int y)
{
 	COORD coord={0,0};
   coord.X=x-1;
   coord.Y=y-1;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int getX(){
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE ), &csbi);
   return csbi.dwCursorPosition.X+1;
}

int getY(){
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE ), &csbi);
   return csbi.dwCursorPosition.Y+1;
}