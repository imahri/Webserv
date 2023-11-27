
/*
Can be Obtained from Request Headers:

	*>REQUEST_METHOD
	*>CONTENT_LENGTH
	*>CONTENT_TYPE

	>HTTP_COOKIE
	>HTTP_ACCEPT
	>HTTP_ACCEPT_LANGUAGE
	>HTTP_REFERER
	>HTTP_USER_AGENT
	>HTTP_ACCEPT_ENCODING
	>HTTP_ACCEPT_CHARSET


Set by the Web Server or CGI Handler:

	*>PATH_INFO
	*>SCRIPT_FILENAME
	*>QUERY_STRING

	>REDIRECT_STATUS
	>REQUEST_URI
	>PATH_TRANSLATED
	>GATEWAY_INTERFACE
	>SERVER_SOFTWARE
	>REMOTE_HOST
	>SERVER_NAME
	>SERVER_PROTOCOL
	>AUTH_TYPE
	>DOCUMENT_ROOT
	>UPLOAD_PATH
	>SERVER_PORT
*/


/*
	//header
		POST /example/path?param1=value1&param2=value2 HTTP/1.1
		Host: example.com
		Cookie: user_session=abc123; preferences=dark-mode
		Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,**;q=0.8
		Accept-Language: en-US,en;q=0.9
		Referer: https://referrer.com/page
		User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36
		Accept-Encoding: gzip, deflate, br
		Accept-Charset: utf-8, iso-8859-1;q=0.5
		Content-Type: application/json
		Content-Length: 56

	//body
		{"key1": "value1", "key2": "value2", "key3": "value3"}
*/

// ["SERVER_PORT"]					== req port +						=>	80
// ["SERVER_NAME"]					== "OreO"							=>	OreO
// ["REQUEST_METHOD"]				== req mathod+						=>	POST
// ["QUERY_STRING"]					== req query+						=>	param1=value1&param2=value2
// ["SERVER_PROTOCOL"]				== ?+								=>	HTTP/1.1
// ["PATH_INFO"]					== 1 line in the header				=>	example/path
// ["REQUEST_URI"]					== 1 line in the header+			=>	/example/path?param1=value1&param2=value2
// ["SCRIPT_FILENAME"]				== script file						=>	/SRC/BUDA/CGI_BIN/php-cgi
// ["CONTENT_LENGTH"]				== req body len+					=>	56
// ["CONTENT_TYPE"]					== req type+						=>	application/json
// ["REDIRECT_STATUS"]				== 200+								=>	200
// ["HTTP_COOKIE"]					== header Cookies					=>	user_session=abc123; preferences=dark-mode
// ["GATEWAY_INTERFACE"]			== "CGI/1.1"						=>	CGI/1.1
// ["PATH_TRANSLATED"] 				== ?								=>	/var/www/html/path/to/resource
// ["HTTP_ACCEPT"]					== header Accept					=>	text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,**;q=0.8
// ["UPLOAD_PATH"]					== upload dir form the config +		=>	/var/www/uploads
// ["HTTP_ACCEPT_LANGUAGE"]			== header Accept-Language			=>	en-US,en;q=0.9
// ["HTTP_REFERER"]					== Referer							=>	https://referrer.com/page
// ["AUTH_TYPE"]					== "Basic" +						=>	Basic
// ["SERVER_SOFTWARE"]				== "webserv/test/1.0"				=>	webserv/test/1.0
// ["REMOTE_HOST"]					== 127.0.0.1						=>	127.0.0.1
// ["HTTP_USER_AGENT"]				== req User-Agent +					=>	Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36


// ["HTTP_ACCEPT_ENCODING"]			== req Accept-Encoding				=>	gzip, deflate, br
// ["DOCUMENT_ROOT"]				== ?								=>	/var/www/html

/* req example

------------------------------------------------------------
// POST /cgi-bin/your_cgi_script HTTP/1.1
// Host: yourdomain.com
// Content-Type: application/json
// Content-Length: 42

// {"key": "value", "another_key": "another_value"}
------------------------------------------------------------

*/


// fill env

// // fill args
// 	// char[3] =
// 		/bin/php,				// jibo mn xi blasa
// 		/www/site/index.php,    // ktb dyalek
// 		null
// 	}
// 	exeve(bin_path, char[3], env_li3mrna);
// 	 // keep pid for polllout


// #include <fcntl.h>
// #include <unistd.h>
// #include <cstdlib>
// #include <sys/wait.h>
// #include <sstream>
// #include <cstring>
// #include <cstdio>
// void test()
// {
// 	// FILE *fIn = tmpfile();
// }


