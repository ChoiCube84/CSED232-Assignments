#ifndef __DRAWER_HPP__
#define __DRAWER_HPP__

#include <string>
#include "artist.hpp"

// The drawer class serves as a base class for various image transformation operations
// It represents an abstract concept of a "drawer" that applies transformations using a specific artist style
class drawer
{
private:
    // A pointer to an artist object representing the style used for the transformation
    artist* style;

protected:
    // Protected method for derived classes to access the style
    artist* get_style(void) const;

public:
    // Constructor initializes the drawer object with a specific artist style
    drawer(artist*);

    // Virtual function for applying the transformation and generating the output
    // Derived classes must override this function to implement specific operations
    virtual string draw(void);
};

// Derived classes for different image transformation operations
class downsample : public drawer
{
public:
    downsample(artist*);
    string draw(void) override;
};

class upsample : public drawer
{
public:
    upsample(artist*);
    string draw(void) override;
};

class scale : public drawer
{
private:
    // Scaling factors for x and y dimensions
    int x, y;

public:
    scale(artist*, int, int);
    string draw(void) override;
};

#endif // !__DRAWER_HPP__
