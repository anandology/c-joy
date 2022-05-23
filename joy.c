#include <stdio.h>
#include <stdlib.h>

#include "joy.h"
#include "svg.h"

char * SHAPE_TAGS[] = {
    "circle",
    "rect",
    "g"
};


shape new_shape(int type) {
    shape s;
    s.type = type;
    s.x = 0;
    s.y = 0;
    s.r = 0;
    s.w = 0;
    s.h = 0;
    s.stroke_width = -1;
    s.stroke = NULL;
    s.fill = NULL;
    return s;
}

shape circle(float x, float y, float r) {
    shape s = new_shape(SHAPE_CIRCLE);
    s.x = x;
    s.y = y;
    s.r = r;
    return s;
}

shape rectangle(float x, float y, float w, float h) {
    shape s = new_shape(SHAPE_RECTANGLE);
    s.x = x;
    s.y = y;
    s.w = w;
    s.h = h;
    return s;
}


char * float_to_string(float f) {
    // TODO: fix me
    char *s = (char *)malloc(sizeof(char)*100);
    sprintf(s, "%f", f);
    return s;
}

void show(shape s) {
    struct svg_document *doc = svg_new_document();
    svg_set_attr(doc->root, "width", "300");
    svg_set_attr(doc->root, "height", "300");
    svg_set_attr(doc->root, "viewBox", "-150 -150 300 300");
    svg_set_attr(doc->root, "fill", "none");
    svg_set_attr(doc->root, "stroke", "black");

    struct svg_node *node = svg_new_node(SHAPE_TAGS[s.type]);

    switch (s.type) {
        case SHAPE_CIRCLE:
            svg_set_attr(node, "x", float_to_string(s.x));
            svg_set_attr(node, "y", float_to_string(s.y));
            svg_set_attr(node, "r", float_to_string(s.r));
            break;
        case SHAPE_RECTANGLE:
            svg_set_attr(node, "x", float_to_string(s.x-s.w/2));
            svg_set_attr(node, "y", float_to_string(s.y+s.h/2));
            svg_set_attr(node, "width", float_to_string(s.w));
            svg_set_attr(node, "height", float_to_string(s.h));
            break;
        case SHAPE_GROUP:
            break;
    }
    if (s.stroke_width != -1)
        svg_set_attr(node, "stroke-width", float_to_string(s.stroke_width));
    if (s.stroke != NULL)
        svg_set_attr(node, "stroke", s.stroke);
    if (s.fill != NULL)
        svg_set_attr(node, "fill", s.fill);

    svg_insert_node(doc->root, node);

    struct svg_buffer *buf = svg_render_document(doc);
    printf("%s\n", buf->text);

    svg_free_buffer(buf);
    svg_free_document(doc);
}

