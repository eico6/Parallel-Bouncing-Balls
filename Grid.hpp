#pragma once
#include "Ball.hpp"
#include <unordered_map>
#include <vector>
#include <cmath>

struct CellKey {
    int x, y;
    bool operator==(const CellKey& o) const { return x == o.x && y == o.y; }
};

struct CellKeyHash {
    std::size_t operator()(const CellKey& k) const {
        return std::hash<long long>()(((long long)k.x << 32) ^ (unsigned int)k.y);
    }
};

struct Rect {
    double x, y, width, height;
    double getX()    const { return x; }
    double getY()    const { return y; }
    double getWidth()  const { return width; }
    double getHeight() const { return height; }
    double getMaxX() const { return x + width; }
    double getMaxY() const { return y + height; }
};

class Grid {
public:
    const double cellWidth, cellHeight;

    Grid(double cellWidth, double cellHeight)
        : cellWidth(cellWidth), cellHeight(cellHeight) {}

    // Returns all cell keys covered by rectangle r
    std::vector<CellKey> getCells(const Rect& r) const {
        int x1 = (int)std::floor(r.getX()    / cellWidth);
        int y1 = (int)std::floor(r.getY()    / cellHeight);
        int x2 = (int)std::ceil (r.getMaxX() / cellWidth);
        int y2 = (int)std::ceil (r.getMaxY() / cellHeight);

        std::vector<CellKey> cells;
        for (int x = x1; x < x2; x++)
            for (int y = y1; y < y2; y++)
                cells.push_back({x, y});
        return cells;
    }

    std::vector<Ball*>* get(const CellKey& cell) {
        auto it = data.find(cell);
        return it != data.end() ? &it->second : nullptr;
    }

    std::vector<Ball*>& getOrDefault(const CellKey& cell, std::vector<Ball*>& defaultValue) {
        auto it = data.find(cell);
        return it != data.end() ? it->second : defaultValue;
    }

    void set(const CellKey& cell, std::vector<Ball*> val) {
        data[cell] = std::move(val);
    }

    void clear() { data.clear(); }

    auto begin() { return data.begin(); }
    auto end()   { return data.end(); }
    auto begin() const { return data.cbegin(); }
    auto end()   const { return data.cend(); }

    std::vector<CellKey> cells() const {
        std::vector<CellKey> keys;
        keys.reserve(data.size());
        for (auto& kv : data) keys.push_back(kv.first);
        return keys;
    }

    template<typename Fn>
    void forEach(Fn fn) {
        for (auto& kv : data) fn(kv.second);
    }

private:
    std::unordered_map<CellKey, std::vector<Ball*>, CellKeyHash> data;
};
