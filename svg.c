#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"

#ifdef DEBUG
#define debug(...) printf("  " __VA_ARGS__)
#else
#define debug(...)
#endif

struct svg_buffer * svg_new_buffer();

// Creates a new svg_document
// The caller must free this by calling free_svg_document function.
struct svg_document* svg_new_document() {
    debug("svg_new_document\n");

    struct svg_document *doc = (struct svg_document *)malloc(sizeof(struct svg_document));
    doc->root = svg_new_node("svg");
    debug(".. allocated: %x\n", doc);
    return doc;
}

// Creates a new svg node of given tag.
// If the node is added to a document, then it will be freed when
// the document is freed, otherwise it must be freed by calling
// svg_free_node function.
struct svg_node* svg_new_node(char *tag) {
    struct svg_node *node = (struct svg_node *)malloc(sizeof(struct svg_node));
    node->tag = tag;
    node->attrs = NULL;
    node->parent = NULL;
    node->next = NULL;
    return node;
}

// creates a new attribute
struct svg_attr* svg_new_attr(char *attr_name, char *attr_value) {
    struct svg_attr *attr = (struct svg_attr *)malloc(sizeof(struct svg_attr));
    attr->attr_name = attr_name;
    attr->attr_value = attr_value;
    attr->next = NULL;
    return attr;
}


// renders the svg document as text.
// returns an svg_buffer, the caller must free it by calling
// svg_free_buffer function.
struct svg_buffer* svg_render_document(struct svg_document *doc) {
    debug("svg_render_document: %x\n", doc);
    return svg_new_buffer();
}

// Inserts a new node as the last child of the parent node
void svg_insert_node(struct svg_node *parent, struct svg_node *node) {
    if (parent->children == NULL) {
        parent->children = node;
    }
    else {
        struct svg_node *n = parent->children;
        while (n->next) {
            n = n->next;
        }
        n->next = node;
    }
    node->parent = parent;
    node->next = NULL;

    debug("svg_insert_node: %x %x\n", parent, node);
}

void svg_set_attr(struct svg_node *node, char *attr_name, char *attr_value) {
    if (node->attrs == NULL) {
        node->attrs = svg_new_attr(attr_name, attr_value);
    }
    else {
        struct svg_attr *attr = node->attrs;
        while (attr) {
            if (attr->attr_name == attr_name) {
                attr->attr_value = attr_value;
                return;
            }
            if (attr->next == NULL) {
                attr->next = svg_new_attr(attr_name, attr_value);
                return;
            }
            attr = attr->next;
        }
    }
    debug("svg_setattr: %x %s=%s\n", node, attr_name, attr_value);
}

char * svg_get_attr(struct svg_node *node, char *attr_name) {
    debug("svg_get_attr: %x %s\n", node, attr_name);
    if (node->attrs == NULL) {
        return NULL;
    }
    else {
        for (struct svg_attr *attr = node->attrs; attr; attr=attr->next) {
            if (strcmp(attr->attr_name, attr_name) == 0)
                return attr->attr_value;
        }
        return NULL;
    }
}

// Frees an svg node and all its children
void svg_free_node(struct svg_node *node) {
    // TODO:
    debug("svg_free_node: %x\n", node);
}

// frees an svg document and all the nodes added to it
void svg_free_document(struct svg_document *doc) {
    // TODO:
    debug("svg_free_document: %x\n", doc);
}

struct svg_buffer * svg_new_buffer() {
    debug("svg_new_buffer()\n");
    struct svg_buffer *buf = (struct svg_buffer *)malloc(sizeof(struct svg_buffer));
    buf->size = 0;
    buf->capacity = 0;
    buf->text = "";
    return buf;
}

// frees an svg_buffer
void svg_free_buffer(struct svg_buffer *buf) {
    debug("svg_free_buffer(%x)\n", buf);
}

int svg_child_count(struct svg_node *node) {
    struct svg_node *child = node->children;
    int count = 0;

    while (child) {
        count++;
        child = child->next;
    }
    return count;
}