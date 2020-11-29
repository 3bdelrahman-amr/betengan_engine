#pragma once
#include <glad/gl.h>
//#include<unordered_map>
#include<iostream>
#include<memory>
#include<map>
#include<vector>
#include<bitset>
#include<assert.h>
//#include"System.h"
using namespace std;
typedef unsigned int Entity ;

typedef unsigned int Components;
const Entity MaxE = 5000;
const Components MaxC = 100;
typedef bitset<MaxC> Signature;
enum struct CameraType {
    Orthographic,
    Perspective
};
