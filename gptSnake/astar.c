#include "astar.h"
#include <stdlib.h>
#include <limits.h>
#define GRID_SIZE 28
void init_priority_queue(PriorityQueue* pq, int capacity) {
    pq->nodes = (Node*)malloc(sizeof(Node) * capacity);
    pq->capacity = capacity;
    pq->size = 0;
}

void free_priority_queue(PriorityQueue* pq) {
    free(pq->nodes);
}

void pq_push(PriorityQueue* pq, Node node) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->nodes = (Node*)realloc(pq->nodes, sizeof(Node) * pq->capacity);
    }
    pq->nodes[pq->size++] = node;
    // Bubble up
    for (int i = pq->size - 1; i > 0 && pq->nodes[i].g + pq->nodes[i].h < pq->nodes[(i - 1) / 2].g + pq->nodes[(i - 1) / 2].h; i = (i - 1) / 2) {
        Node temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        pq->nodes[(i - 1) / 2] = temp;
    }
}

Node pq_pop(PriorityQueue* pq) {
    Node top = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    // Bubble down
    for (int i = 0, child; (child = 2 * i + 1) < pq->size; i = child) {
        if (child + 1 < pq->size && pq->nodes[child].g + pq->nodes[child].h > pq->nodes[child + 1].g + pq->nodes[child + 1].h) {
            child++;
        }
        if (pq->nodes[i].g + pq->nodes[i].h <= pq->nodes[child].g + pq->nodes[child].h) {
            break;
        }
        Node temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[child];
        pq->nodes[child] = temp;
    }
    return top;
}

bool pq_is_empty(PriorityQueue* pq) {
    return pq->size == 0;
}

bool is_valid_point(int x, int y) {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
}

bool is_point_in_list(Point* list, int size, Point p) {
    for (int i = 0; i < size; i++) {
        if (list[i].x == p.x && list[i].y == p.y) {
            return true;
        }
    }
    return false;
}

int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
