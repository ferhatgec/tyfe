/* MIT License
#
# Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef TYFE_HPP
#define TYFE_hPP

#if  __cplusplus < 201703L
    #error Tyfe requires compiler that must supports C++17 or higher standard.
#endif

#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 

// Required filesystem flag (-lstdc++fs) & 
// C++17-supported compiler
#include <filesystem>

//#include <functional>

typedef unsigned short UINT16;
typedef unsigned char* UCHARP;

// Supported types
enum TYFES {
    NOTHING = -1,
    JPEG = 0,
    PNG,
    GIF,
    BMP,
    WEBP,
    
    
    FLASCRIPT,
    BASH,
    SH
};
    
class Tyfe {
    std::string extension,
                filename;
                
    /*std::vector<std::string> shebang_ext = {
        "sh",
        "bash",
        "fla"
    };*/
    
    std::vector<std::string> binary_ext = {
        ".jpg",
        ".jpeg",
        ".png",
        ".gif",
        ".bmp",
        ".webp"
    };
    
    std::vector<std::string>::iterator binary_ext_iter;
public:
    /* Some markers & magics for detect type of file */ 
    enum MARKERS : const UINT16 {
        JPEG_SOI          = 0xD8,
        JPEG_START        = 0xFF,
        
        PNG_SOI           = 0x89,
        PNG_START_2       = 0x50,
        PNG_START_3       = 0x4E,
        PNG_START_4       = 0x47,
        
        GIF_SOI           = 0x47,
        GIF_START_2       = 0x49,
        GIF_START_3       = 0x46,
        
        BMP_SOI           = 0x42,
        BMP_START_2       = 0x4D,
        
        WEBP_SOI          = 0x57,
        WEBP_START_2      = 0x45,
        WEBP_START_3      = 0x42,
        WEBP_START_4      = 0x50,
    };
    
    /*
    template<typename T>
    struct check_type {
        bool type() {
            return(std::is_same<T, std::string>::value 
                || std::is_same<T, char*>::value 
                || std::is_same<T,  const char*>::value);
        }
    };
    */
    
    bool ext(std::string  const ext2,
             std::string  const ext3) {
        return ((extension == ext2) || (extension == ext3));
    }
    
    // TODO: Create TYFES to std::string function.
    
    // template<typename T>
    TYFES check(std::string file/* T type */) {
        // check_type<T> __check;
        
        /*if(__check.type() != true) {
            return NOTHING;
        }*/
        
        filename  = file;
        extension = std::filesystem::path(filename).extension();
        
        binary_ext_iter = std::find(binary_ext.begin(), 
                binary_ext.end(), extension);
                
        if(binary_ext_iter != binary_ext.end()) {
            return what_is_this();
        } else {
            return is_shebang(); 
        }
    }
    
    
    TYFES what_is_this() {
        std::ifstream file(filename, std::ios::in | std::ifstream::binary);
        
        /* check file is opened */
        if(!file.is_open()) { 
            throw std::runtime_error("tyfe: Can't open file: " + filename); 
            return NOTHING; 
        }
        
        std::string data((std::istreambuf_iterator<char>(file)),
                    (std::istreambuf_iterator<char>()));
   
        UCHARP marker = reinterpret_cast<UCHARP>(&data[0]);
     
        if(marker[0] == JPEG_START
            && marker[1] == JPEG_SOI
            && marker[2] == JPEG_START) {
            return JPEG;
        }
        
        if(marker[0] == PNG_SOI
            && marker[1] == PNG_START_2
            && marker[2] == PNG_START_3
            && marker[3] == PNG_START_4) {
            return PNG;
        }
        
        if(marker[0] == GIF_SOI
            && marker[1] == GIF_START_2
            && marker[2] == GIF_START_3) {
            return GIF;
        }
        
        if(marker[0] == BMP_SOI
            && marker[1] == BMP_START_2) {
            return BMP;   
        }

        if(marker[8] == WEBP_SOI
            && marker[9] == WEBP_START_2
            && marker[10]== WEBP_START_3
            && marker[11]== WEBP_START_4) {
            return WEBP;
        }
        
        return NOTHING;
    }
    
    TYFES is_shebang() {
        std::ifstream file(filename, std::ios::in | std::ios::app);
        
        std::string   __file;
        
        do {
            if(__file[0] == '#' && __file[1] == '!') {
                __file = __file.erase(0, (std::filesystem::path(__file).parent_path().string()).length());
                
                if(__file.find("fla") != std::string::npos)      return FLASCRIPT; 
                
                if(__file.find("sh")  !=  std::string::npos 
                    && __file.find("bash") == std::string::npos) return SH;
                else 
                    return BASH;
            }
        } while(std::getline(file, __file));
    }
};

#endif // TYFE_HPP
