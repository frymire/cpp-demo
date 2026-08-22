
#include <iostream>
using std::cout;
using std::endl;

#include <array>
using std::array;

#include <vector>
using std::vector;

namespace
{
    class Vertex
    {
        int m_x, m_y, m_z;

    public:

        Vertex(int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}
        Vertex(const Vertex& other) : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z) { cout << "Copied a vertex.\n"; }
        Vertex(Vertex&& other) = default;
        Vertex& operator=(const Vertex& other) = default;
        Vertex& operator=(Vertex&& other) = default;
        ~Vertex() = default;

        void print() const { cout << m_x << " " << m_y << " " << m_z << "\n"; }
    };


} // namespace

int main()
{
    vector<Vertex> vertices;
    vertices.reserve(3);
    vertices.emplace_back(1, 2, 3);
    vertices.emplace_back(4, 5, 6);
    vertices.emplace_back(7, 8, 9);

    vertices[2] = Vertex(9, 8, 7);

    vertices.erase(vertices.begin() + 1);

    for (const Vertex& v: vertices) { v.print(); }
    return 0;
}
