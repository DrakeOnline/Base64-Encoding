#include <stdio.h>
#include <limits.h>

int main() {
    // String to encode
    unsigned char data[] = "test";
    
    // Buffer for byte transformation
    unsigned char buffer[3] = { 0 };

    // Dynamically gets string length
    char data_length = sizeof(data);

    // Prints string
    printf("\n");
    for (int i = 0; i < data_length - 1; ++i) {
        printf("%c", data[i]);
    }
    printf(" ==> ");
    
    // Convert each character from ASCII to their base-64 value
    // +   = 43
    // /   = 47
    // 0-9 = 48-57
    // A-Z = 65-90
    // a-z = 97-120
    for (int i = 0; i < data_length - 1; ++i) {
        // +
        if (data[i] == 43) {
            data[i] = 62;
        // /
        } else if (data[i] == 47) {
            data[i] = 63;
        // 0 - 9
        } else if (data[i] >= 48 && data[i] <= 57) {
            data[i] += 4;
        // A - Z
        } else if (data[i] >= 65 && data[i] <= 90) {
            data[i] -= 65;
        // a - z
        } else if (data[i] > 97 && data[i] <= 123) {
            data[i] -= 71;
        }
    }
    
    for (int i = 0; i < data_length - 1; i += 4) {
        // Our 6-bit chunks
        unsigned char byte0 = data[i];
        unsigned char byte1 = data[i + 1];
        unsigned char byte2 = data[i + 2];
        unsigned char byte3 = data[i + 3];

        // Shifts bits to create 8-bit chunks
        buffer[0]    = byte0 << 2;
        buffer[0]   |= byte1 >> 4;

        buffer[1]    = byte1 << 4;
        buffer[1]   |= byte2 >> 2;

        buffer[2]    = byte2 << 6;
        buffer[2]   |= byte3;

        for (int b = 0; b < 3; ++b) {
            printf("0x%02hhx ", buffer[b]);
        }
    }
    printf("\n");

}