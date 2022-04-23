#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
#include <iostream>

int main() {
    ElevationDataset ed("/home/vagrant/src/mp-mountain-paths-boda26/example-data/ex_input_data/map-input-w480-h480.dat", 480, 480);
    //std::cout << ed.MaxEle() << ' ' << ed.MinEle() << std::endl;
    GrayscaleImage gi(ed);
    gi.ToPpm("gray1.ppm");
    PathImage pi(gi, ed);
    pi.ToPpm("path_image.ppm");
}