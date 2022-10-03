#include "circuitboard.hpp"

using namespace PCB;

const char *MSGS[] = {"----------------\n0. Quit", "1. Input and add contact", "2. Print pcb","3. Add connection",
                      "4. Print group of contacts", "5. Calculate distance between 2 contacts"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int dialog(const char *msgs[], int n) {
    int choice = 0;
    do {
        if (!std::cin.good() or choice < 0 || choice >= n) {
            std::cin.clear();
            std::cin.sync();
            std::cout << "You're wrong. Try again!\n" << std::endl;
        }
        for (int i = 0; i < n; ++i) {
            std::cout << msgs[i] << std::endl;
        }
        std::cout << "Make your choice: " << std::endl;
        std::cin >> choice;
    } while (!std::cin.good() or choice < 0 || choice >= n);
    return choice;
}

int main(){
    int c, from, to, dist, filter;
    contact cont;
    pcb circuit, circ2;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        std::cin.clear();
        std::cin.sync();
        try {
            switch (c) {
                case 1://input and add contact
                    std::cout << "Please, enter coordinates x y and type of contact(0 - input, 1 - output)" << std::endl;
                    cont.input_contact(std::cin);
                    circuit.add_contact(cont);
                    break;
                case 2:
                    circuit.print_pcb(std::cout);
                    break;
                case 3: // Add connection
                    std::cout << "Please, enter id contact from and to" << std::endl;
                    std::cin >> from >> to;
                    circuit.add_link(from, to);
                    break;
                case 4: // Print group of contacts
                    std::cout << "Enter filter - type of contact" << std::endl;
                    std::cin >> filter;
                    circ2 = circuit.group_cont((type) filter);
                    circ2.print_pcb(std::cout);
                    break;
                case 5: // Calculate distance between 2 contacts
                    std::cout << "Please, enter id contact from and to" << std::endl;
                    std::cin >> from >> to;
                    dist = circuit.contact_dist(from, to);
                    if (dist == 0)
                        std::cout << "Path between this contacts don`t exist" << std::endl;
                    else
                        std::cout << "Path between this contacts equal: " << dist << std::endl;
                    break;
                default:
                    std::cout << "Goodbye!" << std::endl;
                    break;
            }
        }
        catch (std::exception &ex) {
            std::cin.clear();
            std::cin.sync();
            std::cout << ex.what() << std::endl;
        }
    } while (c != 0);
    return 0;
}