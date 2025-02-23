#include "ViewZoomIn.h"

namespace dtk
{
    std::vector<uint8_t> getViewZoomIn()
    {
        return std::vector<uint8_t>
        {
            60, 63, 120, 109, 108, 32, 118, 101, 114, 115, 105, 111, 110, 61, 34, 49, 46, 48, 34, 32, 101, 110, 99, 111, 100, 105, 110, 103, 61, 34, 
            85, 84, 70, 45, 56, 34, 32, 115, 116, 97, 110, 100, 97, 108, 111, 110, 101, 61, 34, 110, 111, 34, 63, 62, 13, 10, 60, 33, 45, 45, 
            32, 67, 114, 101, 97, 116, 101, 100, 32, 119, 105, 116, 104, 32, 73, 110, 107, 115, 99, 97, 112, 101, 32, 40, 104, 116, 116, 112, 58, 47, 
            47, 119, 119, 119, 46, 105, 110, 107, 115, 99, 97, 112, 101, 46, 111, 114, 103, 47, 41, 32, 45, 45, 62, 13, 10, 13, 10, 60, 115, 118, 
            103, 13, 10, 32, 32, 32, 119, 105, 100, 116, 104, 61, 34, 50, 48, 34, 13, 10, 32, 32, 32, 104, 101, 105, 103, 104, 116, 61, 34, 50, 
            48, 34, 13, 10, 32, 32, 32, 118, 105, 101, 119, 66, 111, 120, 61, 34, 48, 32, 48, 32, 53, 46, 50, 57, 49, 54, 54, 54, 53, 32, 
            53, 46, 50, 57, 49, 54, 54, 54, 54, 34, 13, 10, 32, 32, 32, 118, 101, 114, 115, 105, 111, 110, 61, 34, 49, 46, 49, 34, 13, 10, 
            32, 32, 32, 105, 100, 61, 34, 115, 118, 103, 56, 34, 13, 10, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 118, 101, 114, 115, 
            105, 111, 110, 61, 34, 49, 46, 49, 46, 49, 32, 40, 51, 98, 102, 53, 97, 101, 48, 100, 50, 53, 44, 32, 50, 48, 50, 49, 45, 48, 
            57, 45, 50, 48, 41, 34, 13, 10, 32, 32, 32, 115, 111, 100, 105, 112, 111, 100, 105, 58, 100, 111, 99, 110, 97, 109, 101, 61, 34, 86, 
            105, 101, 119, 90, 111, 111, 109, 73, 110, 46, 115, 118, 103, 34, 13, 10, 32, 32, 32, 120, 109, 108, 110, 115, 58, 105, 110, 107, 115, 99, 
            97, 112, 101, 61, 34, 104, 116, 116, 112, 58, 47, 47, 119, 119, 119, 46, 105, 110, 107, 115, 99, 97, 112, 101, 46, 111, 114, 103, 47, 110, 
            97, 109, 101, 115, 112, 97, 99, 101, 115, 47, 105, 110, 107, 115, 99, 97, 112, 101, 34, 13, 10, 32, 32, 32, 120, 109, 108, 110, 115, 58, 
            115, 111, 100, 105, 112, 111, 100, 105, 61, 34, 104, 116, 116, 112, 58, 47, 47, 115, 111, 100, 105, 112, 111, 100, 105, 46, 115, 111, 117, 114, 
            99, 101, 102, 111, 114, 103, 101, 46, 110, 101, 116, 47, 68, 84, 68, 47, 115, 111, 100, 105, 112, 111, 100, 105, 45, 48, 46, 100, 116, 100, 
            34, 13, 10, 32, 32, 32, 120, 109, 108, 110, 115, 61, 34, 104, 116, 116, 112, 58, 47, 47, 119, 119, 119, 46, 119, 51, 46, 111, 114, 103, 
            47, 50, 48, 48, 48, 47, 115, 118, 103, 34, 13, 10, 32, 32, 32, 120, 109, 108, 110, 115, 58, 115, 118, 103, 61, 34, 104, 116, 116, 112, 
            58, 47, 47, 119, 119, 119, 46, 119, 51, 46, 111, 114, 103, 47, 50, 48, 48, 48, 47, 115, 118, 103, 34, 13, 10, 32, 32, 32, 120, 109, 
            108, 110, 115, 58, 114, 100, 102, 61, 34, 104, 116, 116, 112, 58, 47, 47, 119, 119, 119, 46, 119, 51, 46, 111, 114, 103, 47, 49, 57, 57, 
            57, 47, 48, 50, 47, 50, 50, 45, 114, 100, 102, 45, 115, 121, 110, 116, 97, 120, 45, 110, 115, 35, 34, 13, 10, 32, 32, 32, 120, 109, 
            108, 110, 115, 58, 99, 99, 61, 34, 104, 116, 116, 112, 58, 47, 47, 99, 114, 101, 97, 116, 105, 118, 101, 99, 111, 109, 109, 111, 110, 115, 
            46, 111, 114, 103, 47, 110, 115, 35, 34, 13, 10, 32, 32, 32, 120, 109, 108, 110, 115, 58, 100, 99, 61, 34, 104, 116, 116, 112, 58, 47, 
            47, 112, 117, 114, 108, 46, 111, 114, 103, 47, 100, 99, 47, 101, 108, 101, 109, 101, 110, 116, 115, 47, 49, 46, 49, 47, 34, 62, 13, 10, 
            32, 32, 60, 100, 101, 102, 115, 13, 10, 32, 32, 32, 32, 32, 105, 100, 61, 34, 100, 101, 102, 115, 50, 34, 32, 47, 62, 13, 10, 32, 
            32, 60, 115, 111, 100, 105, 112, 111, 100, 105, 58, 110, 97, 109, 101, 100, 118, 105, 101, 119, 13, 10, 32, 32, 32, 32, 32, 105, 100, 61, 
            34, 98, 97, 115, 101, 34, 13, 10, 32, 32, 32, 32, 32, 112, 97, 103, 101, 99, 111, 108, 111, 114, 61, 34, 35, 99, 56, 99, 56, 99, 
            56, 34, 13, 10, 32, 32, 32, 32, 32, 98, 111, 114, 100, 101, 114, 99, 111, 108, 111, 114, 61, 34, 35, 54, 54, 54, 54, 54, 54, 34, 
            13, 10, 32, 32, 32, 32, 32, 98, 111, 114, 100, 101, 114, 111, 112, 97, 99, 105, 116, 121, 61, 34, 49, 46, 48, 34, 13, 10, 32, 32, 
            32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 112, 97, 103, 101, 111, 112, 97, 99, 105, 116, 121, 61, 34, 48, 34, 13, 10, 32, 
            32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 112, 97, 103, 101, 115, 104, 97, 100, 111, 119, 61, 34, 50, 34, 13, 10, 32, 
            32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 122, 111, 111, 109, 61, 34, 51, 49, 46, 54, 53, 57, 48, 57, 57, 34, 13, 
            10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 99, 120, 61, 34, 54, 46, 57, 57, 54, 52, 48, 56, 56, 34, 13, 
            10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 99, 121, 61, 34, 49, 48, 46, 52, 50, 51, 53, 52, 52, 34, 13, 
            10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 100, 111, 99, 117, 109, 101, 110, 116, 45, 117, 110, 105, 116, 115, 61, 
            34, 112, 120, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 99, 117, 114, 114, 101, 110, 116, 45, 108, 97, 
            121, 101, 114, 61, 34, 70, 111, 114, 119, 97, 114, 100, 80, 108, 97, 121, 98, 97, 99, 107, 34, 13, 10, 32, 32, 32, 32, 32, 115, 104, 
            111, 119, 103, 114, 105, 100, 61, 34, 116, 114, 117, 101, 34, 13, 10, 32, 32, 32, 32, 32, 117, 110, 105, 116, 115, 61, 34, 112, 120, 34, 
            13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 119, 105, 110, 100, 111, 119, 45, 119, 105, 100, 116, 104, 61, 34, 
            49, 57, 50, 48, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 119, 105, 110, 100, 111, 119, 45, 104, 101, 
            105, 103, 104, 116, 61, 34, 49, 48, 49, 49, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 119, 105, 110, 
            100, 111, 119, 45, 120, 61, 34, 48, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 119, 105, 110, 100, 111, 
            119, 45, 121, 61, 34, 51, 50, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 119, 105, 110, 100, 111, 119, 
            45, 109, 97, 120, 105, 109, 105, 122, 101, 100, 61, 34, 49, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 
            115, 110, 97, 112, 45, 98, 98, 111, 120, 61, 34, 116, 114, 117, 101, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 
            101, 58, 98, 98, 111, 120, 45, 110, 111, 100, 101, 115, 61, 34, 116, 114, 117, 101, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 
            99, 97, 112, 101, 58, 115, 110, 97, 112, 45, 103, 108, 111, 98, 97, 108, 61, 34, 116, 114, 117, 101, 34, 13, 10, 32, 32, 32, 32, 32, 
            105, 110, 107, 115, 99, 97, 112, 101, 58, 112, 97, 103, 101, 99, 104, 101, 99, 107, 101, 114, 98, 111, 97, 114, 100, 61, 34, 48, 34, 13, 
            10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 111, 98, 106, 101, 99, 116, 45, 110, 111, 100, 101, 115, 61, 34, 102, 
            97, 108, 115, 101, 34, 62, 13, 10, 32, 32, 32, 32, 60, 105, 110, 107, 115, 99, 97, 112, 101, 58, 103, 114, 105, 100, 13, 10, 32, 32, 
            32, 32, 32, 32, 32, 116, 121, 112, 101, 61, 34, 120, 121, 103, 114, 105, 100, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 105, 100, 61, 
            34, 103, 114, 105, 100, 52, 53, 50, 54, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 101, 109, 112, 115, 112, 97, 99, 105, 110, 103, 61, 
            34, 49, 48, 34, 32, 47, 62, 13, 10, 32, 32, 60, 47, 115, 111, 100, 105, 112, 111, 100, 105, 58, 110, 97, 109, 101, 100, 118, 105, 101, 
            119, 62, 13, 10, 32, 32, 60, 109, 101, 116, 97, 100, 97, 116, 97, 13, 10, 32, 32, 32, 32, 32, 105, 100, 61, 34, 109, 101, 116, 97, 
            100, 97, 116, 97, 53, 34, 62, 13, 10, 32, 32, 32, 32, 60, 114, 100, 102, 58, 82, 68, 70, 62, 13, 10, 32, 32, 32, 32, 32, 32, 
            60, 99, 99, 58, 87, 111, 114, 107, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 114, 100, 102, 58, 97, 98, 111, 117, 116, 61, 34, 
            34, 62, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 60, 100, 99, 58, 102, 111, 114, 109, 97, 116, 62, 105, 109, 97, 103, 101, 47, 115, 
            118, 103, 43, 120, 109, 108, 60, 47, 100, 99, 58, 102, 111, 114, 109, 97, 116, 62, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 60, 100, 
            99, 58, 116, 121, 112, 101, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 114, 100, 102, 58, 114, 101, 115, 111, 117, 114, 99, 
            101, 61, 34, 104, 116, 116, 112, 58, 47, 47, 112, 117, 114, 108, 46, 111, 114, 103, 47, 100, 99, 47, 100, 99, 109, 105, 116, 121, 112, 101, 
            47, 83, 116, 105, 108, 108, 73, 109, 97, 103, 101, 34, 32, 47, 62, 13, 10, 32, 32, 32, 32, 32, 32, 60, 47, 99, 99, 58, 87, 111, 
            114, 107, 62, 13, 10, 32, 32, 32, 32, 60, 47, 114, 100, 102, 58, 82, 68, 70, 62, 13, 10, 32, 32, 60, 47, 109, 101, 116, 97, 100, 
            97, 116, 97, 62, 13, 10, 32, 32, 60, 103, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 108, 97, 98, 101, 
            108, 61, 34, 76, 97, 121, 101, 114, 32, 49, 34, 13, 10, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 103, 114, 111, 
            117, 112, 109, 111, 100, 101, 61, 34, 108, 97, 121, 101, 114, 34, 13, 10, 32, 32, 32, 32, 32, 105, 100, 61, 34, 108, 97, 121, 101, 114, 
            49, 34, 13, 10, 32, 32, 32, 32, 32, 116, 114, 97, 110, 115, 102, 111, 114, 109, 61, 34, 116, 114, 97, 110, 115, 108, 97, 116, 101, 40, 
            48, 44, 45, 50, 57, 49, 46, 55, 48, 56, 51, 49, 41, 34, 62, 13, 10, 32, 32, 32, 32, 60, 103, 13, 10, 32, 32, 32, 32, 32, 
            32, 32, 105, 100, 61, 34, 70, 111, 114, 119, 97, 114, 100, 80, 108, 97, 121, 98, 97, 99, 107, 34, 13, 10, 32, 32, 32, 32, 32, 32, 
            32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 108, 97, 98, 101, 108, 61, 34, 35, 103, 52, 53, 50, 52, 34, 13, 10, 32, 32, 32, 32, 
            32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 101, 120, 112, 111, 114, 116, 45, 120, 100, 112, 105, 61, 34, 57, 54, 34, 13, 10, 
            32, 32, 32, 32, 32, 32, 32, 105, 110, 107, 115, 99, 97, 112, 101, 58, 101, 120, 112, 111, 114, 116, 45, 121, 100, 112, 105, 61, 34, 57, 
            54, 34, 62, 13, 10, 32, 32, 32, 32, 32, 32, 60, 112, 97, 116, 104, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 115, 116, 121, 
            108, 101, 61, 34, 102, 105, 108, 108, 58, 35, 102, 48, 102, 48, 102, 48, 59, 115, 116, 114, 111, 107, 101, 45, 119, 105, 100, 116, 104, 58, 
            48, 46, 50, 54, 52, 53, 56, 51, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 100, 61, 34, 109, 32, 49, 46, 55, 49, 48, 
            51, 57, 48, 52, 44, 50, 57, 50, 46, 51, 54, 48, 51, 55, 32, 97, 32, 49, 46, 51, 50, 50, 57, 49, 54, 55, 44, 49, 46, 51, 
            50, 50, 57, 49, 54, 55, 32, 48, 32, 48, 32, 48, 32, 50, 46, 52, 101, 45, 54, 44, 49, 46, 56, 55, 48, 56, 57, 32, 49, 46, 
            51, 50, 50, 57, 49, 54, 55, 44, 49, 46, 51, 50, 50, 57, 49, 54, 55, 32, 48, 32, 48, 32, 48, 32, 49, 46, 56, 55, 48, 56, 
            56, 49, 57, 44, 45, 49, 101, 45, 53, 32, 49, 46, 51, 50, 50, 57, 49, 54, 55, 44, 49, 46, 51, 50, 50, 57, 49, 54, 55, 32, 
            48, 32, 48, 32, 48, 32, 52, 46, 56, 101, 45, 54, 44, 45, 49, 46, 56, 55, 48, 56, 56, 32, 49, 46, 51, 50, 50, 57, 49, 54, 
            55, 44, 49, 46, 51, 50, 50, 57, 49, 54, 55, 32, 48, 32, 48, 32, 48, 32, 45, 49, 46, 56, 55, 48, 56, 56, 57, 49, 44, 48, 
            32, 122, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 105, 100, 61, 34, 112, 97, 116, 104, 57, 50, 55, 34, 32, 47, 62, 13, 
            10, 32, 32, 32, 32, 32, 32, 60, 114, 101, 99, 116, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 115, 116, 121, 108, 101, 61, 34, 
            102, 105, 108, 108, 58, 35, 102, 48, 102, 48, 102, 48, 59, 115, 116, 114, 111, 107, 101, 45, 119, 105, 100, 116, 104, 58, 48, 46, 50, 54, 
            52, 53, 56, 51, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 105, 100, 61, 34, 114, 101, 99, 116, 49, 48, 51, 52, 34, 13, 
            10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 119, 105, 100, 116, 104, 61, 34, 48, 46, 53, 50, 57, 49, 54, 54, 54, 52, 34, 13, 10, 
            32, 32, 32, 32, 32, 32, 32, 32, 32, 104, 101, 105, 103, 104, 116, 61, 34, 50, 46, 49, 49, 54, 54, 54, 54, 54, 34, 13, 10, 32, 
            32, 32, 32, 32, 32, 32, 32, 32, 120, 61, 34, 45, 50, 48, 53, 46, 55, 56, 53, 49, 54, 34, 13, 10, 32, 32, 32, 32, 32, 32, 
            32, 32, 32, 121, 61, 34, 50, 49, 48, 46, 51, 50, 48, 55, 49, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 116, 114, 97, 
            110, 115, 102, 111, 114, 109, 61, 34, 114, 111, 116, 97, 116, 101, 40, 45, 52, 53, 41, 34, 32, 47, 62, 13, 10, 32, 32, 32, 32, 32, 
            32, 60, 112, 97, 116, 104, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 105, 100, 61, 34, 114, 101, 99, 116, 56, 51, 49, 34, 13, 
            10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 115, 116, 121, 108, 101, 61, 34, 102, 105, 108, 108, 58, 35, 102, 48, 102, 48, 102, 48, 59, 
            102, 105, 108, 108, 45, 111, 112, 97, 99, 105, 116, 121, 58, 49, 59, 115, 116, 114, 111, 107, 101, 58, 110, 111, 110, 101, 59, 115, 116, 114, 
            111, 107, 101, 45, 119, 105, 100, 116, 104, 58, 48, 46, 55, 52, 56, 51, 53, 53, 59, 115, 116, 114, 111, 107, 101, 45, 109, 105, 116, 101, 
            114, 108, 105, 109, 105, 116, 58, 52, 59, 115, 116, 114, 111, 107, 101, 45, 100, 97, 115, 104, 97, 114, 114, 97, 121, 58, 110, 111, 110, 101, 
            59, 115, 116, 114, 111, 107, 101, 45, 111, 112, 97, 99, 105, 116, 121, 58, 49, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 100, 
            61, 34, 109, 32, 49, 46, 53, 56, 55, 53, 53, 51, 51, 44, 50, 57, 52, 46, 51, 53, 52, 49, 51, 32, 45, 48, 46, 50, 54, 52, 
            53, 57, 55, 57, 44, 50, 101, 45, 53, 32, 45, 51, 46, 56, 56, 101, 45, 53, 44, 49, 46, 48, 53, 56, 51, 51, 32, 72, 32, 48, 
            46, 50, 54, 52, 54, 50, 48, 53, 51, 32, 108, 32, 49, 46, 52, 53, 51, 101, 45, 53, 44, 48, 46, 50, 54, 52, 53, 55, 32, 49, 
            46, 48, 53, 56, 50, 57, 54, 48, 52, 44, 45, 49, 101, 45, 53, 32, 45, 50, 46, 56, 57, 101, 45, 53, 44, 49, 46, 48, 53, 56, 
            51, 54, 32, 48, 46, 50, 54, 52, 53, 57, 55, 56, 44, 45, 49, 101, 45, 53, 32, 50, 46, 49, 57, 101, 45, 53, 44, 45, 49, 46, 
            48, 53, 56, 51, 56, 32, 49, 46, 48, 53, 56, 51, 52, 57, 49, 44, 53, 101, 45, 53, 32, 45, 49, 46, 52, 53, 101, 45, 53, 44, 
            45, 48, 46, 50, 54, 52, 53, 55, 32, 45, 49, 46, 48, 53, 56, 51, 52, 50, 49, 44, 45, 51, 101, 45, 53, 32, 122, 34, 13, 10, 
            32, 32, 32, 32, 32, 32, 32, 32, 32, 115, 111, 100, 105, 112, 111, 100, 105, 58, 110, 111, 100, 101, 116, 121, 112, 101, 115, 61, 34, 99, 
            99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 34, 32, 47, 62, 13, 10, 32, 32, 32, 32, 32, 32, 60, 112, 97, 116, 104, 13, 
            10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 115, 116, 121, 108, 101, 61, 34, 102, 105, 108, 108, 58, 35, 53, 97, 53, 97, 53, 97, 59, 
            115, 116, 114, 111, 107, 101, 45, 119, 105, 100, 116, 104, 58, 48, 46, 50, 54, 52, 53, 56, 51, 59, 102, 105, 108, 108, 45, 111, 112, 97, 
            99, 105, 116, 121, 58, 49, 34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 100, 61, 34, 109, 32, 49, 46, 56, 57, 55, 52, 55, 
            54, 55, 44, 50, 57, 50, 46, 53, 52, 55, 52, 53, 32, 97, 32, 49, 46, 48, 53, 56, 51, 51, 51, 51, 44, 49, 46, 48, 53, 56, 
            51, 51, 51, 51, 32, 48, 32, 48, 32, 49, 32, 49, 46, 52, 57, 54, 55, 49, 52, 44, 49, 48, 101, 45, 54, 32, 49, 46, 48, 53, 
            56, 51, 51, 51, 51, 44, 49, 46, 48, 53, 56, 51, 51, 51, 51, 32, 48, 32, 48, 32, 49, 32, 45, 50, 46, 51, 101, 45, 54, 44, 
            49, 46, 52, 57, 54, 55, 49, 32, 49, 46, 48, 53, 56, 51, 51, 51, 51, 44, 49, 46, 48, 53, 56, 51, 51, 51, 51, 32, 48, 32, 
            48, 32, 49, 32, 45, 49, 46, 52, 57, 54, 55, 48, 55, 44, 48, 32, 49, 46, 48, 53, 56, 51, 51, 51, 51, 44, 49, 46, 48, 53, 
            56, 51, 51, 51, 51, 32, 48, 32, 48, 32, 49, 32, 45, 52, 46, 55, 101, 45, 54, 44, 45, 49, 46, 52, 57, 54, 55, 50, 32, 122, 
            34, 13, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 105, 100, 61, 34, 112, 97, 116, 104, 56, 50, 57, 34, 32, 47, 62, 13, 10, 32, 
            32, 32, 32, 60, 47, 103, 62, 13, 10, 32, 32, 60, 47, 103, 62, 13, 10, 60, 47, 115, 118, 103, 62, 13, 10, 
        };
    }
}
