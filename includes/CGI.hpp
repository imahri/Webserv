#ifndef CGI_HPP
#define CGI_HPP

#include <map>
#include <vector>
#include <iostream>
#include <sys/time.h>

#include <fstream>
#include <sstream>
typedef struct L
{
        bool                                                    autoindex;
        bool                                                    CheckIndex;
        bool                                                    CheckCGI;
        bool                                                    CheckRedirect;
        bool                                                    CheckMethods;
        bool                                                    CheckUploadDir;
        bool                                                    CheckErrorPage;
        
        std::string                                             upload_dir;
        std::string                                             root;
        std::string                                             index;
        std::vector <std::string>                               methodes;
        size_t                                                  client_body_max_size;
        std::vector < std::pair <std::string , std::string > >  cgi;
        std::vector < std::pair <std::string , std::string > >  redirect;
        std::vector < std::pair < std::string, std::string > >  error_page;
        
}  LOCATION;

struct Rawr
{
    std::string                                             code;
    std::string                                             header;
    std::string                                             body;
    std::vector < std::pair <std::string , std::string > >  mapap;
};


class CGI
{
    public:
        std::map<std::string, std::string>  HeaderData;
        std::string                         header;
        std::string                         body;
    	std::string                         httpVersion;
    	std::string                         methode;
    	std::string                         URI;
    	std::string                         RequestPath;
        int                                 CodeStatus;
    	std::string                         Query;
        std::string                         root;
        LOCATION                            locationData;
        Rawr                                ret;

        //---------------------------
        std::string inFileName;
        std::ofstream inFile;

        std::string outFileName;
        std::ifstream outFile;
        int        callCGI(LOCATION& l, std::string& reqPath);

    CGI(){};

    CGI(const CGI &obj)
    {
        *this = obj;
    };

    CGI &operator=(const CGI &obj)
    {
        this->HeaderData = obj.HeaderData;
        this->header = obj.header;
        this->body = obj.body;
        this->httpVersion = obj.httpVersion;
        this->methode = obj.methode;
        this->URI = obj.URI;
        this->RequestPath = obj.RequestPath;
        this->CodeStatus = obj.CodeStatus;
        this->Query = obj.Query;

        this->locationData.autoindex = obj.locationData.autoindex;
        this->locationData.CheckIndex = obj.locationData.CheckIndex;
        this->locationData.CheckCGI = obj.locationData.CheckCGI;
        this->locationData.CheckRedirect = obj.locationData.CheckRedirect;
        this->locationData.CheckMethods = obj.locationData.CheckMethods;
        this->locationData.CheckUploadDir = obj.locationData.CheckUploadDir;
        this->locationData.upload_dir = obj.locationData.upload_dir;
        this->locationData.root = obj.locationData.root;
        this->locationData.index = obj.locationData.index;
        this->locationData.methodes = obj.locationData.methodes;
        this->locationData.client_body_max_size = obj.locationData.client_body_max_size;
        this->locationData.cgi = obj.locationData.cgi;
        this->locationData.redirect = obj.locationData.redirect;

        this->ret.code = obj.ret.code;
        this->ret.header = obj.ret.header;
        this->ret.body = obj.ret.body;
        this->ret.mapap = obj.ret.mapap;
        
        return(*this);
    };

    ~CGI(){};
};
#endif 
