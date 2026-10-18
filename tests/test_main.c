#include "framework.h"

int main(void) {
  MT_BEGIN("main");

  int value = 67;
  MT_CHECK_INT(67, value);

  return MT_END();
}
