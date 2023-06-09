#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <Arduino.h>

/**
 * @brief Enable or disable the debug mode.
 * 
 * If debug mode is enabled, then debug prints via serial port will be displayed.
 * If debug mode is disabled, then debug prints won't take effect. Also, Serial.begin() won't be called.
 * 
 * @note Debug prints don't affect the performance of the app if debug mode is disabled.
 */
#define DEBUG_MODE 1

/**
 * @brief Implement methods to consistent print debug output via serial port
 * 
 */
class Debugger{
public:

  /**
   * @brief Construct a new Debugger object
   * 
   * @param baud The baud rate
   */
  Debugger(unsigned long int baud = 115200);

  /**
   * @brief Get the information about the debug mode status
   * 
   * @return true If debug mode is enabled.
   * @return false If debug mode is disabled.
   */
  bool enabled();

  template<typename T>
  void print(const T content)
  {
    if (log_print_i > 0) _println(String(content));
  }

  template<typename T>
  void print(const T* const array, size_t _length, unsigned char opt = DEC)
  {
    if (log_print_i > 0 && _length > 0)
    {
      _print("[" + String(array[0], opt));
      for(size_t i = 1; i < _length; i++)
      {
        _print(", " + String(array[i], opt), true);
      }
      _println(String("]"), true);
    }
  }

  template<typename T>
  void print(const T* const array, size_t rows, size_t columns, unsigned char opt = DEC)
  {
    if (log_print_i > 0 && rows*columns > 0)
    {
      for (size_t j = 0; j < rows; j++)
      {
        _print("|" + String(array[j*columns + 0], opt));
        for(size_t i = 1; i < columns; i++)
          _print(" " + String(array[j*columns + i], opt), true);
        _println(String("|"), true);
      }
    }
  }
  
  void print(const float* const array, size_t _length, unsigned char decimals = 4)
  {
    if (log_print_i > 0 && _length > 0)
    {
      _print("[" + String(array[0], (uint32_t)decimals));
      for(size_t i = 1; i < _length; i++)
      {
        _print(", " + String(array[i], (uint32_t)decimals), true);
      }
      _println(String("]"), true);
    }
  }

  void print(const float* const array, size_t rows, size_t columns, unsigned char decimals = 4)
  {
    if (log_print_i > 0 && rows*columns > 0)
    {
      for (size_t j = 0; j < rows; j++)
      {
        _print("|" + String(array[j*columns + 0], (uint32_t)decimals));
        for(size_t i = 1; i < columns; i++)
          _print(" " + String(array[j*columns + i], (uint32_t)decimals), true);
        _println(String("|"), true);
      }
    }
  }
private:
  uint64_t log_print_i = 0;

  /**
   * @brief Actually write outputs via serial port
   * 
   * @param content
   * @param same If true, Debug log won't be printed.
   */
  void _println(String content, bool same = false);

  /**
   * @brief Actually write outputs via serial port without \n
   * 
   * @param content 
   * @param same If true, Debug log won't be printed.
   */
  void _print(String content, bool same = false);
};

/**
 * @brief Global debugger object
 * 
 */
extern Debugger debug;

#endif