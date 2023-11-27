#include "../../includes/Webserv.hpp"

Parsing::Parsing(const Parsing& copy) : servers(copy.servers), responseTypes(copy.responseTypes) {}

Parsing& Parsing::operator=(const Parsing& copy)
{
    if (this != &copy)
	{
        this->servers = copy.servers;
		this->responseTypes = copy.responseTypes;
	}
    return *this;
}

void		Parsing::fillResponseTypes()
{
	std::string		line;
	std::ifstream	typesFile;

	typesFile.open("SRC/Buda/types.txt");
	if (!typesFile)
	{
		std::cerr << "Unable to open the file types.txt" << std::endl;
		return ;
	}

	while (std::getline(typesFile, line))
	{
		std::vector < std::string >	splitedLine = ft_split(line, " ;");
		std::vector < std::string >	values(splitedLine.begin() + 1, splitedLine.end());
		
		if (line.empty() || ft_isAllSpace(line))
			continue;
		this->responseTypes[splitedLine[0]] = values;
		splitedLine.clear();
		values.clear();
	}
	
}

