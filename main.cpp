#include "mbed.h"
#include <string>
#include "cstdlib"
#include "TextLCD.h"

// Maximum number of element the application buffer can contain
#define MAXIMUM_BUFFER_SIZE 32
// Create a DigitalOutput object to toggle an LED whenever data is received.
static DigitalOut led(LED1);
// Create a BufferedSerial object with a default baud rate.
static BufferedSerial serial_port(USBTX, USBRX);

// I2C Communication
I2C i2c_lcd(D14, D15); // SDA, SCL
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2);

int main(void) {
    led = 0;
    lcd.setCursor(TextLCD::CurOff_BlkOn);
    char buf;
    while (true){
        if (serial_port.readable()){
            led = !led;
            uint32_t num = serial_port.read(&buf, 1);
            if (buf == '0'){
                char col[2];
                num = serial_port.read(&buf, 1);
                col[1] = buf;
                num = serial_port.read(&buf, 1);
                col[0] = buf;
                int column = (col[1] - '0') * 10 + (col[0] - '0');
                num = serial_port.read(&buf, 1);
                int row = buf - '0';
                lcd.locate(column, row);
            }else if (buf == '1'){
                lcd.cls();
            }else if (buf == '2'){
                printf("%d\n", lcd.rows());
            }else if (buf == '3'){
                printf("%d\n", lcd.columns());
            }else if (buf == '4'){
                num = serial_port.read(&buf, 1);
                lcd.putc(buf);
            }
        }
    }
}