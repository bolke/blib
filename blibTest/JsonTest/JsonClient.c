#include <stdio.h>
#include "JsonClient.h"

void DeserializeJson(const char* line,size_t length){
	JSON_Value* js=json_parse_string(line);
	JSON_Object* jsObject=json_value_get_object(js);	
	printf(json_serialize_to_string(js));
	json_value_free(js);
}