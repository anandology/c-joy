# c-joy: Joy in C

[Joy][] is a simple and elegant creative coding library. This is a port of Joy into C programming language.

[Joy]: https://github.com/anandology/joy

## API

Shape c;

c = cirlce(10, 10, 20);
c.strokeWidth = 5;
c.stroke = "red";
c.fill = "blue";

show(c);

//

Shape c;

c = apply(c, rotate(40))
c = apply(c, repeat(4, rotate(40)))

rotate(c, 40)
repeat(c, 4, rotate(40))

