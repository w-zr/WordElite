#ifndef RIO_LIBRARY_H
#define RIO_LIBRARY_H

#define RIO_BUFSIZE 8192
#define MAXLINE 1024

namespace rio {
    void initb(int fd);

    ssize_t writen(int fd, char const *usrbuf, size_t n);

    ssize_t readlineb(char *usrbuf, size_t maxlen);
}
#endif //RIO_LIBRARY_H