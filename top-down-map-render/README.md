# top-down-map-render

Just a little C++ codebase written on my mac that will draw a map and a player in the map.

Maps are just lines based off a beginning and ending vertex.

## Dependencies
- SDL3

## Map format

First line is in integer that contains the number of walls. Rows following contain wall data. The rows are formatted in the following way:

```
src.X srx.Y dst.X dst.Y
```

Example of a file:

```
2
5 5 10 5
5 10 10 10
```

The above line has 2 walls. The first line starts at  (5, 5) and ends at (10, 5). The following wall starts at (5, 10) and ends at (10, 10);
