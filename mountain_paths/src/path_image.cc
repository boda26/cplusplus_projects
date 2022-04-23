#include "path_image.hpp"
#include <iostream>
#include <fstream>

const int kRedRed = 252;
const int kRedGreen = 25;
const int kRedBlue = 63;
const int kGreenRed = 31;
const int kGreenGreen = 253;
const int kGreenBlue = 13;


PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) {
    width_ = image.Width();height_ = image.Height();
    for (unsigned a = 0; a < height_; a++) {std::vector<Color> vec;
        for (unsigned b = 0; b < width_; b++) {vec.push_back(image.ColorAt((int)a, (int)b));}path_image_.push_back(vec);
    }
    unsigned best_change = INT32_MAX;
    best_row_ = 0;
    for (unsigned i = 0; i < dataset.Height(); i++) {Path p(width_, i);unsigned r = i;p.SetLoc(0, i);
        for (unsigned j = 0; j < dataset.Width(); j++) {
            if (j != dataset.Width() - 1) {int r1 = (int)r - 1;int r2 = (int)r;int r3 = (int)r + 1;
                if (r1 < 0) {int change2 = std::abs(dataset.DatumAt(r,j) - dataset.DatumAt(r2, j+1));int change3 = std::abs(dataset.DatumAt(r,j) - dataset.DatumAt(r3, j+1));
                    if (change2 == change3) {p.IncEleChange(change2);p.SetLoc(j+1, r2);r = r2;
                    } else {int change = std::min(change2, change3);
                        if (change == change2) {p.IncEleChange(change2);p.SetLoc(j+1, r2);r = r2;
                        } else {p.IncEleChange(change3);p.SetLoc(j+1, r3);r = r3;}}
                } else if (r3 >= (int)dataset.Height()) {int change1 = std::abs(dataset.DatumAt(r,j)-dataset.DatumAt(r1,j+1));int change2 = std::abs(dataset.DatumAt(r,j)-dataset.DatumAt(r2,j+1));
                    if (change1 == change2) {p.IncEleChange(change2);p.SetLoc(j+1,r2);r = r2;
                    } else {int change = std::min(change1,change2);
                        if (change == change1) {p.IncEleChange(change1);p.SetLoc(j+1, r1);r = r1;
                        } else {p.IncEleChange(change2);p.SetLoc(j+1,r2);r = r2;}}
                } else {int change1 = std::abs(dataset.DatumAt(r,j)-dataset.DatumAt(r1,j+1));int change2 = std::abs(dataset.DatumAt(r,j)-dataset.DatumAt(r2,j+1));int change3 = std::abs(dataset.DatumAt(r,j)-dataset.DatumAt(r3,j+1));
                    if ((change2 == change1 && change2 < change3) || (change2 == change3 && change2 < change1) || (change2 == change1 && change2 == change3)) {p.IncEleChange(change2);p.SetLoc(j+1,r2);r = r2;
                    } else if (change3 == change1 && change3 < change2) {p.IncEleChange(change3);p.SetLoc(j+1,r3);r = r3;
                    } else {int change = std::min(std::min(change1, change2), change3);
                        if (change == change1) {p.IncEleChange(change1);p.SetLoc(j+1, r1);r = r1;
                        } else if (change == change2) {p.IncEleChange(change2);p.SetLoc(j+1,r2);r = r2;
                        } else {p.IncEleChange(change3);p.SetLoc(j+1,r3);r = r3;}}}}
        }
        paths_.push_back(p);
        if (p.EleChange() < best_change) {best_row_ = i;best_change = p.EleChange();}
    }
    for (unsigned x = 0; x < height_; x++) {Path p = paths_.at(x);const std::vector<size_t>& pathlist = p.GetPath();
        for (unsigned col = 0; col < width_; col++) {Color c(kRedRed, kRedGreen, kRedBlue);path_image_.at(pathlist.at(col)).at(col) = c;}
    }
    Path pb = paths_.at(best_row_);
    const std::vector<size_t>& pblist = pb.GetPath();
    for (unsigned c = 0; c < pblist.size(); c++) {
        Color g(kGreenRed, kGreenGreen, kGreenBlue);
        path_image_.at(pblist.at(c)).at(c) = g;
    }
}

size_t PathImage::Width() const {
    return width_;
}

size_t PathImage::Height() const {
    return height_;
}

unsigned int PathImage::MaxColorValue() const {
    return kMaxColorValue;
}

const std::vector<Path>& PathImage::Paths() const {
    return paths_;
}

const std::vector<std::vector<Color> >& PathImage::GetPathImage() const {
    return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
    std::ofstream ofs{name};
    ofs << "P3\n";
    ofs << width_ << ' ' << height_ << '\n';
    ofs << kMaxColorValue << '\n';
    for (unsigned i = 0; i < height_; i++) {
        for (unsigned j = 0; j < width_; j++) {
            Color c = path_image_.at(i).at(j);
            ofs << c.Red() << ' ' << c.Green() << ' ' << c.Blue() << ' ';
        }
        ofs << '\n';
    }
}
