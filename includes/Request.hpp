#pragma once

#include "CGI.hpp"
#include "Webserv.hpp"

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
        LOCATION                            Loc;
        Response                            Req;
        std::map<std::string, std::string>  HeaderData;
        std::string                         header;
        std::string                         body;
    	std::string                         line;
    	std::string                         http;
    	std::string                         httpVersion;
    	std::string                         methode;
    	std::string                         URI;
    	std::string                         Query;
    	std::string                         RequestPath;
    	std::string                         ResponseHeaders;
    	std::string                         ResponseBody;
        size_t                              index;
        int                                 statusCode;
		Parsing								Server;
        int                                 locationIndex;
        bool                                IsDirectory;
        size_t                              ServerIndex;
        bool                                SendFile;
        size_t                              FileSize;
        int                                 offset;
        bool                                CheckExtension;
        std::string                         Extension;
        bool                                CgiIsDone;
        //--------------------POST VARS----------------------//
        std::string                         Boundry;
        std::string                         BoundryStart;
        std::string                         BoundryEnd;
        bool                                isBoundry;
        bool                                isChuncked;
        int                                 GetNextBoundry(std::string &base, bool check);
        std::vector <std::string>           BoundryVec;
        int                                 GetReverseMimeType();
        //--------------------DELETE VARS--------------------//
        int                                 DeleteDir();
        int                                 DeleteFile();
        int                                 CheckDirectoryFiles(std::string& directory, std::vector<std::string>& filesToDelete);
        //--------------------FIDDLER'S----------------------//
        bool                                KeepAlive;
        bool                                RequestIsDone;
        //---------------------------------------------------//
        
        Request();
        Request(const Request &obj);
        Request &operator=(const Request &other);
        ~Request();
        
        int                                 getRequest(std::string &buffer);
        int                                 fillHeaderAndBody(std::string &buffer);
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
        int                                 GetRessource();
        int                                 PostFile();
        int                                 PostDir();
        int                                 GetCorrectLocation();
        int                                 GenerateResponse();
        int                                 GetMimeType();
        int                                 FillFromHtmlFile();
        int                                 FillResponseBodyFromFile();
        std::string                         InitRequest(std::string &str, Parsing &ps);
        void                                Reset();
        void                                FillCgi();
        int                                 GenerateRedirection();
        int                                 parseBoundry();
        int                                 GetExtension();
        int                                 FillFromErrorFile();
        int                                 GetFileLength(std::string &fileName);
        int                                 parseBody();
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
        int                                 readFile(std::string &fileName, std::string &Tostore);
        size_t                              CovertHexaToDecimal(const std::string &hexString);
        std::vector<std::string>            Divide(const std::string& input, const std::string& delimiter);
        std::string                         intToString(int number);
        std::string                         GetStatusCode(int index);
        size_t                              GetFileSize(std::string &fileName);

    