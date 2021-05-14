#ifndef KEYPAD
#define KEYPAD
#define KEYPAD_COUNT_CLOCK  0
#define KEYPAD_CLOCK        1
#define KEYPAD_FALL         2


char ch;    // keyboard 입력 값 저장용 버퍼

int kbhit();   // 터미널 입력: 입력 있으면 1, 없으면 0 반환
char getch();  // 입력받은 keyboard 값 반환

#endif