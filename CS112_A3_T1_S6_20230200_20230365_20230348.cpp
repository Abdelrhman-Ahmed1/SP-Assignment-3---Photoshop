
#include <iostream>
#include "Image_Class.h"
#include <fstream>
#include "regex"

using namespace std;
int main();

bool restart() {
    // restart option
    cout << "\n1) Restart The Current Program" << endl;
    cout << "2) Return To Main Menu" << endl;
    cout << "3) Exit The Program" << endl;
    cout << "Please select your program from 1-3: ";
    string choice;
    cin >> choice;

    while (choice != "1" && choice != "2" && choice != "3") {

        cout << "\nInvalid Choice\n" << endl;
        cin.clear();
        cout << "\n1) Restart The Current Program" << endl;
        cout << "2) Return To Main Menu" << endl;
        cout << "3) Exit The Program" << endl;
        cout << "Please select your program from 1-3: ";
        cin >> choice;
    }

    cin.clear();
    if (choice == "1") {
        cin.clear();
        return true;
    } else if (choice == "2") {
        main();
    } else if (choice == "3") {
        exit(0);
    }

}

void grayscale(){

    string path;
    cout << "Enter your file path (with File Extention): ";
    getline(cin, path);

    ifstream filename;
    filename.open(path);

    while (!filename){
        cout << "File Not Found" << endl;
        cin.clear();
        cout << "Enter your file path (with File Extention): ";
        getline(cin, path);
        filename.open(path);

    }

    string saved_file;
    cout << "Enter The name of the saved file with extentions .jpg / .jpeg / .png / .bmp: " << endl;
    getline(cin, saved_file);

    regex result("([a-zA-Z0-9]+)\\.(jpg|bmp|png|tga)");
    while(!regex_match(saved_file, result)){

        cin.ignore();
        cout << "Invalid File name or extention" << endl;
        cout << "Enter The name of the saved file with extentions .jpg / .jpeg / .png / .bmp: " << endl;
        getline(cin, saved_file);

    }


    Image image(path);

    for (int i = 0; i < image.width; ++i){
        for (int j = 0; j < image.height; ++j){

            unsigned int avr = 0;
            for (int k = 0; k < image.channels; ++k){
                avr += image(i,j,k);
            }
            avr = avr/3;

            image(i,j,0) = avr;
            image(i,j,1) = avr;
            image(i,j,2) = avr;


        }

    }

    image.saveImage(saved_file);
    cout << "\n Image Saved succesfully as " << saved_file << "\n" << endl;

    if (restart()){
        grayscale();
    }
}


void invert_image(){

    char answer;
    string pic_name, new_pic_name;
    cout << "Enter the picture's name [with extention]: ";
    cin >> pic_name;

    ifstream file;
    file.open(pic_name);
    while(!file){
        cout << "Image doesn't exist. Enter a valid path: ";
        cin >> pic_name;
        file.open(pic_name);
    }

    regex extention("\\.(jpg|jpeg|png|gif|bmp)$");
    cout << "Enter the new picture's name [with extention]: ";
    cin >> new_pic_name;
    while(!regex_search(new_pic_name, extention)){
        cout << "Invalid file name, Please enter a valid one: ";
        cin >> new_pic_name;
    }

    Image image(pic_name);

    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++){
            for(int k = 0; k < 3; k++){
                image(i,j,k) = 255 - image(i,j,k);
            }
        }
    }

    image.saveImage(new_pic_name);
    cout << "Image saved successfully as: " << new_pic_name << endl;

    if (restart()){
        invert_image();
    }
}



void Darken_lighten(){

    string mode;
    cout << "1) lighten\n2) Darken" << endl;
    cout << "Please select your mode:" << endl;
    getline(cin, mode);

    while (mode != "1" && mode != "2"){
        cerr << "Invalid Choice" << endl;
        cin.ignore();
        cout << "1) lighten\n2) Darken" << endl;
        cout << "Please select your mode:" << endl;
        getline(cin, mode);

    }

    string path;
    cout << "Enter your file path (with File Extention): ";
    getline(cin, path);

    ifstream filename;
    filename.open(path);

    while (!filename){
        cout << "File Not Found" << endl;
        cin.clear();
        cout << "Enter your file path (with File Extention): ";
        getline(cin, path);
        filename.open(path);

    }

    string saved_file;
    cout << "Enter The name of the saved file with extentions .jpg / .jpeg / .png / .bmp: " << endl;
    getline(cin, saved_file);

    regex result("([a-zA-Z0-9]+)\\.(jpg|bmp|png|tga)");
    while(!regex_match(saved_file, result)){

        cin.ignore();
        cout << "Invalid File name or extention" << endl;
        cout << "Enter The name of the saved file with extentions .jpg / .jpeg / .png / .bmp: " << endl;
        getline(cin, saved_file);

    }

    if (mode == "1") {

        Image image(path);

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                unsigned int x = 0;
                for (int k = 0; k < image.channels; ++k) {

                    x = image(i, j, k) / 2 + image(i, j, k);
                    if (x > 255) {
                        x = 255;
                    }
                    image(i, j, k) = x;


                }

            }
        }

        image.saveImage(saved_file);
        cout << "\n Image Saved succesfully as " << saved_file << "\n" << endl;
    }

    else if (mode == "2") {

        Image image(path);

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                unsigned int x = 0;
                for (int k = 0; k < image.channels; ++k) {

                    x = image(i, j, k) / 2;
                    image(i, j, k) = x;


                }

            }
        }

        image.saveImage(saved_file);
        cout << "\n Image Saved succesfully as " << saved_file << "\n" << endl;
    }

    if (restart()){
        Darken_lighten();
    }

}

void ImageFlip() {

    string imagename , newimagename;
    int choice;
    cout << "Enter the path of the image you want to flip ";
    cout << "(e.g. ImageName.Extension): " << endl;

    getline(cin, imagename);
    ifstream filename1;
    filename1.open(imagename);

    while (!filename1) {
        cout << "Wrong path. please try again" << endl;
        cin.clear();
        cout << "Enter the path of the image you want to crop ";
        cout << "(e.g. ImageName.Extension): " << endl;
        getline(cin, imagename);
        filename1.open(imagename);

    }

    Image image(imagename);
    Image flipped(image.width, image.height);
    cout << "flip: " << endl;
    cout << "1.Vertically" << endl;
    cout << "2.Horizontally" << endl;

    while (true) {
        cin >> choice;
        if (choice == 1 || choice == 2) {
            break;
        } else {
            cout << "Invalid choice. please try again.\n";
        }
    }

    if (choice == 1) {
        cin.ignore();
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    unsigned char pixelvalue = image.getPixel(i, j, k);
                    flipped.setPixel(image.width - i, j, k, pixelvalue);
                }
            }
        }

        cout << "Enter a name to store new image ";
        cout << "and specify extension: ";
        getline(cin, newimagename);
        flipped.saveImage(newimagename);
    } else if (choice == 2) {
        cin.ignore();
        for (int i = 0; i < image.width; i++) {
            for (int j = image.height - 1; j > 0; j--) {
                for (int k = 0; k < 3; k++) {
                    unsigned char pixelvalue = image.getPixel(i, j, k);
                    flipped.setPixel(i, image.height - j, k, pixelvalue);
                }
            }
        }

        while (true) {
            cout << "Enter a name to store new image and specify extension: ";
            getline(cin, newimagename);
            regex check("([a-zA-Z0-9]+)\\.(jpg|bmp|png|tga)");
            if (regex_match(newimagename, check)) {
                flipped.saveImage(newimagename);
                break;
            } else {
                cout << "Invalid filename or extension. Please try again\n";
            }
        }
    }

    if (restart()){
        ImageFlip();
    }
}

void ImageCrop() {

    string imagename , newimagename;
    regex check("([a-zA-Z0-9]+)\\.(jpg|bmp|png|tga)");
    cout << "Enter the path of the image you want to crop ";
    cout << "(e.g. ImageName.Extension): " << endl;
    getline(cin, imagename);
    ifstream filename1;
    filename1.open(imagename);

    while (!filename1){
        cout << "Wrong path. please try again" << endl;
        cin.clear();
        cout << "Enter the path of the image you want to crop ";
        cout << "(e.g. ImageName.Extension): " << endl;
        getline(cin, imagename);
        filename1.open(imagename);

    }
    Image image(imagename);

    cout << "Image width = " << image.width << endl;
    cout << "Image height = " << image.height << endl;

    int x, y, newW, newH;
    while (true) {
        cout << "Enter x , y cords of the cropping starting point: " << endl;
        cout << "x = ";
        cin >> x;
        cout << "y = ";
        cin >> y;
        if (x < image.width && y < image.height && x >= 0 && y >= 0) {
            break;
        }
        else {
            cout << "Please Enter valid coordinates\n";
        }
    }
    int xmargin = image.width - x;
    int ymargin = image.height - y;

    while (true) {
        cout << "Enter new dimensions: " << endl;
        cout << "Width = ";

        cin >> newW;

        cout << "Height = ";
        cin >> newH;

        if (newW < xmargin && newH < ymargin) {
            Image newimage(newW, newH);

            for (int i = 0; i < newW; i++) {
                for (int k = 0; k < newH; k++) {
                    for (int j = 0; j < 3; j++) {
                        unsigned char pixelvalue = image.getPixel(i + x, k + y, j);
                        newimage.setPixel(i, k, j, pixelvalue);
                    }
                }
            }
            cin.ignore();
            while (true){
                cout << "Enter a name to store new image ";
                cout << "and specify extension: ";
                getline(cin, newimagename);
                bool valid = regex_match(newimagename, check);
                if (valid){
                    newimage.saveImage(newimagename);
                    break;
                } else {
                    cout << "Invalid extension. please try again\n";
                }
            }
            break;

        } else {
            cout << "the input dimensions are too big. try again.\n";
        }

    }

    if (restart()){
        ImageCrop();
    }
}






int main(){

    cout << "\n--- Welcome to { BABY PHOTOSHOP } ---\n" << endl;
    cout << "1) Grayscale" << endl;
    cout << "2) Invert Image" << endl;
    cout << "3) Flip Image" << endl;
    cout << "4) Darken & Lighten" << endl;
    cout << "5) Crop Image" << endl;
    cout << "Please select the filter : " << endl;
    string selection;
    getline(cin, selection);

    while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5"){
        cout << "\nInvalid Choice\n" << endl;
        cin.clear();
        cout << "1) Grayscale" << endl;
        cout << "2) Invert Image" << endl;
        cout << "3) Flip Image" << endl;
        cout << "4) Darken & Lighten" << endl;
        cout << "5) Crop Image" << endl;
        cout << "Please select the filter : " << endl;
        cin >> selection;

    }

    cin.clear();
    if (selection == "1"){
        grayscale();
    }

    if (selection == "2"){
        invert_image();
    }

    if (selection == "3"){
        ImageFlip();
    }

    if (selection == "4"){
        Darken_lighten();
    }

    if (selection == "5"){
        ImageCrop();
    }


}


