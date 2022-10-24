#ifndef FUNC_HPP
#define FUNC_HPP

#include "pcb.hpp"

const char *MSGS[] = {"----------------\n0. Quit", "1. Input and add 1 contact", "2. Print pcb","3. Add connection",
                      "4. Print group of contacts", "5. Calculate distance between 2 contacts", "6. Pop contact",
                      "7. Invert links in pcb", "8. Input pcb with n contacts"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int get_choice(const char *msgs[], int n);
void dialog();

#endif