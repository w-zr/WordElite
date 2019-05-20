//
// Created by wei on 19-4-28.
//

#include <unistd.h>
#include <cerrno>
#include <cstring>
#include "rio.hpp"

namespace rio {
    namespace {
        int rio_fd;
        int rio_cnt;
        char *rio_bufptr;
        char rio_buf[RIO_BUFSIZE]{};

        ssize_t r_read(char *usrbuf, size_t n) {
            int cnt;
            while (rio_cnt <= 0) {
                rio_cnt = read(rio_fd, rio_buf, sizeof rio_buf);
                if (rio_cnt < 0) {
                    if (errno != EINTR) return -1;
                } else if (rio_cnt == 0) return 0;
                else rio_bufptr = rio_buf;
            }
            cnt = n;
            if (rio_cnt < n) cnt = rio_cnt;
            memcpy(usrbuf, rio_bufptr, cnt);
            rio_bufptr += cnt;
            rio_cnt -= cnt;
            return cnt;
        }
    }

    void initb(int fd) {
        rio_fd = fd;
        rio_cnt = 0;
        rio_bufptr = rio_buf;
    }

    ssize_t writen(int fd, char const *usrbuf, size_t n) {
        size_t nleft = n;
        ssize_t nwritten;
        const char *bufp = usrbuf;
        while (nleft > 0) {
            if ((nwritten = write(fd, bufp, nleft)) <= 0) {
                if (errno == EINTR) nwritten = 0;
                else return -1;
            }
            nleft -= nwritten;
            bufp += nwritten;
        }
        return n;
    }

    ssize_t readlineb(char *usrbuf, size_t maxlen) {
        int n, rc;
        char c, *bufp = usrbuf;
        for (n = 1; n < maxlen; n++) {
            if ((rc = r_read(&c, 1)) == 1) {
                *bufp++ = c;
                if (c == '\n') {
                    n++;
                    break;
                }
            } else if (rc == 0) {
                if (n == 1) return 0;
                else break;
            } else return -1;
        }
        *bufp = 0;
        return n - 1;
    }
}