#include "string_algorithm.hpp"


char* Strstr(char * str,char * substr)
{
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
