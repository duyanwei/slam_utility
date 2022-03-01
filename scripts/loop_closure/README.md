# The directory contains information related to LoopClosure Detection

- `parsing.py`\
The script is used to parse the [NewCollege2008](https://www.robots.ox.ac.uk/~mobile/IJRR_2008_Dataset/data.html) and [CityCentre](https://www.robots.ox.ac.uk/~mobile/IJRR_2008_Dataset/data.html) dataset into left, right, append mode, and it also contains a method to prepare the imagelist for [MILD](https://github.com/lhanaf/MILD) paper. After the parsing, the structure of the directory looks similar as the following.
```
CityCentre/
├── append
├── CityCentreGroundTruth.mat
├── CityCentreSatPhoto.jpg
├── CityCentreTextFormat.zip
├── ImageCollectionCoordinates.mat
├── ImageCollectionCoordinates.txt
├── imagelist_CityCentre_append.txt
├── imagelist_CityCentre_left.txt
├── imagelist_CityCentre_right.txt
├── Images.zip
├── left
└── right
```