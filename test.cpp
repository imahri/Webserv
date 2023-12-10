            else if (net[j].revents & POLLOUT)
            {
                if (!re.request_msg[net[j].fd].send_file)
                {
                    // std::cout << "--------  SMALL  -------" << std::endl;

                    send(net[j].fd, re.request_msg[net[j].fd].c_response.c_str(), std::min((size_t)50000, re.request_msg[net[j].fd].c_response.length()), 0);
                    re.request_msg[net[j].fd].c_response = re.request_msg[net[j].fd].c_response.substr(re.request_msg[net[j].fd].c_response.length() < 50000 ? re.request_msg[net[j].fd].c_response.length() : 50000);
                    if (re.request_msg[net[j].fd].c_response.size() == 0)
                    {
                        net[j].events = POLLIN;
                        if (!re.request_msg[net[j].fd].keepAlive)
                            close(net[j].fd);
                        clearClinet(net[j].fd, re.request_msg);
                    }
                }
                else
                {
                    // std::cout << "--------  BIG  -------" << std::endl;

                    std::ifstream inputFile(re.request_msg[net[j].fd].path.c_str(), std::ios::binary);
                    re.request_msg[net[j].fd].initialPosition = inputFile.tellg();
                    if (!re.request_msg[net[j].fd].header)
                    {
                        send(net[j].fd, re.request_msg[net[j].fd].c_response.c_str(), re.request_msg[net[j].fd].c_response.length(), 0);
                        re.request_msg[net[j].fd].header = true;
                    }

                    const int bufferSize = 50000;
                    char fileBuffer[bufferSize];
                    while (true)
                    {
                        inputFile.read(fileBuffer, bufferSize);
                        int bytesRead = inputFile.gcount();
                        if (bytesRead > 0)
                        {
                            send(net[j].fd, fileBuffer, bytesRead, 0);
                        }
                        if (bytesRead < bufferSize)
                        {
                            break;
                        }
                    }

                    inputFile.close();

                    // Clear the response and update the events
                    re.request_msg[net[j].fd].c_response.clear();
                    net[j].events = POLLIN;
                    if (!re.request_msg[net[j].fd].keepAlive)
                        close(net[j].fd);
                    clearClinet(net[j].fd, re.request_msg);
                }
            }

                                std::ifstream inputFile(re.request_msg[net[j].fd].path.c_str(), std::ios::binary);
                                re.request_msg[net[j].fd].initialPosition = inputFile.tellg();
                                if (!re.request_msg[net[j].fd].header)
                                {
                                    send(net[j].fd, re.request_msg[net[j].fd].c_response.c_str(), re.request_msg[net[j].fd].c_response.length(), 0);
                                    re.request_msg[net[j].fd].header = true;
                                }
                                
                                char resp[4096];
                                inputFile.read(resp, 4096);
                                re.request_msg[net[j].fd].bytesRead = inputFile.gcount();
                                if (re.request_msg[net[j].fd].bytesRead == 0)
                                {
                                    inputFile.close();
                                    if (!re.request_msg[net[j].fd].keepAlive)
                                        close(net[j].fd);
                                    net[j].events = POLLIN;
                                    clearClinet(net[j].fd, re.request_msg);
                                }
                                else
                                {
                                    send(net[j].fd, resp, re.request_msg[net[j].fd].bytesRead, 0);
                                    re.request_msg[net[j].fd].currentPosition = inputFile.tellg();
                                }
                            }
                            continue;
                        }
        }