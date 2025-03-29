#ifndef MOCK_UNISTD_H
#define MOCK_UNISTD_H

#define ssize_t int
#define size_t  int

ssize_t read(int fd, void *buf, size_t count);

ssize_t write(int fd, const void *buf, size_t count);

int unlink(const char *pathname);

int close(int fd);

#endif  // MOCK_UNISTD_H
