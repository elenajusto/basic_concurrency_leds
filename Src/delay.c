#include "delay.h"

void delay(unsigned int time_del) {
    volatile int n;
    while(time_del--) {
        n = 1000;
        while(n--);
    }
}
