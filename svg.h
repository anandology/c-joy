#ifndef _SVG_H_
#define _SVG_H_

#define SVGNODE_CIRCLE "circle"
#define SVGNODE_RECT "rect"

struct svg_attr {
    char *attr_name;
    char *attr_value;
    struct svg_attr *next;
};

struct svg_node {
    char *tag;
    struct svg_attr *attrs;
    struct svg_node *parent;
    struct svg_node *children;
    struct svg_node *next;
};

struct svg_document {
    struct svg_node *root;
};

struct svg_buffer {
    int capacity;
    int size;
    char *text;
};

// Creates a new svg_document
// The caller must free this by calling free_svg_document function.
struct svg_document* svg_new_document();

// Creates a new svg node of given tag.
// If the node is added to a document, then it will be freed when
// the document is freed, otherwise it must be freed by calling
// svg_free_node function.
struct svg_node* svg_new_node(char *tag);

// renders the svg document as text.
// returns an svg_buffer, the caller must free it by calling
// svg_free_buffer function.
struct svg_buffer* svg_render_document(struct svg_document *doc);

// Inserts a new node as the last child of the parent node
void svg_insert_node(struct svg_node *parent, struct svg_node *node);

void svg_set_attr(struct svg_node *node, char *attr_name, char *attr_value);
char * svg_get_attr(struct svg_node *node, char *attr_name);

// Frees an svg node and all its children
void svg_free_node(struct svg_node *node);

// frees an svg document and all the nodes added to it
void svg_free_document(struct svg_document *doc);

// frees an svg_buffer
void svg_free_buffer(struct svg_buffer *buf);

int svg_child_count(struct svg_node *node);

#endif