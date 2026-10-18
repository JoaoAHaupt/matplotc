#ifndef MATPLOTC_TESTS_FRAMEWORK_H
#define MATPLOTC_TESTS_FRAMEWORK_H

#include <math.h>
#include <stdio.h>
#include <string.h>

static int total = 0;
static int failed = 0;

#define MT_BEGIN(suite)                                                        \
  do {                                                                         \
    printf(">>> %s\n", (suite));                                               \
    total = 0;                                                                 \
    failed = 0;                                                                \
  } while (0)

#define MT_CHECK(cond)                                                         \
  do {                                                                         \
    total++;                                                                   \
    if (!(cond)) {                                                             \
      failed++;                                                                \
      printf("  FALHOU  %s  (%s:%d)\n", #cond, __FILE__, __LINE__);            \
    }                                                                          \
  } while (0)

#define MT_CHECK_INT(expected, actual)                                         \
  do {                                                                         \
    long long mt_e = (long long)(expected);                                    \
    long long mt_a = (long long)(actual);                                      \
    total++;                                                                   \
    if (mt_e != mt_a) {                                                        \
      failed++;                                                                \
      printf("  FALHOU  %s == %s  (esperado %lld, obtido %lld)  "              \
             "(%s:%d)\n",                                                      \
             #expected, #actual, mt_e, mt_a, __FILE__, __LINE__);              \
    }                                                                          \
  } while (0)

#define MT_CHECK_FLOAT(expected, actual, epsilon)                              \
  do {                                                                         \
    double mt_e = (double)(expected);                                          \
    double mt_a = (double)(actual);                                            \
    total++;                                                                   \
    if (fabs(mt_e - mt_a) > (double)(epsilon)) {                               \
      failed++;                                                                \
      printf("  FALHOU  %s == %s  (esperado %g, obtido %g)  "                  \
             "(%s:%d)\n",                                                      \
             #expected, #actual, mt_e, mt_a, __FILE__, __LINE__);              \
    }                                                                          \
  } while (0)

#define MT_CHECK_STR(expected, actual)                                         \
  do {                                                                         \
    const char *mt_e = (expected);                                             \
    const char *mt_a = (actual);                                               \
    total++;                                                                   \
    if (mt_e == NULL || mt_a == NULL || strcmp(mt_e, mt_a) != 0) {             \
      failed++;                                                                \
      printf("  FALHOU  %s == %s  (esperado \"%s\", obtido \"%s\")  "          \
             "(%s:%d)\n",                                                      \
             #expected, #actual, mt_e ? mt_e : "NULL", mt_a ? mt_a : "NULL",   \
             __FILE__, __LINE__);                                              \
    }                                                                          \
  } while (0)

#define MT_END()                                                               \
  (printf("    %s: %d/%d asserções\n", failed ? "FALHOU" : "PASSOU",           \
          total - failed, total),                                              \
   failed ? 1 : 0)

#endif /* MATPLOTC_TESTS_FRAMEWORK_H */
