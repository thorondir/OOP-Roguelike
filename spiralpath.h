#ifndef SPIRALPATH_H_
#define SPIRALPATH_H_

#include <cmath>
#include <queue>
#include <utility>

class SpiralPathFOV {
    public:
        SpiralPathFOV(int, int, int, double, double);

        // calculate fov/lighting and write to a 2d array of bools
        std::vector<std::vector<bool>> SpiralPath(int, int);

        std::vector<std::vector<bool>> transparentmap_; // map of where light can pass
    private:
        int map_width_, map_height_, radius_;
        double arc_start_, arc_end_;
        std::pair<int, int> origin_; // coordinates of origin
        std::queue<std::pair<int, int>> queue_; // queue of coordinates
        std::vector<std::vector<bool>> map_; // map of bools
        std::vector<std::vector<std::pair<double, double>>> lightmap_; // min and max angles for every square
        std::vector<std::vector<double>> geometrymap_; // every square's angle to the origin

        double CoordAngle(std::pair<int, int>);
        double MinAngle(std::pair<int, int>);
        double MaxAngle(std::pair<int, int>);
        double OuterAngle(std::pair<int, int>);
        double OuterAngle2(std::pair<int, int>);

        double CoordAngle(int, int);
        double MinAngle(int, int);
        double MaxAngle(int, int);

        double Distance(std::pair<int, int>, std::pair<int, int>);
        bool InArc(std::pair<int, int>);

        double NormaliseAngle(double);

        std::pair<int, int> Child1(std::pair<int, int>);
        std::pair<int, int> Child2(std::pair<int, int>);
        std::pair<int, int> Child3(std::pair<int, int>);

        void TestMark(std::pair<int, int>, double, double, double, double);
        void Mark(std::pair<int, int>, double, double);
        std::pair<int, int> Dequeue();
};

#endif
