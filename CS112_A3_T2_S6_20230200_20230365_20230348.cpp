
// Assignment 3 | Photoshop Program | Part 2B
// Including 15 Filters ( 12 Filters + 3 Bonus )

// Authors:
// 1. Abdelrhman Ahmed Abdelmonem Ahmed | 20230200 | Grayscale - Darken & Lighten - Detect Image Edges - Merge Two Images - Infrared Photography (Bonus)
// 2. Mohamed Kamel Ramadan             | 20230348 | Flip Image - Crop Image - Black & White - Resizing Images - Sunny Filter (Bonus)
// 3. Mohammed Yasser Ismael El-Sayed   | 20230365 | Invert Image - Rotate Image - Blur Images - Adding a Frame - Night Filter (Bonus)

// Section Number: S6

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include "Image_Class.h"
#include <stdio.h>

using namespace std;


int main();

void Apply(Image image, string imagename);

void printmsg(){
    cout << "\n=================" << endl;
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
    cout << "13) Infrared Photography (Bonus)" << endl;
    cout << "14) Sunny Filter (Bonus)" << endl;
    cout << "15) Night Filter (Bonus)" << endl;
    cout << "Please select the filter (1-15): ";
}

bool isValidFilter(string selection) {
    static const string validFilters[] = {"0", "1", "2", "3", "4", "5", "6", "7",
                                          "8", "9", "10", "11", "12", "13", "14", "15"};

    for (const string& validFilter : validFilters) {
        if (selection == validFilter) {
            return true;
        }
    }

    return false;
}

void validimage(string& imagename) {


    ifstream filename1(imagename);

    while (!filename1) {
        cout << "Wrong path. please try again" << endl;
        cin.clear();
        cout << "Enter the path of the image you want to edit ";
        cout << "(e.g. ImageName.Extension): " << endl;
        getline(cin, imagename);
        filename1.open(imagename);
    }
}

void saveImageWithValidName(Image& newimage) {
    string newimagename;
    while (true) {
        cout << "Enter a name to store new image and specify extension: ";
        getline(cin, newimagename);
        regex check("([a-zA-Z0-9]+)\\.(jpg|bmp|png|tga)");
        if (regex_match(newimagename, check)) {
            newimage.saveImage(newimagename);
            cout << "Image saved successfully as: " << newimagename << endl;
            remove("data.jpg");
            break;
        } else {
            cout << "Invalid filename or extension. Please try again\n";
        }
    }
}

void Image_Filp(string imagename){
    char choice;
    Image image(imagename);
    Image flipped(image.width, image.height);
    cout << "flip: " << endl;
    cout << "1.Vertically" << endl;
    cout << "2.Horizontally" << endl;

    while (true) {
        cin >> choice;
        if (choice == '1' || choice == '2') {
            break;
        } else {
            cout << "Invalid choice. please try again.\n";
            cout << "flip: " << endl;
            cout << "1.Vertically" << endl;
            cout << "2.Horizontally" << endl;
        }
    }
    cin.ignore();

    if (choice == '1') {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    unsigned char pixelvalue = image.getPixel(i, j, k);
                    flipped.setPixel(i, image.height - j - 1, k, pixelvalue);
                }
            }
        }


    } else if (choice == '2') {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < 3; k++) {
                    unsigned char pixelvalue = image.getPixel(i, j, k);
                    flipped.setPixel(image.width - i - 1, j, k, pixelvalue);
                }
            }
        }
    }
    Apply(flipped, imagename);
}

void Grayscale(string imagename){
    Image image(imagename);

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
    //cin.ignore();
    Apply(image, imagename);
}

void Invert_Image(string imagename){
    Image image(imagename);
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++){
            for(int k = 0; k < 3; k++){
                image(i,j,k) = 255 - image(i,j,k);
            }
        }
    }
    //cin.ignore();
    Apply(image, imagename);
}

void Rotate_Image(string imagename){
    Image image(imagename);
    Image NEW(image.width, image.height);
    Image NEW2(image.height, image.width);
    char answer;

    cout << "Select rotation degree: \nA) 90 Deg\nB) 180 Deg\nC) 270 Deg" << endl;
    cin >> answer;
    answer = tolower(answer);

    while (answer != 'a' && answer != 'b' && answer != 'c'){
        cout << "Invalid choice. Please try again\n";
        cout << "Select rotation degree: \nA) 90 Deg\nB) 180 Deg\nC) 270 Deg" << endl;
        cin >> answer;
        answer = tolower(answer);
    }

    switch(answer){
        case 'c':
            for(int i = 0; i < image.width; i++){
                for(int j = 0; j < image.height; j++){
                    for(int k = 0; k < 3; k++){
                        NEW2(j,i,k) = image(i,image.height - 1 - j, k);
                    }
                }
            }
            cin.ignore();
            Apply(NEW2, imagename);
            break;

        case 'a':
            for(int i = 0; i < image.width; i++) {
                for(int j = 0; j < image.height; j++) {
                    for(int k = 0; k < 3; k++) {
                        NEW2(j, image.width - 1 - i, k) = image(i, j, k);
                    }
                }
            }
            cin.ignore();
            Apply(NEW2, imagename);
            break;

        case 'b':
            for(int i = 0; i < image.width; i++) {
                for(int j = 0; j < image.height; j++) {
                    for(int k = 0; k < 3; k++) {
                        NEW(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
                    }
                }
            }
            //cin.ignore();
            Apply(NEW2, imagename);
            break;
    }
}

void Blur_Image(string imagename){
    char answer;
    int radius;
    Image image(imagename);

    cout << "Enter Level of blurring:\nA) Level 1\nB) Level 2\nC) Level 3\nD) Level 4\nE) Level 5" << endl;
    cin >> answer;
    answer = tolower(answer);

    while (answer != 'a' && answer != 'b' && answer != 'c' && answer != 'd' && answer != 'e'){
        cout << "Invalid choice. Please try again\n";
        cout << "Enter Level of blurring:\nA) Level 1\nB) Level 2\nC) Level 3\nD) Level 4\nE) Level 5" << endl;
        cin >> answer;
        answer = tolower(answer);
    }

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
    //cin.ignore();
    Apply(blurred, imagename);
}

void Add_Frame(string pic_name) {
    string new_pic_name;

    Image image(pic_name);
    int R = 0, G = 0, B = 0, R2 = 0, G2 = 0, B2 = 0;
    char frame_type, primary_frame_color, secondary_frame_color;
    bool There_Is_SFM = false, Its_Primary = true, Is_Fancy = false;
    int a, b, c, d, e, f, g, h, m;

    cout << "Enter frame type:\nA) Basic Frame\nB) Simple Two Colors Frame\nC) Simple Three Colors Frame\n"
            "D) Fancy Two Colors Frame\nE) Fancy Three Colors Frame" << endl;
    cin >> frame_type;
    frame_type = tolower(frame_type);

    while(true){
        if(frame_type == 'a'){
            Its_Primary = false;
            break;
        }
        else if(frame_type == 'b'){
            There_Is_SFM = true;
            break;
        }
        else if(frame_type == 'c'){
            There_Is_SFM = true;
            break;
        }
        else if(frame_type == 'd'){
            Is_Fancy = true;
            There_Is_SFM = true;
            break;
        }
        else if(frame_type == 'e'){
            Is_Fancy = true;
            There_Is_SFM = true;
            break;
        }
        else{
            cout << "Invalid answer, enter a valid one: ";
            cin >> frame_type;
            frame_type = tolower(frame_type);
        }
    }

    if(Its_Primary){
        cout << "Enter Primary Frame Color [Inner Color]:\nA) White\nB) Black\nC) Red\nD) Orange\nE) Yellow\nF) Blue\nG) Cyan" << endl;
    }
    else{
        cout << "Enter Frame Color:\nA) White\nB) Black\nC) Red\nD) Orange\nE) Yellow\nF) Blue\nG) Cyan" << endl;
    }

    cin >> primary_frame_color;
    primary_frame_color = tolower(primary_frame_color);

    while(true){
        if(primary_frame_color == 'a'){
            R = 255, G = 255, B = 255;
            break;
        }
        else if(primary_frame_color == 'b'){
            break;
        }
        else if(primary_frame_color == 'c'){
            R = 255;
            break;
        }
        else if(primary_frame_color == 'd'){
            R = 255, G = 165;
            break;
        }
        else if(primary_frame_color == 'e'){
            R = 255, G = 255;
            break;
        }
        else if(primary_frame_color == 'f'){
            B = 255;
            break;
        }
        else if(primary_frame_color == 'g'){
            G = 255, B = 255;
            break;
        }
        else{
            cout << "Invalid answer, enter a valid one: ";
            cin >> primary_frame_color;
            primary_frame_color = tolower(primary_frame_color);
        }

    }

    if(There_Is_SFM){
        cout << "Enter Secondary Frame Color [Outer Color]:\nA) White\nB) Light Gray\nC) Gray\nD) Dark Gray\nE) Black" << endl;
        cin >> secondary_frame_color;
        secondary_frame_color = tolower(secondary_frame_color);

        while(true){
            if(secondary_frame_color == 'a'){
                R2 = 255, G2 = 255, B2 = 255;
                break;
            }
            else if(secondary_frame_color == 'b'){
                R2 = 220, G2 = 220, B2 = 220;
                break;
            }
            else if(secondary_frame_color == 'c'){
                R2 = 180, G2 = 180, B2 = 180;
                break;
            }
            else if(secondary_frame_color == 'd'){
                R2 = 125, G2 = 125, B2 = 125;
                break;
            }
            else if(secondary_frame_color == 'e'){
                break;
            }
            else{
                cout << "Invalid answer, enter a valid one: ";
                cin >> secondary_frame_color;
                secondary_frame_color = tolower(secondary_frame_color);
            }

        }
    }



    switch(frame_type){
        case 'b': case 'd':
            a = int(image.height * (1.25/100));
            b = int(image.width * (1.25/100));
            c = int(image.width * (1.25/100));
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
            c = int(image.height * (1.25/100));
            d = image.width - int(image.width * (0.75/100));
            e = int(image.height * (0.75/100));
            f = image.height - int(image.width * (0.75/100));
            g = int(image.width * (0.75/100));
            h = int(image.width * (2.75/100));
            m = int(image.height * (2.75/100));
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

    Apply(image, pic_name);

}

void Darken_Lighten(string imagename){
    string mode;
    Image image(imagename);

    cout << "1) lighten\n2) Darken" << endl;
    cout << "Please select your mode:" << endl;
    cin >> mode;

    while (mode != "1" && mode != "2"){
        cout << "Invalid Choice" << endl;
        cout << "1) lighten\n2) Darken" << endl;
        cout << "Please select your mode:" << endl;
        cin >> mode;
    }
    if (mode == "1") {

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
        //cin.ignore();
        Apply(image, imagename);
    }

    else if (mode == "2") {

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                unsigned int x = 0;
                for (int k = 0; k < image.channels; ++k) {

                    x = image(i, j, k) / 2;
                    image(i, j, k) = x;


                }

            }
        }
        cin.ignore();
        Apply(image, imagename);
    }
}

void Image_Crop(string imagename){
    string newimagename;
    Image image(imagename);
    cout << "Image width = " << image.width << endl;
    cout << "Image height = " << image.height << endl;

    int x, y, newW, newH;
    while (true) {
        cout << "Enter x , y cords of the cropping starting point: " << endl;
        cout << "x = ";
        while (!(cin >> x)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer for x.\n";
            cout << "x = ";
        }
        cout << "y = ";
        while (!(cin >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer for y\n ";
            cout << "y = ";
        }
        if (x < image.width && y < image.height && x >= 0 && y >= 0) {
            break;
        }
        else {
            cout << "Please Enter valid coordinates\n";
        }
    }

    int xmargin = image.width - x;
    int ymargin = image.height - y;

    cout << "Enter new dimensions: " << endl;

    cout << "Width = ";
    while (!(cin >> newW)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer for width\n";
        cout << "Width = ";
    }

    cout << "Height = ";
    while (!(cin >> newH)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer for height\n";
        cout << "Height = ";
    }

    while (newW > xmargin || newH > ymargin){
        cout << "the input dimensions are too big. try again.\n";

        cout << "Width = ";
        while (!(cin >> newW)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer for width\n";
            cout << "Width = ";
        }

        cout << "Height = ";
        while (!(cin >> newH)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer for height\n";
            cout << "Height = ";
        }
    }

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
        //cin.ignore();
        Apply(image, imagename);
    }
}

void Detect_Edges(string imagename){
    Image image(imagename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int avr = 0;
            for (int k = 0; k < image.channels; ++k) {
                avr += image(i, j, k);
            }
            avr = avr / 3;

            image(i, j, 0) = avr;
            image(i, j, 1) = avr;
            image(i, j, 2) = avr;


        }
    }

    for (int i = 0; i < image.width - 1; ++i) {
        for (int j = 0; j < image.height - 1; ++j) {

            unsigned int avr = 0;
            for (int k = 0; k < image.channels; ++k) {
                if (abs(image(i, j, k) - image(i + 1, j + 1, k) >= 20)) {
                    avr = 0;
                } else {
                    avr = 255;
                }
            }

            image(i, j, 0) = avr;
            image(i, j, 1) = avr;
            image(i, j, 2) = avr;
        }
    }
    //cin.ignore();
    Apply(image, imagename);
}

void Merge_Two_Images(string imagename){


    Image image(imagename);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string path2;
    cout << "Enter your second file path (with File Extension): ";
    getline(cin, path2);


    ifstream filename2;
    filename2.open(path2);

    while (!filename2){

        cout << "File Not Found" << endl;
        cin.clear();
        cout << "Enter your second file path (with File Extension): ";
        getline(cin, path2);
        filename2.open(path2);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string mode;
    cout << "1) Merge with max height & width\n2) Merge with min height & width" << endl;
    cout << "Please select your mode:" << endl;
    cin >> mode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (mode != "1" && mode != "2"){
        cout << "Invalid Choice" << endl;
        cin.ignore();
        cout << "1) Merge with max height & width\n2) Merge with min height & width" << endl;
        cout << "Please select your mode:" << endl;
        cin >> mode;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }

    Image image2(path2);
    int result_width, result_height;

    if (mode == "1"){
        result_width = max(image.width, image2.width);
        result_height = max(image.height, image2.height);
    }
    else if (mode == "2"){
        result_width = min(image.width, image2.width);
        result_height = min(image.height, image2.height);
    }


    Image newimage1(result_width, result_height);
    Image newimage2(result_width, result_height);
    Image result(result_width, result_height);

    double w1factor = floor(image.width) / result_width;
    double h1factor = floor(image.height) / result_height;

    double w2factor = floor(image2.width) / result_width;
    double h2factor = floor(image2.height) / result_height;


    for (int i = 0; i < result_width; i++) {
        for (int j = 0; j < result_height; j++) {
            for (int k = 0; k < 3; k++) {
                int xref1 = floor(i * w1factor);
                int yref1 = floor(j * h1factor);

                int xref2 = floor(i * w2factor);
                int yref2 = floor(j * h2factor);

                unsigned char pixelvalue1 = image.getPixel(xref1, yref1, k);
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
    //cin.ignore();
    Apply(result, imagename);
}

void Black_And_White(string imagename){
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

    //cin.ignore();
    Apply(image, imagename);
}

void Resize_Image(string imagename){
    string newname;
    double percentage, factor, wfactor, hfactor;
    int nwidth, nheight;

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
            //cin >> percentage;
            while (!(cin >> percentage)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a positive integer.\n";
                cout << "Enter resizing percentage: ";
            }

            while (percentage <= 0) {
                cout << "Please enter a positive percentage: ";
                while (!(cin >> percentage)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a positive integer.\n";
                    cout << "Enter resizing percentage: ";
                }
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
            cin.ignore();
            saveImageWithValidName(newimage);
            break;
        }


        case '2': {
            cout << "Enter new width: ";
            while (!(cin >> nwidth)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a positive integer.\n";
                cout << "Enter new width: : ";
            }

            cout << "Enter new height: ";
            while (!(cin >> nheight)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a positive integer.\n";
                cout << "Enter new height: ";
            }

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
            cin.ignore();
            Apply(newimage, imagename);
        }

    }

}

void Infrared_Photography(string imagename){
    Image image(imagename);

    for (int i = 0; i < image.width; ++i){
        for (int j = 0; j < image.height; ++j){

            unsigned int x  = 0;

            image(i,j,0) = 255;
            image(i,j,1) = 255 - image(i,j,1);
            image(i,j,2) = 255 - image(i,j,2);


        }
    }

    Apply(image, imagename);

}

void Sunny_Filter(string imagename) {

    Image img(imagename);

    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            if (img(x,y,0) + 37 > 255){
                img(x,y,0) = 255;
            }
            else {
                img(x,y,0) += 37;
            }
            if (img(x,y,1) + 40 > 255){
                img(x,y,1) = 255;
            }
            else {
                img(x,y,1) += 40;
            }
            if (img(x,y,2) - 10 < 0){
                img(x,y,2) = 0;
            }
            else {
                img(x,y,0) -= 10;
            }
        }
    }

    Apply(img, imagename);
}


void Night_Filter(string imagename) {

    Image image(imagename);

    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++){
            image(i, j, 1) *= 0/7;
        }
    }

    Apply(image, imagename);
}


void Apply(Image image, string imagename){

    Image old_image;
    cout << "\nYour filter has been applied succesfully\n" << endl;
    char choice;
    string new_selection;
    cout << "\n--- Program Options ---\n" << endl;
    cout << "1) Save Image & Exit program" << endl;
    cout << "2) Apply Another Filter/ Same Filter" << endl;
    cout << "3) Save Image & Restart Program" << endl;
    cout << "Please select your option (1-3): ";
    cin.clear();
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (choice != '1' && choice != '2' && choice != '3'){

        cin.ignore();
        cout << "\nInvalid Choice\n" << endl;
        cout << "\n--- Program Options ---\n" << endl;
        cout << "1) Save Image & Exit program" << endl;
        cout << "2) Apply Another Filter/ Same Filter" << endl;
        cout << "3) Save Image & Restart Program" << endl;
        cout << "Please select your option (1-3): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }

    cin.clear();
    if (choice == '3') {
        saveImageWithValidName(image);
        main();
    }
    else if (choice == '1') {
        saveImageWithValidName(image);
        cout << "\nExiting...\n" << endl;
        exit(0);
    }
    else if (choice == '2'){

        Image old_image = image;
        old_image.saveImage("data.jpg");
        printmsg();
        cin >> new_selection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while(!isValidFilter(new_selection) || new_selection == "0"){
            cout << "\nInvalid Choice. Please enter a Valid Filter Number\n";
            printmsg();
            cin >> new_selection;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }
        if (new_selection == "1"){
            Grayscale("data.jpg");
        }

        if (new_selection == "2"){
            Invert_Image("data.jpg");
        }

        if (new_selection == "3"){
            Image_Filp("data.jpg");
        }

        if (new_selection == "4"){
            Rotate_Image("data.jpg");
        }

        if (new_selection == "5"){
            Darken_Lighten("data.jpg");
        }

        if (new_selection == "6"){
            Image_Crop("data.jpg");
        }

        if (new_selection == "7"){
            Detect_Edges("data.jpg");
        }

        if (new_selection == "8"){
            Blur_Image("data.jpg");
        }

        if (new_selection == "9"){
            Add_Frame("data.jpg");
        }

        if (new_selection == "10"){
            Merge_Two_Images("data.jpg");
        }

        if (new_selection == "11"){
            Black_And_White("data.jpg");
        }
        if (new_selection == "12"){
            Resize_Image("data.jpg");
        }
        if (new_selection == "13"){
            Infrared_Photography("data.jpg");
        }
        if (new_selection == "14"){
            Sunny_Filter("data.jpg");
        }
        if (new_selection == "15"){
            Night_Filter("data.jpg");
        }
        main();
    }

}

int main() {

    string selection;
    string imagename;

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
    cout << "13) Infrared Photography (Bonus)" << endl;
    cout << "14) Sunny Filter (Bonus)" << endl;
    cout << "15) Night Filter (Bonus)" << endl;
    cout << "0) Exit The Program" << endl;
    cout << "Please select the filter (0-15): ";
    cin >> selection;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    while (!isValidFilter(selection)) {
        cout << "\nInvalid Choice. Please enter a Valid Filter Number\n" << endl;
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
        cout << "13) Infrared Photography (Bonus)" << endl;
        cout << "14) Sunny Filter (Bonus)" << endl;
        cout << "15) Night Filter (Bonus)" << endl;
        cout << "0) Exit The Program" << endl;
        cout << "Please select the filter (0-15): ";
        cin >> selection;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (selection == "0"){
        cout << "\nExiting...\n" << endl;
        exit(0);
    }

    cout << "Enter the path of the image you want to edit ";
    cout << "(e.g. ImageName.Extension): " << endl;
    getline(cin, imagename);
    validimage(imagename);


    if (selection == "1"){
        Grayscale(imagename);
    }

    if (selection == "2"){
        Invert_Image(imagename);
    }

    if (selection == "3"){
        Image_Filp(imagename);
    }

    if (selection == "4"){
        Rotate_Image(imagename);
    }

    if (selection == "5"){
        Darken_Lighten(imagename);
    }

    if (selection == "6"){
        Image_Crop(imagename);
    }

    if (selection == "7"){
        Detect_Edges(imagename);
    }

    if (selection == "8"){
        Blur_Image(imagename);
    }

    if (selection == "9"){
        Add_Frame(imagename);
    }

    if (selection == "10"){
        Merge_Two_Images(imagename);
    }

    if (selection == "11"){
        Black_And_White(imagename);
    }
    if (selection == "12"){
        Resize_Image(imagename);
    }
    if (selection == "13"){
        Infrared_Photography(imagename);
    }
    if (selection == "14"){
        Sunny_Filter(imagename);
    }
    if (selection == "15"){
        Night_Filter(imagename);
    }

    return 0;
}
