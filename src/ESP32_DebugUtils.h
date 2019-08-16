#ifndef ESP32_DEBUG_UTILS_H_
#define ESP32_DEBUG_UTILS_H_

/******************************************************************************
   INCLUDE
 ******************************************************************************/

#include <Arduino.h>
#include <stdarg.h>
#include "FS.h"

/******************************************************************************
   CONSTANTS
 ******************************************************************************/

static int const DBG_NONE    = -1;
static int const DBG_ERROR   =  0;
static int const DBG_WARNING =  1;
static int const DBG_INFO    =  2;
static int const DBG_DEBUG   =  3;
static int const DBG_VERBOSE =  4;

/******************************************************************************
   CLASS DECLARATION
 ******************************************************************************/

class ESP32_DebugUtils {

  public:

    ESP32_DebugUtils();
    ESP32_DebugUtils(File file);
    ESP32_DebugUtils(Stream *  _debug_output_stream);

    void setFormat(char * format);
    void setDebugLevel(int const debug_level);

    void setDebugOutputStream(Stream * stream);
    void clearDebugOutputStream();
    void setDebugOutputFile(File file);
    void clearDebugOutputFile();

    void timestampOn();
    void timestampOff();

    void messageTypeOn();
    void messageTypeOff();

    void print(int const debug_level, const char * fmt, ...);


  private:

    bool      _timestamp_on;
    bool      _messageType_on;
    int       _debug_level;
    bool      _debug_output_stream_enabled;
    Stream *  _debug_output_stream;
    bool      _debug_output_file_enabled;
    File      _debug_output_file;
    char *    _format;

    void vPrint(char const * fmt, va_list args);

};

/******************************************************************************
   EXTERN
 ******************************************************************************/

extern ESP32_DebugUtils Debug;

#endif /* ESP32_DEBUG_UTILS_H_ */