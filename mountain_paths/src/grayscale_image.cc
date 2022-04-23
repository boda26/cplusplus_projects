#include "grayscale_image.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

//const double kMax = 255.0;

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    width_ = dataset.Width();
    height_ = dataset.Height();
    //std::cout << dataset.MaxEle() << std::endl;
    //std::cout << dataset.MinEle() << std::endl;
    for (unsigned i = 0; i < height_; i++) {
        std::vector<Color> vec;
        for (unsigned j = 0; j < width_; j++) {
            if (dataset.MaxEle() == dataset.MinEle()) {
                Color c(0,0,0);
                vec.push_back(c);
            } else {
                //std::cout << dataset.MaxEle() - dataset.MinEle() << std::endl;
                double shade_of_gray = std::round((1.0 * dataset.DatumAt(i,j) - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
                int sd = floor(shade_of_gray);
                Color s(sd,sd,sd);
                vec.push_back(s);
            }
        }
        if (!vec.empty()) {
            image_.push_back(vec);
        }
    }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
    ElevationDataset dataset(filename, width, height);
    width_ = width;
    height_ = height;
    for (unsigned i = 0; i < height_; i++) {
        std::vector<Color> vec;
        for (unsigned j = 0; j < width_; j++) {
            if (dataset.MaxEle() == dataset.MinEle()) {
                Color c(0,0,0);
                vec.push_back(c);
            } else {
                double shade_of_gray = std::round((1.0 * dataset.DatumAt(i,j) - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
                int sd = floor(shade_of_gray);
                Color s(sd,sd,sd);
                vec.push_back(s);
            }
        }
        if (!vec.empty()) {
            image_.push_back(vec);
        }
    }
}

size_t GrayscaleImage::Width() const {
    return width_;
}

size_t GrayscaleImage::Height() const {
    return height_;
}

unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
    return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
    return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
    std::ofstream ofs{name};
    ofs << "P3";
    ofs << '\n';
    ofs << width_ << ' ' << height_ << '\n';
    ofs << kMaxColorValue << '\n';
    for (unsigned i = 0; i < height_; i++) {
        for (unsigned j = 0; j < width_; j++) {
            Color c = image_.at(i).at(j);
            ofs << c.Red() << ' ' << c.Green() << ' ' << c.Blue() << ' ';
        }
        ofs << '\n';
    }
}

