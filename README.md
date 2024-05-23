# Ste's Basic C++ Logger

This is a simple logger written in C++20. It logs messages with colored output based on the log level. It also writes log messages to a file.

## Features

- **Colored output**: The logger colors the output based on the log level. This makes it easy to distinguish between different types of log messages.
- **File logging**: In addition to printing log messages to the console, the logger also writes them to a file. This is useful for keeping a record of log messages.
- **Log levels**: The logger supports multiple log levels, including TRACE, INFO, WARN, ERROR, FATAL, and DEBUG. This allows you to control the verbosity of the logging.
- **Function, file, and line logging**: The logger includes the function name, file name, and line number in the log message. This makes it easier to trace where a log message came from.
- **std::format**: You can pass a formatted string to the logger.

## Usage

Include the `logger.h` header file in your source code:

```cpp
#include "logger.h"
```

You can then use the TRACE, INFO, WARN, ERROR, FATAL, and DEBUG macros to log messages:
```cpp
LTRACE("This is a trace message");
LINFO("This is an info message");
LWARN("This is a warning message");
LERROR("This is an error message");
LFATAL("This is a fatal message");
LDEBUG("This is a debug message");
```
If you want to use the ```std::format``` function

```cpp
LTRACE("Message {}", message);
LINFO("Message {}", message);
LWARN("Message {}", message);
LERROR("Message {}", message);
LFATAL("Message {}", message);
LDEBUG("Message {}", message);
```

The log level ```LFATAL``` ends the program.

Each log message will include the function name, file name, and line number.

Example console output

```19:23:45 | [TRACE]: Function: main, File: /home/main.cpp, Line: 11, Message: Socket created with code 4```

## Requirements
This logger requires a compiler that supports C++20, due to its use of the std::format function.

## License
This project is licensed under the MIT License.
