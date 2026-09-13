#include <cstdio>
#include <string>
#include <print> //! Requires C++ 23
#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

// Borrow from https://stackoverflow.com/a/23370070
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

using namespace std;

short minLim = 0, maxLim = 10;

void setTestLengthRange(short &minL, short &maxL)
{
    while (true)
    {
        string length;
        print("請輸入你想要測驗的長度 (s / m / l / 短 / 中 / 長 / q / 離): ");
        getline(cin, length);
        if (length == "s" || length == "短") {
            minL = 0;
            maxL = 10;
            return;
        } else if (length == "m" || length == "中") {
            minL = 10;
            maxL = 30;
            return;
        } else if (length == "l" || length == "長") {
            minL = 30;
            maxL = 60;
            return;
        } else if (length == "q" || length == "離")
        {
            exit(0);
        } else {
            println("請重新依照提示輸入長度");
        }
    }
}  // rewrote by Gemini

size_t getUtf8Length(const string& str) {
    size_t length = 0;
    for (char c : str) {
        // UTF-8 的後續 bytes 都是 10xxxxxx (0x80 ~ 0xBF)，跳過它們
        if ((static_cast<unsigned char>(c) & 0xC0) != 0x80) {
            length++;
        }
    }
    return length;
}  // Wrote by Gemini

int getConsoleWidth()
{   // Borrow from https://stackoverflow.com/a/23370070
    #ifdef WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    #endif
}

int main(int argc, char const *argv[])
{
    string section[] = 
    {
        "這個是一個中文打字速度的測驗",
        "這只有六個字",
        "今天天氣非常好",  
        "喝一杯熱咖啡",     
        "每天都要開心生活", 
        "鍵盤敲擊聲很清脆", 
        "這是一隻可愛的小貓",
        "保持專注全力以赴",
        "窗外的陽光灑在桌面上微風輕輕吹過帶來夏天的氣息",  
        "練習打字需要持之以恆每天進步一點點就能看到成果",  
        "傍晚的天空被夕陽染成金黃色讓人感到無比放鬆與平靜",
        "閱讀一本好書就像是跟一位有智慧的朋友在安靜地對話",
        "一杯溫熱的烏龍茶伴隨著書香這就是最愜意的午後時光",
        "生活就像一場精彩的旅行我們在路途中會遇到許多不同的風景只要保持一顆好奇的心就能發現身邊美好的事物", 
        "學習一門新的技能最困難的往往不是技巧本身而是能否堅持下去只要每天花一點時間練習時間自然會給你最好的答案", 
        "清晨的陽光穿透樹葉灑下斑駁的光影微風吹拂帶來青草的清新氣息整個世界彷彿都在這一刻慢慢甦醒過來", 
        "寫程式的時候最重要的是邏輯與耐心面對看似無法解決的錯誤只要靜下心來一步步除錯最終都能找到問題的核心所在"
    };

    bool run = true;
    srand(static_cast<unsigned int>(time(0)));
    
    setTestLengthRange(minLim, maxLim);
    
    while (run)
    {
        // Create and assign per-loop vars and choose test string
        string runChoice = "r";
        string q, a;
        do
        {   // Choose a string that sufficients user's prefrence
            q = section[rand() % size(section)];
        } while (getUtf8Length(q) < minLim || getUtf8Length(q) > maxLim);
        
        // Preview and wait
        println();
        string preview = "";
        for (short i = 0; i < 6; i++)
            preview += q[i];
        print("準備好後按下 Enter 鍵\n{}", preview);
        getline(cin, a); a = "";

        println("\033[A\r\033[K{}", q);  // Clear the preview text and display the full test string

        auto start_time = chrono::steady_clock::now();

        // Start input
        getline(cin, a);
        while (!a.empty() && (a.back() == '\r' || a.back() == ' '))
            a.pop_back();  // by Gemini, handling \r char and any space characters
        a.erase(remove(a.begin(), a.end(), ' '), a.end());  // by Gemini, removing trailing \n and space

        auto end_time = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

        // Display errors
        short errors = 0;
        bool detectedNEL = false;  // detected Not Enough Length
        for (int i = 0; i < size(q); i += 3)
        {
            if (i + 3 > a.size())  // Length not enough
            {   if (!detectedNEL) print("|");
                errors++;
                detectedNEL = true;
                continue;
            }  // This if is based on Gemini
            bool match = true;
            for (int j = i; j < i + 3; j++)  // Detect wrong char. Each Chinese char is 3B
                if (a[j] != q[j])
                {   match = false;
                    errors++;
                    break;
                }
                
            if (getUtf8Length(q) <= (int)(getConsoleWidth() / 2))
            {
                if(match) print("  ");
                else print(" ͯ ");
            }
            else
            {
                if(match) print("Ｏ");
                else print("Ｘ");
            }
        }
        println();

        // Calculate CPMs
        float rawCPM = getUtf8Length(a) / max(duration.count() / 60000.0f, 0.0001f);
        float cpm = max(0, (int)(getUtf8Length(q) - errors)) / max(duration.count() / 60000.0f, 0.0001f);

        // Output result
        println("花費時間: {:.2f} 秒", duration.count() / 1000.0);
        if (cpm == rawCPM)
            println("|>> {:.2f} CPM <<|\n", cpm);
        else
            println("|>> {:.2f} CPM <<|\n{:.2f} CPM (RAW)", cpm, rawCPM);
        println("總字數: {} | 正確字數: {} | 錯誤字數: {} | 正確率: {:.2f}%", getUtf8Length(q), getUtf8Length(q) - errors, errors, ((getUtf8Length(q) - (float)errors) / getUtf8Length(q)) * 100);

        do  // Again?
        {
            print("\n再來一次?\nr / 再 / 在: 再來一次\ts / 設: 進入設置\tq / 離: 離開\n > ");
            getline(cin, runChoice);
            if (runChoice == "r" || runChoice == "再" || runChoice == "在") 
            {   run = true;
                break;
            } else if (runChoice == "s" || runChoice == "設") 
            {   setTestLengthRange(minLim, maxLim);
                break;
            } else if (runChoice == "q" || runChoice == "離")
            {   run = false;
                break;
            } else println("\n請依照提示輸入指令");
        } while (true);
    }
    
    return 0;
}