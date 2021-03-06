#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "commonFunctions.h"
using namespace std;
namespace yh {
   // Convert string of lowercase to STRING OF UPPERCASE
   const char* toUpperString(char* destination, char* source) {
      int i;
      for (i = 0; source[i]; i++) {
         destination[i] = (char)toupper(source[i]);
      }
      destination[i] = '\0';
      return destination;
   }
   // Convert character of lowercase to CHRACTER OF UPPERCASE
   char toUpperCharacter(char character) {
      return (char) toupper(character);
   }
   // Draw the number of seperator=
   void seperatorDouble(std::ostream& ostr, int num) {
      ostr.width(num);
      ostr.fill('=');
      ostr << "=" << endl;
      ostr.fill(' ');
   }
   // Copy character array dynamically
   void allocateCopy(char*& destination, const char* source) {
      delete[] destination;
      destination = nullptr;
      if (source != nullptr) {
         destination = new char[strlen(source) + 1];
         strcpy(destination, source);
      }
   }
   // Receive string & allocate dynamically
   char* getDynCstr(std::istream& istr, char delim) {
      char* cstr{};
      std::string str;
      getline(istr, str, delim);
      if (istr) allocateCopy(cstr, str.c_str());
      return cstr;
   }
   // Receive integer within range
   int getint(int min, int max) {
      int num;
      bool done;
      do {
         done = true;
         cin >> num;
         if (cin.fail()) {
            done = false;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Option, retry: ";
         }
         else if (min > num || num > max) {
            done = false;
            cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
         }
      } while (!done);
      return num;
   }
}