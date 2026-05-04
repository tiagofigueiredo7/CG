#include "engine/structs/Material.hpp"

Material::Material() {
    // Valores padrão
    difuse[0] = 200.0f/255.0f; difuse[1] = 200.0f/255.0f; difuse[2] = 200.0f/255.0f; difuse[3] = 1.0f;
    ambient[0] = 50.0f/255.0f; ambient[1] = 50.0f/255.0f; ambient[2] = 50.0f/255.0f; ambient[3] = 1.0f;
    specular[0] = 0.0f; specular[1] = 0.0f; specular[2] = 0.0f; specular[3] = 1.0f;
    emissive[0] = 0.0f; emissive[1] = 0.0f; emissive[2] = 0.0f; emissive[3] = 1.0f;
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
    difuse[0] = r/255.0f; difuse[1] = g/255.0f; difuse[2] = b/255.0f; difuse[3] = a;
}

void Material::setAmbient(float r, float g, float b, float a) {
    ambient[0] = r/255.0f; ambient[1] = g/255.0f; ambient[2] = b/255.0f; ambient[3] = a;
}

void Material::setSpecular(float r, float g, float b, float a) {
    specular[0] = r/255.0f; specular[1] = g/255.0f; specular[2] = b/255.0f; specular[3] = a;
}

void Material::setEmissive(float r, float g, float b, float a) {
    emissive[0] = r/255.0f; emissive[1] = g/255.0f; emissive[2] = b/255.0f; emissive[3] = a;
}

void Material::setShininess(float s) {
    shininess = s;
}