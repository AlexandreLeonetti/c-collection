#ifndef ASTAR_H
#define ASTAR_H

#include <stdbool.h>

typedef struct {
    int x, y;
} Point;

typedef struct Node {
    Point pos;
    int g, h;
    struct Node* parent;
} Node;

typedef struct {
    Node* nodes;
    int capacity;
    int size;
} PriorityQueue;

void init_priority_queue(PriorityQueue* pq, int capacity);
void free_priority_queue(PriorityQueue* pq);
void pq_push(PriorityQueue* pq, Node node);
Node pq_pop(PriorityQueue* pq);
bool pq_is_empty(PriorityQueue* pq);

bool is_valid_point(int x, int y);
bool is_point_in_list(Point* list, int size, Point p);

int heuristic(Point a, Point b);

#endif // ASTAR_H
