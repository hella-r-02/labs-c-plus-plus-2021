#include <iso646.h>
#ifndef PARSER_HPP
#define PARSER_HPP

#include <ostream>
#include <sstream>
#include <functional>

#include "phoneBookInterface.hpp"

using CommandName = std::function<void(PhoneBookInterface &, std::ostream &)>;

std::string readNumber(std::istringstream &stream);
std::string readName(std::istringstream &stream);
std::string readMark(std::istringstream &stream);
bool isTrash(std::istringstream &stream);

CommandName parseAdd(std::istringstream &stream);
CommandName parseStore(std::istringstream &stream);
CommandName parseInsert(std::istringstream &stream);
CommandName parseDelete(std::istringstream &stream);
CommandName parseShow(std::istringstream &stream);
CommandName parseMove(std::istringstream &stream);
CommandName parse(std::istringstream &stream);

void invalidCommand(PhoneBookInterface &, std::ostream &out);
void invalidBookmark( std::ostream &out);
void invalidStep( PhoneBookInterface &,std::ostream &out);
void empty( std::ostream &out);

const std::map<std::string, CommandName(*)(std::istringstream &)> commands =
  {
    {"add", &parseAdd},
    {"store", &parseStore},
    {"insert", &parseInsert},
    {"delete", &parseDelete},
    {"show", &parseShow},
    {"move", &parseMove}
  };

#endif
