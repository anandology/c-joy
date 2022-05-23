#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"

#ifdef DEBUG
#define debug(...) printf("  " __VA_ARGS__)
#else
#define debug(...)
#endif

// Creates a new svg_document
// The caller must free this by calling free_svg_document function.
struct svg_document* svg_new_document() {
    debug("svg_new_document\n");

    struct svg_document *doc = (struct svg_document *)malloc(sizeof(struct svg_document));
    doc->root = svg_new_node("svg");
    svg_set_attr(doc->root, "xmlns", "http://www.w3.org/2000/svg");
    svg_set_attr(doc->root, "xmlns:xlink", "http://www.w3.org/1999/xlink");

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

void buffer_write2(struct svg_buffer *buf, char* s1, char *s2) {
    svg_buffer_append(buf, s1);
    svg_buffer_append(buf, s2);
}

void buffer_write3(struct svg_buffer *buf, char* s1, char *s2, char *s3) {
    svg_buffer_append(buf, s1);
    svg_buffer_append(buf, s2);
    svg_buffer_append(buf, s3);
}
void buffer_write6(
        struct svg_buffer *buf,
        char* s1, char *s2, char *s3,
        char* s4, char *s5, char *s6) {
    svg_buffer_append(buf, s1);
    svg_buffer_append(buf, s2);
    svg_buffer_append(buf, s3);
    svg_buffer_append(buf, s4);
    svg_buffer_append(buf, s5);
    svg_buffer_append(buf, s6);
}


void write_node(struct svg_buffer *buf, struct svg_node *node) {
    debug("write_node %s %x\n", node->tag, node->children);
    buffer_write2(buf, "<", node->tag);
    if (node->attrs) {
        for (struct svg_attr *a=node->attrs; a != NULL; a=a->next){
            buffer_write6(buf, " ", a->attr_name, "=", "\"", a->attr_value, "\"");
        }
    }
    svg_buffer_append(buf, ">");
    for (struct svg_node *c=node->children; c != NULL; c=c->next) {
        write_node(buf, c);
    }
    buffer_write3(buf, "</", node->tag, ">");
}

// renders the svg document as text.
// returns an svg_buffer, the caller must free it by calling
// svg_free_buffer function.
struct svg_buffer* svg_render_document(struct svg_document *doc) {
    debug("svg_render_document: %x\n", doc);
    struct svg_buffer *buf = svg_new_buffer(10);
    write_node(buf, doc->root);
    return buf;
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

struct svg_buffer * svg_new_buffer(int capacity) {
    debug("svg_new_buffer(%d)\n", capacity);
    struct svg_buffer *buf = (struct svg_buffer *)malloc(sizeof(struct svg_buffer));
    buf->size = 1;
    buf->capacity = capacity;
    buf->text = (char *)malloc(capacity * sizeof(char));
    buf->text[0] = '\0';
    return buf;
}

int max(int a, int b) {
    return a > b? a: b;
}

void svg_buffer_append(struct svg_buffer *buf, char *s) {
    // debug("svg_buffer_append %x %s\n", buf, s);

    int n = strlen(s);
    if (buf->size+n > buf->capacity) {
        buf->capacity = max(2*buf->capacity, buf->size+n);
        buf->text = (char *)realloc(buf->text, buf->capacity);
    }
    char *start = buf->text+ buf->size - 1;
    strcpy(start, s);
    buf->size += n;
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