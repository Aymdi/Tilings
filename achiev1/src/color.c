#include <stdio.h>
#include <string.h>

#include "struct_color.h"

#define MAX_COLOR 8

struct color color[MAX_COLOR]={{"noir","\e[0;30m"},
                     {"rouge","\e[0;31m"},
					 {"vert","\e[0;32m"},
					 {"jaune","\e[0;33m"},
					 {"bleu","\e[0;34m"},
					 {"violet","\e[0;35m"},
					 {"cyan","\e[0;36m"},
					 {"blanc","\e[0;37m"}
					 };

const char* color_name(const struct color *t){
	return(t->name);
}

//Returns the ANSI-code of the color
const char* color_cstring(const struct color* t){
	return (t->ANSI_code);
}

//Returns a color from its name, or NULL
struct color* color_from_name(const char* name){
	for (int i=0; i<MAX_COLOR; i++){
		if (strcmp(name,color[i].name) == 0)
			return (&(color[i]));
	}
	return NULL;
}
