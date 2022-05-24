# c-joy: Joy in C

[Joy][] is a simple and elegant creative coding library. This is a port of Joy into C programming language.

[Joy]: https://github.com/anandology/joy

## API

Here is how you draw a circle.

```
#include "joy.h"

int main() {
    shape c = circle(0, 0, 100);
    show(c);
}
```

Checkout the [Proposed API][1] to know more.

[1]: https://github.com/anandology/c-joy/issues/1

You can also look at the live preview at:
<https://sandbox.anandology.com/joy/>