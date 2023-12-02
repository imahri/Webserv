int Request::GetNextBoundary(const std::string& base) {
    Chunk.clear();
    findFirst = 0;
    findLast = 0;

    findFirst = base.find(BoundryStart);
    if (findFirst == std::string::npos)
        return 1;

    findLast = base.find(BoundryStart, findFirst + BoundryStart.length());
    if (findLast == std::string::npos) {
        findLast = base.find(BoundryEnd);
        if (findLast == std::string::npos)
            return 1;
        Chunk = base.substr(BoundryStart.length(), findLast - BoundryStart.length());
        return 0;
    }

    Chunk = base.substr(BoundryStart.length(), findLast - BoundryStart.length());
    return 0;
}

int Request::parseBoundary() {
    std::cout << "-----------------------HEADER BOUNDARY-------------------" << std::endl;
    std::cout << header << std::endl;
    std::cout << "-----------------------BODY-------------------" << std::endl;
    std::cout << body << std::endl;
    std::cout << "-----------------------END OF BODY-------------------" << std::endl;

    DoneWithBoundary = false;
    size_t find = Req.ContentType.find("boundary=");
    if (find == std::string::npos)
        return 1;

    Boundry = Req.ContentType.substr(find + 9);
    if (Boundry.empty())
        return 1;
    BoundryStart = "--" + Boundry;
    BoundryEnd = BoundryStart + "--";

    findFirst = 0;
    findLast = 0;

    std::cout << "Boundry: " << Boundry << std::endl;
    std::cout << "BoundryStart: " << BoundryStart << std::endl;
    std::cout << "BoundryEnd: " << BoundryEnd << std::endl;

    std::string FakeBody = body;
    std::cout << "-----------------------START OF CHUNKS-------------------" << std::endl;

    while (!DoneWithBoundary) {
        FakeBody.erase(findFirst, findLast);
        if (GetNextBoundary(FakeBody))
            return 1;

        std::cout << Chunk << std::endl;
        std::cout << "-----------------------MIDDLE OF CHUNKS-------------------" << std::endl;
    }

    std::cout << "-----------------------END OF CHUNKS-------------------" << std::endl;
    return 0;
}

//-----------------------------------------------------




// int		Request::GetNextBoundry(std::string base)
// {
// 	Chunk.clear();
// 	findFirst = 0;
// 	findLast = 0;

// 	findFirst = base.find(BoundryStart);
// 	if(findFirst == base.npos)
// 		return(DoneWithBoundry = true, 0);
// 	else
// 	{
// 		findLast = base.find(BoundryStart, BoundryStart.length());
// 		if(findLast == base.npos)
// 		{
// 			findLast = base.find(BoundryEnd);
// 			if(findLast == base.npos)
// 				return(DoneWithBoundry = true, 1);
// 			else
// 				return(Chunk = base.substr(BoundryStart.length(), base.length() - BoundryEnd.length() + 1), 0);
// 		}
// 		else
// 			return(Chunk = base.substr(BoundryStart.length(), base.length() - BoundryStart.length() + 1), 0);
// 	}
// }

// int		Request::parseBoundry()
// {
// 	std::cout << "-----------------------HEADER BOUNDRY-------------------" << std::endl;
// 	std::cout << header << std::endl;
// 	// std::cout << "-----------------------BODY-------------------" << std::endl;
// 	std::cout << body << std::endl;
// 	std::cout << "-----------------------END OF BODY-------------------" << std::endl;

// 	DoneWithBoundry = false;
// 	size_t find = Req.ContentType.find("boundary=");
// 	if(find == Req.ContentType.npos)
// 		return(1);

// 	Boundry = Req.ContentType.substr(find + 9, Req.ContentType.length());
// 	if(Boundry.length() == 0)
// 		return(1);
// 	BoundryStart = "--" +  Boundry;
// 	BoundryEnd = BoundryStart + "--";

// 	findFirst = 0;
// 	findLast = 0;

// 	std::cout << "bfq:" << Boundry << std::endl;
// 	std::cout << "bfS:" << BoundryStart << std::endl;
// 	std::cout << "bfE:" << BoundryEnd << std::endl;
// 	std::string FakeBody = body;
// 	std::cout << "-----------------------START OF CHUNKS-------------------" << std::endl;
// 	while (DoneWithBoundry == false)
// 	{
// 		FakeBody.erase(findFirst, findLast);
// 		if(GetNextBoundry(FakeBody))
// 			return(1);

// 		std::cout << Chunk << std::endl;
// 		std::cout << "-----------------------MIDDLE OF CHUNKS-------------------" << std::endl;
// 	}
// 	std::cout << "-----------------------END OF CHUNKS-------------------" << std::endl;
// 	return(0);
// }
