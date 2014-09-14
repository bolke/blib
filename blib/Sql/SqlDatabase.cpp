#include "SqlDatabase.h"

using namespace blib;

SqlDatabase::SqlDatabase(std::string filename){
	this->filename=filename;
	db=NULL;
}

size_t SqlDatabase::Size(){
	size_t result=0;
	if(lock->Lock()){
		result=data.size();
		lock->Unlock();
	}
	return result;
}

size_t SqlDatabase::Pop(char_t& c,size_t size){
	size_t result=0;
	if(lock->Lock()){
		if(data.size()>0){
			if(data.size()<size)
				size=data.size();
			std::copy(data.begin(),data.begin()+size,&c);
			data.erase(data.begin(),data.begin()+size);
			result=size;
		}
		lock->Unlock();
	}
	return result;
}

size_t SqlDatabase::Pop(std::string& data){
	return Device::Pop(data);
}

size_t SqlDatabase::Push(const char_t &c,size_t size){
	size_t result=0;
	if(lock->Lock()){
		if(IsOpen()){
			if(data.size()==0){
			  sqlite3_stmt* statement;
				int32_t sqliteResult=sqlite3_prepare_v2(db,&c,-1,&statement,NULL);
				if(sqliteResult==SQLITE_OK){
					int32_t sqliteResult=sqlite3_step(statement);
					StringParser sp;
					while(sqliteResult==SQLITE_BUSY)
					  sqliteResult=sqlite3_step(statement);					
					const char* error=NULL;
					int32_t columnCnt=0;
					std::string value="";
					switch(sqliteResult){						
						case SQLITE_ERROR:
							error=sqlite3_errmsg(db);
							data.insert(data.end(),error,error+sizeof(error));							
							result=0;
							break;
						case SQLITE_ROW:							
							columnCnt=sqlite3_column_count(statement);							
							value=sp.ToString("%i",columnCnt);
							data.insert(data.end(),value.c_str(),value.c_str()+value.size());
							data.push_back('\x0');
							while(sqliteResult==SQLITE_ROW){
								for(int32_t i=0;i<columnCnt;i++){
									if(sqlite3_column_text(statement,i)!=NULL){										
										value.assign((char*)sqlite3_column_text(statement,i));
										data.insert(data.end(),value.c_str(),value.c_str()+value.size());
									}
									data.push_back('\x0');
								}
							  sqliteResult=sqlite3_step(statement);
							}
							result=size;
							break;
						default:
							data.push_back('0');
							data.push_back('\x0');
							result=size;
							break;							
					}
				}else if(sqliteResult==SQLITE_ERROR){					
					std::string error(sqlite3_errmsg(db));
					data.insert(data.end(),error.c_str(),error.c_str()+error.size());
					result=0;
				}
				sqlite3_finalize(statement);
			}
		}
		lock->Unlock();
	}
	return result;
}

size_t SqlDatabase::Push(const std::string& data){
	return Device::Push(data);
}

std::string SqlDatabase::GetFilename(){
	std::string result="";
	if(lock->Lock()){
		result=filename;
		lock->Unlock();
	}
	return result;
}

EnumResult_t SqlDatabase::SetFilename(std::string filename){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(!IsOpen()){
			this->filename=filename;
			result=SUCCESS;
		}
		lock->Unlock();
	}
	return result;
}

EnumResult_t SqlDatabase::Open(void){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(filename.size()>0){
			if(sqlite3_open(filename.c_str(),&db)==SQLITE_OK){
        result=SUCCESS;   
				isOpen=true;
			}
		}		
		lock->Unlock();
	}
	return result;
}

EnumResult_t SqlDatabase::Close(void){
	EnumResult_t result=FAIL;
	if(lock->Lock()){
		if(db!=NULL){
      if(sqlite3_close(db)==SQLITE_OK){
        result=SUCCESS;
        db=NULL;
				isOpen=false;
      }
		}
		lock->Unlock();
	}
	return result;
}

bool SqlDatabase::IsOpen(void){
	bool result=false;
	if(lock->Lock()){
		result=db!=NULL;
		isOpen=result;
		lock->Unlock();
	}
	return result;
}
