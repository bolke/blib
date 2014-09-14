#ifndef BLIB_SQLDATABASE_H

#include "Core.h"
#include "sqlite3.h"

namespace blib{

class SqlDatabase:public Device,public Base{
protected:
	std::vector<char_t> data;
	std::string filename;
  sqlite3 *db;
public:
	SqlDatabase(std::string filename="");
	virtual size_t Size();
  
	virtual size_t Pop(char_t& c,size_t size=1);  
  virtual size_t Pop(std::string& data);
  
	virtual size_t Push(const char_t &c,size_t size=1);  
  virtual size_t Push(const std::string& data); 
	
  virtual EnumResult_t Open(void);
  virtual EnumResult_t Close(void);
  virtual bool IsOpen(void);

	virtual std::string GetFilename();
	virtual EnumResult_t SetFilename(std::string filename);
};

};

#endif
