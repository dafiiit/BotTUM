#include <iostream>
#include <vector>
#include <math.h>

#ifndef vektorrechnung_H
#define vektorrechnung_H

// Funktion zum Addieren von Vektoren
std::vector<double> vec_add(const std::vector<double>& v1, const std::vector<double>& v2) {
    std::vector<double> result;
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

// Funktion zum Multiplizieren von Vektoren
std::vector<double> vec_multiply(const std::vector<double>& v1, const std::vector<double>& v2) {
    std::vector<double> result;
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

// Funktion zum Skalieren von Vektoren
std::vector<double> vec_scale(const std::vector<double>& v, double factor) {
    std::vector<double> result;
    result.resize(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * factor;
    }
    return result;
}

// Funktion zum Berechnen der Länge eines Vektors
double vec_length(const std::vector<double>& v) {
    double result = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        result += v[i] * v[i];
    }
    return sqrt(result);
}

// Funktion zum Berechnen des Skalarprodukts von Vektoren
double vec_scalar_product(const std::vector<double>& v1, const std::vector<double>& v2) {
    double result = 0;
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
double vec_angle(const std::vector<double>& v1, const std::vector<double>& v2) {
    double result = 0;
    if (v1.size() != v2.size()) {
        std::cout << "Fehler: Die Vektoren müssen die gleiche Länge haben." << std::endl;
        return result;
    }
    result = scalarProduct(v1, v2) / (lengthVector(v1) * lengthVector(v2));
    return acos(result) * 180 / PI;
}

// Funktion zum Berechnen des Kreuzprodukts von Vektoren
std::vector<double> vec_cross_product(const std::vector<double>& v1, const std::vector<double>& v2) {
    std::vector<double> result;
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

#endif