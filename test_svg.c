#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "svg.h"

#define assert_string(s1, s2)     { char* s=s1; assert(s != NULL); assert(strcmp(s, s2) == 0); }

void test_svg_new_node() {
    struct svg_node *node = svg_new_node("circle");
    assert(node != NULL);
    assert(node->tag != NULL);
    assert(strcmp(node->tag, "circle") == 0);

    assert(node->attrs == NULL);
    assert(node->parent == NULL);
    assert(node->next == NULL);

    printf("test_svg_new_node: pass\n");
}

void test_svg_new_document() {
    struct svg_document *doc = svg_new_document();
    assert(doc != NULL);
    assert(doc->root != NULL);

    printf("test_svg_new_document: pass\n");
}

void test_svg_insert_node() {
    struct svg_node *g = svg_new_node("g");
    struct svg_node *n1 = svg_new_node("circle");
    struct svg_node *n2 = svg_new_node("rectangle");

    svg_insert_node(g, n1);
    assert(svg_child_count(g) == 1);
    assert(g->children == n1);
    assert(n1->next == NULL);

    svg_insert_node(g, n2);
    assert(svg_child_count(g) == 2);
    assert(g->children == n1);
    assert(n1->next == n2);
    assert(n2->next == NULL);

    printf("test_svg_insert_node: pass\n");
}

void test_svg_set_attr() {
    struct svg_node *node = svg_new_node("circle");
    svg_set_attr(node, "x", "100");
    svg_set_attr(node, "y", "50");

    char *x = svg_get_attr(node, "x");
    assert_string(x, "100");

    char *y = svg_get_attr(node, "y");
    assert_string(y, "50");

    printf("test_svg_set_attr: pass\n");
}

void test_svg_set_attr_overwrite() {
    struct svg_node *node = svg_new_node("circle");
    svg_set_attr(node, "x", "100");
    svg_set_attr(node, "x", "50");

    char *x = svg_get_attr(node, "x");
    assert_string(x, "50");
    printf("test_svg_set_attr_overwrite: pass\n");
}

void test_svg_buffer_append() {
    struct svg_buffer *buf = svg_new_buffer(10);
    assert_string(buf->text, "");

    svg_buffer_append(buf, "hello");
    assert_string(buf->text, "hello");
    assert(buf->capacity == 10);

    svg_buffer_append(buf, "world");
    assert_string(buf->text, "helloworld");
    assert(buf->capacity == 20);
    printf("test_svg_buffer_append: pass\n");
}

void test_svg_render_document() {
    struct svg_document *doc = svg_new_document();
    struct svg_buffer *buf = svg_render_document(doc);
    assert_string(buf->text, "<svg></svg>");

    struct svg_node *node = svg_new_node("circle");
    svg_insert_node(doc->root, node);
    buf = svg_render_document(doc);
    assert_string(buf->text, "<svg><circle></circle></svg>");

    svg_set_attr(node, "x", "10");
    svg_set_attr(node, "y", "20");
    svg_set_attr(node, "r", "50");
    buf = svg_render_document(doc);
    assert_string(buf->text, "<svg><circle x=\"10\" y=\"20\" r=\"50\"></circle></svg>");

    printf("test_svg_render_document: pass\n");
}

int main() {
    test_svg_new_node();
    test_svg_new_document();
    test_svg_insert_node();
    test_svg_set_attr();
    test_svg_set_attr_overwrite();
    test_svg_buffer_append();
    test_svg_render_document();

    // struct svg_document *doc = svg_new_document();

    // struct svg_node *node = svg_new_node("circle");
    // svg_set_attr(node, "x", "0");
    // svg_set_attr(node, "y", "0");
    // svg_set_attr(node, "r", "100");
    // svg_set_attr(node, "stroke-width", "5");
    // svg_set_attr(node, "stroke", "red");
    // svg_set_attr(node, "fill", "yellow");

    // printf("doc %x\n", doc);

    // svg_insert_node(doc->root, node);

    // struct svg_buffer *buf = svg_render_document(doc);
    // //printf("%s\n", buf->text);

    // svg_free_document(doc);
    // svg_free_buffer(buf);
}