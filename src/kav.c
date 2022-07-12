#include <sys/ioctl.h>
#include <unistd.h>
#include "h_r_add.h"
#include <string.h>
#include <stdlib.h>


typedef struct {
    char *ip_addr;
    int mon_count;
    int screen_w;
    int screen_h;
    int term_x;
    int term_y;
} System;


void net_grab_ip(System *ptr) {
    ptr->ip_addr = r_vstr("curl ifconfig.me 2> /dev/null");
}

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

void handle_tests(char *argx) {
    System sys, *ptr = &sys;
    if (strcmp(argx, "ip")==0) {
        net_grab_ip(ptr);
        printf("Ip :: %s\n",ptr->ip_addr);
    }
    else if (strcmp(argx, "monitor-count")==0) {
        set_monitor_count(ptr);
        printf("Monitor Count ::  %d\n",ptr->mon_count);
    }
    else if (strcmp(argx, "resolution")==0) {
        get_screen_res(ptr);
        printf("Screen Resolution :: %dx%d\n",ptr->screen_h, ptr->screen_w);
    }
    else if (strcmp(argx, "term-info")==0) {
        x_term_set(ptr);
        printf("%d :: %d\n",ptr->term_x, ptr->term_y);
    }
    else {
        printf("Failed To Parse.\n");
        return;
    }
}



int main(int argc, char **argv) {
    handle_tests(argv[1]);
}





