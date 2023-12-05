#include "../../../includes/Request.hpp"

int     Request::fillHeaderAndBody(std::string buffer)
{
	index = buffer.find('\n');
	if(index == buffer.npos)
		return(statusCode = 400, 1);
	http = buffer.substr(0, index - 1);

	size_t oldIndex = index + 1;

	index = buffer.find("\r\n\r\n");
	for (; oldIndex < index; oldIndex++)
		header += buffer[oldIndex];

	for (oldIndex = index + 4; oldIndex < buffer.size(); oldIndex++)
		body += buffer[oldIndex];

	std::vector<std::string> vec = ft_split(header, "\n\r");
	for (std::vector<std::string>::iterator it = vec.begin();  it != vec.end(); it++)
	{
		std::vector<std::string> vec = ft_split(*it, ':');
		HeaderData[ft_trim(vec[0], ' ')] = ft_trim(vec[1], ' ');
	}
    return (0);
}

int		Request::GetExtension()
{
	size_t dotPos = URI.find_last_of('.');
	CheckExtension = false;
    if (dotPos != std::string::npos && dotPos < URI.length() - 1)
	{
		CheckExtension = true;
		Extension = &URI[dotPos + 1];
		if(GetMimeType() == 0)
			CheckExtension = false;
	}
	return(0);
}
int		Request::checkHttp()
{
	std::string		search = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	size_t			find;

	std::vector<std::string> vec = ft_split(http, " \n\r\t");
	std::vector<std::string>::iterator it = vec.begin();

	if(vec.size() != 3)
		return(statusCode = 400, 1);
	
	it = vec.begin();
	methode = *it;
	URI = *(it + 1);
	httpVersion = *(it + 2);

	if(httpVersion != "HTTP/1.1")
		return(statusCode = 400, 1);

	if(methode != "POST" && methode != "GET" && methode != "DELETE")
		return(statusCode = 405, 1);
	else if(URI.size() == 0 ||  URI.size() > 2048)
		return(statusCode = 414, 1);

	for (size_t i = 0; i < URI.size(); i++)
		if((find = search.find(URI[i])) == search.npos)
			return(statusCode = 400, 1);

	find = URI.find('?');
	if(find != URI.npos)
	{
		if(URI[find + 1] + 1 != ' ')
			Query = URI.substr(find + 1, URI.length());
		else
			Query = URI.substr(find, URI.length());

		URI = URI.substr(0, find);
	}

	GetExtension();
	return(0);
}

int		Request::checkBody()
{
	if(body.size() > Loc.client_body_max_size)
		return(statusCode = 413, 1);
	return(0);
}

int		Request::checkHeader()
{
	std::map<std::string, std::string>::iterator it = HeaderData.begin();

	size_t find = 0;
	isChuncked = false;
	isBoundry = false;
	bool ContentLength = false;
	bool ContentType = false;
	bool transferEncoding = false;

	for (; it != HeaderData.end(); it++)
	{
		if(it->second.size() == 0)
			return(statusCode = 400, 1);

		if(it->first == "Transfer-Encoding" && it->second != "chunked")
			return(statusCode = 501, 1);

		if(it->first == "Transfer-Encoding" && it->second == "chunked")
			isChuncked = true;

		if(it->first == "Transfer-Encoding")
			transferEncoding = true;

		if(it->first == "Content-Length")
			ContentLength = true;

		if(methode == "POST" &&  it->first == "Content-Type")
		{
			ContentType = true;
			find = it->second.find("multipart/form-data; boundary=");
			if(find != it->second.npos)
				isBoundry = true;
		}

		if(it->first == "Host" && it->second.size())
			Req.Host = it->second;
		else if(it->first == "Connection" && it->second.size())
			Req.Connection = it->second;
		else if(it->first == "User-Agent" && it->second.size())
			Req.UserAgent = it->second;
		else if(it->first == "Content-Type" && it->second.size())
			Req.ContentType = it->second;
		else if(it->first == "Content-Length" && it->second.size())
			Req.ContentLength = it->second;
	}

	if(methode == "POST" && (isBoundry || isChuncked) && (ContentType == false || (ContentType == true && ContentLength == false) ))
		return(puts("qwer"), statusCode = 400, 1);

	if(transferEncoding == 0 && ContentLength == 0 && methode == "POST")
		return(puts("7485"), statusCode = 400, 1);
	return(0);
}

int		Request::getRequest(std::string buffer)
{
	if(fillHeaderAndBody(buffer))
		return(std::cout << "CAUGHT REQUEST1" << std::endl, 1);
	if(parseRequest()) 
		return(std::cout << "CAUGHT REQUEST2" << std::endl, 1);
	std::cout << "GOOD REQUEST" << std::endl;
	return(0);
}

int		Request::parseRequest()
{
	if(checkHttp())
		return(1);

	std::cout << "-----------------------HEADER-------------------" << std::endl;
	std::cout << header << std::endl;
	// std::cout << "-----------------------BODY-------------------" << std::endl;
	// std::cout << body << std::endl;
	// std::cout << "-----------------------END OF BODY-------------------" << std::endl;
	if(checkHeader())
		return(1);
	if(checkLocations())
		return(1);

	if(checkBody())
		return(1);	
	if(methode == "GET")
	{
		if(GET())
			return(1);
	}
	else if(methode == "POST")
	{
		if(POST())
			return(1);
	}
	else if(DELETE())
		return(1);

	return(0);
}

int		Request::WaitForFullRequest(char *buff)
{
	if(RequestIsDone == false)
	{
		ds += buff;
		size_t	 first = ds.find_first_of("\r\n\r\n");
		if(first != ds.npos)
		{
			size_t	 last = ds.find_last_of("\r\n\r\n");
			if(last != ds.npos)
				RequestIsDone = true;
		}
	}
	return(0);
}
