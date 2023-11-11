/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:34:00 by imahri            #+#    #+#             */
/*   Updated: 2023/11/01 10:11:36 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

int    Reception_processing(int index)
{
    switch (index) {
        case 100:
            std::cout << BIYellow << "Continue" << Color_Off << std::endl;
            std::cout << BIYellow << "This means there is no problem with the request, so you can send the next request. Can be ignored if completed" << Color_Off << std::endl;
            break;
        case 101:            
            std::cout << BIYellow << "Switching Protocol" << Color_Off << std::endl;
            std::cout << BIYellow << "This means changing the protocol on the server." << Color_Off << std::endl;
            break;
        case 102:
            std::cout << BIYellow << "Processing" << Color_Off << std::endl;
            std::cout << BIYellow << "This means that the request is being received and processed, but a proper response cannot be provided." << Color_Off << std::endl;
            break;
        case 103:
            std::cout << BIYellow << "Early Hints" << Color_Off << std::endl;
            std::cout << BIYellow << "Allows the user agent to start preloading while the server is preparing the response." << Color_Off << std::endl;
            break;
        default:
            return 1;
    }
    return 0;
}

int    success(int index)
{
    switch (index) {
        case 200:
            std::cout << BGreen << "OK" << Color_Off << std::endl;
            std::cout << BGreen << "Request completed successfully" << Color_Off << std::endl;
            break;
        case 201:
            std::cout << BGreen << "Created" << Color_Off << std::endl;
            std::cout << BPurple << "Create a new resource" << Color_Off << std::endl;
            break;
        case 202:
            std::cout << BGreen << "Accepted" << Color_Off << std::endl;
            std::cout << BGreen << "Unable to act in response to request" << Color_Off << std::endl;
            break;
        case 203:
            std::cout << BGreen << "Non-Authoritative Information" << Color_Off << std::endl;
            std::cout << BGreen << "Third party copies collected" << Color_Off << std::endl;
            break;
        case 204:
            std::cout << BGreen << "No Content" << Color_Off << std::endl;
            std::cout << BGreen << "No page conversion" << Color_Off << std::endl;
            break;
        case 205:
            std::cout << BGreen << "Reset Content" << Color_Off << std::endl;
            std::cout << BGreen << "Reset document view" << Color_Off << std::endl;
            break;
        default:
            return 1;
    }
    return 0;
}

int redirection(int index)
{
    switch (index) {
        case 300:
            std::cout << BPurple << "Multiple Choice" << Color_Off << std::endl;
            std::cout << BPurple << "Allows more than one response to a request." << Color_Off << std::endl;
            break;
        case 301:
            std::cout << BPurple << "Moved Permanently" << Color_Off << std::endl;
            std::cout << BPurple << "Permanently change URL." << Color_Off << std::endl;
            break;
        case 302:
            std::cout << BPurple << "Found" << Color_Off << std::endl;
            std::cout << BPurple << "Temporary URL change." << Color_Off << std::endl;
            break;
        case 303:
            std::cout << BPurple << "See Other" << Color_Off << std::endl;
            std::cout << BPurple << "The requested resource must be GETted from another URI." << Color_Off << std::endl;
            break;
        case 304:
            std::cout << BPurple << "Not Modified" << Color_Off << std::endl;
            std::cout << BPurple << "Response was not modified." << Color_Off << std::endl;
            break;
        default:
            return 1;
    }
    return 0;
}

int server_error(int index)
{
    switch (index) {
        case 500:
            std::cout << BRed << "Internal Server Error" << Color_Off << std::endl;
            std::cout << BRed << "Not sure how to handle it." << Color_Off << std::endl;
            break;
        case 501:
            std::cout << BRed << "Not Implemented" << Color_Off << std::endl;
            std::cout << BRed << "Not supported by server." << Color_Off << std::endl;
            break;
        case 502:
            std::cout << BRed << "Bad Gateway" << Color_Off << std::endl;
            std::cout << BRed << "Bad response received." << Color_Off << std::endl;
            break;
        case 503:
            std::cout << BRed << "Service Unavailable" << Color_Off << std::endl;
            std::cout << BRed << "Not ready to process request." << Color_Off << std::endl;
            break;
        case 504:
            std::cout << BRed << "Gateway Timeout" << Color_Off << std::endl;
            std::cout << BRed << "Unable to receive timely response." << Color_Off << std::endl;
            break;
        case 505:
            std::cout << BRed << "HTTP Version Not Supported" << Color_Off << std::endl;
            std::cout << BRed << "HTTP version not supported." << Color_Off << std::endl;
            break;
        case 508:
            std::cout << BRed << "Loop Detected" << Color_Off << std::endl;
            std::cout << BRed << "Server infinite loop." << Color_Off << std::endl;
            break;
        case 510:
            std::cout << BRed << "Not Extended" << Color_Off << std::endl;
            std::cout << BRed << "Additional server expansion required." << Color_Off << std::endl;
            break;
        case 511:
            std::cout << BRed << "Network Authentication Required" << Color_Off << std::endl;
            std::cout << BRed << "Client's network authentication required." << Color_Off << std::endl;
            break;
        default:
            return 1;       
    }
    return 0;
}


int client_error(int index)
{
    switch (index) {
        case 400:
            std::cout << BRed << "Bad Request" << Color_Off << std::endl;
            std::cout << BRed << "Bad response." << Color_Off << std::endl;
            break;
        case 401:
            std::cout << BRed << "Unauthorized" << Color_Off << std::endl;
            std::cout << BRed << "Unauthorized (client unknown)." << Color_Off << std::endl;
            break;
        case 403:
            std::cout << BRed << "Forbidden" << Color_Off << std::endl;
            std::cout << BRed << "No access rights (client knows)." << Color_Off << std::endl;
            break;
        case 404:
            std::cout << BRed << "Not Found" << Color_Off << std::endl;
            std::cout << BRed << "Resource not found." << Color_Off << std::endl;
            break;
        case 405:
            std::cout << BRed << "Method Not Allowed" << Color_Off << std::endl;
            std::cout << BRed << "Method not allowed." << Color_Off << std::endl;
            break;
        case 406:
            std::cout << BRed << "Not Acceptable" << Color_Off << std::endl;
            std::cout << BRed << "Content not found." << Color_Off << std::endl;
            break;
        case 407:
            std::cout << BRed << "Proxy Authentication Required" << Color_Off << std::endl;
            std::cout << BRed << "Proxy authentication required." << Color_Off << std::endl;
            break;
        case 409:
            std::cout << BRed << "Conflict" << Color_Off << std::endl;
            std::cout << BRed << "Server state conflict." << Color_Off << std::endl;
            break;
        case 410:
            std::cout << BRed << "Gone" << Color_Off << std::endl;
            std::cout << BRed << "Content permanently deleted." << Color_Off << std::endl;
            break;
        case 411:
            std::cout << BRed << "Length Required" << Color_Off << std::endl;
            std::cout << BRed << "Undefined request." << Color_Off << std::endl;
            break;
        case 412:
            std::cout << BRed << "Precondition Failed" << Color_Off << std::endl;
            std::cout << BRed << "Invalid precondition." << Color_Off << std::endl;
            break;
        case 413:
            std::cout << BRed << "Payload Too Large" << Color_Off << std::endl;
            std::cout << BRed << "The entity is larger than the limit defined by the server." << Color_Off << std::endl;
            break;
        case 414:
            std::cout << BRed << "URI Too Long" << Color_Off << std::endl;
            std::cout << BRed << "URI is too long." << Color_Off << std::endl;
            break;
        case 415:
            std::cout << BRed << "Unsupported Media Type" << Color_Off << std::endl;
            std::cout << BRed << "Unsupported media format." << Color_Off << std::endl;
            break;
        case 416:
            std::cout << BRed << "Requested Range Not Satisfiable" << Color_Off << std::endl;
            std::cout << BRed << "The specified range requested in the Range header field cannot be satisfied." << Color_Off << std::endl;
            break;
        case 418:
            std::cout << BRed << "I'm a teapot" << Color_Off << std::endl;
            std::cout << BRed << "Refuse to brew coffee in a teapot." << Color_Off << std::endl;
            break;
        case 422:
            std::cout << BRed << "Unprocessable Entity" << Color_Off << std::endl;
            std::cout << BRed << "Grammar error." << Color_Off << std::endl;
            break;
        case 429:
            std::cout << BRed << "Too Many Requests" << Color_Off << std::endl;
            break;
        case 431:
            std::cout << BRed << "Request Header Fields Too Large" << Color_Off << std::endl;
            break;
        case 451:
            std::cout << BRed << "Unavailable For Legal Reasons" << Color_Off << std::endl;
            std::cout << BRed << "Illegal Resources." << Color_Off << std::endl;
            break;
        default:
            return 1;       
    }
    return 0;
}

void    get_type(int index)
{
    if (Reception_processing(index) == 0)
        return;
    else if (success(index) == 0)
        return;
    else if (redirection(index) == 0)
        return;
    else if (server_error(index) == 0)
        return;
    else if (client_error(index) == 0)
        return;
    else
        std::cout << "There is no message concerning the status code" << std::endl;
    return;
}