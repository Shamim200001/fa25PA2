//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        size++;
        // The upheap will restoring heap by bubbling the new element
        upheap(size -1, weightArr);

    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        //First check if the heap is empty
        //the root contains the last element
        if (size == 0) return -1;
        int minIdx = data[0];

        //The root get replaced by the last element
        data[0] = data[size -1];
        size--;

        if (size > 0) {
            //The new root gets moved down for minHeap
            downheap(0, weightArr);
        }

        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        //all the elements are moving up to fill the root
        //calculate the parent index
        //the parent has to be smaller or even then the children
        //after checked the heap looks good then stop the upHeap
        while (pos > 0) {
            int parent = (pos -1) / 2;
            if (weightArr[data[pos]] >= weightArr[data[parent]]) {
                break;
            }
            //Here the swapping starts
            //the smaller node has to swap with parent
            //keep checking the parent node and replace them with smaller node
            //the smaller node has to keep going up
            swap(data[pos], data[parent]);
            pos = parent;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        //keep calculating the indices of the left and right children
        //using while loop to continue until the heap is full
        while (true) {
            int leftChild = 2 * pos +1;
            int rightChild = 2 * pos +2;
            int smallest = pos;

            //if the left child exist and it's smaller than current
            //keep updating the smallest left child
            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]]) {
                smallest = leftChild;
            }
            //The same process with the right child
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]]) {
                smallest = rightChild;
            }
            //swapping
            //if there is smaller child than current node then swap it
            //the smallest child always get swap
            //the biggest children keeps going down
            //after checked the heap looks good then stop the downHeap
            if (smallest != pos) {
                swap(data[pos], data[smallest]);
                pos = smallest;
            }else {
                break;
            }
        }
    }
};

#endif