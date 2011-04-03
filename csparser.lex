/* use C++ instead of C */
%option c++

/* count line numbers automatically */
%option yylineno

/* do not use yywrap function/method */
%option noyywrap

%{
#include "csparser-priv.hh"
%}

spaces              [ \t\n]*
nocolons            [^:]+

init                ^Error:{spaces}
defect              [A-Z][A-Z_]+:$
file                ^{nocolons}\/{nocolons}
line                :[0-9:]+{spaces}
mesg                [a-z][a-z_-]+:\ .*$
mesg_extra          ^\ +.*$

%%
"\n"
{init}              return T_INIT;
{defect}            return T_DEFECT;
{file}              return T_FILE;
{line}              return T_LINE;
{mesg}              return T_MSG;
{mesg_extra}        return T_MSG_EX;

%%

