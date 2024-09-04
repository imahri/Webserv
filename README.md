# Webserv

## Project Description
   
**Webserv**  is an innovative project aimed at creating a web server in C++98, inspired by the functionalities of Nginx. This server is designed to efficiently handle HTTP requests while providing a flexible configuration system.

## Key Features:

### 1. Configuration File Parsing

Webserv utilizes a straightforward and intuitive configuration file format, allowing users to easily define server parameters. The configuration supports directives such as:

- listen: Specifies the IP address and port number.
- autoindex: Enables automatic directory listing.
- upload_dir: Designates the directory for file uploads.
- root: Sets the root directory for the server.
- client_body_max_size: Defines the maximum size of the client request body.

### 2. Request and Response Handling

Webserv efficiently processes HTTP requests and generates appropriate responses. It supports various HTTP methods, including:

- GET : Retrieve data from the server.
- DELETE : Remove specified resources.
- POST : Submit data to be processed.

### 3. CGI Support for Multiple Languages

Webserv includes support for Common Gateway Interface (CGI) scripting in multiple programming languages:

- PHP: Execute PHP scripts for dynamic content generation.
- Python: Run Python scripts to handle web requests.
- Ruby: Support Ruby scripts for flexibility in web development.

### 4. Multiplexing Support

The server is capable of handling multiple clients simultaneously through multiplexing. Each server instance can manage several connections, ensuring high performance and responsiveness.

## Conclusion

Webserv is an ambitious project that combines simplicity with powerful features, making it an excellent choice for developers looking to understand web server architecture. With a focus on C++98, it serves as a great learning tool for programming and network communications, while also providing robust support for dynamic content generation through CGI in PHP, Python, and Ruby.

## Setup Instructions

To set up the project locally, follow these steps:

1. **Clone the Repository**:

   ```bash
   git clone git@github.com:imahri/Webserv.git
   ```

2. **Modify Config File**:

   Update the `default.conf` file in the `Root` directory with the appropriate Directory locations and paths.

3. **Compile the Project**:

   ```bash
   make
   ```

4. **Run the Webserver**:
    ```
    ./Webserv
    ```

## Technologies Used

- **C++**
- **C**

## Contributors

- **Elmahdi Amghar**: [GitHub Profile](https://github.com/AMGHAR-ELMAHDI)
- **Mahri Imad-Eddine**: [GitHub Profile](https://github.com/imahri)
- **Yahya TAQSI**: [GitHub Profile](https://github.com/YahyaTAQSI)
