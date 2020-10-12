// spiral path fov based on http://www.roguebasin.com/index.php?title=Spiral_Path_FOV
#include "spiralpath.h"

// Spiral Path FOV Constructor
SpiralPathFOV::SpiralPathFOV(int map_height, int map_width,
        int radius, double arc_start, double arc_end) {
    map_height_ = map_height;
    map_width_ = map_width;
    radius_ = radius;
    arc_start_ = arc_start;
    arc_end_ = arc_end;

    // resize the map
    map_.resize(map_height+1);
    transparentmap_.resize(map_height+1);
    lightmap_.resize(map_height);
    geometrymap_.resize(map_height);
    for (int y = 0; y < map_height_; y++) {
        map_[y].resize(map_width_);
        transparentmap_[y].resize(map_width_);
        lightmap_[y].resize(map_width_);
        geometrymap_[y].resize(map_width_);
    }
}

// Get the distance between two points
double SpiralPathFOV::Distance(std::pair<int, int> p1, std::pair<int, int> p2) {
    return sqrt(pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2));
}

double SpiralPathFOV::CoordAngle(int y, int x) {
    // should take values from geometrymap_
    if ((0 <= y && y < map_height_) && (0 <= x && x < map_width_)) {
        return geometrymap_[y][x];
    }
    else return 0.0;
}

// Normalise angle between 0 and 2*PI
double SpiralPathFOV::NormaliseAngle(double angle) {
    while (angle < 0.0) {
        angle += 2*M_PI;
    }
    while (angle > 2*M_PI) {
        angle -= 2*M_PI;
    }
    return angle;
}

// Get the smallest angle to a square, from the centre of the origin
double SpiralPathFOV::MinAngle(int y, int x) {
    if (y == origin_.first && x == origin_.second) {
        return 0.0;
    } else if (y > origin_.first && x >= origin_.second) { // quadrant 1
        return CoordAngle(y, x+1);
    } else if (y >= origin_.first && x < origin_.second) { // quadrant 2
        return CoordAngle(y+1, x+1);
    } else if (y < origin_.first && x <= origin_.second) { // quadrant 3
        return CoordAngle(y+1, x);
    } else {
        return CoordAngle(y, x);
    }
}

double SpiralPathFOV::MinAngle(std::pair<int, int> coordinates) {
    return MinAngle(coordinates.first, coordinates.second);
}

// Get the largest angle to a square, from the centre of the origin
double SpiralPathFOV::MaxAngle(int y, int x) {
    if (y == origin_.first && x == origin_.second) {
        return 2*M_PI;
    } else if (y >= origin_.first && x > origin_.second) { // quadrant 1
        return CoordAngle(y+1, x);
    } else if (y > origin_.first && x <= origin_.second) { // quadrant 2
        return CoordAngle(y, x);
    } else if (y <= origin_.first && x < origin_.second) { // quadrant 3
        return CoordAngle(y, x+1);
    } else {
        return CoordAngle(y+1, x+1);
    }
}

double SpiralPathFOV::MaxAngle(std::pair<int, int> coordinates) {
    return MaxAngle(coordinates.first, coordinates.second);
}

double SpiralPathFOV::OuterAngle(std::pair<int, int> coordinates) {
    int y = coordinates.first;
    int x = coordinates.second;
    if (y == origin_.first && x == origin_.second) {
        return 0.0;
    } else if (y > origin_.first && x >= origin_.second) { // quadrant 1
        return CoordAngle(y+1, x+1);
    } else if (y >= origin_.first && x < origin_.second) { // quadrant 2
        return CoordAngle(y+1, x);
    } else if (y < origin_.first && x <= origin_.second) { // quadrant 3
        return CoordAngle(y, x);
    } else {
        return CoordAngle(y, x+1);
    }
}

double SpiralPathFOV::OuterAngle2(std::pair<int, int> coordinates) {
    int y = coordinates.first;
    int x = coordinates.second;
    // there's no need for a second outer angle on non axis squares
    if (y != origin_.first && x != origin_.second) {
        return 0.0;
    } else if (x > origin_.second) { // east
        return CoordAngle(y+1, x+1);
    } else if (y < origin_.first) { // north
        return CoordAngle(y+1, x);
    } else if (x < origin_.second) { // west
        return CoordAngle(y, x);
    } else if (y > origin_.first) { // south
        return CoordAngle(y+1, x);
    } else {
        return 0.0; // origin
    }
}

// check if square is within arc
bool SpiralPathFOV::InArc(std::pair<int, int> coordinates) {
    int y = coordinates.first;
    int x = coordinates.second;
    if (arc_start_ > arc_end_) { // arc includes anomaly line
        return (MinAngle(y, x) < arc_start_ ||
                MaxAngle(y, x) < arc_start_ ||
                MinAngle(y, x) > arc_end_ ||
                MaxAngle(y, x) > arc_end_);
    } else {
        return (MaxAngle(y, x) > arc_start_ || MinAngle(y, x) < arc_end_);
    }
}

std::pair<int, int> SpiralPathFOV::Child1(std::pair<int, int> coordinates) {
    int y = coordinates.first;
    int x = coordinates.second;

    if (coordinates == origin_) { // origin
        return coordinates;
    } else if (y > origin_.first && x >= origin_.second) { // quadrant 1
        return std::make_pair(y, x + 1);
    } else if (y >= origin_.first && x < origin_.second) { // quadrant 2
        return std::make_pair(y + 1, x);
    } else if (y < origin_.first && x <= origin_.second) { // quadrant 3
        return std::make_pair(y, x - 1);
    } else { // quadrant 4
        return std::make_pair(y - 1, x);
    }
}

std::pair<int, int> SpiralPathFOV::Child2(std::pair<int, int> coordinates) {
    int y = coordinates.first;
    int x = coordinates.second;

    if (coordinates == origin_) { // origin
        return coordinates;
    } else if (y > origin_.first && x >= origin_.second) { // quadrant 1
        return std::make_pair(y + 1, x);
    } else if (y >= origin_.first && x < origin_.second) { // quadrant 2
        return std::make_pair(y, x - 1);
    } else if (y < origin_.first && x <= origin_.second) { // quadrant 3
        return std::make_pair(y - 1, x);
    } else { // quadrant 4
        return std::make_pair(y, x + 1);
    }
}

std::pair<int, int> SpiralPathFOV::Child3(std::pair<int, int> coordinates) {
    int y = coordinates.first;
    int x = coordinates.second;
    
    if (y != origin_.first && x != origin_.second) { // non-axis
        return origin_;
    } else if (x > origin_.second) { // east
        return std::make_pair(y + 1, x);
    } else if (y > origin_.first) { // south
        return std::make_pair(y, x - 1);
    } else if (x < origin_.second) { // west
        return std::make_pair(y - 1, x);
    } else if (y < origin_.first) { // north
        return std::make_pair(y, x + 1);
    }
    return origin_; // if input was origin
}

// add light to square, and add square to queue if necessary
void SpiralPathFOV::Mark(std::pair<int, int> coordinates, double min_angle, double max_angle) {
    std::pair<double, double> already_lit = lightmap_[coordinates.first][coordinates.second];
    if (already_lit.first == 0.0 && already_lit.second == 0.0) { // not yet in queue
        queue_.push(coordinates);
        lightmap_[coordinates.first][coordinates.second] = std::make_pair(min_angle, max_angle);
    } else {
        if (min_angle < already_lit.first) {
            lightmap_[coordinates.first][coordinates.second].first = min_angle;
        }
        if (max_angle > already_lit.second) {
            lightmap_[coordinates.first][coordinates.second].second = max_angle;
        }
    }
}

// try to add light to square
void SpiralPathFOV::TestMark(std::pair<int, int> coordinates,
        double smallest_lit_angle, double largest_lit_angle,
        double min_lightable_angle, double max_lightable_angle) {

    if (smallest_lit_angle > largest_lit_angle) { // lit angle along anomaly
        // only happens along axis
        Mark(coordinates, min_lightable_angle, max_lightable_angle);
    } else if (max_lightable_angle < smallest_lit_angle || min_lightable_angle > largest_lit_angle) {
        // lightable area is outside of light
        return;
    } else if (min_lightable_angle <= smallest_lit_angle && largest_lit_angle <= max_lightable_angle) {
        // light falls within lightable area
        Mark(coordinates, smallest_lit_angle, largest_lit_angle);
    } else if (min_lightable_angle >= smallest_lit_angle && max_lightable_angle <= largest_lit_angle) {
        // lightable area falls within light
        Mark(coordinates, min_lightable_angle, max_lightable_angle);
    } else if (min_lightable_angle >= smallest_lit_angle && largest_lit_angle <= max_lightable_angle) {
        // least of the lightable area instersects the light
        Mark(coordinates, min_lightable_angle, largest_lit_angle);
    } else if (min_lightable_angle <= smallest_lit_angle && largest_lit_angle >= max_lightable_angle) {
        // greatest of the lightable area intersects the light
        Mark(coordinates, smallest_lit_angle, max_lightable_angle);
    } else { // this shouldn't happen
        // throw some kind of debug error!
        return;
    }
}

// Dequeue the square at the top of the queue
std::pair<int, int> SpiralPathFOV::Dequeue() {

    // get and remove the coord pair at the top of the queue
    std::pair<int, int> current_coordinates = queue_.front();
    queue_.pop();

    //test mark children
    if (Distance(origin_, current_coordinates) <= radius_ && InArc(current_coordinates)){
        // mark those coordinates seen/visible/lit
        double smallest_lit_angle = lightmap_[current_coordinates.first][current_coordinates.second].first;
        double largest_lit_angle = lightmap_[current_coordinates.first][current_coordinates.second].second;
        double min_lightable_angle = MinAngle(current_coordinates);
        double outer_angle = OuterAngle(current_coordinates);
        double outer_angle2 = OuterAngle2(current_coordinates);
        double max_lightable_angle = MaxAngle(current_coordinates);

        map_[current_coordinates.first][current_coordinates.second] = true;
        
        std::pair<int, int> child_coords;

        if (transparentmap_[current_coordinates.first][current_coordinates.second]) {
            child_coords = Child1(current_coordinates);
            if (child_coords.first >= 0 && child_coords.first < map_height_ &&
                    child_coords.second >= 0 && child_coords.second < map_width_){
                TestMark(child_coords, smallest_lit_angle, largest_lit_angle, min_lightable_angle, outer_angle);
            }
            if (outer_angle2 != 0.0) {
                child_coords = Child2(current_coordinates);
                if (child_coords.first >= 0 && child_coords.first < map_height_ &&
                        child_coords.second >= 0 && child_coords.second < map_width_){
                    TestMark(child_coords, smallest_lit_angle, largest_lit_angle, outer_angle, outer_angle2);
                }
                child_coords = Child3(current_coordinates);
                if (child_coords.first >= 0 && child_coords.first < map_height_ &&
                        child_coords.second >= 0 && child_coords.second < map_width_){
                    TestMark(child_coords, smallest_lit_angle, largest_lit_angle, outer_angle2, max_lightable_angle);
                }
            } else {
                child_coords = Child2(current_coordinates);
                if (child_coords.first >= 0 && child_coords.first < map_height_ &&
                        child_coords.second >= 0 && child_coords.second < map_width_){
                    TestMark(child_coords, smallest_lit_angle, largest_lit_angle, outer_angle, max_lightable_angle);
                }
            }
        } else { // opaque, check for corner
            if (smallest_lit_angle == min_lightable_angle) {
                child_coords = Child1(current_coordinates);
                if (child_coords.first >= 0 && child_coords.first < map_height_ &&
                        child_coords.second >= 0 && child_coords.second < map_width_){
                    Mark(child_coords, smallest_lit_angle, smallest_lit_angle);
                }
            }
        }
    }
    
    return current_coordinates;
}

// calculate the spiral path
std::vector<std::vector<bool>> SpiralPathFOV::SpiralPath(int y, int x) {
    origin_ = std::make_pair(y, x);
    std::pair<int, int> current_coordinates = origin_;

    for (int i = 0; i < map_height_; i++) {
        for (int j = 0; j < map_width_; j++) {
            // initialise light angles all to 0
            lightmap_[i][j] = std::make_pair(0.0, 0.0);
            // initialise all squares to be invisible
            map_[i][j] = false;
            // create map of angles to the middle of the origin square
            geometrymap_[i][j] = NormaliseAngle(
                    atan2(i-(origin_.first + 0.5),j-(origin_.second + 0.5)));
        }
    }

    // set the origin to lit/seen
    map_[current_coordinates.first][current_coordinates.second] = true;

    // add the first 4 squares to the spiral
    // east
    TestMark(std::make_pair(current_coordinates.first, current_coordinates.second + 1),
            arc_start_, arc_end_,
            MinAngle(current_coordinates.first, current_coordinates.second + 1),
            MaxAngle(current_coordinates.first, current_coordinates.second + 1));
    //south
    TestMark(std::make_pair(current_coordinates.first + 1, current_coordinates.second),
            arc_start_, arc_end_,
            MinAngle(current_coordinates.first + 1, current_coordinates.second),
            MaxAngle(current_coordinates.first + 1, current_coordinates.second));
    // west
    TestMark(std::make_pair(current_coordinates.first, current_coordinates.second - 1),
            arc_start_, arc_end_,
            MinAngle(current_coordinates.first, current_coordinates.second - 1),
            MaxAngle(current_coordinates.first, current_coordinates.second - 1));
    // north
    TestMark(std::make_pair(current_coordinates.first- 1, current_coordinates.second),
            arc_start_, arc_end_,
            MinAngle(current_coordinates.first - 1, current_coordinates.second),
            MaxAngle(current_coordinates.first - 1, current_coordinates.second));

    // loop until the queue is exhausted
    while (queue_.size() > 0) {
        // get the coordinates at the front of the queue
        current_coordinates = Dequeue();
    }
    return map_;
}
