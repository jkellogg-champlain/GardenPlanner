#pragma once
#include <SFML/Graphics.hpp>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Plant
{
public:
  Plant();
  ~Plant();

  void SetName(std::string name);
  std::string GetName();
  void SetVariety(std::string variety);
  std::string GetVariety();
  void SetSpacing(int spacing);
  int GetSpacing();
  void SetRowSpacing(int rowSpacing);
  int GetRowSpacing();
  void AddToDatabase();

private:
  std::string m_name;
  std::string m_variety;
  int m_spacing;
  int m_rowSpacing;
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;

};
