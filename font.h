void setFontSize(int FontSize, int fontWeight, wchar_t fontName[])
{
	//wprintf(fontName);
    CONSOLE_FONT_INFOEX info = {0};
    info.cbSize       = sizeof(info);
    //info.dwFontSize.X = 0;
    info.dwFontSize.Y = FontSize;
    info.FontWeight   = fontWeight;
    
    //Function to copy wide string data type from one variable to another variable
    wcscpy(info.FaceName, fontName);
    
    //Actual fuction which takes information from "info" and change FontAttributes
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 1, &info);
}