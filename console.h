void setConsoleSize(int cols, int lines)
{
	char consoleT[99];
	
	SendMessage(GetConsoleWindow(),WM_SYSKEYDOWN,VK_RETURN,0x20000000); //Fullscreen
	snprintf(consoleT, sizeof(consoleT), "mode con COLS=%d LINES=%d",cols, lines);
	system(consoleT);
}

void hideInput(bool b){
    HANDLE hStdin = ::GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    ::GetConsoleMode(hStdin, &mode);
    if(b){
        mode &= ~ENABLE_ECHO_INPUT;
    } else{
		mode |= ENABLE_ECHO_INPUT;
    }
    ::SetConsoleMode(hStdin, mode);
}