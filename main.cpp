#include <cstdio>

int main() {
    FILE *fp;
    int i;
    char buffer[1024*1024]; // Buffer size of 1 MB

    // Open file for writing
    fp = fopen("ccb.json", "w");
    if (fp == nullptr) {
        printf("Error opening file.\n");
        return 1;
    }

    // Write JSON structure to buffer
    int offset = sprintf(buffer, "{\n  \"variants\": {\n");
    const int bufferLimit = sizeof(buffer) - 100; // Leave some space for safety
    for (i = 0; i <= 16581375; ++i) {
        offset += sprintf(buffer + offset, R"(    "color=%d":{"model":"minecraft:block/white_concrete"})", i);
        if (i < 16581375) {
            offset += sprintf(buffer + offset, ",");
        }
        offset += sprintf(buffer + offset, "\n");

        // Write buffer to file if nearing the limit
        if (offset >= bufferLimit) {
            fwrite(buffer, 1, offset, fp);
            offset = 0; // Reset offset
        }
    }
    offset += sprintf(buffer + offset, "  }\n}\n");

    // Write remaining buffer content to file
    if (offset > 0) {
        fwrite(buffer, 1, offset, fp);
    }

    // Close file
    fclose(fp);

    printf("JSON file generated successfully.\n");

    return 0;
}