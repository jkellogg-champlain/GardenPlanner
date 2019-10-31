#pragma once
#include <SFML/Graphics.hpp>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Map
{
public:
  Map();
  ~Map();

  void SetName(std::string name);
  std::string GetName();
  void SetYear(std::string year);
  std::string GetYear();
  void SetLength(int length);
  int GetLength();
  void SetWidth(int width);
  int GetWidth();
  void AddToDatabase();

private:
  std::string m_name;
  std::string m_year;
  int m_length;
  int m_width;
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
};
