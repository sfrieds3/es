#include <stdio.h>
#include <fcntl.h>

#define PAGE_SIZE 20
#define LINE_WIDTH 80

void display_page()
{
	
}

int load_file(const char* fname)
{
        int fd = open(fname, O_RDONLY);
        return fd;
}

int main(int argc, char* argv[])
{
        int fd = load_file("/home/scwfri/tmp");
        printf("Got fd: %d", fd);
}
