{
    "scan": {
        "analyzer-version-clang": "6.0.0",
        "analyzer-version-coverity": "2017.07-SP2",
        "analyzer-version-cppcheck": "1.80",
        "analyzer-version-gcc": "8.1.1",
        "analyzer-version-shellcheck": "0.4.7",
        "cov-compilation-unit-count": 193,
        "cov-compilation-unit-ratio": 100,
        "cov-lines-processed": 174359,
        "cov-time-elapsed-analysis": "00:01:55",
        "exit-code": 0,
        "host": "cov01.lab.eng.brq.redhat.com",
        "mock-config": "rhel-8.0-x86_64",
        "project-name": "curl-7.60.0-1.el8+7",
        "store-results-to": "/tmp/tmpteasee/curl-7.60.0-1.el8+7.tar.xz",
        "time-created": "2018-06-28 01:26:37",
        "time-finished": "2018-06-28 01:47:28",
        "tool": "csmock",
        "tool-args": "'/usr/bin/csmock' '-t' 'cppcheck,gcc,shellcheck,clang,coverity' '-o' '/tmp/tmpteasee/curl-7.60.0-1.el8+7.tar.xz' '-r' 'rhel-8.0-x86_64' '--cov-analyze-java' '--cov-analyze-opts=--security --concurrency' '--cov-use-version' 'cov-sa-2017.07' '--cov-fs-capture' '--use-host-cppcheck' '/tmp/tmpteasee/curl-7.60.0-1.el8+7.src.rpm'",
        "tool-version": "csmock-2.1.1.20180627.142826.g96a4a75-1.el6"
    },
    "defects": [
        {
            "checker": "SHELLCHECK_WARNING",
            "language": "shell",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "/usr/bin/curl-config",
                    "line": 25,
                    "column": 1,
                    "event": "warning[SC2034]",
                    "message": "exec_prefix appears unused. Verify it or export it.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   23|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   24|   prefix=/usr",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   25|-> exec_prefix=/usr",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   26|   includedir=/usr/include",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   27|   cppflag_curl_staticlib=",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "SHELLCHECK_WARNING",
            "language": "shell",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "/usr/bin/curl-config",
                    "line": 26,
                    "column": 1,
                    "event": "warning[SC2034]",
                    "message": "includedir appears unused. Verify it or export it.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   24|   prefix=/usr",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   25|   exec_prefix=/usr",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   26|-> includedir=/usr/include",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   27|   cppflag_curl_staticlib=",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   28|   ",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "SHELLCHECK_WARNING",
            "language": "shell",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "/usr/bin/curl-config",
                    "line": 66,
                    "column": 8,
                    "event": "warning[SC2034]",
                    "message": "value appears unused. Verify it or export it.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   64|       # [not currently used]",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   65|       -*=*) value=`echo \"$1\" | sed 's/[-_a-zA-Z0-9]*=//'` ;;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   66|->     *) value= ;;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   67|       esac",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   68|   ",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "SHELLCHECK_WARNING",
            "language": "shell",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "/usr/bin/curl-config",
                    "line": 146,
                    "column": 14,
                    "event": "warning[SC2039]",
                    "message": "In POSIX sh, echo flags are undefined.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  144|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  145|       --libs)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  146|->         echo -lcurl",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  147|           ;;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  148|       --ssl-backends)",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 4,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/base64.c",
                    "line": 183,
                    "event": "assignment",
                    "message": "Assigning: \"convbuf\" = \"NULL\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/base64.c",
                    "line": 213,
                    "event": "null",
                    "message": "At condition \"convbuf\", the value of \"convbuf\" must be \"NULL\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/base64.c",
                    "line": 213,
                    "event": "dead_error_condition",
                    "message": "The condition \"convbuf\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/base64.c",
                    "line": 214,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"indata = (char *)convbuf;\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/base64.c",
                    "line": 214,
                    "event": "effectively_constant",
                    "message": "Local variable \"convbuf\" is assigned only once, to a constant value, making it effectively constant throughout its scope. If this is not the intent, examine the logic to see if there is a missing assignment that would make \"convbuf\" not remain constant.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  212|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  213|     if(convbuf)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  214|->     indata = (char *)convbuf;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  215|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  216|     while(insize > 0) {",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "OVERRUN",
            "cwe": 119,
            "key_event_idx": 4,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/connect.c",
                    "line": 1353,
                    "event": "cond_true",
                    "message": "Condition \"!addr\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/connect.c",
                    "line": 1367,
                    "event": "cond_true",
                    "message": "Condition \"conn->socktype == SOCK_DGRAM\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/connect.c",
                    "line": 1370,
                    "event": "cond_true",
                    "message": "Condition \"addr->addrlen > 128UL /* sizeof (struct Curl_sockaddr_storage) */\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/connect.c",
                    "line": 1371,
                    "event": "assignment",
                    "message": "Assigning: \"addr->addrlen\" = \"128U\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/connect.c",
                    "line": 1372,
                    "event": "overrun-buffer-arg",
                    "message": "Overrunning struct type sockaddr of 16 bytes by passing it to a function which accesses it at byte offset 127 using argument \"addr->addrlen\" (which evaluates to 128). [Note: The source code implementation of the function has been overridden by a builtin model.]",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1370|     if(addr->addrlen > sizeof(struct Curl_sockaddr_storage))",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1371|        addr->addrlen = sizeof(struct Curl_sockaddr_storage);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1372|->   memcpy(&addr->sa_addr, ai->ai_addr, addr->addrlen);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1373|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1374|     if(data->set.fopensocket) {",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CPPCHECK_WARNING",
            "cwe": 456,
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 414,
                    "event": "error[uninitvar]",
                    "message": "Uninitialized variable: ks",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  412|     DES_key_schedule ks;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  413|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  414|->   setup_des_key(keys, DESKEY(ks));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  415|     DES_ecb_encrypt((DES_cblock*) plaintext, (DES_cblock*) results,",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  416|                     DESKEY(ks), DES_ENCRYPT);",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 479,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 480,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 480,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 481,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return result;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  479|     result = Curl_convert_to_network(data, (char *)pw, 14);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  480|     if(result)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  481|->     return result;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  482|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  483|     {",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CPPCHECK_WARNING",
            "cwe": 456,
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 489,
                    "event": "error[uninitvar]",
                    "message": "Uninitialized variable: ks",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  487|       DES_key_schedule ks;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  488|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  489|->     setup_des_key(pw, DESKEY(ks));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  490|       DES_ecb_encrypt((DES_cblock *)magic, (DES_cblock *)lmbuffer,",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  491|                       DESKEY(ks), DES_ENCRYPT);",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 571,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 572,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 572,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_core.c",
                    "line": 573,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return result;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  571|     result = Curl_convert_to_network(data, (char *)pw, len * 2);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  572|     if(result)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  573|->     return result;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  574|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  575|     {",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "TAINTED_STRING",
            "cwe": 20,
            "key_event_idx": 31,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 129,
                    "event": "cond_false",
                    "message": "Condition \"conn->ntlm_auth_hlpr_socket != -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 129,
                    "event": "cond_false",
                    "message": "Condition \"conn->ntlm_auth_hlpr_pid\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 131,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 142,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 144,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 146,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 147,
                    "event": "tainted_string_return_content",
                    "message": "\"getenv\" returns tainted string content.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 147,
                    "event": "var_assign",
                    "message": "Assigning: \"username\" = \"getenv(\"USER\")\", which taints \"username\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_false",
                    "message": "Condition \"!username\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_false",
                    "message": "Condition \"!username[0]\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 153,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 155,
                    "event": "cond_false",
                    "message": "Condition \"!username\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 155,
                    "event": "cond_false",
                    "message": "Condition \"!username[0]\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 156,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 159,
                    "event": "cond_true",
                    "message": "Condition \"slash\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 160,
                    "event": "tainted_data_transitive",
                    "message": "Call to function \"strdup\" with tainted argument \"username\" returns tainted data.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 160,
                    "event": "var_assign",
                    "message": "Assigning: \"domain\" = \"strdup(username)\", which taints \"domain\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 161,
                    "event": "cond_false",
                    "message": "Condition \"!domain\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 162,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 180,
                    "event": "cond_false",
                    "message": "Condition \"access(ntlm_auth, 1) != 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 184,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 186,
                    "event": "cond_false",
                    "message": "Condition \"socketpair(1, SOCK_STREAM, 0, sockfds)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 190,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 193,
                    "event": "cond_false",
                    "message": "Condition \"child_pid == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 200,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 200,
                    "event": "cond_true",
                    "message": "Condition \"!child_pid\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 207,
                    "event": "cond_false",
                    "message": "Condition \"dup2(sockfds[1], 0) == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 211,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 213,
                    "event": "cond_false",
                    "message": "Condition \"dup2(sockfds[1], 1) == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 217,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 219,
                    "event": "cond_true",
                    "message": "Condition \"domain\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 220,
                    "event": "tainted_string",
                    "message": "Passing tainted string \"domain\" to \"execl\", which cannot accept tainted data.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  218|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  219|       if(domain)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  220|->       execl(ntlm_auth, ntlm_auth,",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  221|               \"--helper-protocol\", \"ntlmssp-client-1\",",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  222|               \"--use-cached-creds\",",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "TAINTED_STRING",
            "cwe": 20,
            "key_event_idx": 30,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 129,
                    "event": "cond_false",
                    "message": "Condition \"conn->ntlm_auth_hlpr_socket != -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 129,
                    "event": "cond_false",
                    "message": "Condition \"conn->ntlm_auth_hlpr_pid\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 131,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 142,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 144,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 146,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 147,
                    "event": "tainted_string_return_content",
                    "message": "\"getenv\" returns tainted string content.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 147,
                    "event": "var_assign",
                    "message": "Assigning: \"username\" = \"getenv(\"USER\")\", which taints \"username\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_false",
                    "message": "Condition \"!username\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_false",
                    "message": "Condition \"!username[0]\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 153,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 155,
                    "event": "cond_false",
                    "message": "Condition \"!username\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 155,
                    "event": "cond_false",
                    "message": "Condition \"!username[0]\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 156,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 159,
                    "event": "cond_true",
                    "message": "Condition \"slash\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 161,
                    "event": "cond_false",
                    "message": "Condition \"!domain\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 162,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 165,
                    "event": "var_assign_var",
                    "message": "Assigning: \"username\" = \"username + (slash - domain) + 1\". Both are now tainted.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 180,
                    "event": "cond_false",
                    "message": "Condition \"access(ntlm_auth, 1) != 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 184,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 186,
                    "event": "cond_false",
                    "message": "Condition \"socketpair(1, SOCK_STREAM, 0, sockfds)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 190,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 193,
                    "event": "cond_false",
                    "message": "Condition \"child_pid == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 200,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 200,
                    "event": "cond_true",
                    "message": "Condition \"!child_pid\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 207,
                    "event": "cond_false",
                    "message": "Condition \"dup2(sockfds[1], 0) == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 211,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 213,
                    "event": "cond_false",
                    "message": "Condition \"dup2(sockfds[1], 1) == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 217,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 219,
                    "event": "cond_true",
                    "message": "Condition \"domain\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 220,
                    "event": "tainted_string",
                    "message": "Passing tainted string \"username\" to \"execl\", which cannot accept tainted data.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  218|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  219|       if(domain)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  220|->       execl(ntlm_auth, ntlm_auth,",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  221|               \"--helper-protocol\", \"ntlmssp-client-1\",",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  222|               \"--use-cached-creds\",",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "TOCTOU",
            "cwe": 367,
            "key_event_idx": 24,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 129,
                    "event": "cond_false",
                    "message": "Condition \"conn->ntlm_auth_hlpr_socket != -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 129,
                    "event": "cond_false",
                    "message": "Condition \"conn->ntlm_auth_hlpr_pid\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 131,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 142,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 144,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 146,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_true",
                    "message": "Condition \"!getpwuid_r(geteuid(), &pw, pwbuf, 1024UL /* sizeof (pwbuf) */, &pw_res)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_true",
                    "message": "Condition \"pw_res\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 155,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 159,
                    "event": "cond_true",
                    "message": "Condition \"slash\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 161,
                    "event": "cond_false",
                    "message": "Condition \"!domain\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 162,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 180,
                    "event": "fs_check_call",
                    "message": "Calling function \"access\" to perform check on \"ntlm_auth\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 180,
                    "event": "cond_false",
                    "message": "Condition \"access(ntlm_auth, 1) != 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 184,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 186,
                    "event": "cond_false",
                    "message": "Condition \"socketpair(1, SOCK_STREAM, 0, sockfds)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 190,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 193,
                    "event": "cond_false",
                    "message": "Condition \"child_pid == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 200,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 200,
                    "event": "cond_true",
                    "message": "Condition \"!child_pid\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 207,
                    "event": "cond_true",
                    "message": "Condition \"dup2(sockfds[1], 0) == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 213,
                    "event": "cond_true",
                    "message": "Condition \"dup2(sockfds[1], 1) == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 219,
                    "event": "cond_true",
                    "message": "Condition \"domain\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 220,
                    "event": "toctou",
                    "message": "Calling function \"execl\" that uses \"ntlm_auth\" after a check function. This can cause a time-of-check, time-of-use race condition.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  218|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  219|       if(domain)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  220|->       execl(ntlm_auth, ntlm_auth,",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  221|               \"--helper-protocol\", \"ntlmssp-client-1\",",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  222|               \"--use-cached-creds\",",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "TOCTOU",
            "cwe": 367,
            "key_event_idx": 24,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 129,
                    "event": "cond_false",
                    "message": "Condition \"conn->ntlm_auth_hlpr_socket != -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 129,
                    "event": "cond_false",
                    "message": "Condition \"conn->ntlm_auth_hlpr_pid\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 131,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 142,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 144,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 146,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_true",
                    "message": "Condition \"!getpwuid_r(geteuid(), &pw, pwbuf, 1024UL /* sizeof (pwbuf) */, &pw_res)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 149,
                    "event": "cond_true",
                    "message": "Condition \"pw_res\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 155,
                    "event": "cond_true",
                    "message": "Condition \"!username\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 159,
                    "event": "cond_false",
                    "message": "Condition \"slash\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 166,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 180,
                    "event": "fs_check_call",
                    "message": "Calling function \"access\" to perform check on \"ntlm_auth\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 180,
                    "event": "cond_false",
                    "message": "Condition \"access(ntlm_auth, 1) != 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 184,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 186,
                    "event": "cond_false",
                    "message": "Condition \"socketpair(1, SOCK_STREAM, 0, sockfds)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 190,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 193,
                    "event": "cond_false",
                    "message": "Condition \"child_pid == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 200,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 200,
                    "event": "cond_true",
                    "message": "Condition \"!child_pid\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 207,
                    "event": "cond_true",
                    "message": "Condition \"dup2(sockfds[1], 0) == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 213,
                    "event": "cond_true",
                    "message": "Condition \"dup2(sockfds[1], 1) == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 219,
                    "event": "cond_false",
                    "message": "Condition \"domain\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 227,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/curl_ntlm_wb.c",
                    "line": 227,
                    "event": "toctou",
                    "message": "Calling function \"execl\" that uses \"ntlm_auth\" after a check function. This can cause a time-of-check, time-of-use race condition.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  225|               NULL);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  226|       else",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  227|->       execl(ntlm_auth, ntlm_auth,",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  228|               \"--helper-protocol\", \"ntlmssp-client-1\",",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  229|               \"--use-cached-creds\",",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CLANG_WARNING",
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/formdata.c",
                    "line": 0,
                    "event": "internal warning",
                    "message": "child 19175 timed out after 30s",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CLANG_WARNING",
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/formdata.c",
                    "line": 0,
                    "event": "internal warning",
                    "message": "child 31044 timed out after 30s",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CLANG_WARNING",
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/ftp.c",
                    "line": 0,
                    "event": "internal warning",
                    "message": "child 31022 timed out after 30s",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/ftp.c",
                    "line": 3975,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)conn->data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ftp.c",
                    "line": 3977,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ftp.c",
                    "line": 3977,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ftp.c",
                    "line": 3978,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return result;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3976|     /* Curl_convert_to_network calls failf if unsuccessful */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3977|     if(result)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3978|->     return result;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3979|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3980|     for(;;) {",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CONSTANT_EXPRESSION_RESULT",
            "cwe": 398,
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/getinfo.c",
                    "line": 159,
                    "event": "result_independent_of_operands",
                    "message": "\"data->info.filetime > 9223372036854775807L\" is always false regardless of the values of its operands. This occurs as the logical operand of \"if\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  157|       break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  158|     case CURLINFO_FILETIME:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  159|->     if(data->info.filetime > LONG_MAX)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  160|         *param_longp = LONG_MAX;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  161|       else if(data->info.filetime < LONG_MIN)",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CONSTANT_EXPRESSION_RESULT",
            "cwe": 398,
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/getinfo.c",
                    "line": 161,
                    "event": "result_independent_of_operands",
                    "message": "\"data->info.filetime < -9223372036854775808L /* -9223372036854775807L - 1L */\" is always false regardless of the values of its operands. This occurs as the logical operand of \"if\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  159|       if(data->info.filetime > LONG_MAX)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  160|         *param_longp = LONG_MAX;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  161|->     else if(data->info.filetime < LONG_MIN)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  162|         *param_longp = LONG_MIN;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  163|       else",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/http.c",
                    "line": 1086,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)conn->data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http.c",
                    "line": 1088,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http.c",
                    "line": 1088,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http.c",
                    "line": 1090,
                    "event": "dead_error_begin",
                    "message": "Execution cannot reach this statement: \"Curl_add_buffer_free(in);\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1088|     if(result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1089|       /* conversion failed, free memory and return to the caller */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1090|->     Curl_add_buffer_free(in);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1091|       return result;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1092|     }",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/http.c",
                    "line": 3566,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http.c",
                    "line": 3568,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http.c",
                    "line": 3568,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http.c",
                    "line": 3569,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return result;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3567|       /* Curl_convert_from_network calls failf if unsuccessful */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3568|       if(result)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3569|->       return result;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3570|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3571|       /* Check for Content-Length: header lines to get size */",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/http_chunks.c",
                    "line": 157,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)conn->data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_chunks.c",
                    "line": 159,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_chunks.c",
                    "line": 159,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_chunks.c",
                    "line": 162,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return CHUNKE_ILLEGAL_HEX;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  160|             /* Curl_convert_from_network calls failf if unsuccessful */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  161|             /* Treat it as a bad hex character */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  162|->           return CHUNKE_ILLEGAL_HEX;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  163|           }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  164|   ",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/http_chunks.c",
                    "line": 237,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)conn->data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_chunks.c",
                    "line": 239,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_chunks.c",
                    "line": 239,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_chunks.c",
                    "line": 242,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return CHUNKE_BAD_CHUNK;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  240|               /* Curl_convert_from_network calls failf if unsuccessful */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  241|               /* Treat it as a bad chunk */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  242|->             return CHUNKE_BAD_CHUNK;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  243|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  244|             if(!data->set.http_te_skip) {",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/http_proxy.c",
                    "line": 413,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_proxy.c",
                    "line": 416,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_proxy.c",
                    "line": 416,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/http_proxy.c",
                    "line": 417,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return result;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  415|           /* Curl_convert_from_network calls failf if unsuccessful */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  416|           if(result)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  417|->           return result;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  418|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  419|           /* output debug if that is requested */",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CLANG_WARNING",
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 0,
                    "event": "internal warning",
                    "message": "child 32119 timed out after 30s",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "key_event_idx": 103,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 959,
                    "event": "assign_zero",
                    "message": "Assigning: \"ufds\" = \"NULL\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 965,
                    "event": "cond_true",
                    "message": "Condition \"multi\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 965,
                    "event": "cond_true",
                    "message": "Condition \"multi->type == 764702\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 966,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 968,
                    "event": "cond_false",
                    "message": "Condition \"multi->in_callback\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 969,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 975,
                    "event": "cond_false",
                    "message": "Condition \"timeout_internal >= 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 976,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 989,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 989,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_false",
                    "message": "Condition \"data\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1005,
                    "event": "cond_false",
                    "message": "Condition \"nfds\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1018,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1024,
                    "event": "cond_true",
                    "message": "Condition \"curlfds\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1027,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1030,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1033,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1034,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"ufds\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1032|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1033|           if(bitmap & GETSOCK_READSOCK(i)) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1034|->           ufds[nfds].fd = sockbunch[i];",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1035|             ufds[nfds].events = POLLIN;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1036|             ++nfds;",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "key_event_idx": 105,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 959,
                    "event": "assign_zero",
                    "message": "Assigning: \"ufds\" = \"NULL\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 965,
                    "event": "cond_true",
                    "message": "Condition \"multi\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 965,
                    "event": "cond_true",
                    "message": "Condition \"multi->type == 764702\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 966,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 968,
                    "event": "cond_false",
                    "message": "Condition \"multi->in_callback\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 969,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 975,
                    "event": "cond_false",
                    "message": "Condition \"timeout_internal >= 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 976,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 989,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 989,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_false",
                    "message": "Condition \"data\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1005,
                    "event": "cond_false",
                    "message": "Condition \"nfds\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1018,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1024,
                    "event": "cond_true",
                    "message": "Condition \"curlfds\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1027,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1030,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1033,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1038,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1039,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1040,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"ufds\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1038|           }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1039|           if(bitmap & GETSOCK_WRITESOCK(i)) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1040|->           ufds[nfds].fd = sockbunch[i];",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1041|             ufds[nfds].events = POLLOUT;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1042|             ++nfds;",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "key_event_idx": 114,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 959,
                    "event": "assign_zero",
                    "message": "Assigning: \"ufds\" = \"NULL\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 965,
                    "event": "cond_true",
                    "message": "Condition \"multi\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 965,
                    "event": "cond_true",
                    "message": "Condition \"multi->type == 764702\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 966,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 968,
                    "event": "cond_false",
                    "message": "Condition \"multi->in_callback\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 969,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 975,
                    "event": "cond_false",
                    "message": "Condition \"timeout_internal >= 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 976,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 989,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_false",
                    "message": "Condition \"s == -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 996,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_true",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 983,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 986,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 989,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 990,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 993,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 994,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 995,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 997,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 980,
                    "event": "cond_false",
                    "message": "Condition \"data\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1000,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1005,
                    "event": "cond_false",
                    "message": "Condition \"nfds\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1018,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1024,
                    "event": "cond_true",
                    "message": "Condition \"curlfds\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1027,
                    "event": "cond_true",
                    "message": "Condition \"data\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1030,
                    "event": "cond_true",
                    "message": "Condition \"i < 5\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1033,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1038,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1039,
                    "event": "cond_false",
                    "message": "Condition \"bitmap & (1 << 16 + i)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1044,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1045,
                    "event": "cond_true",
                    "message": "Condition \"s == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1046,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1048,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1051,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1027,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1027,
                    "event": "cond_false",
                    "message": "Condition \"data\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1051,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1055,
                    "event": "cond_true",
                    "message": "Condition \"i < extra_nfds\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/multi.c",
                    "line": 1056,
                    "event": "var_deref_op",
                    "message": "Dereferencing null pointer \"ufds\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1054|     /* Add external file descriptions from poll-like struct curl_waitfd */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1055|     for(i = 0; i < extra_nfds; i++) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1056|->     ufds[nfds].fd = extra_fds[i].fd;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1057|       ufds[nfds].events = 0;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1058|       if(extra_fds[i].events & CURL_WAIT_POLLIN)",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/sendf.c",
                    "line": 441,
                    "event": "assignment",
                    "message": "Assigning: \"nread\" = \"0L\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/sendf.c",
                    "line": 442,
                    "event": "const",
                    "message": "At condition \"nread > 0L\", the value of \"nread\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/sendf.c",
                    "line": 442,
                    "event": "dead_error_condition",
                    "message": "The condition \"nread > 0L\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/sendf.c",
                    "line": 443,
                    "event": "dead_error_begin",
                    "message": "Execution cannot reach this statement: \"*code = CURLE_OK;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  441|     nread = get_pre_recved(conn, num, buf, len);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  442|     if(nread > 0) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  443|->     *code = CURLE_OK;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  444|       return nread;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  445|     }",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/sendf.c",
                    "line": 657,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/sendf.c",
                    "line": 659,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/sendf.c",
                    "line": 659,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/sendf.c",
                    "line": 660,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return result;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  658|       /* Curl_convert_from_network calls failf if unsuccessful */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  659|       if(result)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  660|->       return result;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  661|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  662|   #ifdef CURL_DO_LINEEND_CONV",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 10,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 734,
                    "event": "assignment",
                    "message": "Assigning: \"next_state\" = \"SMB_DONE\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 773,
                    "event": "assignment",
                    "message": "Assigning: \"next_state\" = \"SMB_OPEN\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 779,
                    "event": "assignment",
                    "message": "Assigning: \"next_state\" = \"SMB_TREE_DISCONNECT\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 788,
                    "event": "assignment",
                    "message": "Assigning: \"next_state\" = \"SMB_UPLOAD\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 795,
                    "event": "assignment",
                    "message": "Assigning: \"next_state\" = \"SMB_CLOSE\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 801,
                    "event": "assignment",
                    "message": "Assigning: \"next_state\" = \"SMB_DOWNLOAD\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 827,
                    "event": "assignment",
                    "message": "Assigning: \"next_state\" = \"SMB_CLOSE\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 834,
                    "event": "assignment",
                    "message": "Assigning: \"next_state\" = \"(len < 32768) ? SMB_CLOSE : SMB_DOWNLOAD\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 870,
                    "event": "between",
                    "message": "When switching on \"next_state\", the value of \"next_state\" must be between 2 and 7.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 870,
                    "event": "dead_error_condition",
                    "message": "The switch value \"next_state\" cannot reach the default case.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/smb.c",
                    "line": 896,
                    "event": "dead_error_begin",
                    "message": "Execution cannot reach this statement: \"default:\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  894|       break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  895|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  896|->   default:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  897|       break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  898|     }",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "STRING_OVERFLOW",
            "cwe": 120,
            "key_event_idx": 4,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 51,
                    "event": "cond_true",
                    "message": "Condition \"major_status & (4294901760U /* ((OM_uint32)255UL << 24) | ((OM_uint32)255UL << 16) */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 60,
                    "event": "cond_true",
                    "message": "Condition \"!msg_ctx\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 66,
                    "event": "cond_true",
                    "message": "Condition \"maj_stat == 0\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 67,
                    "event": "cond_true",
                    "message": "Condition \"1024UL /* sizeof (buf) */ > len + status_string.length + 1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 68,
                    "event": "fixed_size_dest",
                    "message": "You might overrun the 1024-character fixed-size string \"buf + len\" by copying \"status_string.value\" without checking the length.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   66|         if(maj_stat == GSS_S_COMPLETE) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   67|           if(sizeof(buf) > len + status_string.length + 1) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   68|->           strcpy(buf + len, (char *) status_string.value);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   69|             len += status_string.length;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   70|           }",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "STRING_OVERFLOW",
            "cwe": 120,
            "key_event_idx": 10,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 51,
                    "event": "cond_true",
                    "message": "Condition \"major_status & (4294901760U /* ((OM_uint32)255UL << 24) | ((OM_uint32)255UL << 16) */)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 60,
                    "event": "cond_true",
                    "message": "Condition \"!msg_ctx\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 66,
                    "event": "cond_true",
                    "message": "Condition \"maj_stat == 0\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 67,
                    "event": "cond_true",
                    "message": "Condition \"1024UL /* sizeof (buf) */ > len + status_string.length + 1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 72,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 75,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 76,
                    "event": "cond_true",
                    "message": "Condition \"1024UL /* sizeof (buf) */ > len + 3\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 81,
                    "event": "cond_true",
                    "message": "Condition \"!msg_ctx\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 87,
                    "event": "cond_true",
                    "message": "Condition \"maj_stat == 0\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 88,
                    "event": "cond_true",
                    "message": "Condition \"1024UL /* sizeof (buf) */ > len + status_string.length\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/socks_gssapi.c",
                    "line": 89,
                    "event": "fixed_size_dest",
                    "message": "You might overrun the 1024-character fixed-size string \"buf + len\" by copying \"status_string.value\" without checking the length.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   87|         if(maj_stat == GSS_S_COMPLETE) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   88|           if(sizeof(buf) > len + status_string.length)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   89|->           strcpy(buf + len, (char *) status_string.value);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   90|           gss_release_buffer(&min_stat, &status_string);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "   91|           break;",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CLANG_WARNING",
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1116,
                    "column": 15,
                    "event": "warning",
                    "message": "Null pointer passed as an argument to a 'nonnull' parameter",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "             (strlen(protop->path) > 1))) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "              ^      ~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 549,
                    "column": 5,
                    "event": "note",
                    "message": "Control jumps to 'case SSH_SFTP_CLOSE:'  at line 1615",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    switch(sshc->state) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1616,
                    "column": 7,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->sftp_file) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1620,
                    "column": 7,
                    "event": "note",
                    "message": "Null pointer value stored to field 'path'",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      Curl_safefree(protop->path);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^~~~~~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/memdebug.h",
                    "line": 184,
                    "column": 21,
                    "event": "note",
                    "message": "expanded from macro 'Curl_safefree'",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do { free((ptr)); (ptr) = NULL;} WHILE_FALSE",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "                    ^~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1620,
                    "column": 7,
                    "event": "note",
                    "message": "Loop condition is false.  Exiting loop",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/memdebug.h",
                    "line": 184,
                    "column": 3,
                    "event": "note",
                    "message": "expanded from macro 'Curl_safefree'",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do { free((ptr)); (ptr) = NULL;} WHILE_FALSE",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1627,
                    "column": 10,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->nextstate != SSH_NO_STATE &&",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1627,
                    "column": 7,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->nextstate != SSH_NO_STATE &&",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1636,
                    "column": 7,
                    "event": "note",
                    "message": " Execution continues on line 1887",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1887,
                    "column": 11,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  } while(!rc && (sshc->state != SSH_STOP));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1887,
                    "column": 19,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  } while(!rc && (sshc->state != SSH_STOP));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "                  ^~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 547,
                    "column": 3,
                    "event": "note",
                    "message": "Loop condition is true. Execution continues on line 549",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 549,
                    "column": 5,
                    "event": "note",
                    "message": "Control jumps to 'case SSH_SFTP_READDIR_BOTTOM:'  at line 1412",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    switch(sshc->state) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1421,
                    "column": 10,
                    "event": "note",
                    "message": "Assuming 'result' is 0",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(!result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1421,
                    "column": 7,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(!result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1424,
                    "column": 12,
                    "event": "note",
                    "message": "Assuming the condition is false",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(data->set.verbose) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "           ^~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1424,
                    "column": 9,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(data->set.verbose) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1434,
                    "column": 7,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1439,
                    "column": 7,
                    "event": "note",
                    "message": " Execution continues on line 1887",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1887,
                    "column": 11,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  } while(!rc && (sshc->state != SSH_STOP));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 547,
                    "column": 3,
                    "event": "note",
                    "message": "Loop condition is true. Execution continues on line 549",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 549,
                    "column": 5,
                    "event": "note",
                    "message": "Control jumps to 'case SSH_SFTP_READDIR:'  at line 1273",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    switch(sshc->state) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1275,
                    "column": 7,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->readdir_attrs)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1279,
                    "column": 10,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->readdir_attrs) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1279,
                    "column": 7,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->readdir_attrs) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1284,
                    "column": 12,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(data->set.ftp_list_only) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "           ^~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1284,
                    "column": 9,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(data->set.ftp_list_only) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1288,
                    "column": 14,
                    "event": "note",
                    "message": "Assuming 'tmpLine' is not equal to NULL",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(tmpLine == NULL) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "             ^~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1288,
                    "column": 11,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(tmpLine == NULL) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1297,
                    "column": 14,
                    "event": "note",
                    "message": "Assuming 'result' is 0",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "             ^~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1297,
                    "column": 11,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1306,
                    "column": 11,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(data->set.verbose) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1354,
                    "column": 7,
                    "event": "note",
                    "message": " Execution continues on line 1887",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1887,
                    "column": 11,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  } while(!rc && (sshc->state != SSH_STOP));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 547,
                    "column": 3,
                    "event": "note",
                    "message": "Loop condition is true. Execution continues on line 549",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 549,
                    "column": 5,
                    "event": "note",
                    "message": "Control jumps to 'case SSH_SFTP_UPLOAD_INIT:'  at line 1070",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    switch(sshc->state) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1074,
                    "column": 10,
                    "event": "note",
                    "message": "Assuming the condition is false",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(data->state.resume_from != 0) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1074,
                    "column": 7,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(data->state.resume_from != 0) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1095,
                    "column": 10,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(data->set.ftp_append)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1095,
                    "column": 7,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(data->set.ftp_append)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1105,
                    "column": 7,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->sftp_file)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1110,
                    "column": 10,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(!sshc->sftp_file) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1110,
                    "column": 7,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(!sshc->sftp_file) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1113,
                    "column": 14,
                    "event": "note",
                    "message": "Assuming 'err' is equal to SSH_FX_NO_SUCH_FILE",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(((err == SSH_FX_NO_SUCH_FILE || err == SSH_FX_FAILURE ||",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "             ^~~~~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1113,
                    "column": 41,
                    "event": "note",
                    "message": "Left side of '||' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(((err == SSH_FX_NO_SUCH_FILE || err == SSH_FX_FAILURE ||",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "                                        ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1115,
                    "column": 15,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "             (data->set.ftp_create_missing_dirs &&",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "              ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1115,
                    "column": 15,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1116,
                    "column": 15,
                    "event": "note",
                    "message": "Null pointer passed as an argument to a 'nonnull' parameter",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "             (strlen(protop->path) > 1))) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "              ^      ~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1114|                err == SSH_FX_NO_SUCH_PATH)) &&",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1115|                (data->set.ftp_create_missing_dirs &&",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1116|->              (strlen(protop->path) > 1))) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1117|                  /* try to create the path remotely */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1118|                  rc = 0;",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CLANG_WARNING",
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1208,
                    "column": 10,
                    "event": "warning",
                    "message": "Null pointer passed as an argument to a 'nonnull' parameter",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(strlen(protop->path) > 1) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^      ~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 549,
                    "column": 5,
                    "event": "note",
                    "message": "Control jumps to 'case SSH_SFTP_CLOSE:'  at line 1615",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    switch(sshc->state) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1616,
                    "column": 7,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->sftp_file) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1620,
                    "column": 7,
                    "event": "note",
                    "message": "Null pointer value stored to field 'path'",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      Curl_safefree(protop->path);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^~~~~~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/memdebug.h",
                    "line": 184,
                    "column": 21,
                    "event": "note",
                    "message": "expanded from macro 'Curl_safefree'",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do { free((ptr)); (ptr) = NULL;} WHILE_FALSE",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "                    ^~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1620,
                    "column": 7,
                    "event": "note",
                    "message": "Loop condition is false.  Exiting loop",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/memdebug.h",
                    "line": 184,
                    "column": 3,
                    "event": "note",
                    "message": "expanded from macro 'Curl_safefree'",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do { free((ptr)); (ptr) = NULL;} WHILE_FALSE",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1627,
                    "column": 10,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->nextstate != SSH_NO_STATE &&",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1627,
                    "column": 7,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->nextstate != SSH_NO_STATE &&",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1636,
                    "column": 7,
                    "event": "note",
                    "message": " Execution continues on line 1887",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1887,
                    "column": 11,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  } while(!rc && (sshc->state != SSH_STOP));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1887,
                    "column": 19,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  } while(!rc && (sshc->state != SSH_STOP));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "                  ^~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 547,
                    "column": 3,
                    "event": "note",
                    "message": "Loop condition is true. Execution continues on line 549",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 549,
                    "column": 5,
                    "event": "note",
                    "message": "Control jumps to 'case SSH_SFTP_READDIR_BOTTOM:'  at line 1412",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    switch(sshc->state) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1421,
                    "column": 10,
                    "event": "note",
                    "message": "Assuming 'result' is 0",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(!result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1421,
                    "column": 7,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(!result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1424,
                    "column": 12,
                    "event": "note",
                    "message": "Assuming the condition is false",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(data->set.verbose) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "           ^~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1424,
                    "column": 9,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(data->set.verbose) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1434,
                    "column": 7,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1439,
                    "column": 7,
                    "event": "note",
                    "message": " Execution continues on line 1887",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1887,
                    "column": 11,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  } while(!rc && (sshc->state != SSH_STOP));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 547,
                    "column": 3,
                    "event": "note",
                    "message": "Loop condition is true. Execution continues on line 549",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 549,
                    "column": 5,
                    "event": "note",
                    "message": "Control jumps to 'case SSH_SFTP_READDIR:'  at line 1273",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    switch(sshc->state) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1275,
                    "column": 7,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->readdir_attrs)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1279,
                    "column": 10,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->readdir_attrs) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1279,
                    "column": 7,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(sshc->readdir_attrs) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1284,
                    "column": 12,
                    "event": "note",
                    "message": "Assuming the condition is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(data->set.ftp_list_only) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "           ^~~~~~~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1284,
                    "column": 9,
                    "event": "note",
                    "message": "Taking true branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        if(data->set.ftp_list_only) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "        ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1288,
                    "column": 14,
                    "event": "note",
                    "message": "Assuming 'tmpLine' is not equal to NULL",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(tmpLine == NULL) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "             ^~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1288,
                    "column": 11,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(tmpLine == NULL) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1297,
                    "column": 14,
                    "event": "note",
                    "message": "Assuming 'result' is 0",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "             ^~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1297,
                    "column": 11,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(result) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1306,
                    "column": 11,
                    "event": "note",
                    "message": "Taking false branch",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          if(data->set.verbose) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1354,
                    "column": 7,
                    "event": "note",
                    "message": " Execution continues on line 1887",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1887,
                    "column": 11,
                    "event": "note",
                    "message": "Left side of '&&' is true",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  } while(!rc && (sshc->state != SSH_STOP));",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "          ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 547,
                    "column": 3,
                    "event": "note",
                    "message": "Loop condition is true. Execution continues on line 549",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  do {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 549,
                    "column": 5,
                    "event": "note",
                    "message": "Control jumps to 'case SSH_SFTP_CREATE_DIRS_INIT:'  at line 1207",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    switch(sshc->state) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "    ^",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/ssh-libssh.c",
                    "line": 1208,
                    "column": 10,
                    "event": "note",
                    "message": "Null pointer passed as an argument to a 'nonnull' parameter",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "      if(strlen(protop->path) > 1) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "         ^      ~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1206|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1207|       case SSH_SFTP_CREATE_DIRS_INIT:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1208|->       if(strlen(protop->path) > 1) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1209|           sshc->slash_pos = protop->path + 1; /* ignore the leading '/' */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1210|           state(conn, SSH_SFTP_CREATE_DIRS);",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "key_event_idx": 120,
            "events": [
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"i < argc\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"!result\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"stillflags\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"'-' == argv[i][0]\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2148,
                    "event": "cond_false",
                    "message": "Condition \"!strcmp(\"--\", argv[i])\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2152,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2153,
                    "event": "cond_true",
                    "message": "Condition \"i < argc - 1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2156,
                    "event": "cond_false",
                    "message": "Condition \"result == PARAM_NEXT_OPERATION\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2185,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2185,
                    "event": "cond_true",
                    "message": "Condition \"!result\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2185,
                    "event": "cond_true",
                    "message": "Condition \"passarg\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2188,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2195,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2196,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"i < argc\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"!result\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"stillflags\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"'-' == argv[i][0]\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2148,
                    "event": "cond_false",
                    "message": "Condition \"!strcmp(\"--\", argv[i])\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2152,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2153,
                    "event": "cond_true",
                    "message": "Condition \"i < argc - 1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2156,
                    "event": "cond_true",
                    "message": "Condition \"result == PARAM_NEXT_OPERATION\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2161,
                    "event": "cond_true",
                    "message": "Condition \"operation->url_list\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2161,
                    "event": "cond_true",
                    "message": "Condition \"operation->url_list->url\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2164,
                    "event": "cond_true",
                    "message": "Condition \"operation->next\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2180,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2182,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2184,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2186,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2188,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2195,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2196,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"i < argc\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"!result\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"stillflags\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"'-' == argv[i][0]\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2148,
                    "event": "cond_false",
                    "message": "Condition \"!strcmp(\"--\", argv[i])\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2152,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2153,
                    "event": "cond_true",
                    "message": "Condition \"i < argc - 1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2156,
                    "event": "cond_true",
                    "message": "Condition \"result == PARAM_NEXT_OPERATION\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2161,
                    "event": "cond_false",
                    "message": "Condition \"operation->url_list\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2183,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2184,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2186,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2188,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2195,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2196,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"i < argc\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"!result\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"stillflags\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"'-' == argv[i][0]\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2148,
                    "event": "cond_false",
                    "message": "Condition \"!strcmp(\"--\", argv[i])\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2152,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2153,
                    "event": "cond_false",
                    "message": "Condition \"i < argc - 1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2156,
                    "event": "cond_false",
                    "message": "Condition \"result == PARAM_NEXT_OPERATION\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2185,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2185,
                    "event": "cond_true",
                    "message": "Condition \"!result\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2185,
                    "event": "cond_false",
                    "message": "Condition \"passarg\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2186,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2188,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2195,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2196,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"i < argc\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2140,
                    "event": "cond_true",
                    "message": "Condition \"!result\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"stillflags\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2143,
                    "event": "cond_true",
                    "message": "Condition \"'-' == argv[i][0]\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2148,
                    "event": "cond_false",
                    "message": "Condition \"!strcmp(\"--\", argv[i])\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2152,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2153,
                    "event": "cond_false",
                    "message": "Condition \"i < argc - 1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2153,
                    "event": "assign_zero",
                    "message": "Assigning: \"nextarg\" = \"NULL\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 2155,
                    "event": "var_deref_model",
                    "message": "Passing null pointer \"nextarg\" to \"getparameter\", which dereferences it.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 505,
                    "column": 3,
                    "event": "cond_true",
                    "message": "Condition \"'-' != flag[0]\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 512,
                    "column": 5,
                    "event": "cond_true",
                    "message": "Condition \"!strncmp(word, \"no-\", 3)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 518,
                    "column": 5,
                    "event": "cond_true",
                    "message": "Condition \"j < 221UL /* sizeof (aliases) / sizeof (aliases[0]) */\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 519,
                    "column": 7,
                    "event": "cond_true",
                    "message": "Condition \"curl_strnequal(aliases[j].lname, word, fnam)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 522,
                    "column": 9,
                    "event": "cond_false",
                    "message": "Condition \"curl_strequal(aliases[j].lname, word)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 527,
                    "column": 9,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 531,
                    "column": 5,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 518,
                    "column": 5,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 518,
                    "column": 5,
                    "event": "cond_true",
                    "message": "Condition \"j < 221UL /* sizeof (aliases) / sizeof (aliases[0]) */\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 519,
                    "column": 7,
                    "event": "cond_true",
                    "message": "Condition \"curl_strnequal(aliases[j].lname, word, fnam)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 522,
                    "column": 9,
                    "event": "cond_false",
                    "message": "Condition \"curl_strequal(aliases[j].lname, word)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 527,
                    "column": 9,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 531,
                    "column": 5,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 518,
                    "column": 5,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 518,
                    "column": 5,
                    "event": "cond_true",
                    "message": "Condition \"j < 221UL /* sizeof (aliases) / sizeof (aliases[0]) */\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 519,
                    "column": 7,
                    "event": "cond_true",
                    "message": "Condition \"curl_strnequal(aliases[j].lname, word, fnam)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 522,
                    "column": 9,
                    "event": "cond_false",
                    "message": "Condition \"curl_strequal(aliases[j].lname, word)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 527,
                    "column": 9,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 531,
                    "column": 5,
                    "event": "loop",
                    "message": "Jumping back to the beginning of the loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 518,
                    "column": 5,
                    "event": "loop_begin",
                    "message": "Jumped back to beginning of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 518,
                    "column": 5,
                    "event": "cond_true",
                    "message": "Condition \"j < 221UL /* sizeof (aliases) / sizeof (aliases[0]) */\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 519,
                    "column": 7,
                    "event": "cond_true",
                    "message": "Condition \"curl_strnequal(aliases[j].lname, word, fnam)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 522,
                    "column": 9,
                    "event": "cond_true",
                    "message": "Condition \"curl_strequal(aliases[j].lname, word)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 526,
                    "column": 11,
                    "event": "break",
                    "message": "Breaking from loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 531,
                    "column": 5,
                    "event": "loop_end",
                    "message": "Reached end of loop.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 532,
                    "column": 5,
                    "event": "cond_false",
                    "message": "Condition \"numhits > 1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 535,
                    "column": 5,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 536,
                    "column": 5,
                    "event": "cond_false",
                    "message": "Condition \"hit < 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 538,
                    "column": 5,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 539,
                    "column": 3,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 544,
                    "column": 3,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 549,
                    "column": 5,
                    "event": "cond_false",
                    "message": "Condition \"!longopt\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 553,
                    "column": 10,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 558,
                    "column": 5,
                    "event": "cond_false",
                    "message": "Condition \"hit < 0\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 568,
                    "column": 5,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 570,
                    "column": 5,
                    "event": "cond_false",
                    "message": "Condition \"aliases[hit].desc == ARG_STRING\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 581,
                    "column": 10,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 581,
                    "column": 10,
                    "event": "cond_false",
                    "message": "Condition \"aliases[hit].desc == ARG_NONE\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 582,
                    "column": 7,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 584,
                    "column": 5,
                    "event": "switch",
                    "message": "Switch case value \"'*'\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 585,
                    "column": 10,
                    "event": "switch_case",
                    "message": "Reached case \"'*'\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 586,
                    "column": 7,
                    "event": "switch",
                    "message": "Switch case value \"'i'\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 646,
                    "column": 12,
                    "event": "switch_case",
                    "message": "Reached case \"'i'\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 649,
                    "column": 27,
                    "event": "deref_parm_in_call",
                    "message": "Function \"GetSizeParameter\" dereferences \"nextarg\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_getparam.c",
                    "line": 442,
                    "column": 3,
                    "event": "deref_parm_in_call",
                    "message": "Function \"curlx_strtoofft\" dereferences \"arg\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/strtoofft.c",
                    "line": 223,
                    "column": 3,
                    "event": "deref_parm",
                    "message": "Directly dereferencing parameter \"str\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  221|     *num = 0; /* clear by default */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  222|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  223|->   while(*str && ISSPACE(*str))",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  224|       str++;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  225|     if('-' == *str) {",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "STRING_NULL",
            "cwe": 170,
            "key_event_idx": 6,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 1110,
                    "event": "string_null_argument",
                    "message": "Function \"recvfrom\" does not terminate string \"*state->rpacket.data\". [Note: The source code implementation of the function has been overridden by a builtin model.]",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 1116,
                    "event": "cond_true",
                    "message": "Condition \"state->remote_addrlen == 0\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 1122,
                    "event": "cond_false",
                    "message": "Condition \"state->rbytes < 4\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 1127,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 1132,
                    "event": "switch",
                    "message": "Switch case value \"TFTP_EVENT_OACK\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 1157,
                    "event": "switch_case",
                    "message": "Reached case \"TFTP_EVENT_OACK\".",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 1158,
                    "event": "string_null",
                    "message": "Passing unterminated string \"(char const *)state->rpacket.data + 2\" to \"tftp_parse_option_ack\", which expects a null-terminated string.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 337,
                    "column": 19,
                    "event": "var_assign_parm",
                    "message": "Assigning: \"tmp\" = \"ptr\". They now point to the same thing.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 343,
                    "column": 3,
                    "event": "cond_true",
                    "message": "Condition \"tmp < ptr + len\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 346,
                    "column": 5,
                    "event": "string_null_sink_lv_call",
                    "message": "Passing local \"tmp\", that points to a parameter, to \"tftp_option_get\", which expects a null-terminated string.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 320,
                    "column": 3,
                    "event": "cond_false",
                    "message": "Condition \"loc >= len\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 321,
                    "column": 5,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 322,
                    "column": 3,
                    "event": "var_assign_parm",
                    "message": "Assigning: \"*option\" = \"buf\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 327,
                    "column": 3,
                    "event": "cond_false",
                    "message": "Condition \"loc > len\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 328,
                    "column": 5,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/tftp.c",
                    "line": 329,
                    "column": 3,
                    "event": "string_null_sink_parm_call",
                    "message": "Passing parameter \"*option\" to \"strlen\" which expects a null-terminated string.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1156|         break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1157|       case TFTP_EVENT_OACK:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1158|->       result = tftp_parse_option_ack(state,",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1159|                                        (const char *)state->rpacket.data + 2,",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 1160|                                        state->rbytes-2);",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "NEGATIVE_RETURNS",
            "cwe": 394,
            "key_event_idx": 21,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 131,
                    "event": "cond_true",
                    "message": "Condition \"data->req.upload_chunky\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 144,
                    "event": "cond_false",
                    "message": "Condition \"nread == 268435456\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 148,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 149,
                    "event": "cond_false",
                    "message": "Condition \"nread == 268435457\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 170,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 170,
                    "event": "cond_false",
                    "message": "Condition \"(size_t)nread > buffersize\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 175,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 177,
                    "event": "cond_true",
                    "message": "Condition \"!data->req.forbidchunk\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 177,
                    "event": "cond_true",
                    "message": "Condition \"data->req.upload_chunky\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 198,
                    "event": "cond_true",
                    "message": "Condition \"data->set.prefer_ascii\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 206,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 210,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 211,
                    "event": "negative_return_fn",
                    "message": "Function \"curl_msnprintf(hexbuffer, 11UL, \"%x%s\", nread, endofline_native)\" returns a negative number.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1023,
                    "column": 3,
                    "event": "negative_return",
                    "message": "Calling \"curl_mvsnprintf\", which might return a negative value.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1007,
                    "column": 3,
                    "event": "cond_false",
                    "message": "Condition \"retcode != -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1014,
                    "column": 3,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1007,
                    "column": 3,
                    "event": "var_tested_neg",
                    "message": "Variable \"retcode\" is negative.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1015,
                    "column": 3,
                    "event": "return_negative_variable",
                    "message": "Explicitly returning negative variable \"retcode\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1023,
                    "column": 3,
                    "event": "var_assign",
                    "message": "Assigning: \"retcode\" = \"curl_mvsnprintf(buffer, maxlength, format, ap_save)\", which might be negative.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1025,
                    "column": 3,
                    "event": "return_negative_variable",
                    "message": "Explicitly returning negative variable \"retcode\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 211,
                    "event": "var_assign",
                    "message": "Assigning: signed variable \"hexlen\" = \"curl_msnprintf\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/transfer.c",
                    "line": 219,
                    "event": "negative_returns",
                    "message": "\"hexlen\" is passed to a parameter that cannot be negative. [Note: The source code implementation of the function has been overridden by a builtin model.]",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  217|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  218|       /* copy the prefix to the buffer, leaving out the NUL */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  219|->     memcpy(data->req.upload_fromhere, hexbuffer, hexlen);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  220|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  221|       /* always append ASCII CRLF to the data */",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "CLANG_WARNING",
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/url.c",
                    "line": 0,
                    "event": "internal warning",
                    "message": "child 19172 timed out after 30s",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "CLANG_WARNING",
            "language": "c/c++",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/url.c",
                    "line": 0,
                    "event": "internal warning",
                    "message": "child 31100 timed out after 30s",
                    "verbosity_level": "0"
                }
            ]
        },
        {
            "checker": "NEGATIVE_RETURNS",
            "cwe": 394,
            "key_event_idx": 35,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 541,
                    "event": "cond_true",
                    "message": "Condition \"!user\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 544,
                    "event": "cond_false",
                    "message": "Condition \"user\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 550,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 556,
                    "event": "cond_false",
                    "message": "Condition \"Curl_gethostname(host, 1025UL /* sizeof (host) */)\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 560,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 565,
                    "event": "cond_true",
                    "message": "Condition \"ntlm->target_info_len\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 571,
                    "event": "cond_false",
                    "message": "Condition \"result\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 572,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 575,
                    "event": "cond_false",
                    "message": "Condition \"result\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 576,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 580,
                    "event": "cond_false",
                    "message": "Condition \"result\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 581,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 586,
                    "event": "cond_false",
                    "message": "Condition \"result\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 587,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 592,
                    "event": "cond_false",
                    "message": "Condition \"result\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 593,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 596,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 662,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 664,
                    "event": "cond_true",
                    "message": "Condition \"unicode\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 681,
                    "event": "negative_return_fn",
                    "message": "Function \"curl_msnprintf((char *)ntlmbuf, 1024UL, \"NTLMSSP%c\\3%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\", 0, 0, 0, 0, 24, 0, 24, 0, (int)(lmrespoff & 0xff), (int)((lmrespoff >> 8) & 0xff), 0, 0, (int)(ntresplen & 0xffU), (int)((ntresplen >> 8) & 0xffU), (int)(ntresplen & 0xffU), (int)((ntresplen >> 8) & 0xffU), (int)(ntrespoff & 0xff), (int)((ntrespoff >> 8) & 0xff), 0, 0, (int)(domlen & 0xffUL), (int)((domlen >> 8) & 0xffUL), (int)(domlen & 0xffUL), (int)((domlen >> 8) & 0xffUL), (int)(domoff & 0xffUL), (int)((domoff >> 8) & 0xffUL), 0, 0, (int)(userlen & 0xffUL), (int)((userlen >> 8) & 0xffUL), (int)(userlen & 0xffUL), (int)((userlen >> 8) & 0xffUL), (int)(useroff & 0xffUL), (int)((useroff >> 8) & 0xffUL), 0, 0, (int)(hostlen & 0xffUL), (int)((hostlen >> 8) & 0xffUL), (int)(hostlen & 0xffUL), (int)((hostlen >> 8) & 0xffUL), (int)(hostoff & 0xffUL), (int)((hostoff >> 8) & 0xffUL), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (int)(ntlm->flags & 0xffU), (int)((ntlm->flags >> 8) & 0xffU), (int)((ntlm->flags >> 16) & 0xffU), (int)((ntlm->flags >> 24) & 0xffU))\" returns a negative number.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1023,
                    "column": 3,
                    "event": "negative_return",
                    "message": "Calling \"curl_mvsnprintf\", which might return a negative value.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1007,
                    "column": 3,
                    "event": "cond_false",
                    "message": "Condition \"retcode != -1\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1014,
                    "column": 3,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1007,
                    "column": 3,
                    "event": "var_tested_neg",
                    "message": "Variable \"retcode\" is negative.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1015,
                    "column": 3,
                    "event": "return_negative_variable",
                    "message": "Explicitly returning negative variable \"retcode\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1023,
                    "column": 3,
                    "event": "var_assign",
                    "message": "Assigning: \"retcode\" = \"curl_mvsnprintf(buffer, maxlength, format, ap_save)\", which might be negative.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/mprintf.c",
                    "line": 1025,
                    "column": 3,
                    "event": "return_negative_variable",
                    "message": "Explicitly returning negative variable \"retcode\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 681,
                    "event": "var_assign",
                    "message": "Assigning: unsigned variable \"size\" = \"curl_msnprintf\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 768,
                    "event": "cond_false",
                    "message": "Condition \"size < 1000UL /* 1024 - 24 */\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 771,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 779,
                    "event": "cond_false",
                    "message": "Condition \"size < 1024 - ntresplen\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 783,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 803,
                    "event": "cond_false",
                    "message": "Condition \"size + userlen + domlen + hostlen >= 1024\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 806,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 809,
                    "event": "cond_true",
                    "message": "Condition \"unicode\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 810,
                    "event": "negative_returns",
                    "message": "Using variable \"size\" as an index to array \"ntlmbuf\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  808|     DEBUGASSERT(size == domoff);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  809|     if(unicode)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  810|->     unicodecpy(&ntlmbuf[size], domain, domlen / 2);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  811|     else",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  812|       memcpy(&ntlmbuf[size], domain, domlen);",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 833,
                    "event": "assignment",
                    "message": "Assigning: \"result\" = \"((void)data) , CURLE_OK\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 835,
                    "event": "const",
                    "message": "At condition \"result\", the value of \"result\" must be equal to 0.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 835,
                    "event": "dead_error_condition",
                    "message": "The condition \"result\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vauth/ntlm.c",
                    "line": 836,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"return CURLE_CONV_FAILED;\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  834|                                      size - domoff);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  835|     if(result)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  836|->     return CURLE_CONV_FAILED;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  837|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  838|     /* Return with binary blob encoded into base64 */",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "COMPILER_WARNING",
            "language": "c/c++",
            "key_event_idx": 1,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 0,
                    "event": "scope_hint",
                    "message": "In function 'ossl_connect_step1'",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2217,
                    "column": 5,
                    "event": "warning[-Wdeprecated-declarations]",
                    "message": "'SSLv3_client_method' is deprecated",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "     req_method = SSLv3_client_method();",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "     ^~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/usr/include/openssl/opensslconf.h",
                    "line": 42,
                    "event": "included_from",
                    "message": "Included from here.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/usr/include/openssl/ct.h",
                    "line": 13,
                    "event": "included_from",
                    "message": "Included from here.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/usr/include/openssl/ssl.h",
                    "line": 61,
                    "event": "included_from",
                    "message": "Included from here.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 52,
                    "event": "included_from",
                    "message": "Included from here.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "/usr/include/openssl/ssl.h",
                    "line": 1619,
                    "column": 1,
                    "event": "note",
                    "message": "declared here",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " DEPRECATEDIN_1_1_0(__owur const SSL_METHOD *SSLv3_client_method(void)) /* SSLv3 */",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " ^~~~~~~~~~~~~~~~~~",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2215|         return CURLE_SSL_CONNECT_ERROR;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2216|   #endif",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2217|->     req_method = SSLv3_client_method();",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2218|       use_sni(FALSE);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2219|       break;",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 3,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2214,
                    "event": "cond_cannot_single",
                    "message": "Condition \"ssl_authtype == CURL_TLSAUTH_SRP\", taking false branch. Now the value of \"ssl_authtype\" cannot be equal to 1.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2309,
                    "event": "cannot_single",
                    "message": "At condition \"ssl_authtype == CURL_TLSAUTH_SRP\", the value of \"ssl_authtype\" cannot be equal to 1.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2309,
                    "event": "dead_error_condition",
                    "message": "The condition \"ssl_authtype == CURL_TLSAUTH_SRP\" cannot be true.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2310,
                    "event": "dead_error_line",
                    "message": "Execution cannot reach this statement: \"Curl_infof(data, \"Set versi...\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2308|   #ifdef USE_TLS_SRP",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2309|       if(ssl_authtype == CURL_TLSAUTH_SRP) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2310|->       infof(data, \"Set version TLSv1.x for SRP authorisation\\n\");",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2311|       }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2312|   #endif",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 9,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2181,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_DEFAULT\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2182,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2183,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1_0\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2184,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1_1\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2185,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1_2\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2186,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1_3\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2208,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_SSLv3\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2306,
                    "event": "intervals",
                    "message": "When switching on \"ssl_version\", the value of \"ssl_version\" must be in one of the following intervals: {[0,1], [3,7]}.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2339,
                    "event": "dead_error_condition",
                    "message": "The switch value \"ssl_version\" cannot be \"CURL_SSLVERSION_SSLv2\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2339,
                    "event": "dead_error_begin",
                    "message": "Execution cannot reach this statement: \"case CURL_SSLVERSION_SSLv2:\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2337|       break;",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2338|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2339|->   case CURL_SSLVERSION_SSLv2:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2340|   #ifndef OPENSSL_NO_SSL2",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2341|       ctx_options |= SSL_OP_NO_SSLv3;",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "DEADCODE",
            "cwe": 561,
            "key_event_idx": 9,
            "events": [
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2181,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_DEFAULT\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2182,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2183,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1_0\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2184,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1_1\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2185,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1_2\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2186,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_TLSv1_3\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2208,
                    "event": "equality_cond",
                    "message": "Jumping to case \"CURL_SSLVERSION_SSLv3\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2306,
                    "event": "intervals",
                    "message": "When switching on \"ssl_version\", the value of \"ssl_version\" must be in one of the following intervals: {[0,1], [3,7]}.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2306,
                    "event": "dead_error_condition",
                    "message": "The switch value \"ssl_version\" cannot reach the default case.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/lib/vtls/openssl.c",
                    "line": 2356,
                    "event": "dead_error_begin",
                    "message": "Execution cannot reach this statement: \"default:\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2354|   #endif",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2355|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2356|->   default:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2357|       failf(data, \"Unrecognized parameter passed via CURLOPT_SSLVERSION\");",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2358|       return CURLE_SSL_CONNECT_ERROR;",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "TOCTOU",
            "cwe": 367,
            "key_event_idx": 11,
            "events": [
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 113,
                    "event": "cond_false",
                    "message": "Condition \"!outdup\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 114,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 117,
                    "event": "cond_false",
                    "message": "Condition \"!dirbuildup\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 120,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 127,
                    "event": "cond_true",
                    "message": "Condition \"tempdir != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 131,
                    "event": "cond_true",
                    "message": "Condition \"tempdir2 != NULL\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 133,
                    "event": "cond_true",
                    "message": "Condition \"dlen\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 134,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 141,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 142,
                    "event": "fs_check_call",
                    "message": "Calling function \"access\" to perform check on \"dirbuildup\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 142,
                    "event": "cond_true",
                    "message": "Condition \"access(dirbuildup, 0) == -1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/src/tool_dirhie.c",
                    "line": 143,
                    "event": "toctou",
                    "message": "Calling function \"mkdir\" that uses \"dirbuildup\" after a check function. This can cause a time-of-check, time-of-use race condition.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  141|         }",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  142|         if(access(dirbuildup, F_OK) == -1) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  143|->         if(-1 == mkdir(dirbuildup, (mode_t)0000750)) {",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  144|             show_dir_errno(errors, dirbuildup);",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  145|             result = CURLE_WRITE_ERROR;",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "COPY_PASTE_ERROR",
            "cwe": 398,
            "key_event_idx": 1,
            "events": [
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/ntlm.py",
                    "line": 595,
                    "event": "original",
                    "message": "\"user.decode\" looks like the original copy.",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/ntlm.py",
                    "line": 603,
                    "event": "copy_paste_error",
                    "message": "\"user\" in \"user.decode\" looks like a copy-paste error.",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/ntlm.py",
                    "line": 603,
                    "event": "remediation",
                    "message": "Should it say \"domain\" instead?",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  601|               domain.encode('utf-16le')",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  602|           except:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  603|->             domain = user.decode(encoding)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  604|   ",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": "  605|       ntlmChallenge = NTLMAuthChallenge(type2)",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "key_event_idx": 14,
            "events": [
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3504,
                    "event": "assign_undefined",
                    "message": "Assigning: \"readAndX\" = \"undefined\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3504,
                    "event": "cond_true",
                    "message": "Condition \"!max_size\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3505,
                    "event": "cond_true",
                    "message": "Condition \"self._dialects_parameters[\"Capabilities\"] & SMB.CAP_LARGE_READX\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3505,
                    "event": "cond_true",
                    "message": "Condition \"self._SignatureEnabled === False\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3505,
                    "event": "cond_true",
                    "message": "Condition \"(self._dialects_parameters[\"Capabilities\"] & SMB.CAP_LARGE_READX) && (self._SignatureEnabled === False)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3506,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3508,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3512,
                    "event": "cond_false",
                    "message": "Condition \"smb_packet === None\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3523,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3525,
                    "event": "cond_true",
                    "message": "Condition \"wait_answer\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3527,
                    "event": "cond_true",
                    "message": "Condition \"1\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3531,
                    "event": "cond_true",
                    "message": "Condition \"ans.isValidAnswer(SMB.SMB_COM_READ_ANDX)\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3539,
                    "event": "cond_false",
                    "message": "Condition \"!ans.isMoreData()\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3540,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3542,
                    "event": "property_access",
                    "message": "Accessing a property of null-like value \"readAndX\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3540|                           return answer",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3541|                       max_size = min(max_size, readAndXParameters['Remaining'])",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3542|->                     readAndX['Parameters']['Offset'] += count                      # XXX Offset is not important (apparently)",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3543|           else:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3544|               self.sendSMB(smb)",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "IDENTICAL_BRANCHES",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3775,
                    "event": "identical_branches",
                    "message": "Ternary expression on condition \"self.__flags2 & SMB.FLAGS2_UNICODE\" has identical then and else expressions: \"\"\"\". Should one of the expressions be modified, or the entire ternary expression replaced?",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3773|               findFirstParameter['InformationLevel'] = SMB_FIND_FILE_BOTH_DIRECTORY_INFO",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3774|               findFirstParameter['SearchStorageType'] = 0",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3775|->             findFirstParameter['FileName'] = path + ('\\x00\\x00' if self.__flags2 & SMB.FLAGS2_UNICODE else '\\x00')",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3776|               self.send_trans2(tid, SMB.TRANS2_FIND_FIRST2, '\\x00', findFirstParameter, '')",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3777|               files = [ ]",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "IDENTICAL_BRANCHES",
            "key_event_idx": 0,
            "events": [
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smb.py",
                    "line": 3818,
                    "event": "identical_branches",
                    "message": "Ternary expression on condition \"self.__flags2 & SMB.FLAGS2_UNICODE\" has identical then and else expressions: \"\"\"\". Should one of the expressions be modified, or the entire ternary expression replaced?",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3816|                           findNextParameter['ResumeKey'] = 0",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3817|                           findNextParameter['Flags'] = SMB_FIND_RETURN_RESUME_KEYS | SMB_FIND_CLOSE_AT_EOS",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3818|->                         findNextParameter['FileName'] = resume_filename + ('\\x00\\x00' if self.__flags2 & SMB.FLAGS2_UNICODE else '\\x00')",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3819|                           self.send_trans2(tid, SMB.TRANS2_FIND_NEXT2, '\\x00', findNextParameter, '')",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 3820|                           findData = ''",
                    "verbosity_level": "1"
                }
            ]
        },
        {
            "checker": "FORWARD_NULL",
            "cwe": 476,
            "key_event_idx": 7,
            "events": [
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smbserver.py",
                    "line": 2066,
                    "event": "assign_undefined",
                    "message": "Assigning: \"mode\" = \"undefined\".",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smbserver.py",
                    "line": 2077,
                    "event": "cond_false",
                    "message": "Condition \"connData[\"ConnectedShares\"].has_key(recvPacket[\"Tid\"])\", taking false branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smbserver.py",
                    "line": 2085,
                    "event": "else_branch",
                    "message": "Reached else branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smbserver.py",
                    "line": 2087,
                    "event": "cond_true",
                    "message": "Condition \"errorCode == STATUS_SUCCESS\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smbserver.py",
                    "line": 2090,
                    "event": "cond_true",
                    "message": "Condition \"len(connData[\"OpenedFiles\"]) == 0\", taking true branch.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smbserver.py",
                    "line": 2091,
                    "event": "if_fallthrough",
                    "message": "Falling through to end of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smbserver.py",
                    "line": 2093,
                    "event": "if_end",
                    "message": "End of if statement.",
                    "verbosity_level": "2"
                },
                {
                    "file_name": "curl-7.60.0/tests/python_dependencies/impacket/smbserver.py",
                    "line": 2095,
                    "event": "invalid_operation",
                    "message": "Invalid operation on null-like value \"mode\".",
                    "verbosity_level": "0"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2093|                  fid = connData['OpenedFiles'].keys()[-1] + 1",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2094|               respParameters['Fid'] = fid",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2095|->             if mode & os.O_CREAT:",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2096|                   # File did not exist and was created",
                    "verbosity_level": "1"
                },
                {
                    "file_name": "",
                    "line": 0,
                    "event": "#",
                    "message": " 2097|                   respParameters['Action'] = 0x2",
                    "verbosity_level": "1"
                }
            ]
        }
    ]
}
