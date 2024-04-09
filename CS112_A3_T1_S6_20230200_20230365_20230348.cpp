
// Assignment 3 | Photoshop Program | Task 2
// Including 12 Filters

// Authors:
// 1. Abdelrhman Ahmed Abdelmonem Ahmed | 20230200 | Grayscale - Darken & Lighten - Detect Image Edges - Merge Two Images
// 2. Mohamed Kamel Ramadan             | 20230348 | Flip Image - Crop Image - Black & White - Resizing Images
// 3. Mohammed Yasser Ismael El-Sayed   | 20230365 | Invert Image - Rotate Image - Blur Images - Adding a Frame


#include <iostream>
#include "Image_Class.h"
#include <fstream>
#include "regex"
#include "cmath"

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

    return 0;
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


void Rotate_Image(){

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

    regex extension("\\.(jpg|jpeg|png|gif|bmp)$");
    cout << "Enter the new picture's name [with extention]: ";
    cin >> new_pic_name;

    while(!regex_search(new_pic_name, extension)){
        cout << "Invalid file name, Please enter a valid one: ";
        cin >> new_pic_name;
    }

    Image image(pic_name);
    Image NEW(image.width, image.height);
    Image NEW2(image.height, image.width);
    char answer;

    cout << "Select rotation degree: \nA) 90 Deg\nB) 180 Deg\nC) 270 Deg" << endl;
    cin >> answer;
    answer = tolower(answer);

    switch(answer){
        case 'c':
            for(int i = 0; i < image.width; i++){
                for(int j = 0; j < image.height; j++){
                    for(int k = 0; k < 3; k++){
                        NEW2(j,i,k) = image(i,image.height - 1 - j, k);
                    }
                }
            }
            NEW2.saveImage(new_pic_name);
            cout << "Image saved successfully as: " << new_pic_name << endl;
            break;

        case 'a':
            for(int i = 0; i < image.width; i++) {
                for(int j = 0; j < image.height; j++) {
                    for(int k = 0; k < 3; k++) {
                        NEW2(j, image.width - 1 - i, k) = image(i, j, k);
                    }
                }
            }
            NEW2.saveImage(new_pic_name);
            cout << "Image saved successfully as: " << new_pic_name << endl;
            break;

        case 'b':
            for(int i = 0; i < image.width; i++) {
                for(int j = 0; j < image.height; j++) {
                    for(int k = 0; k < 3; k++) {
                        NEW(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                    }
                }
            }
            NEW.saveImage(new_pic_name);
            cout << "Image saved successfully as: " << new_pic_name << endl;
            break;

    }

    if (restart()){
        Rotate_Image();
    }

}


void Blur_Image() {
    string pic_name, new_pic_name;
    cout << "Enter the picture's name [with extension]: ";
    cin >> pic_name;

    ifstream file;
    file.open(pic_name);
    while (!file) {
        cout << "Image doesn't exist. Enter a valid path: ";
        cin >> pic_name;
        file.open(pic_name);
    }

    regex extension("\\.(jpg|jpeg|png|gif|bmp)$");
    cout << "Enter the new picture's name [with extension]: ";
    cin >> new_pic_name;

    while (!regex_search(new_pic_name, extension)) {
        cout << "Invalid file name, enter a valid one: ";
        cin >> new_pic_name;
    }

    Image image(pic_name);
    char answer;
    int radius;
    cout << "Enter Level of blurring:\nA) Level 1\nB) Level 2\nC) Level 3\nD) Level 4\nE) Level 5" << endl;
    cin >> answer;
    answer = tolower(answer);

    switch (answer) {
        case 'a':
            radius = 1;
            break;
        case 'b':
            radius = 2;
            break;
        case 'c':
            radius = 3;
            break;
        case 'd':
            radius = 4;
            break;
        case 'e':
            radius = 5;
            break;
        default:
            cout << "Invalid input, enter a valid one: ";
            cin >> answer;
    }

    Image blurred(image.width, image.height);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int RedSum = 0, GreenSum = 0, BlueSum = 0, count = 0;
            for (int y = -radius; y <= radius; y++) {
                int newY = j + y;
                if (newY >= 0 && newY < image.height) {
                    for (int x = -radius; x <= radius; x++) {
                        int newX = i + x;
                        if (newX >= 0 && newX < image.width) {
                            RedSum += image(newX, newY, 0);
                            GreenSum += image(newX, newY, 1);
                            BlueSum += image(newX, newY, 2);
                            count++;
                        }
                    }
                }
            }
            blurred(i, j, 0) = RedSum / count;
            blurred(i, j, 1) = GreenSum / count;
            blurred(i, j, 2) = BlueSum / count;
        }
    }

    blurred.saveImage(new_pic_name);
    cout << "Image saved successfully as: " << new_pic_name << endl;


    if (restart()){
        Blur_Image();
    }
}

void Add_Frame() {
    string pic_name, new_pic_name;
    cout << "Enter the picture's name [with extension]: ";
    cin >> pic_name;

    ifstream file;
    file.open(pic_name);
    while (!file) {
        cout << "Image doesn't exist. Enter a valid path: ";
        cin >> pic_name;
        file.open(pic_name);
    }

    regex extension("\\.(jpg|jpeg|png|gif|bmp)$");
    cout << "Enter the new picture's name [with extension]: ";
    cin >> new_pic_name;

    while (!regex_search(new_pic_name, extension)) {
        cout << "Invalid file name, enter a valid one: ";
        cin >> new_pic_name;
    }

    Image image(pic_name);
    int R = 0, G = 0, B = 0, R2 = 0, G2 = 0, B2 = 0;
    char frame_type, primary_frame_color, secondary_frame_color;
    bool There_Is_SFM = false, Its_Primary = true, Is_Fancy = false;
    int a, b, c, d, e, f, g, h, m;

    cout << "Enter frame type:\nA) Basic Frame\nB) Simple Two Colors Frame\nC) Simple Three Colors Frame\nD) Fancy Two Colors Frame\nE) Fancy Three Colors Frame" << endl;
    cin >> frame_type;
    frame_type = tolower(frame_type);

    switch(frame_type){
        case 'a':
            Its_Primary = false;
            break;
        case 'b':
            There_Is_SFM = true;
            break;
        case 'd':
            Is_Fancy = true;
            There_Is_SFM = true;
            break;
        case 'c':
            There_Is_SFM = true;
            break;
        case 'e':
            Is_Fancy = true;
            There_Is_SFM = true;
            break;
        default:
            cout << "Invalid answer, enter a valid one: ";
            cin >> frame_type;
    }

    if(Its_Primary){
        cout << "Enter Primary Frame Color [Inner Color]:\nA) White\nB) Black\nC) Red\nD) Orange\nE) Yellow\nF) Blue\nG) Cyan\n" << endl;
    }
    else{
        cout << "Enter Frame Color:\nA) White\nB) Black\nC) Red\nD) Orange\nE) Yellow\nF) Blue\nG) Cyan\n" << endl;
    }

    cin >> primary_frame_color;
    primary_frame_color = tolower(primary_frame_color);

    switch(primary_frame_color){
        case 'a':
            R = 255, G = 255, B = 255;
            break;
        case 'b':
            break;
        case 'c':
            R = 255;
            break;
        case 'd':
            R = 255, G = 165;
            break;
        case 'e':
            R = 255, G = 255;
            break;
        case 'f':
            B = 255;
            break;
        case 'g':
            G = 255, B = 255;
            break;
        default:
            cout << "Invalid answer, enter a valid one: ";
            cin >> primary_frame_color;
    }

    if(There_Is_SFM){
        cout << "Enter Secondary Frame Color [Outer Color]:\nA) White\nB) Light Gray\nC) Gray\nD) Dark Gray\nE) Black" << endl;
        cin >> secondary_frame_color;
        secondary_frame_color = tolower(secondary_frame_color);

        switch(secondary_frame_color){
            case 'a':
                R2 = 255, G2 = 255, B2 = 255;
                break;
            case 'b':
                R2 = 220, G2 = 220, B2 = 220;
                break;
            case 'c':
                R2 = 180, G2 = 180, B2 = 180;
                break;
            case 'd':
                R2 = 125, G2 = 125, B2 = 125;
                break;
            case 'e':
                break;
            default:
                cout << "Invalid answer, enter a valid one: ";
                cin >> secondary_frame_color;
        }
    }



    switch(frame_type){
        case 'b': case 'd':
            a = int(image.height * (1.25/100));
            b = int(image.width * (1.25/100));
            c = int(image.height * (1.25/100));
            d = image.width - int(image.width * (1.25/100));
            e = int(image.height * (1.25/100));
            f = image.height - int(image.width * (1.25/100));
            g = int(image.width * (1.25/100));
            h = int(image.width * (3.5/100));
            m = int(image.height * (3.5/100));
            break;
        case 'c': case 'e':
            a = int(image.height * (3.5/100));
            b = int(image.width * (3.5/100));
            c = int(image.height * (2.75/100));
            d = image.width - int(image.width * (0.75/100));
            e = int(image.height * (0.75/100));
            f = image.height - int(image.width * (0.75/100));
            g = int(image.width * (0.75/100));
            h = int(image.width * (2.75/100));
            m = c;
            break;
    }


    switch(frame_type){
        case 'a':
            for (int i = 0; i < image.width; i++){
                for (int j = 0; j < int(image.height * (3.5/100)); j++){
                    for (int k = 0; k < 3; k++){
                        switch (k){
                            case 0:
                                image(i, j, k) = R;
                                image(i, image.height - 1 - j, k) = R;
                                break;
                            case 1:
                                image(i, j, k) = G;
                                image(i, image.height - 1 - j, k) = G;
                                break;
                            case 2:
                                image(i, j, k) = B;
                                image(i, image.height - 1 - j, k) = B;
                                break;
                        }
                    }
                }
            }
            for (int i = 0; i < int(image.width * (3.5/100)); i++){
                for (int j = 0; j < image.height; j++){
                    for (int k = 0; k < 3; k++){
                        switch (k){
                            case 0:
                                image(i, j, k) = R;
                                image(image.width - 1 - i, j, k) = R;
                                break;
                            case 1:
                                image(i, j, k) = G;
                                image(image.width - 1 - i, j, k) = G;
                                break;
                            case 2:
                                image(i, j, k) = B;
                                image(image.width - 1 - i, j, k) = B;
                                break;
                        }
                    }
                }
            }
            break;

        case 'b': case 'c': case 'd': case 'e':
            for (int i = 0; i < image.width; i++){
                for (int j = 0; j < a; j++){
                    for (int k = 0; k < 3; k++){
                        switch (k){
                            case 0:
                                image(i, j, k) = R2;
                                image(i, image.height - 1 - j, k) = R2;
                                break;
                            case 1:
                                image(i, j, k) = G2;
                                image(i, image.height - 1 - j, k) = G2;
                                break;
                            case 2:
                                image(i, j, k) = B2;
                                image(i, image.height - 1 - j, k) = B2;
                                break;
                        }
                    }
                }
            }

            for (int i = 0; i < b; i++){
                for (int j = 0; j < image.height; j++){
                    for (int k = 0; k < 3; k++){
                        switch (k){
                            case 0:
                                image(i, j, k) = R2;
                                image(image.width - 1 - i, j, k) = R2;
                                break;
                            case 1:
                                image(i, j, k) = G2;
                                image(image.width - 1 - i, j, k) = G2;
                                break;
                            case 2:
                                image(i, j, k) = B2;
                                image(image.width - 1 - i, j, k) = B2;
                                break;
                        }
                    }
                }
            }

            for (int i = c; i < d; i++){
                for (int j = e; j < m; j++){
                    for (int k = 0; k < 3; k++){
                        switch (k){
                            case 0:
                                image(i, j, k) = R;
                                image(i, image.height - 1 - j, k) = R;
                                break;
                            case 1:
                                image(i, j, k) = G;
                                image(i, image.height - 1 - j, k) = G;
                                break;
                            case 2:
                                image(i, j, k) = B;
                                image(i, image.height - 1 - j, k) = B;
                                break;
                        }
                    }
                }
            }

            for (int i = g; i < h; i++){
                for (int j = g; j < f; j++){
                    for (int k = 0; k < 3; k++){
                        switch (k){
                            case 0:
                                image(i, j, k) = R;
                                image(image.width - 1 - i, j, k) = R;
                                break;
                            case 1:
                                image(i, j, k) = G;
                                image(image.width - 1 - i, j, k) = G;
                                break;
                            case 2:
                                image(i, j, k) = B;
                                image(image.width - 1 - i, j, k) = B;
                                break;
                        }
                    }
                }
            }

            break;
    }

    if(Is_Fancy){
        int start_i = image.width * 0.015;
        int end_i = image.width * 0.065;
        int start_j = image.height * 0.015;
        int end_j = image.height * 0.065;

        for(int i = start_i; i < end_i; i++){
            for(int j = start_j; j < end_j; j++){
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;

                image(i, image.height - 1 - j, 0) = R;
                image(i, image.height - 1 - j, 1) = G;
                image(i, image.height - 1 - j, 2) = B;

                image(image.width - 1 - i, j, 0) = R;
                image(image.width - 1 - i, j, 1) = G;
                image(image.width - 1 - i, j, 2) = B;

                image(image.width - 1 - i, image.height - 1 - j, 0) = R;
                image(image.width - 1 - i, image.height - 1 - j, 1) = G;
                image(image.width - 1 - i, image.height - 1 - j, 2) = B;
            }
        }
    }


    image.saveImage(new_pic_name);
    cout << "Image saved successfully as: " << new_pic_name << endl;

    if (restart()){
        Add_Frame();
    }

}


void Darken_lighten(){

    string mode;
    cout << "1) lighten\n2) Darken" << endl;
    cout << "Please select your mode:" << endl;
    cin >> mode;

    while (mode != "1" && mode != "2"){
        cin.clear();
        cout << "Invalid Choice" << endl;
        cin.ignore();
        cout << "1) lighten\n2) Darken" << endl;
        cout << "Please select your mode:" << endl;
        cin >> mode;

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
        cout << "Image saved successfully as: " << newimagename << endl;
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
                cout << "Image saved successfully as: " << newimagename << endl;
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
                    cout << "Image saved successfully as: " << newimagename << endl;
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


void Detect_edges(){

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

            for (int k = 0; k < image.channels; ++k){
                if (abs(image(i,j,k)-image(i+1,j+1,k) >= 25)){
                    avr= 0;
                }
                else{
                    avr= 255;
                }
            }

            image(i,j,0) = avr;
            image(i,j,1) = avr;
            image(i,j,2) = avr;

        }

    }

    image.saveImage(saved_file);
    cout << "\n Image Saved succesfully as " << saved_file << "\n" << endl;

    if (restart()){
        Detect_edges();
    }

}

void Merge_two_images(){


    string path1;
    cout << "Enter your first file path (with File Extention): ";
    getline(cin, path1);

    ifstream filename1;
    filename1.open(path1);

    while (!filename1){
        cout << "File Not Found" << endl;
        cin.clear();
        cout << "Enter your first file path (with File Extention): ";
        getline(cin, path1);
        filename1.open(path1);

    }

    string path2;
    cout << "Enter your second file path (with File Extention): ";
    getline(cin, path2);

    ifstream filename2;
    filename2.open(path2);

    while (!filename2){

        cout << "File Not Found" << endl;
        cin.clear();
        cout << "Enter your second file path (with File Extention): ";
        getline(cin, path2);
        filename2.open(path2);

    }


    string mode;
    cout << "1) Merge with max height & width\n2) Merge with min height & width" << endl;
    cout << "Please select your mode:" << endl;
    cin >> mode;

    while (mode != "1" && mode != "2"){
        cout << "Invalid Choice" << endl;
        cin.ignore();
        cout << "1) Merge with max height & width\n2) Merge with min height & width" << endl;
        cout << "Please select your mode:" << endl;
        cin >> mode;

    }

    string saved_file;
    cout << "Enter The name of the saved file with extentions .jpg / .jpeg / .png / .bmp: " << endl;
    getline(cin, saved_file);

    regex saved("([a-zA-Z0-9]+)\\.(jpg|bmp|png|tga)");
    while(!regex_match(saved_file, saved)){

        cin.ignore();
        cout << "Invalid File name or extention" << endl;
        cout << "Enter The name of the saved file with extentions .jpg / .jpeg / .png / .bmp: " << endl;
        getline(cin, saved_file);

    }


    Image image1(path1);
    Image image2(path2);
    int result_width, result_height;

    if (mode == "1"){
        result_width = max(image1.width, image2.width);
        result_height = max(image1.height, image2.height);
    }
    else if (mode == "2"){
        result_width = min(image1.width, image2.width);
        result_height = min(image1.height, image2.height);
    }


    Image newimage1(result_width, result_height);
    Image newimage2(result_width, result_height);
    Image result(result_width, result_height);

    double w1factor = floor(image1.width) / result_width;
    double h1factor = floor(image1.height) / result_height;

    double w2factor = floor(image2.width) / result_width;
    double h2factor = floor(image2.height) / result_height;


    for (int i = 0; i < result_width; i++) {
        for (int j = 0; j < result_height; j++) {
            for (int k = 0; k < 3; k++) {
                int xref1 = floor(i * w1factor);
                int yref1 = floor(j * h1factor);

                int xref2 = floor(i * w2factor);
                int yref2 = floor(j * h2factor);

                unsigned char pixelvalue1 = image1.getPixel(xref1, yref1, k);
                newimage1.setPixel(i, j, k, pixelvalue1);

                unsigned char pixelvalue2 = image2.getPixel(xref2, yref2, k);
                newimage2.setPixel(i, j, k, pixelvalue2);

            }
        }
    }



    for (int i = 0; i < result_width; ++i){
        for (int j = 0; j < result_height; ++j){

            unsigned int x  = 0;
            for (int k = 0; k < image2.channels; ++k){

                x = newimage1(i,j,k) + newimage2(i,j,k);
                x = x / 2;
                if (x > 255){
                    x = 255;
                }
                result(i,j,k) = x;


            }

        }
    }

    result.saveImage(saved_file);
    cout << "\n Image Saved succesfully as " << saved_file << "\n" << endl;

    if (restart()){
        Merge_two_images();
    }


}

void BlackandWhite(){

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

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0;

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }

            avg /= 3;

            if (avg >= 115){
                for (int k = 0 ; k < 3 ; k++){
                    image(i, j, k) = 255;
                }
            }
            else if (avg < 115){
                for (int k = 0 ; k < 3 ; k++){
                    image(i, j, k) = 0;
                }
            }
        }
    }

    cout << "Enter new image name: ";
    cin >> newimagename;

    while (!regex_match(newimagename, check)) {
        cout << "Invalid extension. Please try again\n";
        cin >> newimagename;
    }

    image.saveImage(newimagename);
    cout << "\n Image Saved succesfully as " << newimagename << "\n" << endl;

    if (restart()){
        BlackandWhite();
    }
}


void imageresize(){

    regex check("([a-zA-Z0-9]+)\\.(jpg|bmp|png|tga)");
    string imagename, newname;
    double percentage, factor, wfactor, hfactor;
    int nwidth, nheight;

    cout << "Enter image path: ";
    getline(cin, imagename);

    ifstream filename1(imagename);
    while (!filename1) {
        cout << "Wrong path. Please try again." << endl;
        cin.clear();
        cout << "Enter image path: ";
        getline(cin, imagename);
        filename1.open(imagename);
    }
    Image oimage(imagename);

    cout << "Image width = " << oimage.width << endl;
    cout << "Image height = " << oimage.height << endl;

    cout << "1) Resize by a percentage      2) Choose new dimensions\n";

    char choice;
    cin >> choice;

    while (choice != '1' && choice != '2') {
        cout << "Invalid input. please try again. \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice;
    }

    switch (choice) {
        case '1': {
            cout << "Enter resizing percentage: ";
            cin >> percentage;

            while (percentage <= 0) {
                cout << "Please enter a positive percentage: ";
                cin >> percentage;
            }

            factor = percentage / 100;

            nwidth = floor(oimage.width * factor);
            nheight = floor(oimage.height * factor);

            Image newimage(nwidth, nheight);

            for (int i = 0; i < newimage.width; i++) {
                for (int j = 0; j < newimage.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        int xref = floor(i / factor);
                        int yref = floor(j / factor);

                        unsigned char pixelvalue = oimage.getPixel(xref, yref, k);
                        newimage.setPixel(i, j, k, pixelvalue);
                    }
                }
            }

            cout << "Enter new image name: ";
            cin >> newname;

            while (!regex_match(newname, check)) {
                cout << "Invalid extension. Please try again\n";
                cin >> newname;
            }

            newimage.saveImage(newname);
            cout << "\n Image Saved succesfully as " << newname << "\n" << endl;
            if (restart()){
                BlackandWhite();
            }
            break;
        }
        case '2': {
            cout << "Enter new width: ";
            cin >> nwidth;
            cout << "Enter new height: ";
            cin >> nheight;

            while (nwidth <= 0 || nheight <= 0) {
                cout << "Please enter positive dimensions: ";
                cin >> nwidth >> nheight;
            }

            wfactor = floor(oimage.width) / nwidth;
            hfactor = floor(oimage.height) / nheight;

            Image newimage(nwidth, nheight);

            for (int i = 0; i < newimage.width; i++) {
                for (int j = 0; j < newimage.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        int xref = floor(i * wfactor);
                        int yref = floor(j * hfactor);

                        unsigned char pixelvalue = oimage.getPixel(xref, yref, k);
                        newimage.setPixel(i, j, k, pixelvalue);
                    }
                }
            }
            cout << "Enter new image name: ";
            cin >> newname;

            while (!regex_match(newname, check)) {
                cout << "Invalid extension. Please try again\n";
                cin >> newname;
            }

            newimage.saveImage(newname);
            cout << "\n Image Saved succesfully as " << newname << "\n" << endl;

            if (restart()){
                BlackandWhite();
            }

            break;
        }
        default:
            cout << "Invalid choice\n";
    }

}



int main(){

    cout << "\n--- Welcome to { BABY PHOTOSHOP } ---\n" << endl;
    cout << "1) Grayscale" << endl;
    cout << "2) Invert Image" << endl;
    cout << "3) Flip Image" << endl;
    cout << "4) Rotate Image" << endl;
    cout << "5) Darken & Lighten" << endl;
    cout << "6) Crop Image" << endl;
    cout << "7) Detect Image Edges" << endl;
    cout << "8) Blur Image" << endl;
    cout << "9) Adding a Frame" << endl;
    cout << "10) Merge Two Images" << endl;
    cout << "11) Black & White" << endl;
    cout << "12) Resizing Images" << endl;
    cout << "Please select the filter : " << endl;
    string selection;
    getline(cin, selection);

    while (selection != "1" && selection != "2" && selection != "3" && selection != "4" && selection != "5" && selection != "6" && selection != "7" && selection != "8" && selection != "9" && selection != "10" && selection != "11" && selection != "12"){
        cout << "\nInvalid Choice\n" << endl;
        cin.clear();
        cout << "1) Grayscale" << endl;
        cout << "2) Invert Image" << endl;
        cout << "3) Flip Image" << endl;
        cout << "4) Rotate Image" << endl;
        cout << "5) Darken & Lighten" << endl;
        cout << "6) Crop Image" << endl;
        cout << "7) Detect Image Edges" << endl;
        cout << "8) Blur Image" << endl;
        cout << "9) Adding a Frame" << endl;
        cout << "10) Merge Two Images" << endl;
        cout << "11) Black & White" << endl;
        cout << "12) Resizing Images" << endl;
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
        Rotate_Image();
    }

    if (selection == "5"){
        Darken_lighten();
    }

    if (selection == "6"){
        ImageCrop();
    }

    if (selection == "7"){
        Detect_edges();
    }

    if (selection == "8"){
        Blur_Image();
    }

    if (selection == "9"){
        Add_Frame();
    }

    if (selection == "10"){
        Merge_two_images();
    }

    if (selection == "11"){
        BlackandWhite();
    }
    if (selection == "12"){
        imageresize();
    }

}
