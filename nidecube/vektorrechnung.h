#ifndef vektorrechnung_H
#define vektorrechnung_H

#include <cmath>

// Function to calculate the dot product of two vectors
float vec_dot_product(const float v1[3], const float v2[3]) {
  float result = 0.0;
  for (int i = 0; i < 3; i++) {
    result += v1[i] * v2[i];
  }
  return result;
}

// Function to calculate the length (magnitude) of a vector
float vec_length(const float v[3]) {
  float result = 0.0;
  for (int i = 0; i < 3; i++) {
    result += v[i] * v[i];
  }
  return sqrt(result);
}

//Function to calculate the cross produkt between two vectors


// Function to calculate the angle between two vectors
float vec_angle(const float v1[3], const float v2[3]) {
  float result = 0.0;
  float dot_product = vec_dot_product(v1, v2);
  float length_v1 = vec_length(v1);
  float length_v2 = vec_length(v2);
  result = dot_product / (length_v1 * length_v2);
  return acos(result) * 180.0 / M_PI;
}

/*

Das hier hat iwie nicht funktioniert

#include <iostream>
#include <vector>
#include <math.h>

// Funktion zum Addieren von Vektoren
std::vector<float> vec_add(const std::vector<float>& v1, const std::vector<float>& v2) {
    std::vector<float> result;
    if (v1.size() != v2.size()) {
        std::cout << "Fehler: Die Vektoren müssen die gleiche Länge haben." << std::endl;
        return result;
    }
    result.resize(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

//Funktion zum Subtrahieren von Vektoren
std::vector<float> vec_subtract(const std::vector<float>& v1, const std::vector<float>& v2) {
    std::vector<float> result;
    if (v1.size() != v2.size()) {
        std::cout << "Fehler: Die Vektoren müssen die gleiche Länge haben." << std::endl;
        return result;
    }
    result.resize(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

// Funktion zum elementweisen addieren eines Vektors mit einem Skalar
std::vector<float> vec_add_scalar(const std::vector<float>& v, float scalar) {
    std::vector<float> result;
    result.resize(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] + scalar;
    }
    return result;
}

// Funktion zum Multiplizieren von Vektoren
std::vector<float> vec_multiply(const std::vector<float>& v1, const std::vector<float>& v2) {
    std::vector<float> result;
    if (v1.size() != v2.size()) {
        std::cout << "Fehler: Die Vektoren müssen die gleiche Länge haben." << std::endl;
        return result;
    }
    result.resize(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] * v2[i];
    }
    return result;
}

// Funktion zum Dividieren von Vektoren
std::vector<float> vec_divide(const std::vector<float>& v1, const std::vector<float>& v2) {
    std::vector<float> result;
    if (v1.size() != v2.size()) {
        std::cout << "Fehler: Die Vektoren müssen die gleiche Länge haben." << std::endl;
        return result;
    }
    result.resize(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] / v2[i];
    }
    return result;
}
// Funktion zum Skalieren von Vektoren
std::vector<float> vec_scale(const std::vector<float>& v, float factor) {
    std::vector<float> result;
    result.resize(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * factor;
    }
    return result;
}

// Funktion zum Berechnen der Länge eines Vektors
float vec_length(const std::vector<float>& v) {
    float result = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        result += v[i] * v[i];
    }
    return sqrt(result);
}

// Funktion zum Berechnen des Skalarprodukts von Vektoren
float vec_scalar_product(const std::vector<float>& v1, const std::vector<float>& v2) {
    float result = 0;
    if (v1.size() != v2.size()) {
        std::cout << "Fehler: Die Vektoren müssen die gleiche Länge haben." << std::endl;
        return result;
    }
    for (size_t i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}


// Funktion zum Berechnen des Winkels zwischen zwei Vektoren
float vec_angle(const std::vector<float>& v1, const std::vector<float>& v2) {
    float result = 0;
    if (v1.size() != v2.size()) {
        std::cout << "Fehler: Die Vektoren müssen die gleiche Länge haben." << std::endl;
        return result;
    }
    result = vec_scalar_product(v1, v2) / (vec_length(v1) * vec_length(v2));
    return acos(result) * 180 / M_PI;
}

// Funktion zum Berechnen des Kreuzprodukts von Vektoren
std::vector<float> vec_cross_product(const std::vector<float>& v1, const std::vector<float>& v2) {
    std::vector<float> result;
    if (v1.size() != v2.size()) {
        std::cout << "Fehler: Die Vektoren müssen die gleiche Länge haben." << std::endl;
        return result;
    }
    if (v1.size() != 3) {
        std::cout << "Fehler: Die Vektoren müssen dreidimensional sein." << std::endl;
        return result;
    }
    result.resize(3);
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return result;
}

//Funktion welche den gesamten Vektor mithilfe von Serial print ausgibt. Im Format(Vektorname_Index : Wert)
void vec_print(const std::vector<float>& v, const std::string& name) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << name << "_" << i << ": " << v[i] << std::endl;
    }
}
*/

#endif