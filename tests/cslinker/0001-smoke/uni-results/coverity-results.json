{
    "defects":
    [
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 404,
            "function": "do_dbdef",
            "language": "c/c++",
            "key_event_idx": 5,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/commandconf.c",
                    "line": 811,
                    "event": "path",
                    "message": "Starting defect path here.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/commandconf.c",
                    "line": 811,
                    "event": "path",
                    "message": "Condition \"*conf_db_url == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/commandconf.c",
                    "line": 812,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"parse_url\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/commandconf.c",
                    "line": 812,
                    "event": "var_assign",
                    "message": "Assigning: \"u\" = storage returned from \"parse_url(val)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/commandconf.c",
                    "line": 815,
                    "event": "path",
                    "message": "Switch case default.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/commandconf.c",
                    "line": 842,
                    "event": "leaked_storage",
                    "message": "Variable \"u\" going out of scope leaks the storage it points to.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "NULL_RETURNS",
            "cwe": 476,
            "function": "get_attribute_values",
            "language": "c/c++",
            "key_event_idx": 6,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 427,
                    "event": "path",
                    "message": "Condition \"line == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 427,
                    "event": "path",
                    "message": "Condition \"!(line->attr & attr)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 431,
                    "event": "path",
                    "message": "Condition \"(2097152ULL /* 1ULL << 21 */) & attr\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 435,
                    "event": "path",
                    "message": "Condition \"(8589934592ULL /* 1ULL << 33 */) & attr\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 440,
                    "event": "path",
                    "message": "Condition \"(34359738368ULL /* 1ULL << 35 */) & attr\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 441,
                    "event": "returned_null",
                    "message": "\"get_file_type_string\" returns \"NULL\" (checked 4 out of 5 times).",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 441,
                    "event": "dereference",
                    "message": "Dereferencing a pointer that might be \"NULL\" \"get_file_type_string(line->perm)\" when calling \"strlen\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 550,
                    "event": "example_assign",
                    "message": "Example 1: Assigning: \"file_type\" = return value from \"get_file_type_string(((nline == NULL) ? oline : nline)->perm)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 551,
                    "event": "example_checked",
                    "message": "Example 1 (cont.): \"file_type\" has its value checked in \"file_type\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 639,
                    "event": "example_assign",
                    "message": "Example 2: Assigning: \"file_type\" = return value from \"get_file_type_string(line->perm)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 640,
                    "event": "example_checked",
                    "message": "Example 2 (cont.): \"file_type\" has its value checked in \"file_type\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 649,
                    "event": "example_assign",
                    "message": "Example 3: Assigning: \"file_type\" = return value from \"get_file_type_string(line->perm)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 650,
                    "event": "example_checked",
                    "message": "Example 3 (cont.): \"file_type\" has its value checked in \"file_type\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 591,
                    "event": "example_assign",
                    "message": "Example 4: Assigning: \"file_type\" = return value from \"get_file_type_string(((nline == NULL) ? oline : nline)->perm)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/compare_db.c",
                    "line": 592,
                    "event": "example_checked",
                    "message": "Example 4 (cont.): \"file_type\" has its value checked in \"file_type\".",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "function": "conflex",
            "language": "c/c++",
            "key_event_idx": 7,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 5871,
                    "event": "path",
                    "message": "Condition \"!yy_init\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 5879,
                    "event": "path",
                    "message": "Condition \"!yy_start\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 5882,
                    "event": "path",
                    "message": "Condition \"!confin\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 5885,
                    "event": "path",
                    "message": "Condition \"!confout\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 5888,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 5888,
                    "event": "var_compare_op",
                    "message": "Comparing \"yy_buffer_stack\" to null implies that \"yy_buffer_stack\" might be null.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 5888,
                    "event": "path",
                    "message": "Condition \"!(yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 5890,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"yy_buffer_stack\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "function": "confrestart",
            "language": "c/c++",
            "key_event_idx": 3,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 6975,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 6975,
                    "event": "var_compare_op",
                    "message": "Comparing \"yy_buffer_stack\" to null implies that \"yy_buffer_stack\" might be null.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 6975,
                    "event": "path",
                    "message": "Condition \"!(yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 6977,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"yy_buffer_stack\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "function": "conf_switch_to_buffer",
            "language": "c/c++",
            "key_event_idx": 5,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 6998,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 6998,
                    "event": "path",
                    "message": "Condition \"(yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL) == new_buffer\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7001,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7001,
                    "event": "var_compare_op",
                    "message": "Comparing \"yy_buffer_stack\" to null implies that \"yy_buffer_stack\" might be null.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7001,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7009,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"yy_buffer_stack\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "function": "confpush_buffer_state",
            "language": "c/c++",
            "key_event_idx": 6,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7140,
                    "event": "path",
                    "message": "Condition \"new_buffer == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7146,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7146,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7155,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7155,
                    "event": "var_compare_op",
                    "message": "Comparing \"yy_buffer_stack\" to null implies that \"yy_buffer_stack\" might be null.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7155,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_lex.c",
                    "line": 7157,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"yy_buffer_stack\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "ARRAY_VS_SINGLETON",
            "cwe": 119,
            "function": "confparse",
            "language": "c/c++",
            "key_event_idx": 9,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1217,
                    "event": "path",
                    "message": "Jumping to label \"yysetstate\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1234,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1240,
                    "event": "path",
                    "message": "Condition \"yyss + yystacksize - 1 <= yyssp\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1269,
                    "event": "path",
                    "message": "Condition \"10000 <= yystacksize\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1272,
                    "event": "path",
                    "message": "Condition \"10000 < yystacksize\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1280,
                    "event": "path",
                    "message": "Condition \"!yyptr\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1282,
                    "event": "address_of",
                    "message": "Taking address with \"&yyptr->yyss_alloc\" yields a singleton pointer.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1282,
                    "event": "assign",
                    "message": "Assigning: \"yyss\" = \"&yyptr->yyss_alloc\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1285,
                    "event": "path",
                    "message": "Condition \"yyss1 != yyssa\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1290,
                    "event": "ptr_arith",
                    "message": "Using \"yyss\" as an array.  This might corrupt or misinterpret adjacent memory locations.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "OVERRUN",
            "cwe": 119,
            "function": "confparse",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1185,
                    "event": "assignment",
                    "message": "Assigning: \"yystacksize\" = \"200L\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1217,
                    "event": "path",
                    "message": "Jumping to label \"yysetstate\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1234,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1240,
                    "event": "path",
                    "message": "Condition \"yyss + yystacksize - 1 <= yyssp\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1269,
                    "event": "path",
                    "message": "Condition \"10000 <= yystacksize\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1271,
                    "event": "assignment",
                    "message": "Assigning: \"yystacksize\" *= \"2L\". The value of \"yystacksize\" is now 400.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1272,
                    "event": "path",
                    "message": "Condition \"10000 < yystacksize\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1280,
                    "event": "path",
                    "message": "Condition \"!yyptr\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1282,
                    "event": "alias",
                    "message": "Assigning: \"yyss\" = \"&yyptr->yyss_alloc\". \"yyss\" now points to byte 0 of \"yyptr->yyss_alloc\" (which consists of 8 bytes).",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1285,
                    "event": "path",
                    "message": "Condition \"yyss1 != yyssa\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1298,
                    "event": "illegal_address",
                    "message": "\"yyss + yystacksize - 1\" evaluates to an address that is at byte offset 399 of an array of 8 bytes.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1298,
                    "event": "path",
                    "message": "Condition \"yyss + yystacksize - 1 <= yyssp\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 1299,
                    "event": "path",
                    "message": "Jumping to label \"yyabortlab\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 2213,
                    "event": "path",
                    "message": "Jumping to label \"yyreturn\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 2231,
                    "event": "path",
                    "message": "Condition \"confchar != YYEMPTY\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 2243,
                    "event": "path",
                    "message": "Condition \"yyssp != yyss\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/conf_yacc.c",
                    "line": 2250,
                    "event": "path",
                    "message": "Condition \"yyss != yyssa\", taking true branch.",
                    "verbosity_level": "2"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writechar",
            "language": "c/c++",
            "key_event_idx": 1,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 599,
                    "event": "path",
                    "message": "Condition \"i\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 600,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\" \")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writechar",
            "language": "c/c++",
            "key_event_idx": 7,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 599,
                    "event": "path",
                    "message": "Condition \"i\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 603,
                    "event": "path",
                    "message": "Condition \"s == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 607,
                    "event": "path",
                    "message": "Condition \"s[0] == 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 611,
                    "event": "path",
                    "message": "Condition \"s[0] == '0'\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 613,
                    "event": "path",
                    "message": "Condition \"retval < 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 619,
                    "event": "path",
                    "message": "Condition \"!i\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 619,
                    "event": "path",
                    "message": "Condition \"s[0] == '#'\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 620,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\"# \")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeint",
            "language": "c/c++",
            "key_event_idx": 1,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 635,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 636,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\" \")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writelong",
            "language": "c/c++",
            "key_event_idx": 1,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 646,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 647,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\" \")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_write_byte_base64",
            "language": "c/c++",
            "key_event_idx": 5,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 665,
                    "event": "path",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 665,
                    "event": "path",
                    "message": "Condition \"!len\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 668,
                    "event": "path",
                    "message": "Condition \"data != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 668,
                    "event": "path",
                    "message": "Condition \"th & attr\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 673,
                    "event": "path",
                    "message": "Condition \"i\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 674,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\" \")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_write_time_base64",
            "language": "c/c++",
            "key_event_idx": 1,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 696,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 697,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\" \")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeoct",
            "language": "c/c++",
            "key_event_idx": 1,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 729,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 730,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\" \")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeacl",
            "language": "c/c++",
            "key_event_idx": 1,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 837,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 838,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\" \")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeacl",
            "language": "c/c++",
            "key_event_idx": 2,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 837,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 841,
                    "event": "path",
                    "message": "Condition \"acl == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 842,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\"0\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeacl",
            "language": "c/c++",
            "key_event_idx": 2,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 837,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 841,
                    "event": "path",
                    "message": "Condition \"acl == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 844,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\"POSIX\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeacl",
            "language": "c/c++",
            "key_event_idx": 2,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 837,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 841,
                    "event": "path",
                    "message": "Condition \"acl == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 846,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\",\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeacl",
            "language": "c/c++",
            "key_event_idx": 3,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 837,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 841,
                    "event": "path",
                    "message": "Condition \"acl == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 847,
                    "event": "path",
                    "message": "Condition \"acl->acl_a\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 850,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\"0\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeacl",
            "language": "c/c++",
            "key_event_idx": 4,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 837,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 841,
                    "event": "path",
                    "message": "Condition \"acl == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 847,
                    "event": "path",
                    "message": "Condition \"acl->acl_a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 848,
                    "event": "path",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 851,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\",\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeacl",
            "language": "c/c++",
            "key_event_idx": 5,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 837,
                    "event": "path",
                    "message": "Condition \"a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 841,
                    "event": "path",
                    "message": "Condition \"acl == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 847,
                    "event": "path",
                    "message": "Condition \"acl->acl_a\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 848,
                    "event": "path",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 852,
                    "event": "path",
                    "message": "Condition \"acl->acl_d\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 855,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\"0\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 6,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 878,
                    "event": "check_return",
                    "message": "Calling \"db_writechar(line->filename, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_linkname\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 882,
                    "event": "check_return",
                    "message": "Calling \"db_writechar(line->linkname, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_bcount\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 886,
                    "event": "check_return",
                    "message": "Calling \"db_writeint(line->bcount, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_mtime\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 891,
                    "event": "check_return",
                    "message": "Calling \"db_write_time_base64(line->mtime, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_atime\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 895,
                    "event": "check_return",
                    "message": "Calling \"db_write_time_base64(line->atime, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_ctime\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 899,
                    "event": "check_return",
                    "message": "Calling \"db_write_time_base64(line->ctime, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_inode\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 903,
                    "event": "check_return",
                    "message": "Calling \"db_writeint(line->inode, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_lnkcount\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 907,
                    "event": "check_return",
                    "message": "Calling \"db_writeint(line->nlink, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_uid\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 911,
                    "event": "check_return",
                    "message": "Calling \"db_writeint(line->uid, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_gid\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 915,
                    "event": "check_return",
                    "message": "Calling \"db_writeint(line->gid, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_size\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 919,
                    "event": "check_return",
                    "message": "Calling \"db_writelong(line->size, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_perm\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 953,
                    "event": "check_return",
                    "message": "Calling \"db_writeoct(line->perm, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_attr\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1009,
                    "event": "check_return",
                    "message": "Calling \"db_writelong(line->attr, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 11,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_xattrs\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1022,
                    "event": "path",
                    "message": "Condition \"!line->xattrs\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1024,
                    "event": "check_return",
                    "message": "Calling \"db_writelong(0L, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 11,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_xattrs\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1022,
                    "event": "path",
                    "message": "Condition \"!line->xattrs\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1028,
                    "event": "check_return",
                    "message": "Calling \"db_writelong(line->xattrs->num, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 16,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_xattrs\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1022,
                    "event": "path",
                    "message": "Condition \"!line->xattrs\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1031,
                    "event": "path",
                    "message": "Condition \"num < line->xattrs->num\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1040,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1031,
                    "event": "path",
                    "message": "Condition \"num < line->xattrs->num\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1040,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1031,
                    "event": "path",
                    "message": "Condition \"num < line->xattrs->num\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1033,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\",\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 16,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_xattrs\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1022,
                    "event": "path",
                    "message": "Condition \"!line->xattrs\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1031,
                    "event": "path",
                    "message": "Condition \"num < line->xattrs->num\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1040,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1031,
                    "event": "path",
                    "message": "Condition \"num < line->xattrs->num\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1040,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1031,
                    "event": "path",
                    "message": "Condition \"num < line->xattrs->num\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1035,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\",\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_selinux\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1044,
                    "event": "check_return",
                    "message": "Calling \"db_write_byte_base64((byte *)line->cntx, 0UL, dbconf->db_out, i, 1ULL, 1ULL)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_e2fsattrs\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1049,
                    "event": "check_return",
                    "message": "Calling \"db_writelong(line->e2fsattrs, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 10,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_checkmask\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1054,
                    "event": "check_return",
                    "message": "Calling \"db_writeoct(line->attr, dbconf->db_out, i)\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "db_writeline_file",
            "language": "c/c++",
            "key_event_idx": 9,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 876,
                    "event": "path",
                    "message": "Switch case value \"db_filename\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 879,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1065,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 875,
                    "event": "path",
                    "message": "Condition \"i < dbconf->db_out_size\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_file.c",
                    "line": 1067,
                    "event": "check_return",
                    "message": "Calling \"dofprintf(\"\\n\")\" without checking return value. It wraps a library function that may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "function": "db_scan",
            "language": "c/c++",
            "key_event_idx": 7,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1004,
                    "event": "path",
                    "message": "Condition \"!yy_init\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1012,
                    "event": "path",
                    "message": "Condition \"!yy_start\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1015,
                    "event": "path",
                    "message": "Condition \"!dbin\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1018,
                    "event": "path",
                    "message": "Condition \"!dbout\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1021,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1021,
                    "event": "var_compare_op",
                    "message": "Comparing \"yy_buffer_stack\" to null implies that \"yy_buffer_stack\" might be null.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1021,
                    "event": "path",
                    "message": "Condition \"!(yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1023,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"yy_buffer_stack\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "function": "dbrestart",
            "language": "c/c++",
            "key_event_idx": 3,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1615,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1615,
                    "event": "var_compare_op",
                    "message": "Comparing \"yy_buffer_stack\" to null implies that \"yy_buffer_stack\" might be null.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1615,
                    "event": "path",
                    "message": "Condition \"!(yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1617,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"yy_buffer_stack\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "function": "db_switch_to_buffer",
            "language": "c/c++",
            "key_event_idx": 5,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1638,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1638,
                    "event": "path",
                    "message": "Condition \"(yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL) == new_buffer\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1641,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1641,
                    "event": "var_compare_op",
                    "message": "Comparing \"yy_buffer_stack\" to null implies that \"yy_buffer_stack\" might be null.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1641,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1649,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"yy_buffer_stack\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "function": "dbpush_buffer_state",
            "language": "c/c++",
            "key_event_idx": 6,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1780,
                    "event": "path",
                    "message": "Condition \"new_buffer == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1786,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1786,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1795,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1795,
                    "event": "var_compare_op",
                    "message": "Comparing \"yy_buffer_stack\" to null implies that \"yy_buffer_stack\" might be null.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1795,
                    "event": "path",
                    "message": "Condition \"yy_buffer_stack ? yy_buffer_stack[yy_buffer_stack_top] : NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/db_lex.c",
                    "line": 1797,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"yy_buffer_stack\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "UNREACHABLE",
            "cwe": 561,
            "function": "calc_md",
            "language": "c/c++",
            "key_event_idx": 0,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/do_md.c",
                    "line": 342,
                    "event": "unreachable",
                    "message": "This code cannot be reached: \"{\n  if (update_md(&mdc, buf...\".",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "url_fopen",
            "language": "c/c++",
            "key_event_idx": 3,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 187,
                    "event": "path",
                    "message": "Condition \"!file\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 192,
                    "event": "path",
                    "message": "Condition \"file->handle.file = fopen(url, operation)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 199,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 199,
                    "event": "check_return",
                    "message": "Calling \"curl_easy_setopt(file->handle.curl, _curl_opt, url)\" without checking return value. This library function may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "url_fopen",
            "language": "c/c++",
            "key_event_idx": 4,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 187,
                    "event": "path",
                    "message": "Condition \"!file\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 192,
                    "event": "path",
                    "message": "Condition \"file->handle.file = fopen(url, operation)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 199,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 200,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 200,
                    "event": "check_return",
                    "message": "Calling \"curl_easy_setopt(file->handle.curl, _curl_opt, file)\" without checking return value. This library function may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "url_fopen",
            "language": "c/c++",
            "key_event_idx": 5,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 187,
                    "event": "path",
                    "message": "Condition \"!file\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 192,
                    "event": "path",
                    "message": "Condition \"file->handle.file = fopen(url, operation)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 199,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 200,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 201,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 201,
                    "event": "check_return",
                    "message": "Calling \"curl_easy_setopt(file->handle.curl, _curl_opt, 0L)\" without checking return value. This library function may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CHECKED_RETURN",
            "cwe": 252,
            "function": "url_fopen",
            "language": "c/c++",
            "key_event_idx": 6,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 187,
                    "event": "path",
                    "message": "Condition \"!file\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 192,
                    "event": "path",
                    "message": "Condition \"file->handle.file = fopen(url, operation)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 199,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 200,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 201,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 202,
                    "event": "path",
                    "message": "Condition \"0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/fopen.c",
                    "line": 202,
                    "event": "check_return",
                    "message": "Calling \"curl_easy_setopt(file->handle.curl, _curl_opt, write_callback)\" without checking return value. This library function may fail and return an error code.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 404,
            "function": "add_file_to_tree",
            "language": "c/c++",
            "key_event_idx": 7,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 846,
                    "event": "path",
                    "message": "Condition \"file == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 852,
                    "event": "path",
                    "message": "Condition \"!node\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 853,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"new_seltree_node\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 853,
                    "event": "var_assign",
                    "message": "Assigning: \"node\" = storage returned from \"new_seltree_node(tree, file->filename, 0, NULL)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 863,
                    "event": "path",
                    "message": "Switch case value \"1 | 4\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 874,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 876,
                    "event": "path",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 881,
                    "event": "leaked_storage",
                    "message": "Variable \"node\" going out of scope leaks the storage it points to.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 404,
            "function": "add_file_to_tree",
            "language": "c/c++",
            "key_event_idx": 16,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 846,
                    "event": "path",
                    "message": "Condition \"file == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 852,
                    "event": "path",
                    "message": "Condition \"!node\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 853,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"new_seltree_node\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 853,
                    "event": "var_assign",
                    "message": "Assigning: \"node\" = storage returned from \"new_seltree_node(tree, file->filename, 0, NULL)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 863,
                    "event": "path",
                    "message": "Switch case value \"1 << 0\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 866,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 889,
                    "event": "path",
                    "message": "Condition \"node->checked & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 889,
                    "event": "path",
                    "message": "Condition \"node->checked & (4 /* 1 << 2 */)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 923,
                    "event": "path",
                    "message": "Condition \"node->old_data != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 923,
                    "event": "path",
                    "message": "Condition \"file->attr & (134217728ULL /* 1ULL << 27 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 930,
                    "event": "path",
                    "message": "Condition \"db == (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 931,
                    "event": "path",
                    "message": "Condition \"moved_node == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 962,
                    "event": "path",
                    "message": "Condition \"db == (4 /* 1 << 2 */)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 967,
                    "event": "path",
                    "message": "Condition \"db == (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 967,
                    "event": "path",
                    "message": "Condition \"node->old_data != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 967,
                    "event": "path",
                    "message": "Condition \"file->attr & (536870912ULL /* 1ULL << 29 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 972,
                    "event": "leaked_storage",
                    "message": "Variable \"node\" going out of scope leaks the storage it points to.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 404,
            "function": "populate_tree",
            "language": "c/c++",
            "key_event_idx": 16,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1147,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1151,
                    "event": "path",
                    "message": "Condition \"conf->action & (4 /* 1 << 2 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1152,
                    "event": "path",
                    "message": "Condition \"(new = db_readline(4 /* 1 << 2 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1173,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1176,
                    "event": "path",
                    "message": "Condition \"(new = db_readline(256 /* 1 << 8 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1180,
                    "event": "path",
                    "message": "Condition \"conf->action & (2 /* 1 << 1 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1181,
                    "event": "path",
                    "message": "Condition \"(old = db_readline(1 /* 1 << 0 */)) != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1184,
                    "event": "path",
                    "message": "Condition \"(node = get_seltree_node(tree, old->filename)) == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1185,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"new_seltree_node\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1185,
                    "event": "var_assign",
                    "message": "Assigning: \"node\" = storage returned from \"new_seltree_node(tree, old->filename, 0, NULL)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1188,
                    "event": "path",
                    "message": "Condition \"add > 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1190,
                    "event": "path",
                    "message": "Condition \"conf->limit != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1190,
                    "event": "path",
                    "message": "Condition \"add < 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1196,
                    "event": "path",
                    "message": "Condition \"!initdbwarningprinted\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1201,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1181,
                    "event": "path",
                    "message": "Condition \"(old = db_readline(1 /* 1 << 0 */)) != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1184,
                    "event": "overwrite_var",
                    "message": "Overwriting \"node\" in \"node = get_seltree_node(tree, old->filename)\" leaks the storage that \"node\" points to.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 404,
            "function": "populate_tree",
            "language": "c/c++",
            "key_event_idx": 17,
            "events":
            [
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1147,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1151,
                    "event": "path",
                    "message": "Condition \"conf->action & (4 /* 1 << 2 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1152,
                    "event": "path",
                    "message": "Condition \"(new = db_readline(4 /* 1 << 2 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1173,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1176,
                    "event": "path",
                    "message": "Condition \"(new = db_readline(256 /* 1 << 8 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1180,
                    "event": "path",
                    "message": "Condition \"conf->action & (2 /* 1 << 1 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1181,
                    "event": "path",
                    "message": "Condition \"(old = db_readline(1 /* 1 << 0 */)) != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1184,
                    "event": "path",
                    "message": "Condition \"(node = get_seltree_node(tree, old->filename)) == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1185,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"new_seltree_node\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1185,
                    "event": "var_assign",
                    "message": "Assigning: \"node\" = storage returned from \"new_seltree_node(tree, old->filename, 0, NULL)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1188,
                    "event": "path",
                    "message": "Condition \"add > 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1190,
                    "event": "path",
                    "message": "Condition \"conf->limit != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1190,
                    "event": "path",
                    "message": "Condition \"add < 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1196,
                    "event": "path",
                    "message": "Condition \"!initdbwarningprinted\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1201,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1181,
                    "event": "path",
                    "message": "Condition \"(old = db_readline(1 /* 1 << 0 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1203,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "/builddir/build/BUILD/aide-0.16/src/gen_list.c",
                    "line": 1206,
                    "event": "leaked_storage",
                    "message": "Variable \"node\" going out of scope leaks the storage it points to.",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CONSTANT_EXPRESSION_RESULT",
            "cwe": 569,
            "function": "fread",
            "language": "c/c++",
            "key_event_idx": 0,
            "events":
            [
                {
                    "file_name": "/usr/include/bits/stdio2.h",
                    "line": 294,
                    "event": "pointless_expression",
                    "message": "The expression \"1 /* !0 */ || 1 /* !0 */\" does not accomplish anything because it evaluates to either of its identical operands, \"1 /* !0 */\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "/usr/include/bits/stdio2.h",
                    "line": 294,
                    "event": "remediation",
                    "message": "Did you intend the operands to be different?",
                    "verbosity_level": "1"
                }
            ]
        }
    ]
}
