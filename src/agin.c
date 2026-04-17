/*
  Agin  => A string library written in C for C
  About => its a unoptimized library and built around traditional algorihms.
        => its implemented merely as a practice, its code expresses how the strings 
        => and its functions work under the hood and one can implement it using simple,
        => unhectic algorithms that we learn as our foundational algorithms.
        =? it can be copied, forked and further optimized and definitely one can use
        =? AI to easily optimize it painfully (^-^)
  
  Birth => its name origins from the word 'Again' where i mistakenly renamed a .c file
        => because i had no idea what to implement! and I tried 'AGAIN' -> 'AGIN'
*/



#include "agin.h"
#include <stdarg.h>
#include <stdlib.h>
#include<stdio.h>


#define DEFAULT_SIZE 10
#define true 1
#define false 0
#define IS_SPACE (1 << 0)

struct String {
  char *ptr;
  int isFreed;
  size_t len;
};

// C_IMPLEMENATATIONS
// lookup table for isSpace()
static const unsigned char wsp_LT[256] = {
    [' '] = IS_SPACE,  ['\f'] = IS_SPACE, ['\n'] = IS_SPACE,
    ['\r'] = IS_SPACE, ['\t'] = IS_SPACE, ['\v'] = IS_SPACE};
int isWhiteSpace(unsigned int c) {
  if (c < 0 || c > 255)
    return 0;
  return (wsp_LT[c] & IS_SPACE);
}
void *memmove(void *dest, const void *src, size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;
  if (d == s || n == 0)
    return dest;
  if (d < s) {
    for (size_t i = 0; i < n; i++) {
      d[i] = s[i];
    }
  } else {
    for (size_t i = n; i > 0; i--) {
      d[i - 1] = s[i - 1];
    }
  }
  return dest;
}

void throwError(Errors err) {
  switch (err) {
  case MemoryAllocationError:
    perror("MemoryAllocationError: failed to allocate memory!\n");
    break;
  case MemoryFreedError:
    perror("MemoryFreedError: memory already freed!\n");
    break;
  case GeneralError:
    perror("Error: error in the scope because of undefined behaviour!\n");
    break;
  default:
    perror("Unknown* ERROR occured!\n");
  }
}

static size_t length(const char *chars) {
  size_t i = 0;
  while (chars[i] != '\0') {
    i++;
  };
  return i;
}
static int avail(String *str, size_t span) {
  char *nPtr = NULL;
  if (!str->isFreed) {
    nPtr = (char *)realloc(str->ptr, (str->len + span) * sizeof(char));
    if (!nPtr) {
      throwError(MemoryAllocationError);
      return false;
    }
    str->len += span;
    str->ptr = nPtr;
    return true;
  }
  nPtr = (char *)realloc(str->ptr, span * sizeof(char));
  if (!nPtr) {
    throwError(MemoryAllocationError);
    return false;
  }
  str->len = span;
  str->ptr = nPtr;
  return true;
};

int copyTo(const char *chars, String *str) {
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return false;
  }
  int i = 0;
  while (i < length(chars)) {
    str->ptr[i] = chars[i];
    i++;
  }
  return true;
}

int destroy(int total, ...) {
  va_list args;
  va_start(args, total);
  if (total == 0)
    return false;

  for (int i = 0; i < total; i++) {
    String *xs = va_arg(args, String *);
    if (xs->isFreed) {
      throwError(MemoryFreedError);
      return false;
    }
    free(xs->ptr);
    free(xs);
    xs->isFreed = true;
    xs->len = 0;
  }

  va_end(args);
  return true;
}

String *create(const char *chars) {
  String *str = (String *)malloc(sizeof(String));
  if (!str) {
    throwError(MemoryAllocationError);
    exit(1);
  }
  int len = length(chars);
  str->len = len;
  char *ptr = (char *)malloc(sizeof(char) * len);
  if (!ptr) {
    throwError(MemoryAllocationError);
    exit(1);
  }
  str->ptr = ptr;
  str->isFreed = false;
  copyTo(chars, str);
  return str;
}
void println(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  for (int i = 0; i < str->len; i++) {
    printf("%c", str->ptr[i]);
  }
  printf("\n");
}
int lengthOf(String *str) {
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return -1;
  }
  return str->len;
}
char *charAt(String *str, int idx) {
  if (str->len == 0)
    return false;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return NULL;
  }
  if (idx < 0) {
    return str->ptr;
  } else if (idx >= str->len) {
    return str->ptr + str->len - 1;
  } else {
    return str->ptr + idx;
  }
}
int insertChars(String *str, const char *chars) {

  if (str->isFreed) {
    throwError(MemoryFreedError);
    return false;
  }
  int len = length(chars);
  int oldLen = str->len, i = 0;
  int isAvailed = avail(str, len);
  if (isAvailed) {
    while (oldLen < str->len) {
      str->ptr[oldLen] = chars[i++];
      oldLen++;
    }
  } else {
    throwError(MemoryAllocationError);
    return false;
  }
  return true;
}

int insertString(String *s1, String *s2) {
  if (s1->isFreed || s2->isFreed) {
    throwError(MemoryFreedError);
    return false;
  }
  int len = s2->len;
  int oldLen = s1->len, i = 0;
  int isAvailed = avail(s1, len);
  if (isAvailed) {
    while (oldLen < s1->len) {
      s1->ptr[oldLen] = s2->ptr[i++];
      oldLen++;
    }
  } else {
    throwError(MemoryAllocationError);
    return false;
  }
  return true;
}

int insertCharsAt(String *str, int k, const char *chars) {
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return false;
  }
  int len = length(chars);
  int i = 0;
  int strL = str->len;
  int isAvailed = avail(str, len + 1);
  if (isAvailed) {
    for (int j = strL; j >= k; j--) {
      str->ptr[j + len + 1] = str->ptr[j];
    }
    int j = 0, l = k;
    while (j < k) {
      str->ptr[l++] = chars[j];
      j++;
    }
  } else {
    throwError(MemoryAllocationError);
    return false;
  }
  return true;
}
int insertStringAt(String *str, int k, String *chars) {
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return false;
  }
  int len = chars->len;
  int i = 0;
  int strL = str->len;
  int isAvailed = avail(str, len + 1);
  if (isAvailed) {
    for (int j = strL; j >= k; j--) {
      str->ptr[j + len + 1] = str->ptr[j];
    }
    int j = 0, l = k;
    while (j < k) {
      str->ptr[l++] = chars->ptr[j];
      j++;
    }
  } else {
    throwError(MemoryAllocationError);
    return false;
  }
  return true;
}
int insertChar(String *str, const char c) {
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return false;
  }
  int oldLen = str->len, i = 0;
  int isAvailed = avail(str, 1);
  if (isAvailed) {
    str->ptr[oldLen] = c;
  } else {
    throwError(MemoryAllocationError);
    return false;
  }
  return true;
}

char pop(String *str) {
  if (str->len == 0)
    return '\0';
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return '\0';
  }
  char tmp = str->ptr[str->len - 1];
  str->ptr[str->len - 1] = '\0';
  str->len--;
  return tmp;
}
int isEmpty(String *str) {
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return 0;
  }
  return (str->len == 0);
}

char *indexOf(String *str, const char ch) {
  if (str->len == 0)
    return NULL;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return NULL;
  }
  for (char *c = str->ptr; *c; c++) {
    if (*c == ch) {
      return c;
    }
  }
  return NULL;
}

int contains(String *str, const char *chars) {
  if (str->len == 0)
    return -1;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return -1;
  }
  int len = length(chars);
  if (len > str->len)
    return -1;
  int strL = str->len;
  for (int i = 0; i <= strL - len; i++) {
    int m = true, idx = -1;
    for (int j = 0; j < len; j++) {
      if (str->ptr[i + j] != chars[j]) {
        m = false;
        break;
      } else {
        idx = i + j;
      }
    }
    if (m)
      return idx - len + 1;
  }
  return -1;
}

int isEqual(String *s1, String *s2) {
  if (s1->len == 0 || s2->len == 0)
    return -1;
  if (s1->isFreed || s2->isFreed) {
    throwError(MemoryFreedError);
    return -1;
  }
  int l = s1->len > s2->len ? s1->len : s2->len;
  int c = 0;
  for (int i = 0; i < l; i++) {
    if (s1->ptr[i] == s2->ptr[i]) {
      c++;
    }
  }
  return c == l;
}

void toLowerCase(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  for (int i = 0; i < str->len; i++) {
    int c = str->ptr[i];
    str->ptr[i] = c >= 65 && c <= 89 ? c + 32 : c;
  }
}
void toUpperCase(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  for (int i = 0; i < str->len; i++) {
    int c = str->ptr[i];
    str->ptr[i] = c >= 97 && c <= 121 ? c - 32 : c;
  }
}
int isLowerCased(String *str) {
  if (str->len == 0)
    return -1;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return false;
  }
  if (str->len == 0)
    return false;
  char *c = str->ptr;
  while (*c) {
    if (*c >= 'A' && *c <= 'Z')
      return false;
    c++;
  }
  return true;
}
int isUpperCased(String *str) {
  if (str->len == 0)
    return -1;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return false;
  }
  if (str->len == 0)
    return false;
  char *c = str->ptr;
  while (*c) {
    if (*c >= 'a' && *c <= 'z')
      return false;
    c++;
  }
  return true;
}
String *slice(String *str, int l, int h) {
  String *t = create("");
  if (str->len == 0)
    return t;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return t;
  }
  if (l < 0 || l >= str->len || h < 0 || h >= str->len || str->len == 0) {
    return t;
  }
  for (int i = l; i < h; i++) {
    insertChar(t, str->ptr[i]);
  }
  return t;
}

int startsWith(String *str, const char *chars) {
  if (str->len == 0)
    return -1;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return -1;
  }
  int l = length(chars), ok = true;
  if (l == 0)
    return 0;

  for (int i = 0; i < l; i++) {
    if (str->ptr[i] != chars[i]) {
      ok = false;
    }
    if (!ok)
      return false;
  }
  return ok;
}
int endsWith(String *str, const char *chars) {
  if (str->len == 0)
    return -1;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return -1;
  }
  int l = length(chars), ok = true, strL = str->len;
  if (l == 0)
    return 0;
  for (int i = strL - l, j = 0; i < strL; i++) {
    if (str->ptr[i] != chars[j++]) {
      ok = false;
    }
    if (!ok)
      return false;
  }
  return ok;
}
char *lastIndexOf(String *str, const char ch) {
  if (str->len == 0)
    return NULL;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return NULL;
  }
  char *idx = str->ptr;
  for (char *c = str->ptr; *c; c++) {
    if (*c == ch) {
      idx = c;
    }
  }
  return idx;
}

int countOccurence(String *str, const char *chars) {
  if (str->len == 0)
    return -1;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return -1;
  }
  int c = 0, len = length(chars);
  int i = 0;
  while (i < str->len) {
    int j = 0, found = true;
    while (j < len) {
      if (str->ptr[i + j] != chars[j]) {
        found = false;
      }
      j++;
    }
    if (found)
      c++;
    i++;
  }
  return c;
}

int countChars(String *str, const char ch) {
  if (str->len == 0)
    return -1;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return -1;
  }
  int c = 0;
  for (char *p = str->ptr; *p; p++) {
    if (*p == ch) {
      c++;
    }
  }
  return c;
}

void leftTrim(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  if(!isWhiteSpace((unsigned char)*str->ptr)) return;

  char *start = str->ptr;
  while (*start && isWhiteSpace((unsigned char)*start)) {
    start++;
  }
  if (str->ptr != start) {
    memmove(str->ptr, start, length(start));
  }
  str->len = str->len - (start - str->ptr);
}
void rightTrim(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  int s = 0;
  char *end = str->ptr + str->len - 1;
  if(!isWhiteSpace((unsigned char)*end)) return;

  while (end >= str->ptr && isWhiteSpace((unsigned char)*end)) {
    end--;
    s++;
  }
  *(end + 1) = '\0';
  str->len -= s;
}
void trim(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }


  leftTrim(str);
  rightTrim(str);
}

void capitalize(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  int i = 0;
  while (i < str->len) {
    int c;
    if (str->ptr[i] == ' ') {
      c = str->ptr[i + 1];
      str->ptr[i + 1] = c >= 97 && c <= 121 ? c - 32 : c;
    }
    if (i == 0) {
      c = str->ptr[i];
      str->ptr[i] = c >= 97 && c <= 121 ? c - 32 : c;
    }
    i++;
  }
}
void reverse(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  int i = 0, j = str->len - 1;
  while (i < j) {
    str->ptr[i] ^= str->ptr[j];
    str->ptr[j] ^= str->ptr[i];
    str->ptr[i] ^= str->ptr[j];
    i++;
    j--;
  }
}
void replace(String *str, const char *from, const char *to) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  int idx = contains(str, from);
  int fromLen = length(from), toLen = length(to);
  if (toLen > fromLen) {
    int isAvailed = avail(str, toLen - fromLen);
    if (!isAvailed) {
      throwError(MemoryAllocationError);
      return;
    }
  }
  int end = idx + toLen;
  int j = 0;
  if (idx == -1)
    return;
  while (idx < end) {
    str->ptr[idx] = to[j++];
    idx++;
  }
  int f = idx + fromLen - toLen;
  while (idx < f) {
    str->ptr[idx++] = 0;
  }
}
void replaceCharAtIndex(String *str, int index, const char c) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  if (c < 0 || c >= str->len)
    return;
  str->ptr[index] = c;
}
void replaceAll(String *str, const char *from, const char *to) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  int ocs = countOccurence(str, from);
  for (int i = 0; i < ocs; i++) {
    if (contains(str, from) != -1) {
      replace(str, from, to);
    }
  }
}
String *concat(int total, ...) {
  String *combined = create("");
  if (total == 0)
    return combined;
  va_list args;
  va_start(args, total);
  for (int i = 0; i < total; i++) {
    String *s = va_arg(args, String *);
    if (s->isFreed) {
      throwError(MemoryFreedError);
      return combined;
    }
    insertString(combined, s);
  }
  va_end(args);
  return combined;
}
String *join(const char delim, int total, ...) {
  String *joined = create("");
  if (total == 0)
    return joined;
  va_list args;
  va_start(args, total);
  for (int i = 0; i < total; i++) {
    String *s = va_arg(args, String *);
    if (s->isFreed) {
      throwError(MemoryFreedError);
      return joined;
    }
    if (i != total - 1)
      insertChar(s, delim);
    insertString(joined, s);
  }
  va_end(args);
  return joined;
}
char *findChar(String *str, const char ch) {
  if (str->len == 0)
    return NULL;

  if (str->isFreed) {
    throwError(MemoryFreedError);
    return NULL;
  }
  for (char *c = str->ptr; *c; c++) {
    if (*c == ch)
      return c;
  }
  return NULL;
}
long double toNumber(String *str, int need) {
  if (str->len == 0)
    return 0;
  char *eptr;
  long double v = strtold(str->ptr, &eptr);
  if (str->ptr == eptr) {
    throwError(GeneralError);
    return 0;
  }
  if (!eptr)
    return 0;
  if(!need) {
    destroy(1, str);
    return 0;
  }
  return v;
}
void zfill(String *str) {
  if (str->len == 0)
    return;
  if (str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  if(!isWhiteSpace((unsigned char)*str->ptr)) {
    return;
  }
  char *c = str->ptr;
  int i = false;
  while ((*c && isWhiteSpace((unsigned char)*c) || (*c && *c == '-'))) {
    if (*c == '-')
      i = true;
    *c = '0';
    c++;
  }
  if (i)
    *str->ptr = '-';
}
void repeat(String *str, const char *chars, int count) {
  if(str->len == 0) return;
  if(str->isFreed) {
    throwError(MemoryFreedError);
    return;
  }
  int c= 0;
  while(c < count){
    insertChars(str, chars);
    c++;
  }
}
String *getASCIILetters() {
 return  create("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}
String *getPunctuations() {
  return create("!\"#$%%&\'()*+,-./:;<=>?@[\\]^_`{|}~");
}
