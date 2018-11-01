//
//  Created by Kelsey Terrel on 10/24/16.
//  Copyright © 2016 Kelsey Terrel. All rights reserved.
//

#ifndef mem_h
#define mem_h
#include <string>
using namespace std;


template <class T> class ListNode {
private:
    T data;
    ListNode <T> * next;
    
public:
    ListNode(T data);
    
    T setData(T data);
    ListNode<T> *setNext(ListNode<T> *node);
    T getData();
    ListNode<T> * getNext();
};

// Singly linked list

template <class T> class LinkedList{
private:
    ListNode<T>*head;
    
public:
    LinkedList();
    ListNode<T> *setHead(ListNode<T>*head);
    ListNode<T> *getHead();
    ListNode<T> *append(T data);
    
};

struct ProgramInfo {
    string name;
    int size;
    
    ProgramInfo(string name, int size) {
        this->name = name;
        this -> size = size;
    }
};

struct Chunk {
    int startPage, endPage;
    
    Chunk( int start, int end) {
        startPage = start;
        endPage = end;
    }
};

struct UsedMemoryChunk: Chunk{
    string programName;
    
    UsedMemoryChunk(int start, int end, string name):
    Chunk (startPage, endPage){
        startPage = start;
        endPage = end;
        programName = name;
    }
};

//User interacts with this class

class MemoryAllocator{
private:
    string algorithm;
    // best or worst
    
    LinkedList<Chunk> freeMemory;
    LinkedList<UsedMemoryChunk> usedMemory;
    
public:
    MemoryAllocator(string algorithm, int num_pages);
    
    void
    add_program(ProgramInfo prog_info);
    
    void
    kill_program(string programName);
    
    void
    defragment();
    void
    print_fragmentation();
    void
    print_memory();
};

#endif /* mem_h */
