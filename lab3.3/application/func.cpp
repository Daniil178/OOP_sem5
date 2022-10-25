#include "func.hpp"

using namespace PCB_dynamic;

// all variants
const char *MSGS[] = {"----------------\n0. Quit", "1. Input and add 1 contact", "2. Print pcb","3. Add connection",
                      "4. Print group of contacts", "5. Calculate distance between 2 contacts", "6. Pop contact",
                      "7. Invert links in pcb", "8. Input pcb with n contacts", "9. Add to pcb default circuit"};

const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int get_choice(const char *msgs[], int n) {
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
        std::cout << "---------------------\n" << "Make your choice: " << std::endl;
        std::cin >> choice;
    } while (!std::cin.good() or choice < 0 || choice >= n);
    return choice;
}

void dialog(){
    int choice, from, to, dist, filter;
    contact cont;
    pcb circuit, circ2, default_pcb;
    default_pcb.add_contact(contact (1, 1, input));
    default_pcb.add_contact(contact (2, 2, output));
    default_pcb.add_link(0, 1);
    do {
        choice = get_choice(MSGS, MSGS_SIZE);
        std::cin.clear();
        std::cin.sync();
        try {
            switch (choice) {
                case 1://input and add contact
                    std::cout << "Please, enter contact: coordinates x y and type (0 - input, 1 - output)" << std::endl;
                    cont.input_contact(std::cin);
                    circuit.add_contact(cont);
                    break;
                case 2: // print pcb
                    std::cout << circuit;
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
                case 6: // Pop contact
                    --circuit;
                    std::cout << "Last contact deleted" << std::endl;
                    break;
                case 7: // Invert links in pcb
                    circuit = !circuit;
                    std::cout << "All links are inverted" << std::endl;
                    break;
                case 8: // Input pcb with n contacts
                    std::cout << "Please, enter number of contacts" << std::endl;
                    std::cout << "Example of contact x y type (0 - input, 1 - output)" << std::endl;
                    std::cin >> circuit;
                    break;
                case 9: // Add to pcb default circuit
                    std::cout << "Default pcb:" << std::endl;
                    std::cout << default_pcb;
                    circuit = circuit + default_pcb;
                    std::cout << "result of summary:" << std::endl << circuit;
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
    } while (choice != 0);
}