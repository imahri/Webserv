#pragma once

#include "CGI.hpp"
#include "Webserv.hpp"

#define MEGA 1000000
typedef struct L
{
        bool                                                    autoindex;
        bool                                                    CheckIndex;
        bool                                                    CheckCGI;
        bool                                                    CheckRedirect;
        bool                                                    CheckMethods;
        bool                                                    CheckUploadDir;
        
        std::string                                             upload_dir;
        std::string                                             root;
        std::vector <std::string>                               index;
        std::vector <std::string>                               methodes;
        size_t                                                  client_body_max_size;
        std::vector < std::pair <std::string , std::string > >  cgi;
        std::vector < std::pair <std::string , std::string > >  redirect;
        
}  LOCATION;

typedef struct R
{
    std::string     Host;
    std::string     Connection;
    std::string     UserAgent;
    std::string     ContentType;
    std::string     MimeType;
    std::string     ContentLength;
}  Response;



class Request
{
    public:
        CGI                                 cgi;
        std::map<std::string, std::string>  HeaderData;
        std::string                         header;
        std::string                         body;
    	std::string                         line;
    	std::string                         http;
    	std::string                         httpVersion;
    	std::string                         methode;
    	std::string                         URI;
    	std::string                         RequestPath;
    	std::string                         ResponseHeaders;
    	std::string                         ResponseBody;
        size_t                              index;
        int                                 statusCode;
		Parsing								Server;
        int                                 locationIndex;
        bool                                IsDirectory;
        std::string                         File;
        std::string                         UploadDir;
        size_t                              ServerIndex;
        LOCATION                            Loc;
        Response                            Req;
        bool                                SendFile;
        std::streampos                      FileSize;
        std::string                         PathToSaveFile;
        int                                 offset;
        bool                                ClientIsDone;
        std::string                         ds;
        bool                                RequestIsDone;
        
        Request();
        Request(const Request &obj);
        Request &operator=(const Request &other);
        ~Request();
        
        int                                 createServer(Parsing &parsing);
        int                                 getRequest(std::string buffer);
        int                                 fillHeaderAndBody(std::string buffer);
        int                                 parseRequest();
        int                                 checkHttp();
        int                                 checkBody();
        int                                 checkHeader();
        int                                 GET();
        int                                 POST();
        int                                 DELETE();
        int                                 checkLocations();
        int                                 GetFile();
        int                                 GetDirectory();
        int                                 parseChuncked();
        int                                 Upload();
        int                                 CheckRessource();
        int                                 GetRessource();
        int                                 PostFile();
        int                                 PostDir();
        int                                 GetCorrectLocation();
        int                                 GenerateResponse();
        int                                 GetMimeType();
        int                                 FillFromHtmlFile();
        int                                 FillResponseBodyFromFile();
        int                                 WaitForFullRequest(char *buff);
        int                                 InitRequest(std::string str, int j, int index, Parsing &ps);
        int                                 FillResponseBody();
        void                                Reset();
        void                                FillCgi();



};

        //extra functions
        int                                 checkNumbers(std::string str);
        int                                 checkDigit(std::string str);
        size_t                              convertToCharacters(std::string sizeString);
        std::string                         getNextToken(std::istringstream &iss);
        int                                 checkWhiteSpace(std::string str);
        std::vector<std::string>            ft_split(std::string &s, std::string delimiter);
        std::vector<std::string>            ft_split(std::string& s, char c);
        std::vector<std::string>            ft_split(std::string& s);
        std::string                         &ft_trim(std::string& s, char c);
        std::string                         ft_trim(std::string s, std::string delimiter);
