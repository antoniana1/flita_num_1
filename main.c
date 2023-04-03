#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int64_t data;
    struct node_t *next;
} node;

node *new_node(int64_t data) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

node *add_node(node *cur_node, int64_t data) {
    node *new_node_t = new_node(data);
    new_node_t->next = cur_node;
    return new_node_t;
}

uint8_t dec2bin_rec(char *str, uint64_t num) {
    if (num == 0)
        return 0;
    uint8_t pos = dec2bin_rec(str, num / 2);
    str[pos] = num % 2 + '0';
    return pos + 1;
}

char *dec2bin(uint64_t num) {
    char *result = (char *)malloc(65 * sizeof(char));
    uint8_t pos_0 = dec2bin_rec(result, num);
    if (!pos_0) result[pos_0++] = '0';
    result[pos_0] = '\0';
    return result;
}

void print_rec(node *cur_node) {
    if (cur_node == NULL)
        return;
    print_rec(cur_node->next);
    char *binary_str = dec2bin(cur_node->data);
    printf("%ld in dec == %s in bin\n", cur_node->data, binary_str);
    free(binary_str);
}

int64_t del_node(node *cur_node) {
    int64_t delete_data = cur_node->data;
    free(cur_node);
    return delete_data;
}

void del_nodes(node *cur_node) {
    if (cur_node == NULL)
        return;
    del_nodes(cur_node->next);
    del_node(cur_node);
}

int main(void) {
    bool is_exit = true, is_error;
    node *list = NULL;
    int64_t temp;
    char command;
    while (is_exit) {
        printf("Input unsigned digit: ");
        while (scanf("%ld", &temp) != 1) {
            printf("ERROR: Not valid input. Input unsigned digit: ");
            while (getchar() != '\n');
        }
        list = add_node(list, temp);
        printf("Will u continue? (y/n): ");

        do {
            is_error = false;
            while (getchar() != '\n');
            command = getchar();
            switch (command) {
                case 'N':
                case 'n':
                    is_exit = false;
                case 'Y':
                case 'y':
                case '\n':
                    break;
                default:
                    is_error = true;
            }
            if (is_error)
                printf("ERROR: Not valid input. Will u continue? (y/n): ");
        } while (is_error);
    }
    print_rec(list);
    del_nodes(list);
    return 0;
}