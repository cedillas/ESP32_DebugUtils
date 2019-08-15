#include "ESP32_DebugUtils.h"
#include "time.h"

/******************************************************************************
   CONSTANTS
 ******************************************************************************/

static int const DEFAULT_DEBUG_LEVEL   = DBG_INFO;
static Stream *  DEFAULT_OUTPUT_STREAM = &Serial;
static char * DEFAULT_FORMAT = "%A, %B %d %Y %H:%M:%S";

/******************************************************************************
   CTOR/DTOR
 ******************************************************************************/

ESP32_DebugUtils::ESP32_DebugUtils() {
  timestampOff();
  setDebugLevel(DEFAULT_DEBUG_LEVEL);
  setDebugOutputStream(DEFAULT_OUTPUT_STREAM);
  setFormat(DEFAULT_FORMAT);
}

/******************************************************************************
   PUBLIC MEMBER FUNCTIONS
 ******************************************************************************/

void ESP32_DebugUtils::setFormat(char * format) {
  _format = format;
}

void ESP32_DebugUtils::setDebugLevel(int const debug_level) {
  _debug_level = debug_level;
}

void ESP32_DebugUtils::setDebugOutputStream(Stream * stream) {
  _debug_output_stream = stream;
}

void ESP32_DebugUtils::timestampOn() {
  _timestamp_on = true;
}

void ESP32_DebugUtils::timestampOff() {
  _timestamp_on = false;
}

void ESP32_DebugUtils::print(int const debug_level, const char * fmt, ...) {
  if (debug_level >= DBG_ERROR   &&
      debug_level <= DBG_VERBOSE &&
      debug_level <= _debug_level) {
    if (_timestamp_on) {
      struct tm timeinfo;
      char timestamp[50];
      getLocalTime(&timeinfo);
      strftime(timestamp, sizeof(timestamp), _format, &timeinfo);
      _debug_output_stream->print(timestamp);
    }

    va_list args;
    va_start(args, fmt);
    vPrint(fmt, args);
    va_end(args);
  }
}

/******************************************************************************
   PRIVATE MEMBER FUNCTIONS
 ******************************************************************************/

void ESP32_DebugUtils::vPrint(char const * fmt, va_list args) {
  static size_t const MSG_BUF_SIZE = 120;
  char msg_buf[MSG_BUF_SIZE] = {0};

  vsnprintf(msg_buf, MSG_BUF_SIZE, fmt, args);

  _debug_output_stream->println(msg_buf);
}

/******************************************************************************
   CLASS INSTANTIATION
 ******************************************************************************/

ESP32_DebugUtils Debug;