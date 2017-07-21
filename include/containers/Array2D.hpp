#pragma once

#include <memory>

namespace containers
{
    template<typename T>
    class Array2D
    {
        private:
            std::unique_ptr<T[]> data;
            int nx, ny;

        public:
            Array2D(int nx_, int ny_)
            : data(new T[nx_*ny_]), nx(nx_), ny(ny_)
            {
            };

            void set(T t, int x, int y)
            {
                data[x*nx + y] = t;
            }

            T get(int x, int y)
            {
                return data[x*nx + y];
            }

    };
}