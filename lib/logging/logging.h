/**
 * @file logging.h
 * @brief Provides macros and functions for logging at various levels.
 * 
 * This header defines six levels of logging, each with increasing verbosity:
 * 
 * - **FATAL**: The application is going to terminate.
 * - **ERROR**: Logs error information.
 * - **WARNING**: Logs warnings about inappropriate usage of code.
 * - **INFO**: Logs general status information about the application.
 * - **DEBUG**: Logs detailed debug information specific to the application.
 * - **VERBOSE**: Logs verbose information for additional debugging insights.
 * 
 * The logging level is controlled by the `LOG_LEVEL` macro, with a default level of **VERBOSE**.
 * 
 * **Usage:**
 * - Set the desired logging level by defining `LOG_LEVEL`.
 * - Start the serial transmission using `log_init` to enable logging.
 * 
 * Example:
 * ```
 * #define LOG_LEVEL DEBUG
 * log_init(9600);
 * log_info("System initialized.");
 * log_error("An error occurred.");
 * ```
 */
#ifndef LOGGING_H
#define LOGGING_H
#include <WString.h>
#include "macros.h"
 
#define FATAL 1
#define ERROR 2
#define WARNING 3
#define INFO 4
#define DEBUG 5
#define VERBOSE 6

#ifndef LOG_LEVEL
#define LOG_LEVEL VERBOSE
#endif

/**
 * @brief Initializes the serial communication for logging with enabled format specifiers.
 * 
 * This function initializes the serial communication for logging at the specified baudrate.
 * 
 * @param baudrate The baudrate for serial communication.
 */
void log_init(uint32_t baudrate);


#define _LOG_AT_LEVEL(level, fmt, ...)                                     \
     do {                                                                  \
          Serial.print(F("[" level "] "));                                 \
          if (_VA_HAS_ARGS(__VA_ARGS__)) {                                 \
               printf_P(PSTR(fmt), ##__VA_ARGS__);                         \
          } else {                                                         \
               Serial.println(F(fmt));                                     \
          }                                                                \
     } while (0)

#define _LOG_CRITICAL_AT_LEVEL(level, fmt, ...)                            \
     do {                                                                  \
          printf_P(PSTR("%s %d: "), __FILE__, __LINE__);                   \
          Serial.print(F("[" level "] "));                                 \
          if (_VA_HAS_ARGS(__VA_ARGS__)) {                                 \
               printf_P(PSTR(fmt), ##__VA_ARGS__);                         \
          } else {                                                         \
               Serial.println(F(fmt));                                     \
          }                                                                \
     } while (0)

#if LOG_LEVEL >= FATAL
/**
 * @brief Logs a critical fatal error message.
 * 
 * This macro logs a message at the "FATAL" level. It only triggers
 * if the `LOG_LEVEL` is set to allow fatal-level logging.
 * 
 * @param __VA_ARGS__ The message to log, with optional format specifiers.
 * @note It is encouraged to call the `halt` macro explicitly after calling this macro,
 * to halt the program after logging the fatal message, but it is not enforced.
 */
#define log_fatal(...) _LOG_CRITICAL_AT_LEVEL("FATAL", __VA_ARGS__)
#else 
#define log_fatal(...)
#endif

#if LOG_LEVEL >= ERROR
/**
 * @brief Logs an error message.
 * 
 * This macro logs a message at the "ERROR" level if the `LOG_LEVEL`
 * configuration permits it.
 * 
 * @param __VA_ARGS__ The message to log, with optional format specifiers.
 */
#define log_error(...) _LOG_CRITICAL_AT_LEVEL("ERROR", __VA_ARGS__)
#else 
#define log_error(...)
#endif

#if LOG_LEVEL >= WARNING
/**
 * @brief Logs a warning message.
 * 
 * This macro logs a message at the "WARNING" level if allowed by the `LOG_LEVEL`.
 * 
 * @param __VA_ARGS__ The message to log, with optional format specifiers.
 */
#define log_warning(...) _LOG_CRITICAL_AT_LEVEL("WARNING", __VA_ARGS__)
#else
#define log_warning(...)
#endif

#if LOG_LEVEL >= INFO
/**
 * @brief Logs an informational message.
 * 
 * Logs a message at the "INFO" level if the `LOG_LEVEL` allows it.
 * 
 * @param __VA_ARGS__ The message to log, with optional format specifiers.
 */
#define log_info(...) _LOG_AT_LEVEL("INFO", __VA_ARGS__)
#else
#define log_info(...)
#endif

#if LOG_LEVEL >= DEBUG
/**
 * @brief Logs a debug message.
 * 
 * This macro logs a message at the "DEBUG" level for detailed debugging.
 * 
 * @param __VA_ARGS__ The message to log, with optional format specifiers.
 */
#define log_debug(...) _LOG_AT_LEVEL("DEBUG", __VA_ARGS__)
#else
#define log_debug(...)
#endif


#if LOG_LEVEL >= VERBOSE
/**
 * @brief Logs a verbose message.
 * 
 * This macro logs a message at the "VERBOSE" level for detailed diagnostics.
 * 
 * @param __VA_ARGS__ The message to log, with optional format specifiers.
 */
#define log_verbose(...) _LOG_AT_LEVEL("VERBOSE", __VA_ARGS__)
#else
#define log_verbose(...)
#endif


#endif // LOGGING_H