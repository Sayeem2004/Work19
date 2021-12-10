#include "header.h"

void print_error(int err, char *msg) {
    if (err == -1) {
        // If Error Print Error Message and Errno
        printf("Error: %s\n", msg);
        printf("%s\n", strerror(errno));
    }
}

int main() {
    // Attempting To Open User To Worker Pipe
    int read_file = open("user_to_worker", O_RDONLY);
    if (read_file == -1) {
        print_error(-1, "Unable To Open User To Worker Named Pipe");
        return -1;
    }

    // Attempting To Open Worker To User Pipe
    int write_file = open("worker_to_user", O_WRONLY);
    if (write_file == -1) {
        print_error(-1, "Unable To Open Worker To User Named Pipe");
        return -1;
    }

    // Variable Declaration
    char *buff = calloc(BUFF_SIZE, sizeof(char));

    // Constantly Runs
    while (1) {
        // Reading From User To Worker Pipe
        int err1 = read(read_file, buff, BUFF_SIZE);
        if (err1 == -1) {
            print_error(-1, "Unable To Read From User To Worker Named Pipe");
            continue;
        }

        // String Manipulation (Upper Case)
        int i;
        for (i = 0; i < BUFF_SIZE; i++) {
            if (buff[i] == '\0') break;
            buff[i] = toupper(buff[i]);
        }

        // Writing To Worker To User Pipe
        int err2 = write(write_file, buff, BUFF_SIZE);
        if (err2 == -1) {
            print_error(-1, "Unable To Write To Worker To User Named Pipe");
            continue;
        }
    }

    // Exit Normally
    free(buff);
    return 0;
}
