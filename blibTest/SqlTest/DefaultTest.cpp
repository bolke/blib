#include <stdio.h>

#include "blib.h"

using namespace blib;

int32_t main(int32_t argc, char_t* argv[]){
	FileInterface tf;
	tf.SetFilename("dbCompare.txt");
	tf.SetFilemode(std::ios::out);
	tf.Open();

	SqlDatabase db("mydb.db");
	db.Open();
	db.Push("CREATE TABLE tbl(id INT PRIMARY KEY NOT NULL,NAME TEXT NOT NULL);");	
	
	std::cout<<db<<"\r\n";
	std::string line;

	uint64_t tick=GetRunTimeMs();
	
	while(1){
		tick=GetRunTimeMs();
		for(int32_t i=0;i<10000;i++){		  
		  line=StringParser::ToString("INSERT INTO tbl (ID,NAME) VALUES(%u,'cheese')",i);		  			
			db<<line;
		}
		tick=GetRunTimeMs()-tick;
		std::cout<<StringParser::ToString("TICK: %ul\r\n",tick);

		tick=GetRunTimeMs();
		for(int32_t i=0;i<10000;i++){
			line=StringParser::ToString("SELECT NAME FROM tbl WHERE ID=%u;",i);
	//		db.Push(line);
//			db.Pop(line);
		//	std::cout<<db<<"\r\n";
		}
		tick=GetRunTimeMs()-tick;
		std::cout<<StringParser::ToString("TICK: %ul\r\n",tick);

		tick=GetRunTimeMs();
		for(int32_t i=0;i<10000;i++){
			line=StringParser::ToString("%u 'cheese'\n",i);
		  tf<<line;
		}
		tick=GetRunTimeMs()-tick;
		std::cout<<StringParser::ToString("TICK: %ul\r\n",tick);

		tf.Close();
		tf.SetFilemode(std::ios::in);
		tf.Open();

		tick=GetRunTimeMs();
		char buffer[32]={0};
		for(int32_t i=0;i<10000;i++){
			tf.Pop(*buffer,32);			
		}
		tick=GetRunTimeMs()-tick;
		std::cout<<StringParser::ToString("TICK: %ul\r\n",tick);

		while(1)
			SleepMs(1);
	}
	return 0;
}
