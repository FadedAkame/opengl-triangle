#pragma once

namespace gl {

template <typename T>
struct Point3D {
    T x, y, z;
};
template <typename T>
struct ColorRGB {
    T r, g, b;
};

template <typename T>
struct Vertex {
    Point3D<T> position;
    ColorRGB<T> color;
};

}
