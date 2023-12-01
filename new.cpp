

// int WaitForFullRequest(std::string buff)
// {
//     std::string substringToFind = "\r\n\r\n";

//     size_t found = buff.find(substringToFind);

//     if (found != std::string::npos)
//     {
//         size_t index = buff.find('\n');
//         if (index == std::string::npos)
//             return (0);

//         std::string http = buff.substr(0, index - 1);
//         std::vector<std::string> vec = ft_split(http, " \n\r\t");

//         if (*vec.begin() == "GET" || *vec.begin() == "DELETE")
//             return 1;
//         else if (*vec.begin() == "POST")
//         {
//             size_t second = buff.find("Content-Length:") + 15;
//             if (second != std::string::npos)
//             {
//                 std::string Val = buff.substr(second, found - second);
//                 std::cout << "VAL: " << Val << std::endl;
//                 static int i;
//                 while (i < std::atoi(Val.c_str()))
//                     i++;
//                 if (i == std::atoi(Val.c_str()))
//                     return (i = 0, 1);
//                 else
//                     return 0;
//             }
//             else
//                 return 0;
//         }
//         else
//             return 0;
//     }
//     else
//         return 0;
// }