#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
extern "C"
{
  char *Replace(const char *source, const char *pattern, const char *value)
  {
    std::string src = std::string(source);
    for (size_t i = 0; i < src.length(); ++i)
    {
      std::string pt;
      if (i < src.size() - 1 && src.at(i) == '$')
      {
        size_t j = i + 1;
        while (j < src.size() && src[j] != ' ' && src[j] != ';')
        {
          pt.push_back(src.at(j));
          ++j;
        }
        if (j < src.size() && src.at(j) == ';')
        {
          ++j;
        }
        if (!strcmp(pt.c_str(), pattern))
        {
          std::string p1 = src.substr(0, i);
          std::string p2 = src.substr(j);
          src = std::string(p1 + std::string(value) + p2);
        }
      }
    }
    char *cstr = new char[src.length() + 1];
    std::strcpy(cstr, src.c_str());
    return cstr;
  }

  typedef struct Reps
  {
    const char *pattern;
    const char *value;
  } Reps;

  char *ReplaceV(const char *source, Reps rep)
  {
    std::string src = std::string(source);
    for (size_t i = 0; i < src.length(); ++i)
    {
      std::string pt;
      if (i < src.size() - 1 && src.at(i) == '$')
      {
        size_t j = i + 1;
        while (j < src.size() && src[j] != ' ' && src[j] != ';')
        {
          pt.push_back(src.at(j));
          ++j;
        }
        if (j < src.size() && src.at(j) == ';')
        {
          ++j;
        }
        if (!strcmp(pt.c_str(), rep.pattern))
        {
          std::string p1 = src.substr(0, i);
          std::string p2 = src.substr(j);
          src = std::string(p1 + std::string(rep.value) + p2);
          continue;
        }
      }
    }
    char *cstr = new char[src.length() + 1];
    std::strcpy(cstr, src.c_str());
    return cstr;
  }

  char *ReplaceVWrapper(const char *source, const char *pattern, const char *value)
  {
    Reps r;
    r.pattern = pattern;
    r.value = value;
    return ReplaceV(source, r);
  }

  char *ReplaceAll(const char *source, Reps *reps, size_t amount)
  {
    std::string src = std::string(source);
    for (size_t rep_i = 0; rep_i < amount; ++rep_i)
    {
      for (size_t i = 0; i < src.length(); ++i)
      {
        std::string pt;
        if (i < src.size() - 1 && src.at(i) == '$')
        {
          size_t j = i + 1;
          while (j < src.size() && src[j] != ' ' && src[j] != ';')
          {
            pt.push_back(src.at(j));
            ++j;
          }
          if (j < src.size() && src.at(j) == ';')
          {
            ++j;
          }
          if (strcmp(pt.c_str(), reps[rep_i].pattern) == 0)
          {
            std::string p1 = src.substr(0, i);
            std::string p2 = src.substr(j);
            src = std::string(p1 + std::string(reps[rep_i].value) + p2);
            continue;
          }
          pt.clear();
        }
      }
    }
    char *cstr = new char[src.length() + 1];
    std::strcpy(cstr, src.c_str());
    return cstr;
  }

  void FreeString(char *str)
  {
    delete[] str;
  }
}

// For testing purposes
int main(void)
{
  const char *src = "I like $ITEM;, $ITEM and $BRR;. $BRR is american band.";

  std::vector<Reps> reps;

  Reps IceCream = Reps{.pattern = "ITEM", .value = "Ice cream"};
  reps.push_back(IceCream);
  reps.push_back(Reps{.pattern = "BRR", .value = "Deftones"});

  printf("Replace(\"%s\") with effect: \"%s\"\n", src, Replace(src, "ITEM", "Ice cream"));
  printf("ReplaceV(\"%s\") with effect: \"%s\"\n", src, ReplaceV(src, IceCream));
  printf("ReplaceAll(\"%s\") with effect: \"%s\"\n", src, ReplaceAll(src, reps.data(), reps.size()));
}