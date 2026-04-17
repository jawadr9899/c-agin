#ifndef AGIN_H
#define AGIN_H

typedef struct String String;
typedef enum {
  MemoryFreedError,
  MemoryAllocationError,
  GeneralError
} Errors;

String *create(const char *chars);
int isWhiteSpace(unsigned int c);
int copyTo(const char *chars, String *str);
int destroy(int total, ...);
char* charAt(String *str, int idx);
int insertChars(String *str, const char *chars);
int insertCharsAt(String *str, int k, const char *chars);
int insertChar(String *str, const char c);
int insertString(String *s1, String *s2);
int insertStringAt(String *str, int k, String *chars);
char pop(String *str);
void println(String *str);
int lengthOf(String *str);
int isEmpty(String *str);
int contains(String *str, const char *chars);
void toLowerCase(String *str);
void toUpperCase(String *str);
int isLowerCased(String *str) ;
int isUpperCased(String *str) ;
int isEqual(String *s1, String *s2);
String *slice(String *str, int l, int h);
int startsWith(String *str, const char *chars);
int endsWith(String *str, const char *chars);
char* indexOf(String *str, const char ch);
char* lastIndexOf(String *str, const char ch);
int countOccurence(String *str, const char *chars);
int countChars(String *str, const char ch);
void leftTrim(String *str);
void rightTrim(String *str);
void trim(String *str);
void capitalize(String *str);
void reverse(String *str);
void replace(String *str, const char *from, const char *to);
void replaceAll(String *str, const char *from, const char *to);
void replaceCharAtIndex(String*str, int index, const char c);
String *concat(int total, ...);
String* join(const char delim,int total, ...);
char* findChar(String*str, const char ch);
long double toNumber(String*str, int need);
void zfill(String*str);
void repeat(String *str, const char *chars, int count) ;
String *getASCIILetters();
String *getPunctuations();

#endif