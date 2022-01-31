/// @file server.hpp
/// @brief Basic TCP server

#ifndef SERVER_HPP
#define SERVER_HPP

#include <mutex>
#include <thread>

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Base class for TCP servers
    class server
    {
        public:
        /// @brief Constructor
        /// @param port The TCP port to listen on
        server(const short port);

        /// @brief Destructor
        virtual ~server();

        /// @brief Create TCP socket and start listener thread
        /// @details Listener thread will accept a single active connection and process received messages until stop is
        /// called. If the connection terminates but the listener fd is still open it will accept a new connection.
        /// @return True on success, else false
        bool start_listen_thread();

        /// @brief Close TCP socket and terminate the listening thread
        void stop_listen_thread();

        protected:
        /// @brief Pure virtual function that is called when a message is received
        /// @param message The string received from the TCP socket
        virtual void on_receive(const std::string& message) = 0;

        private:
        /// @brief Read buffer length
        static constexpr auto READ_BUFLEN{1024};
        /// @brief The port to listen on
        const short m_port;
        /// @brief The thread that reads input from stdin
        std::thread m_read_thread{};
        /// @brief Mutex protecting the listen and connection file descriptor access
        std::mutex m_fd_mutex;
        /// @brief The listener file descriptor
        int m_listen_fd{0};
        /// @brief The active connection file descriptor
        int m_conn_fd{0};

        /// @brief Listens for TCP connections and reads from connection, calling on_receive
        /// with the message contents
        /// @param port The port to listen on
        /// @return True on successful creation of listener, else False
        void tcp_listen(const short port);
    };
} /// namespace services

#endif /// SERVER_HPP
