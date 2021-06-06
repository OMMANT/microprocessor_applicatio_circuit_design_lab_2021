//-------| src/clcd.c |-------//
#include "clcd.h"

static short * clcd_cmd, * clcd_data;

void init_clcd(short * address_cmd, short * address_data) {
	int D=1, C=0, B=0;
	int DL=1, N=1, F=0;
	
	clcd_cmd  = address_cmd;
	clcd_data = address_data;
	
	clcd_clear_display();
	clcd_return_home();
	clcd_display_control(D, C, B);
	clcd_function_set(DL, N, F);
}

void clcd_write_cmd(int cmd) {
	*clcd_cmd = (short)cmd; usleep(CLCD_CMD_US);
}
void clcd_write_data(int data) {
	*clcd_data = (short)data; usleep(CLCD_DATA_US);
}

void clcd_clear_display() {
	clcd_write_cmd(0x01); usleep(CLCD_RETURN_US);
}
void clcd_return_home() {
	clcd_write_cmd(0x02); usleep(CLCD_RETURN_US);
}
void clcd_entry_mode_set(int ID, int S) {
	int cmd = 1 << 2;
	if( ID != 0 ) { cmd |= (1 << 1); }
	if( S  != 0 ) { cmd |= (1 << 0); }
	clcd_write_cmd(cmd);
}
void clcd_display_control(int D, int C, int B) {
	int cmd = 1 << 3;
	if( D != 0 ) { cmd |= (1 << 2); }
	if( C != 0 ) { cmd |= (1 << 1); }
	if( B != 0 ) { cmd |= (1 << 0); }
	clcd_write_cmd(cmd);
}
void clcd_shift(int SC, int RL) {
	int cmd = 1 << 4;
	if( SC != 0 ) { cmd |= (1 << 3); }
	if( RL != 0 ) { cmd |= (1 << 2); }
	clcd_write_cmd(cmd);
}
void clcd_function_set(int DL, int N, int F) {
	int cmd = 1 << 5;
	if( DL != 0 ) { cmd |= (1 << 4); }
	if( N  != 0 ) { cmd |= (1 << 3); }
	if( F  != 0 ) { cmd |= (1 << 2); }
	clcd_write_cmd(cmd);
}
void clcd_set_DDRAM(int address) {
	int cmd = 1 << 7;
	cmd |= address;
	clcd_write_cmd(cmd);
}

void clcd_write_string(char str[]) {
	int i;
	for( i=0; (str[i] != 0); i++) {
		clcd_write_data(str[i]);
	}
}




static void clcd_set_RAM_address(unsigned short command, int DD_or_CG) {
	command &= ~(0x80);
	if (DD_or_CG) { command |= 0x80; }
	else { command |= 0x40; }
	clcd_write_cmd(command);  
}

void clcd_off() { clcd_clear_display(); }

// NEXT: 
// {SQUARE, CROSS, J, L, STRAIGHT}
char game_board[2][CLCD_MAX_CHAR+1] = {
	" NEXT :         ",
	"GRADE :         "};


char game_grade[CLCD_MAX_GRADE][CLCD_GRADE_LENGTH + 1] = {
	" SILVER ",
	"  GOLD  ",
	"PLATINUM",
	"DIAMOND "
};

char block_style[CLCD_BLOCK_TYPES][CLCD_TYPE_LENGTH + 1] ={
	" SQUARE  ",
	"  CROSS  ",
	"    J    ",
	"    L    ",
	"STRAIGHT "
};


void clcd_make_board() {
	int i;
	clcd_clear_display();
	clcd_return_home();
	for(i=0; i<CLCD_MAX_CHAR; i++){ clcd_write_data(game_board[0][i]); }
	clcd_set_RAM_address(0x40, CLCD_DD);
	for(i=0; i<CLCD_MAX_CHAR; i++){ clcd_write_data(game_board[1][i]); }
}

void clcd_update(int type, int score){
	int grade;
	int i;

	switch (score) {
		case 0 ... 20:
			grade = 0;
			break;
		case 21 ... 50:
			grade = 1;
			break;
		case 51 ... 70:
			grade = 2;
			break;
		default:
			grade = 3;
			break;
	}

	
	clcd_set_RAM_address(0x07, CLCD_DD);
	for(i=0; i<CLCD_MAX_CHAR; i++){ clcd_write_data(block_style[type][i]); }
	clcd_set_RAM_address(0x48, CLCD_DD);
	for(i=0; i<CLCD_GRADE_LENGTH; i++){
		clcd_write_data(game_grade[grade][i]);
	}
}
