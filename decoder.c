#include <stdio.h>

int main() {

    // Data to parse
    unsigned char source[3] = { 0xb5, 0xeb, 0x2d };

    // Buffer for data processing
    char buffer[4] = { 0 };

    // Dynamically sets loop end based on data size
    int source_length = sizeof(source);
    
    // Print our data
    for (int i = 0; i < source_length; ++i) {
        printf("0x%02x ", source[i]);
    }
    printf("==> ");

    // Selects 3 8-byte chunks at a time to turn into 4 6-byte chunks
    for (int i = 0; i < source_length; i += 3) {
        // Our 8-byte chunks
        unsigned char byte0 = source[i];
        unsigned char byte1 = source[i + 1];
        unsigned char byte2 = source[i + 2];

        // Divides 3 8-byte chunks into 4 6-byte buffer slots
        // 0b'xxxx'xxxx ==> 0b'00xx'xxxx        
        buffer[0]   = byte0 >> 2;
        
        // 0x03 = 0b`0000`00xx ==> 0b'00xx'0000
        // 0xf0 = 0b`xxxx`0000 ==> 0b'00xx'xxxx
        buffer[1]   =  (byte0 & 0x03) << 4;
        buffer[1]   |= (byte1 & 0xf0) >> 4;

        // 0x0f = 0b'0000'xxxx ==> 0b'00xx'xx00
        // 0xc0 = 0b'xx00'0000 ==> 0b'00xx'xxxx
        buffer[2]   =  (byte1 & 0x0f) << 2;
        buffer[2]   |= (byte2 & 0xc0) >> 6;

        // 0x3f = 0b'00xx'xxxx
        buffer[3]   = byte2 & 0x3f;

        for (int b = 0; b < 4; b++) {
            if (buffer[b] < 26) {
                // Prints value 0-25, an uppercase letter
                printf("%c", 'A' + buffer[b]);
            } else if (buffer[b] < 52) {
                // Prints value 26-51, a lowercase letter
                printf("%c", 'a' + (buffer[b] - 26));
            } else if (buffer[b] < 62) {
                // Prints value 52-61, a digit
                printf("%c", '0' + (buffer[b] - 52));
            } else if (buffer[b] == 62) {
                printf("+", buffer[b]);
            } else if (buffer[b] == 63) {
                printf("/", buffer[b]);
            } else {
                // Should never run
                printf("\n\n Error! Bad 6-bit value: %c\n", buffer[b]);
            }  
        }
    }
    printf("\n");
}