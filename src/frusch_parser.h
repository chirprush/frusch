#ifndef FRUSCH_PARSER_H
#define FRUSCH_PARSER_H

#include "fvm_int.h"
#include "frusch_ast.h"

typedef struct frusch_parser {
	const char *source;
	u32 length;
	u32 line;
	u32 col;
} frusch_parser;

frusch_parser *frusch_parser_new(const char *source, u32 length);
frusch_parser *frusch_parser_free(frusch_parser *parser);

frusch_node *frusch_parser_parse_atom(frusch_parser *parser);
frusch_node *frusch_parser_parse_(frusch_parser *parser);

#endif // FRUSCH_PARSER_H

