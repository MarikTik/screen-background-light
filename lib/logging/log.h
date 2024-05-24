#define LOG_LEVEL_NONE    0
#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_WARN    2
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_DEBUG   4
#define LOG_LEVEL_VERBOSE 5
#include <HardwareSerial.h>

#ifndef LOG_LEVEL 
#define LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
  #define log_e(...) Serial.printf("[ERROR] " __VA_ARGS__)
#else
  #define log_e(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
  #define log_w(...) Serial.printf("[WARN] " __VA_ARGS__)
#else
  #define log_w(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
  #define log_i(...) Serial.printf("[INFO] " __VA_ARGS__)
#else
  #define log_i(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
  #define log_d(...) Serial.printf("[DEBUG] " __VA_ARGS__)
#else
  #define log_d(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
  #define log_v(...) Serial.printf("[VERBOSE] " __VA_ARGS__)
#else
  #define log_v(...)
#endif
