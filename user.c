#include "header.h"

void print_error(int err, char *msg) {
    if (err == -1) {
        // If Error Print Error Message and Errno
        printf("Error: %s\n", msg);
        printf("%s\n", strerror(errno));
    }
}

int main() {
    // Attempting To Create User To Worker Pipe
    int err1 = mkfifo("user_to_worker", 0644);
    if (err1 == -1) {
        print_error(-1, "Unable To Create User To Worker Named Pipe");
        return -1;
    }

    // Attempting To Create Worker To User Pipe
    int err2 = mkfifo("worker_to_user", 0644);
    if (err2 == -1) {
        print_error(-1, "Unable To Create Worker To User Named Pipe");
        return -1;
    }

    // Attempting To Open User To Worker Pipe
    int write_file = open("user_to_worker", O_WRONLY);
    if (write_file == -1) {
        print_error(-1, "Unable To Open User To Worker Named Pipe");
        return -1;
    }

    // Attempting To Open Worker To User Pipe
    int read_file = open("worker_to_user", O_RDONLY);
    if (read_file == -1) {
        print_error(-1, "Unable To Open Worker To User Named Pipe");
        return -1;
    }

    // Variable Declaration
    char *buff = calloc(BUFF_SIZE, sizeof(char));

    // Constantly Runs
    while (1) {
        // Asking For User Input
        printf("Message To Worker: ");
        fgets(buff, BUFF_SIZE, stdin);
        *strchr(buff, '\n') = '\0';

        // Quit Or Exit Command
        if (strcmp(buff, "exit") == 0 || strcmp(buff, "quit") == 0) break;

        // Writing To User To Worker Pipe
        int err3 = write(write_file, buff, BUFF_SIZE);
        if (err3 == -1) {
            print_error(-1, "Unable To Write To User To Worker Named Pipe");
            continue;
        }

        // Reading From Worker To User Pipe
        int err4 = read(read_file, buff, BUFF_SIZE);
        if (err4 == -1) {
            print_error(-1, "Unable To Read From Worker To User Name Pipe");
            continue;
        }
        printf("Message From Worker: %s\n", buff);
    }

    // Exiting Normally
    free(buff);
    return 0;
}
