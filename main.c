#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_WIDTH 30
#define FIELD_HEIGHT 30
#define MAX_SNAKE_LEN (FIELD_WIDTH * FIELD_HEIGHT)

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction;

typedef struct {
    int width;
    int height;
} field;

typedef struct {
    int len;
    int coords_xy[MAX_SNAKE_LEN * 2];
} snake;

typedef struct {
    int x;
    int y;
} apple;

typedef struct {
    char data[(FIELD_WIDTH + 1) * (FIELD_HEIGHT + 1)];
} display;

void move_snake(snake* s, direction dir) {    
    for (int i = s->len - 1; i > 0; i--) {
        int x_idx_next = 2 * i;
        int x_idx_prev = 2 * (i - 1);
        int y_idx_next = 2 * i + 1;
        int y_idx_prev = 2 * (i - 1) + 1;
        s->coords_xy[x_idx_next] = s->coords_xy[x_idx_prev];   
        s->coords_xy[y_idx_next] = s->coords_xy[y_idx_prev];   
    }

    if (dir == UP) {
        s->coords_xy[1] -= 1;
    } else if (dir == DOWN) {
        s->coords_xy[1] += 1;
    } else if (dir == LEFT) {
        s->coords_xy[0] -= 1;
    } else if (dir == RIGHT) {
        s->coords_xy[0] += 1;
    } else {
        printf("UNCNOWN DIRECTION");
    }
}

int check_apple_eat(snake* s, apple* a) {
    int snake_head_x = s->coords_xy[0];
    int snake_head_y = s->coords_xy[1];
    return (a->x == snake_head_x && a->y == snake_head_y);
}

void render(display* d, snake* s, apple* a, field* f) {
    // render field
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        if ((y == 0) || (y == FIELD_HEIGHT - 1)) {
            for (int x = 0; x < FIELD_WIDTH; x++) {
                d->data[y * FIELD_WIDTH + x] = '#';
            }
        } else {
            d->data[y * FIELD_WIDTH] = '#';
            for (int x = 1; x < FIELD_WIDTH - 1; x++) {
                d->data[y * FIELD_WIDTH + x] = ' ';
            }
            d->data[y * FIELD_WIDTH + FIELD_WIDTH - 1] = '#';
        }
    }

    // render snake
    int y = s->coords_xy[0];
    int x = s->coords_xy[1];
    d->data[y * FIELD_WIDTH + x] = 'O';
    for (int i = 1; i < s->len; i++) {
        int y = s->coords_xy[2 * i];
        int x = s->coords_xy[2 * i + 1];
        d->data[y * FIELD_WIDTH + x] = 's';
    }

    // render apple
}

void show(display* d) {
    for (int coord_x = 0; coord_x < FIELD_WIDTH; coord_x++) {
        for (int coord_y = 0; coord_y < FIELD_HEIGHT; coord_y++) {
            printf("%c", d->data[coord_y * FIELD_WIDTH + coord_x]);
        }
        printf("\n");
    }
}

int main() {
    const int init_snake_len = 5;
    int init_snake_coords[init_snake_len * 2] = {15, 15, 15, 16, 16, 16, 16, 17, 17, 16}; // in {(x, y), (x, y)} format 

    snake S;
    S.len = init_snake_len;
    memcpy(&S.coords_xy, init_snake_coords, init_snake_len * 2 * sizeof(int));
    field F;
    display D;
    apple A;
    int n = 0;
    
    while(1) {
        n++;
        if (n > 5) {
            break;
        }
        printf("n = %d\n", n);
        move_snake(&S, UP);
        render(&D, &S, &A, &F);
        show(&D);
        system("pause");
        // system("clear");
    }
    printf("NOW LEFT\n");
    n = 0;
    while(1) {
        n++;
        if (n > 3) {
            break;
        }
        printf("n = %d\n", n);
        move_snake(&S, LEFT);
        render(&D, &S, &A, &F);
        show(&D);
        // system("clear");
    }
    // move_snake(UP);
}