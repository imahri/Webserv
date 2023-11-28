#ifndef CGI_HPP
#define CGI_HPP

#include <map>
#include <iostream>

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
        return(*this);
    };

    ~CGI(){};
};
#endif 
