{
    "scan":
    {
        "analyzer-version-clang": "11.0.0",
        "analyzer-version-coverity": "2020.09",
        "analyzer-version-cppcheck": "2.1",
        "analyzer-version-gcc": "10.2.1",
        "analyzer-version-gcc-analyzer": "10.2.1",
        "analyzer-version-shellcheck": "0.7.1",
        "cov-compilation-unit-count": 26,
        "cov-compilation-unit-ratio": 100,
        "cov-lines-processed": 44162,
        "cov-time-elapsed-analysis": "00:00:18",
        "defect-blacklist": "/usr/share/csmock/defect-blacklist.err",
        "exit-code": 0,
        "host": "cov03.lab.eng.brq.redhat.com",
        "mock-config": "eln-x86_64",
        "project-name": "aide-0.16-16.eln103",
        "store-results-to": "/tmp/tmpuYxcq0/aide-0.16-16.eln103.tar.xz",
        "time-created": "2020-11-16 18:07:59",
        "time-finished": "2020-11-16 18:18:54",
        "tool": "csmock",
        "tool-args": "'/bin/csmock' '-t' 'cppcheck,gcc,shellcheck,clang,coverity' '-r' 'eln-x86_64' '-o' '/tmp/tmpuYxcq0/aide-0.16-16.eln103.tar.xz' '--cov-analyze-java' '--cov-analyze-opts=--security --concurrency' '--use-host-cppcheck' '--gcc-analyze' '--cov-use-instance' '/opt/cov-sa-2020.09' '/tmp/tmpuYxcq0/aide-0.16-16.eln103.src.rpm'",
        "tool-version": "csmock-2.6.0.20201022.141344.g7db3c91.internal-1.el7"
    },
    "defects":
    [
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 772,
            "function": "do_dbdef",
            "language": "c/c++",
            "key_event_idx": 5,
            "events":
            [
                {
                    "file_name": "aide-0.16/src/commandconf.c",
                    "line": 811,
                    "event": "path",
                    "message": "Starting defect path here.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/commandconf.c",
                    "line": 811,
                    "event": "path",
                    "message": "Condition \"*conf_db_url == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/commandconf.c",
                    "line": 812,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"parse_url\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/commandconf.c",
                    "line": 812,
                    "event": "var_assign",
                    "message": "Assigning: \"u\" = storage returned from \"parse_url(val)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/commandconf.c",
                    "line": 815,
                    "event": "path",
                    "message": "Switch case default.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/commandconf.c",
                    "line": 842,
                    "event": "leaked_storage",
                    "message": "Variable \"u\" going out of scope leaks the storage it points to.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  840|     }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  841|     free(val);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  842|-> }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  843|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  844|   void do_dbindef(char* val)",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 772,
            "function": "add_file_to_tree",
            "language": "c/c++",
            "key_event_idx": 7,
            "events":
            [
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 846,
                    "event": "path",
                    "message": "Condition \"file == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 852,
                    "event": "path",
                    "message": "Condition \"!node\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 853,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"new_seltree_node\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 853,
                    "event": "var_assign",
                    "message": "Assigning: \"node\" = storage returned from \"new_seltree_node(tree, file->filename, 0, NULL)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 863,
                    "event": "path",
                    "message": "Switch case value \"1 | 4\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 874,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 876,
                    "event": "path",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 881,
                    "event": "leaked_storage",
                    "message": "Variable \"node\" going out of scope leaks the storage it points to.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  879|           node->new_data=NULL;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  880|       }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  881|->     return;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  882|     }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  883|     }",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 772,
            "function": "add_file_to_tree",
            "language": "c/c++",
            "key_event_idx": 16,
            "events":
            [
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 846,
                    "event": "path",
                    "message": "Condition \"file == NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 852,
                    "event": "path",
                    "message": "Condition \"!node\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 853,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"new_seltree_node\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 853,
                    "event": "var_assign",
                    "message": "Assigning: \"node\" = storage returned from \"new_seltree_node(tree, file->filename, 0, NULL)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 863,
                    "event": "path",
                    "message": "Switch case value \"1 << 0\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 866,
                    "event": "path",
                    "message": "Breaking from switch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 889,
                    "event": "path",
                    "message": "Condition \"node->checked & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 889,
                    "event": "path",
                    "message": "Condition \"node->checked & (4 /* 1 << 2 */)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 923,
                    "event": "path",
                    "message": "Condition \"node->old_data != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 923,
                    "event": "path",
                    "message": "Condition \"file->attr & (134217728ULL /* 1ULL << 27 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 930,
                    "event": "path",
                    "message": "Condition \"db == (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 931,
                    "event": "path",
                    "message": "Condition \"moved_node == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 962,
                    "event": "path",
                    "message": "Condition \"db == (4 /* 1 << 2 */)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 967,
                    "event": "path",
                    "message": "Condition \"db == (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 967,
                    "event": "path",
                    "message": "Condition \"node->old_data != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 967,
                    "event": "path",
                    "message": "Condition \"file->attr & (536870912ULL /* 1ULL << 29 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 972,
                    "event": "leaked_storage",
                    "message": "Variable \"node\" going out of scope leaks the storage it points to.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  970|   \t  node->checked|=NODE_ALLOW_RM;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  971|     }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  972|-> }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  973|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  974|   int check_rxtree(char* filename,seltree* tree,DB_ATTR_TYPE* attr, mode_t perm)",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 772,
            "function": "populate_tree",
            "language": "c/c++",
            "key_event_idx": 16,
            "events":
            [
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1147,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1151,
                    "event": "path",
                    "message": "Condition \"conf->action & (4 /* 1 << 2 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1152,
                    "event": "path",
                    "message": "Condition \"(new = db_readline(4 /* 1 << 2 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1173,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1176,
                    "event": "path",
                    "message": "Condition \"(new = db_readline(256 /* 1 << 8 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1180,
                    "event": "path",
                    "message": "Condition \"conf->action & (2 /* 1 << 1 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1181,
                    "event": "path",
                    "message": "Condition \"(old = db_readline(1 /* 1 << 0 */)) != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1184,
                    "event": "path",
                    "message": "Condition \"(node = get_seltree_node(tree, old->filename)) == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1185,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"new_seltree_node\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1185,
                    "event": "var_assign",
                    "message": "Assigning: \"node\" = storage returned from \"new_seltree_node(tree, old->filename, 0, NULL)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1188,
                    "event": "path",
                    "message": "Condition \"add > 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1190,
                    "event": "path",
                    "message": "Condition \"conf->limit != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1190,
                    "event": "path",
                    "message": "Condition \"add < 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1196,
                    "event": "path",
                    "message": "Condition \"!initdbwarningprinted\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1201,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1181,
                    "event": "path",
                    "message": "Condition \"(old = db_readline(1 /* 1 << 0 */)) != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1184,
                    "event": "overwrite_var",
                    "message": "Overwriting \"node\" in \"node = get_seltree_node(tree, old->filename)\" leaks the storage that \"node\" points to.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1182|                   /* This is needed because check_rxtree assumes there is a parent",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1183|                      for the node for old->filename */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1184|->                 if((node=get_seltree_node(tree,old->filename))==NULL){",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1185|                       node=new_seltree_node(tree,old->filename,0,NULL);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1186|                   }",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "RESOURCE_LEAK",
            "cwe": 772,
            "function": "populate_tree",
            "language": "c/c++",
            "key_event_idx": 17,
            "events":
            [
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1147,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1151,
                    "event": "path",
                    "message": "Condition \"conf->action & (4 /* 1 << 2 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1152,
                    "event": "path",
                    "message": "Condition \"(new = db_readline(4 /* 1 << 2 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1173,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1176,
                    "event": "path",
                    "message": "Condition \"(new = db_readline(256 /* 1 << 8 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1180,
                    "event": "path",
                    "message": "Condition \"conf->action & (2 /* 1 << 1 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1181,
                    "event": "path",
                    "message": "Condition \"(old = db_readline(1 /* 1 << 0 */)) != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1184,
                    "event": "path",
                    "message": "Condition \"(node = get_seltree_node(tree, old->filename)) == NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1185,
                    "event": "alloc_fn",
                    "message": "Storage is returned from allocation function \"new_seltree_node\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1185,
                    "event": "var_assign",
                    "message": "Assigning: \"node\" = storage returned from \"new_seltree_node(tree, old->filename, 0, NULL)\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1188,
                    "event": "path",
                    "message": "Condition \"add > 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1190,
                    "event": "path",
                    "message": "Condition \"conf->limit != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1190,
                    "event": "path",
                    "message": "Condition \"add < 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1196,
                    "event": "path",
                    "message": "Condition \"!initdbwarningprinted\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1201,
                    "event": "path",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1181,
                    "event": "path",
                    "message": "Condition \"(old = db_readline(1 /* 1 << 0 */)) != NULL\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1203,
                    "event": "path",
                    "message": "Condition \"conf->action & (1 /* 1 << 0 */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "aide-0.16/src/gen_list.c",
                    "line": 1206,
                    "event": "leaked_storage",
                    "message": "Variable \"node\" going out of scope leaks the storage it points to.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1204|           write_tree(tree);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1205|       }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1206|-> }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1207|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1208|   void hsymlnk(db_line* line) {",
                    "verbosity_level": "1"
                }
            ]
        }
    ]
}
