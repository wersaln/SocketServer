//
// chat_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

//----------------------------------------------------------------------

typedef std::deque<std::string> chat_message_queue;

//----------------------------------------------------------------------
const int header_length = 2;
int decode_header(const char* str) {

  return str[1] + str[0] * 256;
}


class chat_session
  : public boost::enable_shared_from_this<chat_session>
{
public:
  chat_session(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    //room_.join(shared_from_this());
    std::cout << "new connection\n";
    boost::asio::async_read(socket_,
        boost::asio::buffer( data, header_length),
        boost::bind(
          &chat_session::handle_read_header, shared_from_this(),
          boost::asio::placeholders::error));
  }
/*
  void deliver(const chat_message& msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      boost::asio::async_write(socket_,
          boost::asio::buffer(write_msgs_.front().data(),
            write_msgs_.front().length()),
          boost::bind(&chat_session::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
  }
*/
  void handle_read_header(const boost::system::error_code& error)
  {
    std::cout << "header\n[" << (int)data[0] <<  "][" << (int)data[1] << "]\n";
    body_length = (int)data[0] + (int)data[1] * 256;
    std::cout << body_length << "\n";
    if (!error && body_length != 0)
    {
      boost::asio::async_read(socket_,
          boost::asio::buffer(data + header_length, body_length),
          boost::bind(&chat_session::handle_read_body, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "disconnected\n";
      //room_.leave(shared_from_this());
    }
  }

  void handle_read_body(const boost::system::error_code& error)
  {
    if (!error)
    {
      //room_.deliver(read_msg_);
      std::cout << "message\n";
      std::cout << data + header_length << std::endl;

      boost::asio::async_read(socket_,
          boost::asio::buffer(data, header_length),
          boost::bind(&chat_session::handle_read_header, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "disconnected\n";
      //room_.leave(shared_from_this());
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      write_msgs_.pop_front();
      if (!write_msgs_.empty())
      {
        boost::asio::async_write(socket_,
            boost::asio::buffer(write_msgs_.front().data(),
              write_msgs_.front().length()),
            boost::bind(&chat_session::handle_write, shared_from_this(),
              boost::asio::placeholders::error));
      }
    }
    else
    {
      std::cout << "disconnected\n";
      //room_.leave(shared_from_this());
    }
  }

private:
  tcp::socket socket_;
  //chat_room& room_;
  std::string read_msg_;
  char data[256];
  int body_length;
  chat_message_queue write_msgs_;
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

//----------------------------------------------------------------------

class chat_server
{
public:
  chat_server(boost::asio::io_service& io_service,
      const tcp::endpoint& endpoint)
    : io_service_(io_service),
      acceptor_(io_service, endpoint)
  {
    start_accept();
  }

  void start_accept()
  {
    chat_session_ptr new_session(new chat_session(io_service_));
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&chat_server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(chat_session_ptr session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      session->start();
    }

    start_accept();
  }

private:
  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
  //chat_room room_;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try
  {
    if (argc < 2)
    {
      std::cerr << "Usage: chat_server <port> [<port> ...]\n";
      return 1;
    }

    boost::asio::io_service io_service;

    chat_server_list servers;
    for (int i = 1; i < argc; ++i)
    {
      using namespace std; // For atoi.
      tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
      chat_server_ptr server(new chat_server(io_service, endpoint));
      servers.push_back(server);
    }

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}