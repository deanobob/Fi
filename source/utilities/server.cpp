/// @file server.cpp

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <memory>
#include <poll.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include "plog/Log.h"
#include "server.hpp"
#include "strings.hpp"

namespace utilities
{
    server::server(const short port)
        : m_port{port}
    {

    }

    server::~server()
    {
        stop_listen_thread();
    }

    bool server::start_listen_thread()
    {
        if (m_read_thread.joinable())
        {
            // Wait for thread if running before starting new
            m_read_thread.join();
        }
        m_read_thread = std::thread(&server::tcp_listen, this, m_port);

        return true;
    }

    void server::stop_listen_thread()
    {
        // Close file descriptors if open, terminating the read thread
        {
            std::lock_guard<std::mutex> lock(m_fd_mutex);
            if (m_listen_fd > 0)
            {
                shutdown(m_listen_fd, SHUT_RDWR); // Required for Linux
                close(m_listen_fd); // Required for Mac OS
                m_listen_fd = 0;
            }

            if (m_conn_fd > 0)
            {
                shutdown(m_conn_fd, SHUT_RDWR); // Required for Linux
                close(m_conn_fd); // Required for Mac OS
                m_conn_fd = 0;
            }
        }

        if (m_read_thread.joinable())
        {
            // Wait for thread if running before starting new
            m_read_thread.join();
        }
    }

    void server::tcp_listen(const short port)
    {
        struct sockaddr_in serv_addr{};
        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(port);

        m_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
        bind(m_listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

        if (listen(m_listen_fd, port) != 0)
        {
            PLOGD << "Failed to start listener";
            return;
        }

        while (m_listen_fd > 0)
        {
            m_conn_fd = accept(m_listen_fd, (struct sockaddr*)NULL, NULL);
            if (m_conn_fd < 0)
            {
                break;
            }

            ssize_t n = 0;
            char recv_buf[READ_BUFLEN]{'\0'};
            while ((n = read(m_conn_fd, recv_buf, sizeof(recv_buf) - 1)) >= 0)
            {
                if (n <= 0)
                {
                    break;
                }

                // Terminate buffer
                recv_buf[n] = 0;

                for (const auto cmd_str : utilities::strings::tokenise(recv_buf, '\n'))
                {
                    if (cmd_str.length() > 0)
                    {
                        on_receive(std::string(cmd_str.substr(0, cmd_str.length() - 1)));
                    }
                }
            }

            if (m_conn_fd > 0)
            {
                close(m_conn_fd);
            }
        }

        if (m_listen_fd > 0)
        {
            close(m_listen_fd);
        }
    }
}
