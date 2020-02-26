#include "main.h"


#define SLAVE_ADDRESS_LCD 0x4E


void lcdInit(void);
void lcd_send_data(char data);
void lcd_send_cmd(char cmd);
void lcd_init(void);
void lcd_send_string(char *str);



