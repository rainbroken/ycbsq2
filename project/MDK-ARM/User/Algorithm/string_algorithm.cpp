#include "string_algorithm.hpp"
#include "bsp_usart.hpp"

char* Strstr(char * str,char * substr)
{
//    log_info("str1 = %s",str);
//    log_info("str2 = %s",substr);
	while(* str!='\0')
	{
		char * tempstr = str;
		char *tempsubstr = substr;
		if(*str == *substr)
		{
			while(*tempsubstr !='\0')
			{
				if(*tempstr!=*tempsubstr)
				{
					break;
				}
				tempstr++;
				tempsubstr++;
			}
			if(*tempsubstr == '\0')
				return str;
		}
		str++;
	}
	return nullptr;
}
