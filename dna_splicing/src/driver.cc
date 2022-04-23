#include <iostream>

#include "dna_strand.hpp"
int main() {
    DNAstrand dna;
    dna.PushBack('c');
    dna.PushBack('b');
    dna.PushBack('a');
    dna.PushBack('t');
    dna.PushBack('t');
    dna.PushBack('c');
    dna.PushBack('b');

    char* pattern = "tcb";
    DNAstrand in;
    in.PushBack('z');
    in.PushBack('z');
    in.PushBack('z');
    dna.SpliceIn(pattern, in);

    Node* cur = dna.Head();
    while (cur != nullptr) {
        std::cout << cur->data << std::endl;
        cur = cur->next;
    }
    dna.~DNAstrand();
}