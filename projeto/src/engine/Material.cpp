#include "engine/Material.hpp"

Material::Material() {
    // Valores padrão
    difuse[0] = 200; difuse[1] = 200; difuse[2] = 200; difuse[3] = 1.0f;
    ambient[0] = 50; ambient[1] = 50; ambient[2] = 50; ambient[3] = 1.0f;
    specular[0] = 0; specular[1] = 0; specular[2] = 0; specular[3] = 1.0f;
    emissive[0] = 0; emissive[1] = 0; emissive[2] = 0; emissive[3] = 1.0f;
    shininess = 0.0f;
}

void Material::aplicarMaterial() {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void Material::setDifuse(float r, float g, float b, float a) {
    difuse[0] = r; difuse[1] = g; difuse[2] = b; difuse[3] = a;
}

void Material::setAmbient(float r, float g, float b, float a) {
    ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;
}

void Material::setSpecular(float r, float g, float b, float a) {
    specular[0] = r; specular[1] = g; specular[2] = b; specular[3] = a;
}

void Material::setEmissive(float r, float g, float b, float a) {
    emissive[0] = r; emissive[1] = g; emissive[2] = b; emissive[3] = a;
}

void Material::setShininess(float s) {
    shininess = s;
}