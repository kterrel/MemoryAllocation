//
//  Created by Kelsey Terrel on 10/23/16.
//  Copyright © 2016 Kelsey Terrel. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include "mem.h"
using namespace std;

// T marks the class template parameter and this function's template parameter
template <class T>
ListNode<T>::ListNode(T inputData):
data(inputData),

next(NULL) {}


template <class T>
// sets the element and creates ListNode to store elements
T ListNode<T>::getData() {
    return data;
}


template <class T>

T ListNode<T>::setData(T passed) {
    data = passed;
    
    return data;
    
}


template <class T>

ListNode<T> *ListNode<T>::getNext() {
    
    return next;
    
}


template <class T>

ListNode<T> *ListNode<T>::setNext(ListNode<T> *node) {
    
    next = node;
    
    return next;
    
}


template <class T>

LinkedList<T>::LinkedList():

head(NULL) {}


template <class T>

ListNode<T> *LinkedList<T>::getHead() {
    
    return head;
    
}


template <class T>

ListNode<T> *LinkedList<T>::setHead(ListNode<T> *head) {
    
    this->head = head;
    
    return
    this->head;
    
}


template <class T>

ListNode<T> *LinkedList<T>::append(T data) {
    
    if (head == NULL) { //if list is currently empty
        
        head = new ListNode<T>(data);
        return head;
        
    }
    
    ListNode<T> *temp = head;
    
    while (temp->getNext() != NULL) {
        
        temp = temp -> getNext();
        
    }
    
    temp->setNext(new ListNode<T>(data));
    
    return temp ->  getNext();
    
}


MemoryAllocator::MemoryAllocator(string passed_alg, int pages) {
    
    algorithm = passed_alg;
    
    printf("Using %s fit algorithm\n", algorithm.c_str());
    
    freeMemory = LinkedList<Chunk>();
    
    freeMemory.append(Chunk(0, pages - 1));
    
    usedMemory = LinkedList<UsedMemoryChunk>();
    
    
}


typedef pair<ListNode<Chunk>*, int> MyPairType;

struct CompareSecond
{
    bool operator()(const MyPairType& left, const MyPairType& right)
    const
    
    {
        
        return left.second < right.second;
        
    }
    
};


//Checks correctness of name and size based on previous nodes. Inserts depending on "best" or "worst" fit algorithms and then determines where to place new node based on page data.
void
MemoryAllocator::add_program(ProgramInfo prog_info) {
    
    if (prog_info.size <= 0) {
        
        printf("Error: Size not valid\n");
        
        return;
        
    }
    
    
    //Makes sure that program name is not already being used
    
    ListNode<UsedMemoryChunk> *used_current = usedMemory.getHead();
    
    while (used_current != NULL) {
        
        if (used_current->getData().programName == prog_info.name) {
            printf("Error, Program %s is already running\n", prog_info.name.c_str());
            
            return;
            
        }
        else {
            
            used_current = used_current->getNext();
            
        }
        
    }
    
    
    map<ListNode<Chunk>*,
    int> free_slots;
    
    ListNode<Chunk> *current = freeMemory.getHead();
    
    int pages = ceil(prog_info.size / 4.0);
    
    
    while (current != NULL) {
        
        int free_size = (current->getData().endPage - current->getData().startPage) + 1;
        
        if (free_size >= (pages)) {
            
            free_slots[current] = free_size;
            
        }
        
        current = current->getNext();
        
    }
    
    
    if (free_slots.size() == 0){
        printf("Error, Not enough memory for Program\n");
        
        return;
        
    }
    
    
    ListNode<UsedMemoryChunk> *new_node = NULL;
    ListNode<Chunk> *node_to_use = NULL;
    
    
    if (this->algorithm == "best") {
        pair<ListNode<Chunk>*,
        int> min = *min_element(free_slots.begin(), free_slots.end(),
                                CompareSecond());
        
        node_to_use = min.first;
        
    }
    else {
        // Worst fit
        
        pair<ListNode<Chunk>*, int> max =
        *max_element(free_slots.begin(), free_slots.end(), CompareSecond());
        node_to_use = max.first;
        
    }
    
    
    /* At times, start page + pages will be greater than the end page. In this occurence, we will not include it in "free memory"
     */
    Chunk chunk_to_use = node_to_use-> getData();
    
    if (chunk_to_use.startPage + pages > chunk_to_use.endPage)
    {
        
        if (freeMemory.getHead() == node_to_use) {
            
            freeMemory.setHead(node_to_use->getNext());
            
        } else {
            
            bool previous_node_found =
            false;
            
            current = freeMemory.getHead()->getNext();
            
            while (current !=
                   NULL && !previous_node_found) {
                
                if (current->getNext() == node_to_use) {
                    
                    current->setNext(node_to_use->getNext());
                    
                    previous_node_found =
                    true;
                    
                } else {
                    
                    current = current->getNext();
                    
                }
                
            }
            
        }
        
    } else {
        
        node_to_use->setData(Chunk(chunk_to_use.startPage + pages, chunk_to_use.endPage));
        
    }
    
    
    int chunkStart = chunk_to_use.startPage, chunkEnd = chunk_to_use.startPage + pages - 1;
    
    new_node =
    new ListNode<UsedMemoryChunk>(UsedMemoryChunk(chunkStart, chunkEnd, prog_info.name));
    
    
    used_current = usedMemory.getHead();
    
    ListNode<UsedMemoryChunk>* used_last = usedMemory.getHead();
    
    
    
    if (used_current != NULL && used_current->getData().startPage > new_node->getData().startPage)
    {
        
        new_node->setNext(usedMemory.getHead());
        
        usedMemory.setHead(new_node);
        
        printf("Program %s added successfully: %d page(s) used\n\n", prog_info.name.c_str(),pages);
        
        return;
        
    }
    
    // Continue placing until passing the start page of allocated memory
    
    
    while (used_current != NULL) {
        
        if (used_current->getData().startPage > new_node->getData().startPage) {
            
            used_last->setNext(new_node);
            
            new_node->setNext(used_current);
            
            printf("Program %s added successfully: %d page(s) used\n\n",
                   
                   prog_info.name.c_str(), pages);
            
            return;
            
        } else {
            
            used_last = used_current;
            
            used_current = used_current->getNext();
            
        }
        
    }
    
    
    // In case we need to append at the end
    
    usedMemory.append(new_node->getData());
    
    printf("Program %s added successfully: %d page(s) used\n\n",
           
           prog_info.name.c_str(), pages);
    
}


void MemoryAllocator::defragment() {
    
    ListNode<Chunk> *current = freeMemory.getHead(),
    
    *last = NULL;
    
    while (current != NULL) {
        
        if (last == NULL) {
            
            last = current;
            
            current = current->getNext();
            
        } else {
            
            int last_end = last->getData().endPage,
            
            current_start = current->getData().startPage;
            
            if (last_end + 1 == current_start) {
                
                Chunk expanded(last->getData().startPage,
                               
                               current->getData().endPage);
                
                last->setData(expanded);
                
                last->setNext(current->getNext());
                
                return;
                
            } else {
                
                last = current;
                
                current = current->getNext();
                
            }
            
        }
        
    }
    
}


// If the program name does not exist, calmly exit. Otherwise, delete the node

// from used and appropriately add a new one to new.

void
MemoryAllocator::kill_program(string programName) {
    
    int freed_start_page = 0, freed_end_page = 0;
    
    bool program_found = false;
    
    ListNode<UsedMemoryChunk> *used_current = usedMemory.getHead();
    
    ListNode<UsedMemoryChunk> *used_last = NULL;
    
    
    while (used_current != NULL && !program_found) {
        
        
        UsedMemoryChunk current_chunk = used_current->getData();
        
        if (programName.compare(current_chunk.programName) == 0) {
            
            freed_start_page = current_chunk.startPage;
            
            freed_end_page = current_chunk.endPage;
            
            if (used_last != NULL) {
                
                used_last->setNext(used_current->getNext());
                
            }
            else {
                
                usedMemory.setHead(used_current->getNext());
                
            }
            
            program_found =  true;
            
        } else {
            
            used_last = used_current;
            
            used_current = used_current->getNext();
            
        }
        
    }
    
    
    if (!program_found) {
        
        printf("Could not find program with name %s\n", programName.c_str());
        
        return;
        
    }
    
    
    Chunk freed(used_current->getData().startPage, used_current->getData().endPage);
    ListNode<Chunk> *new_node = new ListNode<Chunk>(freed);
    
    
    if (freeMemory.getHead() == NULL) {
        
        freeMemory.setHead(new_node);
        
        printf("%s deleted. %d page(s) freed\n\n", programName.c_str(),freed_end_page - freed_start_page +1);
        
        return;
        
    }
    
    /* Go through free memory until passing start page of freed memory, then create new node and point to first node */
    
    
    ListNode<Chunk> *free_current = freeMemory.getHead();
    
    ListNode<Chunk> *free_last = NULL;
    
    while (free_current != NULL) {
        int current_start_page = free_current->getData().startPage;
        
        if (current_start_page > freed.startPage) {
            
            new_node->setNext(free_current);
            
            if (free_last == NULL) {
                
                freeMemory.setHead(new_node);
                
            } else {
                
                free_last->setNext(new_node);
                
            }
            
            defragment();
            
            printf("%s deleted. %d page(s) freed\n\n", programName.c_str(), freed_end_page - freed_start_page + 1);
            
            return;
            
        } else {
            
            free_last = free_current;
            
            free_current = free_current->getNext();
            
        }
        
    }
    
}


void
MemoryAllocator::print_fragmentation() {
    int num_fragments = 0;
    ListNode<Chunk> *current = freeMemory.getHead();
    
    while (current != NULL) {
        
        num_fragments++;
        
        current = current->getNext();
        
    }
    
    printf("There are %d fragment(s)\n\n", num_fragments);
    
}


void
MemoryAllocator::print_memory() {
    
    map<int, string> used_pages;
    // Page index to program name
    
    ListNode<UsedMemoryChunk> *current = usedMemory.getHead();
    
    while (current != NULL) {
        
        UsedMemoryChunk info = current->getData();
        
        for (int i = info.startPage; i <= info.endPage; i++) {
            used_pages[i] = info.programName;
            
        }
        
        current = current->getNext();
        
    }
    
    for (int row = 0; row < 4; row++) {
        
        for (int col = 0; col < 8; col++) {
            int curr_page = row * 8 + col;
            
            if (used_pages.find(curr_page) != used_pages.end())
            {
                printf("%s", used_pages[curr_page].c_str());
                
            } else {
                
                printf("Free");
                
            }
            
        }
        
        printf("\n");
        
    }
    
    printf("\n");
    
}


void
print_instructions() {
    
    cout << "1. Add program\n"
    << "2. Kill program\n"
    << "3. Fragmentation\n"
    << "4. Print memory\n"
    << "5. Exit\n"
    << endl;
    
}


int getChoice() {
    
    int choice;
    
    printf("choice - ");
    cin >> choice;
    printf("\n");
    
    return choice;
    
}


string get_programName() {
    
    string name;
    
    printf("Program name - ");
    
    cin >> name;
    
    return name;
    
}


ProgramInfo
get_programInfo() {
    
    string name = get_programName();
    
    int size;
    
    printf("Program size (KB) -");
    
    cin >> size;
    
    return ProgramInfo(name, size);
    
}


int run_loop(string algorithm) {
    
    MemoryAllocator mem_alloc(algorithm, 32);
    
    print_instructions();
    
    int choice = -1;
    
    while (choice != 5) {
        
        choice = getChoice();
        
        switch (choice) {
                
            case 1: mem_alloc.add_program(get_programInfo());
                break;
                
            case 2: mem_alloc.kill_program(get_programName());
                break;
            case 3: mem_alloc.print_fragmentation();
                break;
            case 4: mem_alloc.print_memory();
                break;
            case 5: break;
            default: printf("Error, invalid option.\n");
                return 0;
                
        }
        
    }
    
    return 0;
}
int main(int argc, char** argv) {
    if (argv[1] !=  NULL) {
        string algorithm = argv[1];
        if (algorithm.compare("best") == 0 || algorithm.compare("worst") == 0) {
            return run_loop(algorithm);
        }
    }
    printf("First argument must be the algorithm to use (namely, ");
    printf("\"best\" or \"worst\")\n");
    return 0;
}
