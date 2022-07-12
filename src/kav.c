#include <sys/ioctl.h>
#include <unistd.h>
#include "h_r_add.h"
#include <string.h>
#include <stdlib.h>


typedef struct {
    int mon_count;
    int screen_w;
    int screen_h;
    int term_x;
    int term_y;
} System;


void set_res_val(System *ptr, char *str) {
    char *value, *key = strtok_r(str, "x", &value);
    if (!key) {
        return;
    }
    ptr->screen_w = atoi(key);
    ptr->screen_h = atoi(value);
}


void x_term_set(System *ptr) {
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    ptr->term_x = win.ws_row;
    ptr->term_y = win.ws_col;
}




void set_monitor_count(System *ptr) {
    ptr->mon_count = atoi(r_vstr("xrandr | grep '*' | awk '{ print $1 }' | wc -l"));
}

void get_screen_res(System *ptr) {
    char *ret = r_vstr("xrandr | grep '*' | awk '{ print $1 }' | grep -m1 \"\"");
    set_res_val(ptr, ret);
}



void toggle_gui(); // will make front end gui   ;


int main() {
    System sys, *ptr = &sys;
    get_screen_res(ptr);
    set_monitor_count(ptr);
    printf("%d :: %d :: Monitor Count :: %d\n",ptr->screen_w, ptr->screen_h, ptr->mon_count);
}
