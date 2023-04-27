#ifndef __ARTIST_HPP__
#define __ARTIST_HPP__

#include <vector>
using namespace std;

// The artist class serves as a base class for various image processing styles
// It represents an abstract concept of an "artist" that manipulates images in different ways
class artist {
private:
    // Image dimensions and pixel values are stored as private members
    int width;
    int height;
    vector<int> vals;

protected:
    // Protected method for derived classes to access the pixel value at a specified index
    int get_pixel(int) const;

public:
    // Constructor initializes the artist object with image dimensions and pixel values
    artist(int, int, const vector<int>&);

    ~artist();

    // Public methods for accessing image dimensions
    int get_width(void) const;
    int get_height(void) const;

    // Pure virtual function for mapping coordinates to output characters
    // This function must be overridden by derived classes to implement specific styles
    virtual char mapper(int, int) = 0;
};

// Derived classes for different image processing styles
class classic : public artist {
public:
    classic(int, int, const vector<int>&);
    char mapper(int, int) override;
};

class iclassic : public artist {
public:
    iclassic(int, int, const vector<int>&);
    char mapper(int, int) override;
};

class sobelx : public artist {
public:
    sobelx(int, int, const vector<int>&);
    char mapper(int, int) override;
};

class sobely : public artist {
public:
    sobely(int, int, const vector<int>&);
    char mapper(int, int) override;
};

class gradient : public artist {
public:
    gradient(int, int, const vector<int>&);
    char mapper(int, int) override;
};

class sobeldiag : public artist {
public:
    sobeldiag(int, int, const vector<int>&);
    char mapper(int, int) override;
};
#endif // !__ARTIST_HPP__